/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

namespace mole {

#if JUCE_WINDOWS || DOXYGEN

    namespace WindowsMediaFoundation {

        using namespace mole::Windows;

        //=============================================================================
        /** Writes audio to audio file format.  */
        class Encoder : public juce::AudioFormatWriter
        {
            COMLibrary library;
            MFPlatform platform;

            IMFSinkWriter* sinkWriter = nullptr;

            DWORD streamIndex = 0; // Audio stream index.
            LONGLONG sampleTime = 0; // Sample presentation time in 100 ns time units.
            const int sampleSize = 0; // (bits per sample / 8 bits per byte) * number of channels
            const double sampleDuration = 0; // Duration of one sample in 100 ns time units.

            //=============================================================================
            public:

            Encoder() = delete;

            Encoder (const MediaFormat& mediaFormat, juce::OutputStream* stream,
                    IMFMediaType* inputMediaType, IMFMediaType* outputMediaType,
                    UINT32 rate, UINT32 chan, UINT32 bits, [[maybe_unused]] UINT32 wmaOption = 0) :
                juce::AudioFormatWriter (stream, mediaFormat.name, (double) rate, chan, bits),
                sampleSize ((bits / 8) * chan), sampleDuration (1e+7 / (double) rate)
            {
                HRESULT hr = (stream != nullptr) ? S_OK : E_INVALIDARG;

                if (SUCCEEDED (hr)) hr = library.Initialize();
                if (SUCCEEDED (hr)) hr = platform.Initialize();

                // Create sink writer.
                if (SUCCEEDED (hr))
                {
                    IMFByteStream* byteStream = nullptr;
                    IMFAttributes* attributes = nullptr;

                    hr = ::MFCreateAttributes (&attributes, 1);
                    if (SUCCEEDED (hr)) hr = attributes->SetGUID (MF_TRANSCODE_CONTAINERTYPE, mediaFormat.container);
                    if (SUCCEEDED (hr)) hr = ByteStreamFromOutputStream (&byteStream, stream, mediaFormat.mimeType.toWideCharPointer());
                    if (SUCCEEDED (hr)) hr = ::MFCreateSinkWriterFromURL (nullptr, byteStream, attributes, &sinkWriter);

                    SafeRelease (&byteStream);
                    SafeRelease (&attributes);
                }

                if (SUCCEEDED (hr)) hr = sinkWriter->AddStream (outputMediaType, &streamIndex);
                if (SUCCEEDED (hr)) hr = sinkWriter->SetInputMediaType (streamIndex, inputMediaType, nullptr);
                if (SUCCEEDED (hr) && mediaFormat.isMP1()) hr = MPEGCodec::setMPEGLayer1 (sinkWriter, streamIndex);
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

            ~Encoder() override
            {
                if (sinkWriter)
                {
                    HRESULT hr = sinkWriter->Finalize();
                    if (FAILED (hr)) DBGAPI(hr);
                    sinkWriter->Release();
                }
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
                DWORD dataSize = 0;

                if (SUCCEEDED (hr)) hr = buffer->Lock (&data, nullptr, &dataSize);

                if (SUCCEEDED (hr))
                {
                    switch (getBitsPerSample())
                    {
                        case 8: juce::AudioFormatWriter::WriteHelper<juce::AudioData::Int8, juce::AudioData::Int32, juce::AudioData::LittleEndian>
                                ::write (data, numChannels, samplesToWrite, numSamples);
                                break;
                        case 16: juce::AudioFormatWriter::WriteHelper<juce::AudioData::Int16, juce::AudioData::Int32, juce::AudioData::LittleEndian>
                                 ::write (data, numChannels, samplesToWrite, numSamples);
                                 break;
                        case 24: juce::AudioFormatWriter::WriteHelper<juce::AudioData::Int24, juce::AudioData::Int32, juce::AudioData::LittleEndian>
                                 ::write (data, numChannels, samplesToWrite, numSamples);
                                 break;
                        case 32: juce::AudioFormatWriter::WriteHelper<juce::AudioData::Int32, juce::AudioData::Int32, juce::AudioData::LittleEndian>
                                 ::write (data, numChannels, samplesToWrite, numSamples);
                                 break;
                        default:
                                 memset (data, 0, dataSize);
                                 jassertfalse;
                                 break;
                    }

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

            private:

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Encoder)
        };

        //=============================================================================
    }
#endif
}
