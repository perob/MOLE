/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

namespace mole {

#if JUCE_WINDOWS

    namespace WindowsMediaFoundation {

        //=============================================================================
        WMATransform::WMATransform()
        {
            HRESULT hr = library.Initialize();
            if (SUCCEEDED (hr)) hr = platform.Initialize();
            jassert (SUCCEEDED (hr));
        }

        WMATransform::~WMATransform()
        {
            SafeRelease (&transform);
        }

        //=============================================================================
        juce::AudioFormatWriter* WMATransform::createSinkFor (
                const MediaFormat& mediaFormat, std::unique_ptr<juce::OutputStream>& stream,
                UINT32 vbrq, UINT32 chan, UINT32 rate, UINT32 bits)
        {
            HRESULT hr = configureEncoder (vbrq, chan, rate, bits);

            if (SUCCEEDED (hr))
            {
                return new (std::nothrow) ASFSink (
                    mediaFormat, std::exchange (stream, {}).release(),
                    rate, chan, bits, transform);
            }

            DBGAPI(hr);
            return nullptr;
        }

        //=============================================================================
        HRESULT WMATransform::configureEncoder (UINT32 vbrq, UINT32 chan, UINT32 rate, UINT32 bits)
        {
            HRESULT hr = ::CoCreateInstance (CLSID_CWMAEncMediaObject, nullptr, CLSCTX_INPROC_SERVER, IID_IMFTransform, (void**) &transform);

            if (SUCCEEDED (hr)) hr = setProperties (vbrq);
            if (SUCCEEDED (hr)) hr = setMediaType (chan, rate, bits);

            return hr;
        }

        //=============================================================================
        HRESULT WMATransform::setProperties (UINT32 vbrQuality)
        {
            IPropertyStore* store = nullptr;

            HRESULT hr = transform->QueryInterface (IID_IPropertyStore, (void**) &store);

            if (SUCCEEDED (hr))
            {
                SetPropertyBOOL (store, MFPKEY_VBRENABLED, TRUE);
                SetPropertyBOOL (store, MFPKEY_CONSTRAIN_ENUMERATED_VBRQUALITY, TRUE);
                SetPropertyUINT32 (store, MFPKEY_DESIRED_VBRQUALITY, vbrQuality);
            }

            SafeRelease (&store);

            return hr;
        }

        //=============================================================================
        HRESULT WMATransform::setMediaType (UINT32 chan, UINT32 rate, UINT32 bits)
        {
            IMFMediaType* inputType = nullptr;

            HRESULT hr = ::MFCreateMediaType (&inputType);

            if (SUCCEEDED (hr))
            {
                const UINT32 blockAlignment = (bits / 8) * chan;
                const UINT32 bytesPerSecond = rate * blockAlignment;

                inputType->SetGUID (MF_MT_MAJOR_TYPE, MFMediaType_Audio);
                inputType->SetGUID (MF_MT_SUBTYPE, MFAudioFormat_PCM);
                inputType->SetUINT32 (MF_MT_AUDIO_NUM_CHANNELS, chan);
                inputType->SetUINT32 (MF_MT_AUDIO_SAMPLES_PER_SECOND, rate);
                inputType->SetUINT32 (MF_MT_AUDIO_BITS_PER_SAMPLE, bits);
                inputType->SetUINT32 (MF_MT_AUDIO_BLOCK_ALIGNMENT, blockAlignment);
                inputType->SetUINT32 (MF_MT_AUDIO_AVG_BYTES_PER_SECOND, bytesPerSecond);

                hr = transform->SetInputType (streamID, inputType, 0);
            }

            SafeRelease (&inputType);

            for (DWORD i = 0; SUCCEEDED (hr); ++i)
            {
                IMFMediaType* outputType = nullptr;

                hr = transform->GetOutputAvailableType (streamID, i, &outputType);

                if (SUCCEEDED (hr))
                {
                    hr = transform->SetOutputType (streamID, outputType, 0);
                    SafeRelease (&outputType);
                    break;
                }

                SafeRelease (&outputType);
            }

            return hr;
        }

        //=============================================================================
    }
#endif
}
