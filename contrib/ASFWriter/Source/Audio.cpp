/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <JuceHeader.h>

#include "Platform.h"
#include "System.h"
#include "WMAEncoder.h"
#include "Audio.h"
#include "PropertyStore.h"

//=====================================================================
namespace {
    IMFSourceReader* sourceReader = nullptr;

    const DWORD ALLSTREAMS       = (DWORD) MF_SOURCE_READER_ALL_STREAMS;
    const DWORD FIRSTAUDIOSTREAM = (DWORD) MF_SOURCE_READER_FIRST_AUDIO_STREAM;

    const MF_FILE_ACCESSMODE ACCESSMODE = MF_ACCESSMODE_READ;
    const MF_FILE_OPENMODE   OPENMODE   = MF_OPENMODE_FAIL_IF_NOT_EXIST;
    const MF_FILE_FLAGS      FILEFLAGS  = MF_FILEFLAGS_NONE;

    DWORD readResult = 0;
    const DWORD readError = MF_SOURCE_READERF_ERROR
        | MF_SOURCE_READERF_ENDOFSTREAM
        | MF_SOURCE_READERF_NEWSTREAM
        | MF_SOURCE_READERF_NATIVEMEDIATYPECHANGED
        | MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED
        | MF_SOURCE_READERF_STREAMTICK
        | MF_SOURCE_READERF_ALLEFFECTSREMOVED;

    UINT32 sampleRate = 0;
    UINT32 numChannels = 0;
    UINT32 bitsPerSample = 0;
    UINT32 sampleSize = 0;
    double sampleDuration = 0;
    LONGLONG sampleTime = 0;
}

//=====================================================================
HRESULT OpenAudioFile (PCWSTR url, IMFMediaType** mediaType)
{
    HRESULT hr = S_OK;

    // Create source reader.
    IMFByteStream* byteStream = nullptr;

    if (SUCCEEDED (hr)) hr = ::MFCreateFile (ACCESSMODE, OPENMODE, FILEFLAGS, url, &byteStream);
    if (SUCCEEDED (hr)) hr = ::MFCreateSourceReaderFromByteStream (byteStream, nullptr, &sourceReader);

    SafeRelease (&byteStream);

    // Select audio stream.
    if (SUCCEEDED (hr)) hr = sourceReader->SetStreamSelection (ALLSTREAMS, FALSE);
    if (SUCCEEDED (hr)) hr = sourceReader->SetStreamSelection (FIRSTAUDIOSTREAM, TRUE);

    // Set decoder output.
    IMFMediaType* pcmType = nullptr;

    if (SUCCEEDED (hr)) hr = ::MFCreateMediaType (&pcmType);
    if (SUCCEEDED (hr)) hr = pcmType->SetGUID (MF_MT_MAJOR_TYPE, MFMediaType_Audio);
    if (SUCCEEDED (hr)) hr = pcmType->SetGUID (MF_MT_SUBTYPE, MFAudioFormat_PCM);
    if (SUCCEEDED (hr)) hr = pcmType->SetUINT32 (MF_MT_AUDIO_BITS_PER_SAMPLE, 16);
    if (SUCCEEDED (hr)) hr = sourceReader->SetCurrentMediaType (FIRSTAUDIOSTREAM, nullptr, pcmType);

    SafeRelease (&pcmType);

    // Get media type.
    IMFMediaType* currentType = nullptr;

    if (SUCCEEDED (hr)) hr = sourceReader->GetCurrentMediaType (FIRSTAUDIOSTREAM, &currentType);
    if (SUCCEEDED (hr))
    {
        *mediaType = currentType;
        (*mediaType)->AddRef();

        // Get audio attributes.
        sampleRate = ::MFGetAttributeUINT32 ((IMFAttributes*) currentType, MF_MT_AUDIO_SAMPLES_PER_SECOND, 0);
        numChannels = ::MFGetAttributeUINT32 ((IMFAttributes*) currentType, MF_MT_AUDIO_NUM_CHANNELS, 0);
        bitsPerSample = ::MFGetAttributeUINT32 ((IMFAttributes*) currentType, MF_MT_AUDIO_BITS_PER_SAMPLE, 0);

        sampleSize = (bitsPerSample / 8) * numChannels;
        sampleDuration = 1e+7 / (double) sampleRate;
    }

    SafeRelease (&currentType);

    if (FAILED (hr))
    {
        DBGAPI(hr);
        readResult = MF_SOURCE_READERF_ERROR;
    }

    return hr;
}

//=====================================================================
HRESULT CloseAudioFile()
{
    SafeRelease (&sourceReader);
    return S_OK;
}

//=====================================================================
HRESULT GetNextAudioSample (BOOL& endOfStream, IMFSample** sample)
{
    HRESULT hr = (readResult & readError) ? MF_E_END_OF_STREAM : S_OK;
    if (SUCCEEDED (hr)) hr = (*sample == nullptr) ? S_OK : E_INVALIDARG;

    IMFSample* nextSample = nullptr;

    if (SUCCEEDED (hr)) hr = sourceReader->ReadSample (FIRSTAUDIOSTREAM, 0, nullptr, &readResult, nullptr, &nextSample);

    if (readResult & readError)
    {
        hr = S_OK;
        endOfStream = TRUE;
    }
    else if (SUCCEEDED (hr) && nextSample)
    {
        DWORD length = 0;

        hr = nextSample->GetTotalLength (&length);

        if (SUCCEEDED (hr))
        {
            const double numSamples = (double) (length / sampleSize);
            const LONGLONG duration = (LONGLONG) (sampleDuration * numSamples);

            nextSample->SetSampleTime (sampleTime);
            nextSample->SetSampleDuration (duration);

            sampleTime += duration;

            *sample = nextSample;
            (*sample)->AddRef();
        }
    }

    SafeRelease (&nextSample);

    if (FAILED (hr))
    {
        DBGAPI(hr);
        readResult = MF_SOURCE_READERF_ERROR;
    }

    return hr;
}

//=============================================================================
HRESULT WMAEncoder::PostEncodeUpdate (IMFASFContentInfo* contentInfo)
{
    HRESULT hr = (mft) ? S_OK : MF_E_NOT_INITIALIZED;
    if (SUCCEEDED (hr)) hr = (contentInfo) ? S_OK : E_INVALIDARG;

    if (mode == EncodeMode_VBR_Quality)
    {
        IPropertyStore* src = nullptr;
        IPropertyStore* dst = nullptr;

        if (SUCCEEDED (hr)) hr = mft->QueryInterface (IID_IPropertyStore, (void**) &src);
        if (SUCCEEDED (hr)) hr = contentInfo->GetEncodingConfigurationPropertyStore (0, &dst);
        if (SUCCEEDED (hr)) hr = CopyValue (src, dst, MFPKEY_STAT_BAVG);
        if (SUCCEEDED (hr)) hr = CopyValue (src, dst, MFPKEY_STAT_RAVG);
        if (SUCCEEDED (hr)) hr = CopyValue (src, dst, MFPKEY_STAT_BMAX);
        if (SUCCEEDED (hr)) hr = CopyValue (src, dst, MFPKEY_STAT_RMAX);
        if (SUCCEEDED (hr)) hr = CopyValue (src, dst, MFPKEY_WMAENC_AVGBYTESPERSEC);

        SafeRelease (&src);
        SafeRelease (&dst);
    }

    return hr;
}

//=============================================================================
HRESULT WMAEncoder::GetPropertyStore (IPropertyStore** store)
{
    return mft->QueryInterface (IID_IPropertyStore, (void**) store);
}

//=============================================================================
