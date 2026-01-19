// The MIT License (MIT)
// Copyright (c) Microsoft Corporation
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#include <JuceHeader.h>

#include "Platform.h"
#include "System.h"
#include "WMAEncoder.h"
#include "PropertyStore.h"

//=====================================================================
WMAEncoder::WMAEncoder()
{
}

WMAEncoder::~WMAEncoder()
{
    SafeRelease (&mft);
    SafeRelease (&outputMediaType);
}

//=====================================================================
HRESULT WMAEncoder::Initialize()
{
    IMFActivate** activate = nullptr;
    UINT32 count = 0;

    GUID category = MFT_CATEGORY_AUDIO_ENCODER;
    const UINT32 flags = MFT_ENUM_FLAG_SYNCMFT | MFT_ENUM_FLAG_SORTANDFILTER;
    MFT_REGISTER_TYPE_INFO info = { MFMediaType_Audio, MFAudioFormat_WMAudioV9 };

    HRESULT hr = ::MFTEnumEx(category, flags, nullptr, &info, &activate, &count);
    if (SUCCEEDED (hr) && count == 0) hr = MF_E_TOPO_CODEC_NOT_FOUND;
    if (SUCCEEDED (hr)) hr = activate[0]->ActivateObject (IID_IMFTransform, (void**) &mft);

    for (DWORD i = 0; i < count; ++i)
        activate[i]->Release();

    CoTaskMemFree (activate);

    return hr;
}

//=====================================================================
HRESULT WMAEncoder::SetEncodingType (EncodeMode encodeMode)
{
    HRESULT hr = (mft) ? S_OK : MF_E_NOT_INITIALIZED;

    IPropertyStore* store = nullptr;

    if (SUCCEEDED (hr)) hr = mft->QueryInterface (IID_IPropertyStore, (void**) &store);
    if (SUCCEEDED (hr)) mode = encodeMode;

    switch (mode)
    {
        case EncodeMode_CBR:
            if (SUCCEEDED (hr)) hr = SetBOOL (store, MFPKEY_VBRENABLED, FALSE);
            break;
        case EncodeMode_VBR_Quality:
            if (SUCCEEDED (hr)) hr = SetBOOL (store, MFPKEY_VBRENABLED, TRUE);
            if (SUCCEEDED (hr)) hr = SetBOOL (store, MFPKEY_CONSTRAIN_ENUMERATED_VBRQUALITY, TRUE);
            if (SUCCEEDED (hr)) hr = SetUINT32 (store, MFPKEY_DESIRED_VBRQUALITY, 90);
            break;
        case EncodeMode_VBR_Peak:
        case EncodeMode_VBR_Unconstrained:
        default:
            hr = E_NOTIMPL;
            break;
    }

    SafeRelease (&store);

    return hr;
}

//=====================================================================
HRESULT WMAEncoder::SetInputType (IMFMediaType* mediaType)
{
    HRESULT hr = (mft) ? S_OK : MF_E_NOT_INITIALIZED;

    SafeRelease (&outputMediaType);

    if (SUCCEEDED (hr)) hr = ::MFCreateMediaType (&outputMediaType);
    if (SUCCEEDED (hr)) hr = mft->GetStreamIDs (1, &inputID, 1, &outputID);

    if (hr == E_NOTIMPL)
    {
        inputID = 0;
        outputID = 0;
        hr = S_OK;
    }

    if (SUCCEEDED (hr)) hr = mft->SetInputType (inputID, mediaType, 0);

    if (mode == EncodeMode_CBR)
    {
        for (DWORD i = 0; SUCCEEDED (hr); ++i)
        {
            IMFMediaType* outputType = nullptr;

            hr = mft->GetOutputAvailableType (outputID, i, &outputType);

            // Filter bytes per second
            UINT32 bytesPerSecond = 0;
            outputType->GetUINT32 (MF_MT_AUDIO_AVG_BYTES_PER_SECOND, &bytesPerSecond);

            if ((bytesPerSecond / 125) == 128)
            {
                if (SUCCEEDED (hr)) hr = mft->SetOutputType (outputID, outputType, 0);
                if (SUCCEEDED (hr)) hr = outputType->CopyAllItems (outputMediaType);

                SafeRelease (&outputType);

                if (SUCCEEDED (hr))
                    break;
            }

            SafeRelease (&outputType);
        }
    }
    else
    {
        IMFMediaType* outputType = nullptr;

        hr = mft->GetOutputAvailableType (outputID, 0, &outputType);

        if (SUCCEEDED (hr)) hr = mft->SetOutputType (outputID, outputType, 0);
        if (SUCCEEDED (hr)) hr = outputType->CopyAllItems (outputMediaType);

        SafeRelease (&outputType);
    }

    return hr;
}

//=====================================================================
HRESULT WMAEncoder::GetOutputType (IMFMediaType** mediaType)
{
    HRESULT hr = (outputMediaType) ? S_OK : MF_E_TRANSFORM_TYPE_NOT_SET;

    if (SUCCEEDED (hr))
    {
        *mediaType = outputMediaType;
        (*mediaType)->AddRef();
    }

    return hr;
}

//=====================================================================
HRESULT WMAEncoder::GetLeakyBucket1 (LeakyBucket* bucket)
{
    HRESULT hr = (mft && outputMediaType) ? S_OK : MF_E_NOT_INITIALIZED;

    if (SUCCEEDED (hr))
    {
        ::ZeroMemory (bucket, sizeof(LeakyBucket));

        bucket->bitrate = 8 * ::MFGetAttributeUINT32 (outputMediaType, MF_MT_AUDIO_AVG_BYTES_PER_SECOND, 0);

        IWMCodecLeakyBucket* leakyBuckets = nullptr;

        hr = mft->QueryInterface (IID_IWMCodecLeakyBucket, (void**) &leakyBuckets);

        if (SUCCEEDED (hr))
        {
            ULONG bits = 0;

            hr = leakyBuckets->GetBufferSizeBits (&bits);

            if (SUCCEEDED (hr)) bucket->bufferSize = bits / (bucket->bitrate / 1000);
        }

        SafeRelease (&leakyBuckets);
    }

    return hr;
}

//=====================================================================
HRESULT WMAEncoder::ProcessInput (IMFSample* sample)
{
    HRESULT hr = (mft) ? S_OK : MF_E_NOT_INITIALIZED;

    if (SUCCEEDED (hr)) hr = mft->ProcessInput (inputID, sample, 0);

    return hr;
}

//=====================================================================
HRESULT WMAEncoder::ProcessOutput (IMFSample** sample)
{
    HRESULT hr = (mft) ? S_OK : MF_E_NOT_INITIALIZED;

    if (SUCCEEDED (hr))
    {
        *sample = nullptr;

        IMFMediaBuffer* outputBuffer = nullptr;
        IMFSample* outputSample = nullptr;

        DWORD status = 0;

        MFT_OUTPUT_STREAM_INFO streamInfo = {0};
        MFT_OUTPUT_DATA_BUFFER outputData = {0};

        hr = mft->GetOutputStreamInfo (outputID, &streamInfo);
        if (SUCCEEDED (hr)) hr = ::MFCreateMemoryBuffer (streamInfo.cbSize, &outputBuffer);
        if (SUCCEEDED (hr)) hr = ::MFCreateSample (&outputSample);
        if (SUCCEEDED (hr)) hr = outputSample->AddBuffer (outputBuffer);

        if (SUCCEEDED (hr))
        {
            outputData.pSample = outputSample;
            outputData.dwStreamID = outputID;
        }

        if (SUCCEEDED (hr)) hr = mft->ProcessOutput (0, 1, &outputData, &status);

        if (hr == MF_E_TRANSFORM_NEED_MORE_INPUT)
        {
            hr = S_OK;
        }
        else if (SUCCEEDED (hr))
        {
            *sample = outputSample;
            (*sample)->AddRef();
        }

        SafeRelease (&outputBuffer);
        SafeRelease (&outputSample);
    }

    if (FAILED (hr)) DBGAPI(hr);

    return hr;
}

//=====================================================================
HRESULT WMAEncoder::Drain()
{
    HRESULT hr = (mft) ? S_OK : MF_E_NOT_INITIALIZED;

    if (SUCCEEDED (hr)) hr = mft->ProcessMessage (MFT_MESSAGE_COMMAND_DRAIN, inputID);

    return hr;
}
