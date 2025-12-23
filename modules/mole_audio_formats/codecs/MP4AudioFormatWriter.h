/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

namespace mole {

#if JUCE_WINDOWS || DOXYGEN

    namespace WindowsMediaFoundation {

        using namespace Windows;

        //=============================================================================
        /** Writes AAC audio to MP4 file format.
         *
         * Requirements for audio format writer options:
         * - sample rate: 44100 or 48000 Hz
         * - bits per sample: 16
         * - number of channels: 1, 2 or 6
         * - channel layout: mono, stereo or 5.1
         * - metadata values: empty (not supported)
         * - quality index: 0-7 (see MP4AudioFormat::getQualityOptions())
         */
        class MP4AudioFormatWriter : public juce::AudioFormatWriter
        {
            COMLibrary library;
            MFPlatform platform;

            IMFSinkWriter* sinkWriter = nullptr;

            DWORD streamIndex = 0; // Audio stream index.
            LONGLONG sampleTime = 0; // Sample presentation time in 100 ns time units.
            const int sampleSize = 0; // (16 bits per sample / 8 bits per byte) * number of channels
            const double sampleDuration = 0; // Duration of one sample in 100 ns time units.

            //=============================================================================
            public:

            MP4AudioFormatWriter() = delete;

            MP4AudioFormatWriter (juce::OutputStream* stream, const juce::AudioFormatWriterOptions& options)
                : juce::AudioFormatWriter (stream, "MP4 file",
                        options.getSampleRate(), options.getNumChannels(), options.getBitsPerSample()),
                  sampleSize ((16 / 8) * numChannels), sampleDuration (1e+9 * 1e-2 / sampleRate)
            {
                HRESULT hr = (stream != nullptr) ? S_OK : E_INVALIDARG;

                if (SUCCEEDED (hr)) hr = library.Initialize();
                if (SUCCEEDED (hr)) hr = platform.Initialize();

                // Create sink writer.
                if (SUCCEEDED (hr))
                {
                    IMFAttributes* attributes = nullptr;
                    IMFByteStream* byteStream = nullptr;

                    // Sink writer attributes.
                    hr = ::MFCreateAttributes (&attributes, 2);
                    if (SUCCEEDED (hr)) hr = attributes->SetUINT32 (MF_READWRITE_ENABLE_HARDWARE_TRANSFORMS, TRUE);
                    if (SUCCEEDED (hr)) hr = attributes->SetGUID (MF_TRANSCODE_CONTAINERTYPE, MFTranscodeContainerType_MPEG4);

                    if (SUCCEEDED (hr)) hr = ByteStreamFromOutputStream (&byteStream, stream, L"audio/mp4");
                    if (SUCCEEDED (hr)) hr = ::MFCreateSinkWriterFromURL (nullptr, byteStream, attributes, &sinkWriter);

                    SafeRelease (&byteStream);
                    SafeRelease (&attributes);
                }

                // Add stream and set output audio attributes.
                if (SUCCEEDED (hr))
                {
                    UINT32 bitrate = 12000; // 12000 bytes per second == 96 kilobits per second
                    const int quality = options.getQualityOptionIndex();

                    if (quality > 0 && quality < 8)
                    {
                        if (quality < 4)
                            bitrate += quality * 4000;
                        else
                            bitrate = (bitrate + (quality - 4) * 4000) * numChannels;
                    }

                    IMFMediaType* outputMediaType = nullptr;

                    hr = ::MFCreateMediaType (&outputMediaType);
                    if (SUCCEEDED (hr)) hr = outputMediaType->SetGUID (MF_MT_MAJOR_TYPE, MFMediaType_Audio);
                    if (SUCCEEDED (hr)) hr = outputMediaType->SetGUID (MF_MT_SUBTYPE, MFAudioFormat_AAC);
                    if (SUCCEEDED (hr)) hr = outputMediaType->SetUINT32 (MF_MT_AUDIO_BITS_PER_SAMPLE, 16);
                    if (SUCCEEDED (hr)) hr = outputMediaType->SetUINT32 (MF_MT_AUDIO_SAMPLES_PER_SECOND, (UINT32) sampleRate);
                    if (SUCCEEDED (hr)) hr = outputMediaType->SetUINT32 (MF_MT_AUDIO_NUM_CHANNELS, (UINT32) numChannels);
                    if (SUCCEEDED (hr)) hr = outputMediaType->SetUINT32 (MF_MT_AUDIO_AVG_BYTES_PER_SECOND, bitrate);

                    if (SUCCEEDED (hr)) hr = sinkWriter->AddStream (outputMediaType, &streamIndex);

                    SafeRelease (&outputMediaType);
                }

                // Set input audio attributes.
                if (SUCCEEDED (hr))
                {
                    IMFMediaType* inputMediaType = nullptr;

                    hr = ::MFCreateMediaType (&inputMediaType);
                    if (SUCCEEDED (hr)) hr = inputMediaType->SetGUID (MF_MT_MAJOR_TYPE, MFMediaType_Audio);
                    if (SUCCEEDED (hr)) hr = inputMediaType->SetGUID (MF_MT_SUBTYPE, MFAudioFormat_PCM);
                    if (SUCCEEDED (hr)) hr = inputMediaType->SetUINT32 (MF_MT_AUDIO_BITS_PER_SAMPLE, 16);
                    if (SUCCEEDED (hr)) hr = inputMediaType->SetUINT32 (MF_MT_AUDIO_SAMPLES_PER_SECOND, (UINT32) sampleRate);
                    if (SUCCEEDED (hr)) hr = inputMediaType->SetUINT32 (MF_MT_AUDIO_NUM_CHANNELS, (UINT32) numChannels);

                    if (SUCCEEDED (hr)) hr = sinkWriter->SetInputMediaType (streamIndex, inputMediaType, nullptr);

                    SafeRelease (&inputMediaType);
                }

                if (SUCCEEDED (hr)) hr = sinkWriter->BeginWriting();

                if (FAILED (hr))
                {
                    DBGAPI(hr);

                    sampleRate = 0;
                    numChannels = 0;
                    bitsPerSample = 0;

                    SafeRelease (&sinkWriter);
                }
            }

            ~MP4AudioFormatWriter() override
            {
                if (sinkWriter)
                {
                    HRESULT hr = sinkWriter->Finalize();
                    if (FAILED (hr)) DBGAPI(hr);
                }

                SafeRelease (&sinkWriter);
            }

            //=============================================================================
            bool flush() override
            {
                if (sinkWriter)
                    return SUCCEEDED (sinkWriter->Flush (streamIndex));

                return false;
            }

            //=============================================================================
            bool write (const int** samplesToWrite, int numSamples) override
            {
                IMFSample* sample = nullptr;
                IMFMediaBuffer* buffer = nullptr;

                const DWORD bufferSize = numSamples * sampleSize;

                HRESULT hr = ::MFCreateSample (&sample);
                if (SUCCEEDED (hr)) hr = ::MFCreateAlignedMemoryBuffer (bufferSize, MF_4_BYTE_ALIGNMENT, &buffer);
                if (SUCCEEDED (hr)) hr = buffer->SetCurrentLength (bufferSize);
                if (SUCCEEDED (hr)) hr = sample->AddBuffer (buffer);

                BYTE* data = nullptr;

                if (SUCCEEDED (hr)) hr = buffer->Lock (&data, nullptr, nullptr);

                if (SUCCEEDED (hr))
                {
                    juce::AudioFormatWriter::WriteHelper
                        <juce::AudioData::Int16, juce::AudioData::Int32, juce::AudioData::LittleEndian>
                        ::write (data, numChannels, samplesToWrite, numSamples);

                    hr = buffer->Unlock();
                }

                const LONGLONG duration = (LONGLONG) (sampleDuration * (double) numSamples);

                if (SUCCEEDED (hr)) hr = sample->SetSampleTime (sampleTime);
                if (SUCCEEDED (hr)) hr = sample->SetSampleDuration (duration);
                if (SUCCEEDED (hr)) hr = sinkWriter->WriteSample (streamIndex, sample);
                if (SUCCEEDED (hr)) sampleTime += duration;

                SafeRelease (&buffer);
                SafeRelease (&sample);

                if (FAILED (hr))
                {
                    DBGAPI(hr);
                    return false;
                }

                return true;
            }
        };
    } // namespace WindowsMediaFoundation

#endif // JUCE_WINDOWS
} // namespace mole
