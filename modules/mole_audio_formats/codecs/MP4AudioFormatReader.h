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
        /** Reads AAC audio from any file format supported by Media Foundation.
         *
         * Metadata values are not supported (see readMetadataFromFile()).
         */
        class MP4AudioFormatReader : public juce::AudioFormatReader
        {
            COMLibrary library;
            MFPlatform platform;

            IMFSourceReader* sourceReader = nullptr;
            IMFSample* sample = nullptr;
            IMFMediaBuffer* mediaBuffer = nullptr;

            int bufferOffset = 0;
            int bufferNumSamples = 0;
            const int bytesPerSample = 4; // 32 bits per sample (int32)
            const DWORD firstAudioStream = (DWORD) MF_SOURCE_READER_FIRST_AUDIO_STREAM;

            juce::int64 currentSampleInFile = 0;

            DWORD readResult = 0;
            const DWORD readError = MF_SOURCE_READERF_ERROR // An error occured. Do not make any further calls to sourceReader.
                | MF_SOURCE_READERF_ENDOFSTREAM // The source reader reached end of stream.
                | MF_SOURCE_READERF_NEWSTREAM // One or more new streams were created.
                | MF_SOURCE_READERF_NATIVEMEDIATYPECHANGED // The native format has changed for one or more streams.
                | MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED // The current media type has changed for one or more streams.
                | MF_SOURCE_READERF_STREAMTICK // There is a gap in the stream.
                | MF_SOURCE_READERF_ALLEFFECTSREMOVED; // All transforms inserted by the application have been removed for a particular stream.

            //=============================================================================
            public:

            MP4AudioFormatReader() = delete;

            MP4AudioFormatReader (juce::InputStream* stream, bool usingNetwork)
                : AudioFormatReader (stream, "MP4 file")
            {
                HRESULT hr = (stream != nullptr) ? S_OK : E_INVALIDARG;

                if (SUCCEEDED (hr)) hr = library.Initialize();
                if (SUCCEEDED (hr)) hr = platform.Initialize();

                // Create source reader.
                if (SUCCEEDED (hr))
                {
                    IMFAttributes* attributes = nullptr;
                    IMFByteStream* byteStream = nullptr;

                    hr = ::MFCreateAttributes (&attributes, 1);

                    // Enables the source reader to use hardware-based Media Foundation transforms (MFTs).
                    if (SUCCEEDED (hr)) hr = attributes->SetUINT32 (MF_READWRITE_ENABLE_HARDWARE_TRANSFORMS, TRUE);

                    // Open all media formats supported by Media Foundation.
                    if (SUCCEEDED (hr)) hr = ByteStreamFromInputStream (&byteStream, stream, nullptr, nullptr, usingNetwork);
                    if (SUCCEEDED (hr)) hr = ::MFCreateSourceReaderFromByteStream (byteStream, attributes, &sourceReader);

                    SafeRelease (&byteStream);
                    SafeRelease (&attributes);
                }

                // Select audio stream.
                if (SUCCEEDED (hr)) hr = sourceReader->SetStreamSelection ((DWORD) MF_SOURCE_READER_ALL_STREAMS, false);
                if (SUCCEEDED (hr)) hr = sourceReader->SetStreamSelection (firstAudioStream, true);

                // Set decoder output (pcm, 32 bits per sample)
                if (SUCCEEDED (hr))
                {
                    IMFMediaType* pcmType = nullptr;

                    hr = ::MFCreateMediaType (&pcmType);

                    if (SUCCEEDED (hr)) hr = pcmType->SetGUID (MF_MT_MAJOR_TYPE, MFMediaType_Audio);
                    if (SUCCEEDED (hr)) hr = pcmType->SetGUID (MF_MT_SUBTYPE, MFAudioFormat_PCM);
                    if (SUCCEEDED (hr)) hr = pcmType->SetUINT32 (MF_MT_AUDIO_BITS_PER_SAMPLE, 32);
                    if (SUCCEEDED (hr)) hr = sourceReader->SetCurrentMediaType (firstAudioStream, nullptr, pcmType);

                    SafeRelease (&pcmType);
                }

                // Get audio attributes.
                if (SUCCEEDED (hr))
                {
                    IMFMediaType* mediaType = nullptr;
                    IMFAttributes* attributes = nullptr;

                    hr = sourceReader->GetCurrentMediaType (firstAudioStream, &mediaType);

                    if (SUCCEEDED (hr)) hr = mediaType->QueryInterface (IID_IMFAttributes, (void**) &attributes);

                    // double sampleRate
                    if (SUCCEEDED (hr))
                    {
                        UINT32 value;
                        hr = attributes->GetUINT32 (MF_MT_AUDIO_SAMPLES_PER_SECOND, &value);

                        if (SUCCEEDED (hr)) sampleRate = (double) value;
                    }

                    // unsigned int bitsPerSample
                    if (SUCCEEDED (hr))
                    {
                        UINT32 value;
                        hr = attributes->GetUINT32 (MF_MT_AUDIO_BITS_PER_SAMPLE, &value);

                        if (SUCCEEDED (hr)) bitsPerSample = (unsigned int) value;

                        jassert (bitsPerSample == 32);
                    }

                    // int64 lengthInSamples
                    if (SUCCEEDED (hr))
                    {
                        UINT64 value = 0;
                        PROPVARIANT prop;
                        PropVariantInit (&prop); // Macro

                        hr = sourceReader->GetPresentationAttribute ((DWORD) MF_SOURCE_READER_MEDIASOURCE, MF_PD_DURATION, &prop);

                        if (SUCCEEDED (hr))
                        {
                            // Duration is in 100 ns time units.
                            hr = ::PropVariantToUInt64 (prop, &value);
                        }
                        ::PropVariantClear (&prop);

                        // length in seconds * sample rate
                        if (SUCCEEDED (hr)) lengthInSamples = (juce::int64) ((double) value * 1e-7 * sampleRate);
                    }

                    // unsigned int numChannels
                    if (SUCCEEDED (hr))
                    {
                        UINT32 value;
                        hr = attributes->GetUINT32 (MF_MT_AUDIO_NUM_CHANNELS, &value);

                        if (SUCCEEDED (hr)) numChannels = (unsigned int) value;
                    }

                    // bool usesFloatingPointData
                    if (SUCCEEDED (hr))
                    {
                        usesFloatingPointData = false;
                    }

                    // StringPairArray metadataValues
                    if (SUCCEEDED (hr))
                    {
                        // Not supported
                    }

                    SafeRelease (&mediaType);
                    SafeRelease (&attributes);
                }

                if (FAILED (hr))
                {
                    DBGAPI(hr);

                    readResult = MF_SOURCE_READERF_ERROR;

                    sampleRate = 0;
                    bitsPerSample = 0;
                    lengthInSamples = 0;
                    numChannels = 0;
                    metadataValues.clear();

                    SafeRelease (&mediaBuffer);
                    SafeRelease (&sample);
                    SafeRelease (&sourceReader);
                }
            }

            ~MP4AudioFormatReader() override
            {
                SafeRelease (&mediaBuffer);
                SafeRelease (&sample);
                SafeRelease (&sourceReader);
            }

            //=============================================================================
            /** Checks for mono, stereo and 5.1 channel layouts.  */
            juce::AudioChannelSet getChannelLayout() override
            {
                if (numChannels == 1) return juce::AudioChannelSet::mono();
                if (numChannels == 2) return juce::AudioChannelSet::stereo();
                if (numChannels == 6) return juce::AudioChannelSet::create5point1();

                return juce::AudioChannelSet();
            }

            //=============================================================================
            bool readSamples (int* const* destChannels, int numDestChannels, int startOffsetInDestBuffer, juce::int64 startSampleInFile, int numSamples) override
            {
                // All errors except end of stream.
                if ((readResult & (~MF_SOURCE_READERF_ENDOFSTREAM)) & readError)
                {
                    // Clear all samples.
                    juce::AudioFormatReader::clearSamplesBeyondAvailableLength (
                            destChannels, numDestChannels, startOffsetInDestBuffer, 0, numSamples, 0);

                    return false;
                }

                // Clear samples beyond available length.
                juce::AudioFormatReader::clearSamplesBeyondAvailableLength (
                        destChannels, numDestChannels, startOffsetInDestBuffer,
                        startSampleInFile, numSamples, lengthInSamples);

                if (numSamples <= 0)
                {
                    return true;
                }

                HRESULT hr = S_OK;

                if (currentSampleInFile != startSampleInFile)
                {
                    // Position in 100 ns time units.
                    juce::int64 newPosition = (juce::int64) ((double) startSampleInFile * 1e+7 / sampleRate);

                    PROPVARIANT prop;
                    ::InitPropVariantFromInt64 (newPosition, &prop);

                    hr = sourceReader->SetCurrentPosition (GUID_NULL, prop);
                    ::PropVariantClear (&prop);

                    bufferOffset = 0;
                    bufferNumSamples = 0;

                    if (SUCCEEDED (hr)) currentSampleInFile = startSampleInFile;
                }
                else if (bufferNumSamples > 0)
                {
                    const int readNumSamples = juce::jmin (numSamples, bufferNumSamples);

                    BYTE* data = nullptr;
                    DWORD dataSize = 0;

                    hr = mediaBuffer->Lock (&data, nullptr, &dataSize);

                    if (SUCCEEDED (hr))
                    {
                        juce::AudioFormatReader::ReadHelper
                            <juce::AudioData::Int32, juce::AudioData::Int32, juce::AudioData::LittleEndian>
                            ::read (destChannels, startOffsetInDestBuffer, numDestChannels,
                                    data + bufferOffset, numChannels, readNumSamples);

                        hr = mediaBuffer->Unlock();

                        if (SUCCEEDED (hr))
                        {
                            numSamples -= readNumSamples;
                            bufferNumSamples -= readNumSamples;
                            bufferOffset += readNumSamples * numChannels * bytesPerSample; // offset in bytes
                            startOffsetInDestBuffer += readNumSamples;
                            currentSampleInFile += readNumSamples;
                        }
                    }
                }

                if (FAILED (hr))
                {
                    DBGAPI(hr);

                    // Clear all samples.
                    juce::AudioFormatReader::clearSamplesBeyondAvailableLength (
                            destChannels, numDestChannels, startOffsetInDestBuffer, 0, numSamples, 0);

                    readResult = MF_SOURCE_READERF_ERROR;
                    return false;
                }

                while (numSamples > 0)
                {
                    SafeRelease (&sample);
                    SafeRelease (&mediaBuffer);

                    hr = sourceReader->ReadSample (firstAudioStream, 0, nullptr, &readResult, nullptr, &sample);

                    if (FAILED (hr))
                        break;

                    // Returns true on first error.
                    if (readResult & readError)
                        break;

                    if (sample == nullptr)
                        continue;

                    hr = sample->ConvertToContiguousBuffer (&mediaBuffer);

                    BYTE* data = nullptr;
                    DWORD dataSize = 0;

                    if (SUCCEEDED (hr)) hr = mediaBuffer->Lock (&data, nullptr, &dataSize);

                    if (SUCCEEDED (hr))
                    {
                        bufferOffset = 0;
                        bufferNumSamples = dataSize / (numChannels * bytesPerSample);

                        const int readNumSamples = juce::jmin (numSamples, bufferNumSamples);

                        juce::AudioFormatReader::ReadHelper
                            <juce::AudioData::Int32, juce::AudioData::Int32, juce::AudioData::LittleEndian>
                            ::read (destChannels, startOffsetInDestBuffer, numDestChannels,
                                    data, numChannels, readNumSamples);

                        hr = mediaBuffer->Unlock();

                        if (SUCCEEDED (hr))
                        {
                            numSamples -= readNumSamples;
                            bufferNumSamples -= readNumSamples;
                            bufferOffset += readNumSamples * numChannels * bytesPerSample; // offset in bytes
                            startOffsetInDestBuffer += readNumSamples;
                            currentSampleInFile += readNumSamples;
                        }
                    }
                }

                // Clear samples beyond available length.
                juce::AudioFormatReader::clearSamplesBeyondAvailableLength (
                        destChannels, numDestChannels, startOffsetInDestBuffer,
                        startSampleInFile, numSamples, currentSampleInFile);

                if (FAILED (hr))
                {
                    DBGAPI(hr);
                    readResult = MF_SOURCE_READERF_ERROR;
                    return false;
                }

                return true;
            }
        };
    } // namespace WindowsMediaFoundation

#endif // JUCE_WINDOWS
} // namespace mole
