/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

namespace mole {

#if JUCE_WINDOWS

    namespace WindowsMediaFoundation {

        //=============================================================================
        const MediaFormat MediaFormat::AAC (FormatTag::AAC, MFAudioFormat_AAC, MFTranscodeContainerType_MPEG4, "Advanced Audio Coding", "audio/mp4", {".mp4", ".aac", ".3gp"});
        const MediaFormat MediaFormat::AC3 (FormatTag::AC3, MFAudioFormat_Dolby_AC3, MFTranscodeContainerType_AC3, "Dolby AC-3", "audio/ac3", {".ac3"});
        const MediaFormat MediaFormat::FLAC (FormatTag::FLAC, MFAudioFormat_FLAC, MFTranscodeContainerType_MPEG4, "Free Lossless Audio Codec", "audio/flac", {".flac"});
        const MediaFormat MediaFormat::Float (FormatTag::Float, MFAudioFormat_Float, MFTranscodeContainerType_WAVE, "Uncompressed IEEE float audio", "audio/wav", {".wav", ".aiff"});
        const MediaFormat MediaFormat::MP1 (FormatTag::MP1, MFAudioFormat_MPEG, MFTranscodeContainerType_MPEG2, "MPEG Layer 1", "audio/mpeg", {".mp1", ".mpa", ".mpg", ".mpeg"});
        const MediaFormat MediaFormat::MP2 (FormatTag::MP2, MFAudioFormat_MPEG, MFTranscodeContainerType_MPEG2, "MPEG Layer 2", "audio/mpeg", {".mp2", ".mpa", ".mpg", ".mpeg"});
        const MediaFormat MediaFormat::MP3 (FormatTag::MP3, MFAudioFormat_MP3, MFTranscodeContainerType_MP3, "MPEG Layer 3", "audio/mpeg", {".mp3"});
        const MediaFormat MediaFormat::PCM (FormatTag::PCM, MFAudioFormat_PCM, MFTranscodeContainerType_WAVE, "Uncompressed PCM audio", "audio/wav", {".wav", ".aiff"});
        const MediaFormat MediaFormat::WMA8 (FormatTag::WMA8, MFAudioFormat_WMAudioV8, MFTranscodeContainerType_ASF, "Windows Media Audio 8", "audio/x-ms-wma", {".wma", ".wmv"});
        const MediaFormat MediaFormat::WMA9 (FormatTag::WMA9, MFAudioFormat_WMAudioV9, MFTranscodeContainerType_ASF, "Windows Media Audio 9", "audio/x-ms-wma", {".wma", ".wmv"});
        const MediaFormat MediaFormat::WMALossless (FormatTag::WMALossless, MFAudioFormat_WMAudio_Lossless, MFTranscodeContainerType_ASF, "Windows Media Audio Lossless", "audio/x-ms-wma", {".wma", ".wmv"});
        const MediaFormat MediaFormat::WMAVoice (FormatTag::WMAVoice, MFAudioFormat_MSP1, MFTranscodeContainerType_ASF, "Windows Media Audio Voice", "audio/x-ms-wma", {".wma", ".wmv"});

        //=============================================================================
        enum ChannelTag
        {
            Mono = (FormatTag::AAC | FormatTag::AC3 | FormatTag::FLAC | FormatTag::Float | FormatTag::MP1 | FormatTag::MP2 | FormatTag::MP3 | FormatTag::PCM | FormatTag::WMA8 | FormatTag::WMA9 | FormatTag::WMALossless | FormatTag::WMAVoice), ///< Mono
            Stereo = (FormatTag::AAC | FormatTag::AC3 | FormatTag::FLAC | FormatTag::Float | FormatTag::MP1 | FormatTag::MP2 | FormatTag::MP3 | FormatTag::PCM | FormatTag::WMA8 | FormatTag::WMA9 | FormatTag::WMALossless), ///< Mono and stereo
            FivePointOne = (FormatTag::AAC | FormatTag::FLAC | FormatTag::Float | FormatTag::PCM | FormatTag::WMA9 | FormatTag::WMALossless), ///< Mono, stereo and 5.1
            SevenPointOne = (FormatTag::AAC | FormatTag::FLAC | FormatTag::Float | FormatTag::PCM | FormatTag::WMA9), ///< Mono, stereo, 5.1 and 7.1
            All = (FormatTag::Float | FormatTag::FLAC | FormatTag::PCM) ///< From 1 to 8 channels
        };

        //=============================================================================
        bool isChannelTagSupported (FormatTag formatTag, const juce::AudioChannelSet& channelSet)
        {
            if (channelSet.size() > 0)
            {
                if (channelSet == juce::AudioChannelSet::mono()) return formatTag & ChannelTag::Mono;
                if (channelSet == juce::AudioChannelSet::stereo()) return formatTag & ChannelTag::Stereo;
                if (channelSet == juce::AudioChannelSet::create5point1()) return formatTag & ChannelTag::FivePointOne;
                if (channelSet == juce::AudioChannelSet::create7point1()) return formatTag & ChannelTag::SevenPointOne;
                if (channelSet.size() <= 8) return formatTag & ChannelTag::All;
            }

            return false;
        }

        //=============================================================================
        HRESULT MPEGCodec::setMPEGLayer1 (IMFSinkWriter* sinkWriter, DWORD streamIndex)
        {
            ICodecAPI* codec = nullptr;
            IMFTransform* transform = nullptr;

            HRESULT hr = sinkWriter->GetServiceForStream (streamIndex, GUID_NULL, IID_IMFTransform, (void**) &transform);
            if (SUCCEEDED (hr)) hr = transform->QueryInterface (IID_ICodecAPI, (void**) &codec);

            if (SUCCEEDED (hr))
            {
                VARIANT var;
                ::InitVariantFromUInt32 (eAVEncMPALayer_1, &var);
                hr = codec->SetValue (&CODECAPI_AVEncMPALayer, &var);
                ::VariantClear (&var);
            }

            SafeRelease (&codec);
            SafeRelease (&transform);

            return hr;
        }

        //=============================================================================
        Codec::Codec()
        {
            HRESULT hr = library.Initialize();
            if (SUCCEEDED (hr)) hr = platform.Initialize();
            jassert (SUCCEEDED (hr));
        }

        Codec::~Codec()
        {
            SafeRelease (&outputMediaType);
            SafeRelease (&inputMediaType);
            SafeRelease (&transform);
        }

        //=============================================================================
        juce::AudioFormatReader* Codec::createDecoderFor (const MediaFormat& mediaFormat, juce::InputStream* stream)
        {
            return new Decoder (mediaFormat, stream);
        }

        //=============================================================================
        juce::AudioFormatWriter* Codec::createEncoderFor (const MediaFormat& mediaFormat,
                std::unique_ptr<juce::OutputStream>& stream,
                UINT32 kbps, UINT32 chan, UINT32 rate, UINT32 bits,
                UINT32 vbrq, UINT32 aacProfile, UINT32 aacPayload)
        {
            format = mediaFormat;

            HRESULT hr = configureEncoder (kbps, chan, rate, bits, vbrq, aacProfile, aacPayload);

            if (SUCCEEDED (hr))
            {
                IMFMediaType* input = getInputMediaType();
                IMFMediaType* output = getOutputMediaType();

                juce::AudioFormatWriter* encoder = new Encoder (
                        format, std::exchange (stream, {}).release(), input, output, rate, chan, bits);

                SafeRelease (&input);
                SafeRelease (&output);

                return encoder;
            }

            return nullptr;
        }

        //=============================================================================
        HRESULT Codec::configureEncoder (UINT32 kbps, UINT32 chan, UINT32 rate, UINT32 bits,
                UINT32 vbrq, UINT32 aacProfile , UINT32 aacPayload)
        {
            HRESULT hr = initEncoder();

            if (SUCCEEDED (hr) && format.isWMA()) hr = setWMAProperties (vbrq);

            if (SUCCEEDED (hr)) hr = findOutputMediaType (kbps, chan, rate, bits, aacProfile, aacPayload);
            if (SUCCEEDED (hr)) hr = findInputMediaType (chan, rate, bits);

            return hr;
        }

        //=============================================================================
        HRESULT Codec::initEncoder()
        {
            SafeRelease (&inputMediaType);
            SafeRelease (&outputMediaType);

            HRESULT hr = ::MFCreateMediaType (&inputMediaType);
            if (SUCCEEDED (hr)) hr = ::MFCreateMediaType (&outputMediaType);

            //=============================================================================
            // Activate IMFTransform.
            if (SUCCEEDED (hr))
            {
                UINT32 count = 0;
                IMFActivate** activate = nullptr;

                MFT_REGISTER_TYPE_INFO inputInfo = { MFMediaType_Audio, MediaFormat::PCM.guid };
                MFT_REGISTER_TYPE_INFO outputInfo = { MFMediaType_Audio, format.guid };

                UINT32 flags = MFT_ENUM_FLAG_SYNCMFT | MFT_ENUM_FLAG_SORTANDFILTER;

                hr = ::MFTEnumEx (MFT_CATEGORY_AUDIO_ENCODER, flags, &inputInfo, &outputInfo, &activate, &count);

                jassert (count == 1);

                if (SUCCEEDED (hr) && count == 0) hr = MF_E_TOPO_CODEC_NOT_FOUND;
                if (SUCCEEDED (hr)) hr = activate[0]->ActivateObject (IID_IMFTransform, (void**) &transform);

                for (UINT32 i = 0; i < count; ++i)
                    activate[i]->Release();

                ::CoTaskMemFree (activate);
            }

            //=============================================================================
            // Get stream count and ID.
            if (SUCCEEDED (hr))
            {
                DWORD inCount = 0, outCount = 0;

                const int inSize = 1, outSize = 1;
                DWORD inID[inSize] = { 0 }, outID[outSize] = { 0 };

                hr = transform->GetStreamCount (&inCount, &outCount);
                if (SUCCEEDED (hr)) hr = transform->GetStreamIDs (inSize, inID, outSize, outID);

                if (SUCCEEDED (hr))
                {
                    inputStreamID = inID[0];
                    outputStreamID = outID[0];
                }
                else if (hr == E_NOTIMPL)
                {
                    // GetStreamIDs() can return E_NOTIMPL if both of the following conditions are true:
                    // - The transform has a fixed number of streams.
                    // - The streams are numbered consecutively from 0 to N-1.
                    hr = S_OK;
                    inputStreamID = 0;
                    outputStreamID = 0;
                }
            }

            return hr;
        }

        //=============================================================================
        HRESULT Codec::findOutputMediaType (UINT32 kbps, UINT32 chan, UINT32 rate, UINT32 bits,
                UINT32 aacProfile, UINT32 aacPayload)
        {
            HRESULT hr = S_OK;
            IMFMediaType* mediaType = nullptr;

            for (DWORD i = 0; SUCCEEDED (hr); ++i)
            {
                SafeRelease (&mediaType);

                hr = transform->GetOutputAvailableType (outputStreamID, i, &mediaType);

                if (SUCCEEDED (hr))
                {
                    bool bitflag = false, aacflag = true;
                    UINT32 mtkbps = 0, mtbits = 0, mtchan = 0, mtrate = 0;

                    GUID subtype = GUID_NULL;
                    mediaType->GetGUID (MF_MT_SUBTYPE, &subtype);

                    if (format.isEqual (subtype) == false)
                        continue;

                    // Filter number of channels
                    mediaType->GetUINT32 (MF_MT_AUDIO_NUM_CHANNELS, &mtchan);

                    if (mtchan != chan)
                        continue;

                    // Filter samples per second
                    mediaType->GetUINT32 (MF_MT_AUDIO_SAMPLES_PER_SECOND, &mtrate);

                    if (mtrate != rate)
                        continue;

                    // Filter bytes per second
                    mediaType->GetUINT32 (MF_MT_AUDIO_AVG_BYTES_PER_SECOND, &mtkbps);
                    mtkbps /= 125;

                    bitflag = mtkbps == kbps;

                    if (format.isWMA8orWMA9())
                    {
                        // Filter WMA versions, bytes per second and bits per sample
                        mediaType->GetUINT32 (MF_MT_AUDIO_BITS_PER_SAMPLE, &mtbits);
                        bitflag = (mtkbps == kbps) && (mtbits == bits);
                    }
                    else if (format.isLossless())
                    {
                        // Filter bits per sample
                        mediaType->GetUINT32 (MF_MT_AUDIO_BITS_PER_SAMPLE, &mtbits);
                        bitflag = mtbits == bits;
                    }

                    if (bitflag == false)
                        continue;

                    // Filter AAC profile level and payload
                    if (format.isAAC() && aacProfile > 0)
                    {
                        UINT32 mtprof = 0, mtpayl = 0;
                        mediaType->GetUINT32 (MF_MT_AAC_AUDIO_PROFILE_LEVEL_INDICATION, &mtprof);
                        mediaType->GetUINT32 (MF_MT_AAC_PAYLOAD_TYPE, &mtpayl);
                        aacflag = (mtprof == aacProfile) && (mtpayl == aacPayload);
                    }

                    if (aacflag == false)
                        continue;

                    // Found output media type
                    mediaType->CopyAllItems (outputMediaType);
                    break;
                }
            }

            SafeRelease (&mediaType);

            if (SUCCEEDED (hr)) hr = transform->SetOutputType (outputStreamID, outputMediaType, 0);

            if (FAILED (hr)) DBGAPI (hr);

            return hr;
        }

        //=============================================================================
        HRESULT Codec::findInputMediaType (UINT32 chan, UINT32 rate, UINT32 bits)
        {
            HRESULT hr = S_OK;
            IMFMediaType* mediaType = nullptr;

            for (DWORD i = 0; SUCCEEDED (hr); ++i)
            {
                SafeRelease (&mediaType);

                hr = transform->GetInputAvailableType (outputStreamID, i, &mediaType);

                if (SUCCEEDED (hr))
                {
                    // Accept only PCM audio
                    GUID subtype = GUID_NULL;
                    mediaType->GetGUID (MF_MT_SUBTYPE, &subtype);

                    if (MediaFormat::PCM.isEqual (subtype))
                    {
                        // Filter bits per sample, number of channels and samples per second
                        UINT32 mtbits = 0, mtchan = 0, mtrate = 0;

                        mediaType->GetUINT32 (MF_MT_AUDIO_BITS_PER_SAMPLE, &mtbits);
                        mediaType->GetUINT32 (MF_MT_AUDIO_NUM_CHANNELS, &mtchan);
                        mediaType->GetUINT32 (MF_MT_AUDIO_SAMPLES_PER_SECOND, &mtrate);

                        if (mtbits == bits && mtchan == chan && mtrate == rate)
                        {
                            // Found input media type
                            mediaType->CopyAllItems (inputMediaType);
                            break;
                        }
                    }
                }
            }

            SafeRelease (&mediaType);

            if (SUCCEEDED (hr)) hr = transform->SetInputType (inputStreamID, inputMediaType, 0);

            if (FAILED (hr)) DBGAPI (hr);

            return hr;
        }

        //=============================================================================
        HRESULT Codec::setWMAProperties (UINT32 value)
        {
            IPropertyStore* store = nullptr;

            HRESULT hres = transform->QueryInterface (IID_IPropertyStore, (void**) &store);

            if (SUCCEEDED (hres))
            {
                PROPVARIANT prop;

                if (format.isWMA8() || (format.isWMA9() && value == 0))
                {
                    ::InitPropVariantFromBoolean (FALSE, &prop);
                    if (SUCCEEDED (hres)) hres = store->SetValue (MFPKEY_VBRENABLED, prop);
                    ::PropVariantClear (&prop);

                    ::InitPropVariantFromInt32 (1, &prop);
                    if (SUCCEEDED (hres)) hres = store->SetValue (MFPKEY_PASSESUSED, prop);
                    ::PropVariantClear (&prop);
                }
                else if (format.isWMA9())
                {
                    jassert (value > 0);

                    ::InitPropVariantFromBoolean (TRUE, &prop);
                    if (SUCCEEDED (hres)) hres = store->SetValue (MFPKEY_VBRENABLED, prop);
                    if (SUCCEEDED (hres)) hres = store->SetValue (MFPKEY_CONSTRAIN_ENUMERATED_VBRQUALITY, prop);
                    ::PropVariantClear (&prop);

                    ::InitPropVariantFromInt32 (1, &prop);
                    if (SUCCEEDED (hres)) hres = store->SetValue (MFPKEY_PASSESUSED, prop);
                    ::PropVariantClear (&prop);

                    ::InitPropVariantFromUInt32 (value, &prop);
                    if (SUCCEEDED (hres)) hres = store->SetValue (MFPKEY_DESIRED_VBRQUALITY, prop);
                    ::PropVariantClear (&prop);
                }
                else if (format.isWMALossless())
                {
                    ::InitPropVariantFromBoolean (TRUE, &prop);
                    if (SUCCEEDED (hres)) hres = store->SetValue (MFPKEY_VBRENABLED, prop);
                    if (SUCCEEDED (hres)) hres = store->SetValue (MFPKEY_CONSTRAIN_ENUMERATED_VBRQUALITY, prop);
                    ::PropVariantClear (&prop);

                    ::InitPropVariantFromUInt32 (100, &prop);
                    if (SUCCEEDED (hres)) hres = store->SetValue (MFPKEY_DESIRED_VBRQUALITY, prop);
                    ::PropVariantClear (&prop);
                }
                else if (format.isWMAVoice())
                {
                    ::InitPropVariantFromInt32 (value, &prop);
                    if (SUCCEEDED (hres)) hres = store->SetValue (MFPKEY_WMAVOICE_ENC_MusicSpeechClassMode, prop);
                    ::PropVariantClear (&prop);
                }
            }

            SafeRelease (&store);

            if (FAILED (hres)) DBGAPI(hres);

            return hres;
        }

        //=============================================================================
        IMFMediaType* Codec::cloneMediaType (IMFMediaType* source)
        {
            IMFMediaType* destination = nullptr;

            HRESULT hr = ::MFCreateMediaType (&destination);
            if (SUCCEEDED (hr)) hr = source->CopyAllItems (destination);
            if (SUCCEEDED (hr)) return destination;

            DBGAPI (hr);
            SafeRelease (&destination);
            return nullptr;
        }

        //=============================================================================
        IMFMediaType* Codec::getInputMediaType()
        {
            jassert (inputMediaType != nullptr);
            return inputMediaType ? cloneMediaType (inputMediaType) : nullptr;
        }

        //=============================================================================
        IMFMediaType* Codec::getOutputMediaType()
        {
            jassert (outputMediaType != nullptr);
            return outputMediaType ? cloneMediaType (outputMediaType) : nullptr;
        }

        //=============================================================================
    }
#endif
}
