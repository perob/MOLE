/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

namespace mole {

#if JUCE_WINDOWS || DOXYGEN

    namespace WindowsMediaFoundation {

        using namespace mole::Windows;

        //=====================================================================
        inline HRESULT SetPropertyBOOL (IPropertyStore* store, PROPERTYKEY key, BOOL value)
        {
            PROPVARIANT prop;
            ::InitPropVariantFromBoolean (value, &prop);
            HRESULT hr = store->SetValue (key, prop);
            ::PropVariantClear (&prop);
            return hr;
        }

        //=====================================================================
        inline HRESULT SetPropertyINT32 (IPropertyStore* store, PROPERTYKEY key, INT32 value)
        {
            PROPVARIANT prop;
            ::InitPropVariantFromInt32 (value, &prop);
            HRESULT hr = store->SetValue (key, prop);
            ::PropVariantClear (&prop);
            return hr;
        }

        //=====================================================================
        inline HRESULT SetPropertyUINT32 (IPropertyStore* store, PROPERTYKEY key, UINT32 value)
        {
            PROPVARIANT prop;
            ::InitPropVariantFromUInt32 (value, &prop);
            HRESULT hr = store->SetValue (key, prop);
            ::PropVariantClear (&prop);
            return hr;
        }

        //=====================================================================
        inline HRESULT CopyPropertyValue (IPropertyStore* src, IPropertyStore* dst, PROPERTYKEY key)
        {
            PROPVARIANT prop;
            PropVariantInit (&prop);
            HRESULT hr = src->GetValue (key, &prop);
            if (SUCCEEDED (hr)) hr = dst->SetValue (key, prop);
            ::PropVariantClear (&prop);
            return hr;
        }

        //=============================================================================
        /** Writes audio to audio file format.  */
        class ASFSink : public juce::AudioFormatWriter
        {
            COMLibrary library;
            MFPlatform platform;

            IMFTransform* transform = nullptr;
            IMFASFContentInfo* contentInfo = nullptr;
            IMFASFMultiplexer* mux = nullptr;
            IMFByteStream* byteStream = nullptr;

            LONGLONG sampleTime = 0; // Sample presentation time in 100 ns time units.
            const int sampleSize = 0; // (bits per sample / 8 bits per byte) * number of channels
            const double sampleDuration = 0; // Duration of one sample in 100 ns time units.

            const DWORD streamID = 0; // Audio stream ID.
            const WORD streamNumber = 1; // Audio stream number.

            //=============================================================================
            public:

            ASFSink() = delete;

            ASFSink (const MediaFormat& mediaFormat, juce::OutputStream* stream,
                    UINT32 rate, UINT32 chan, UINT32 bits, IMFTransform* mft) :
                juce::AudioFormatWriter (stream, mediaFormat.name, (double) rate, chan, bits),
                sampleSize ((bits / 8) * chan), sampleDuration (1e+7 / (double) rate), transform (mft)
            {
                HRESULT hr = (stream != nullptr) ? S_OK : E_INVALIDARG;

                if (SUCCEEDED (hr)) hr = library.Initialize();
                if (SUCCEEDED (hr)) hr = platform.Initialize();

                if (SUCCEEDED (hr)) hr = ByteStreamFromOutputStream (&byteStream, stream, mediaFormat.mimeType.toWideCharPointer());
                if (SUCCEEDED (hr)) hr = createContentInfo();
                if (SUCCEEDED (hr)) hr = createMultiplexer();
                if (SUCCEEDED (hr)) hr = writeHeader();

                if (FAILED (hr))
                {
                    DBGAPI(hr);
                    sampleRate = 0;
                    numChannels = 0;
                    bitsPerSample = 0;

                    SafeRelease (&byteStream);
                }
            }

            ~ASFSink() override
            {
                if (byteStream)
                {
                    HRESULT hr = flush() ? S_OK : E_FAIL;

                    if (SUCCEEDED (hr)) hr = mux->Flush();
                    if (SUCCEEDED (hr)) hr = writePackets();
                    if (SUCCEEDED (hr)) hr = mux->End (contentInfo);

                    if (SUCCEEDED (hr))
                    {
                        IPropertyStore* src = nullptr;
                        IPropertyStore* dst = nullptr;

                        if (SUCCEEDED (hr)) hr = transform->QueryInterface (IID_IPropertyStore, (void**) &src);
                        if (SUCCEEDED (hr)) hr = contentInfo->GetEncodingConfigurationPropertyStore (0, &dst);
                        if (SUCCEEDED (hr)) hr = CopyPropertyValue (src, dst, MFPKEY_STAT_BAVG);
                        if (SUCCEEDED (hr)) hr = CopyPropertyValue (src, dst, MFPKEY_STAT_RAVG);
                        if (SUCCEEDED (hr)) hr = CopyPropertyValue (src, dst, MFPKEY_STAT_BMAX);
                        if (SUCCEEDED (hr)) hr = CopyPropertyValue (src, dst, MFPKEY_STAT_RMAX);
                        if (SUCCEEDED (hr)) hr = CopyPropertyValue (src, dst, MFPKEY_WMAENC_AVGBYTESPERSEC);
                        if (SUCCEEDED (hr)) hr = writeHeader();

                        SafeRelease (&src);
                        SafeRelease (&dst);
                    }

                    if (FAILED (hr)) DBGAPI(hr);
                }

                SafeRelease (&byteStream);
                SafeRelease (&mux);
                SafeRelease (&contentInfo);
                SafeRelease (&transform);
            }

            //=============================================================================
            bool flush() override
            {
                HRESULT hr = transform->ProcessMessage (MFT_MESSAGE_COMMAND_DRAIN, streamID);
                while (SUCCEEDED (hr)) hr = processOutput();
                return hr == MF_E_TRANSFORM_NEED_MORE_INPUT;
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
                if (SUCCEEDED (hr)) sampleTime += duration;

                if (SUCCEEDED (hr)) hr = processInput (sample);
                if (SUCCEEDED (hr)) hr = processOutput();

                if (hr == MF_E_TRANSFORM_NEED_MORE_INPUT) hr = S_OK;

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

            //=============================================================================
            HRESULT createContentInfo()
            {
                IMFASFProfile* profile = nullptr;
                IMFMediaType* mediaType = nullptr;
                IMFASFStreamConfig* stream = nullptr;

                HRESULT hr = ::MFCreateASFContentInfo (&contentInfo);
                if (SUCCEEDED (hr)) hr = ::MFCreateASFProfile (&profile);

                if (SUCCEEDED (hr)) hr = transform->GetOutputCurrentType (streamID, &mediaType);
                if (SUCCEEDED (hr)) hr = profile->CreateStream (mediaType, &stream);
                if (SUCCEEDED (hr)) hr = stream->SetStreamNumber (streamNumber);
                if (SUCCEEDED (hr)) hr = setLeakyBucket (stream, mediaType);
                if (SUCCEEDED (hr)) hr = profile->SetStream (stream);
                if (SUCCEEDED (hr)) hr = setProperties();
                if (SUCCEEDED (hr)) hr = contentInfo->SetProfile (profile);

                SafeRelease (&profile);
                SafeRelease (&stream);
                SafeRelease (&mediaType);

                return hr;
            }

            //=============================================================================
            HRESULT setLeakyBucket (IMFASFStreamConfig* stream, IMFMediaType* mediaType)
            {
                struct LeakyBucket
                {
                    DWORD bitrate = 0;
                    DWORD bufferSize = 0;
                    DWORD initialBufferFullness = 0;
                } bucket;

                IWMCodecLeakyBucket* leakyBucket = nullptr;

                HRESULT hr = transform->QueryInterface (IID_IWMCodecLeakyBucket, (void**) &leakyBucket);

                if (SUCCEEDED (hr))
                {
                    ULONG bits = 0;
                    leakyBucket->GetBufferSizeBits (&bits);
                    bucket.bitrate = 8 * ::MFGetAttributeUINT32 (mediaType, MF_MT_AUDIO_AVG_BYTES_PER_SECOND, 0);
                    bucket.bufferSize = bits / (bucket.bitrate / 1000);

                    hr = stream->SetBlob (MF_ASFSTREAMCONFIG_LEAKYBUCKET1, (UINT8*) &bucket, sizeof (LeakyBucket));
                }

                SafeRelease (&leakyBucket);

                return hr;
            }

            //=============================================================================
            HRESULT setProperties()
            {
                IPropertyStore* src = nullptr;
                IPropertyStore* dst = nullptr;

                HRESULT hr = transform->QueryInterface (IID_IPropertyStore, (void**) &src);
                if (SUCCEEDED (hr)) hr = contentInfo->GetEncodingConfigurationPropertyStore (streamNumber, &dst);

                if (SUCCEEDED (hr))
                {
                    CopyPropertyValue (src, dst, MFPKEY_VBRENABLED);
                    CopyPropertyValue (src, dst, MFPKEY_PASSESUSED);
                    CopyPropertyValue (src, dst, MFPKEY_DESIRED_VBRQUALITY);
                }

                SafeRelease (&src);
                SafeRelease (&dst);

                IPropertyStore* store = nullptr;

                if (SUCCEEDED (hr)) hr = contentInfo->GetEncodingConfigurationPropertyStore (0, &store);
                if (SUCCEEDED (hr)) hr = SetPropertyBOOL (store, MFPKEY_ASFMEDIASINK_AUTOADJUST_BITRATE, TRUE);

                SafeRelease (&store);

                return hr;
            }

            //=============================================================================
            HRESULT createMultiplexer()
            {
                HRESULT hr = ::MFCreateASFMultiplexer (&mux);
                if (SUCCEEDED (hr)) hr = mux->SetFlags (MFASF_MULTIPLEXER_AUTOADJUST_BITRATE);
                if (SUCCEEDED (hr)) hr = mux->Initialize (contentInfo);
                return hr;
            }

            //=============================================================================
            HRESULT writeToStream (IMFMediaBuffer* buffer)
            {
                DWORD dataSize = 0;
                DWORD count = 0;
                BYTE* data = nullptr;

                HRESULT hr = buffer->Lock (&data, nullptr, &dataSize);
                if (SUCCEEDED (hr)) hr = byteStream->Write (data, dataSize, &count);
                if (data) buffer->Unlock();

                jassert (dataSize == count);

                return hr;
            }

            //=============================================================================
            HRESULT writeHeader()
            {
                DWORD size = 0;
                IMFMediaBuffer* header = nullptr;

                HRESULT hr = contentInfo->GenerateHeader (nullptr, &size);
                if (SUCCEEDED (hr)) hr = ::MFCreateMemoryBuffer (size, &header);
                if (SUCCEEDED (hr)) hr = contentInfo->GenerateHeader (header, &size);
                if (SUCCEEDED (hr)) hr = byteStream->SetCurrentPosition (0);
                if (SUCCEEDED (hr)) hr = writeToStream (header);

                SafeRelease (&header);

                return hr;
            }

            //=============================================================================
            HRESULT processInput (IMFSample* sample)
            {
                return transform->ProcessInput (streamID, sample, 0);
            }

            //=============================================================================
            HRESULT processOutput()
            {
                IMFSample* sample = nullptr;
                IMFMediaBuffer* buffer = nullptr;

                DWORD status = 0;

                MFT_OUTPUT_STREAM_INFO streamInfo = {0};
                MFT_OUTPUT_DATA_BUFFER outputData = {0};

                HRESULT hr = transform->GetOutputStreamInfo (streamID, &streamInfo);
                if (SUCCEEDED (hr)) hr = ::MFCreateMemoryBuffer (streamInfo.cbSize, &buffer);
                if (SUCCEEDED (hr)) hr = ::MFCreateSample (&sample);
                if (SUCCEEDED (hr)) hr = sample->AddBuffer (buffer);

                if (SUCCEEDED (hr))
                {
                    outputData.pSample = sample;
                    outputData.dwStreamID = streamID;
                }

                // MF_E_TRANSFORM_NEED_MORE_INPUT
                // The transform cannot produce output data until it receives more input data
                if (SUCCEEDED (hr)) hr = transform->ProcessOutput (0, 1, &outputData, &status);

                if (SUCCEEDED (hr))
                {
                    hr = mux->ProcessSample (streamNumber, sample, 0);
                    if (SUCCEEDED (hr)) hr = writePackets();
                }

                SafeRelease (&buffer);
                SafeRelease (&sample);

                return hr;
            }

            //=============================================================================
            HRESULT writePackets()
            {
                HRESULT hr = S_OK;
                DWORD status = ASF_STATUSFLAGS_INCOMPLETE;

                while (status & ASF_STATUSFLAGS_INCOMPLETE)
                {
                    IMFMediaBuffer *packet = nullptr;
                    IMFSample *outputSample = nullptr;

                    hr = mux->GetNextPacket (&status, &outputSample);

                    if (outputSample)
                    {
                        if (SUCCEEDED (hr)) hr = outputSample->ConvertToContiguousBuffer (&packet);
                        if (SUCCEEDED (hr)) hr = writeToStream (packet);
                    }

                    SafeRelease (&packet);
                    SafeRelease (&outputSample);

                    if (FAILED (hr))
                    {
                        DBGAPI(hr);
                        break;
                    }
                }

                return hr;
            }

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ASFSink)
        };

        //=============================================================================
    }
#endif
}
