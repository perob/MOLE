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
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#include <JuceHeader.h>

#include "Platform.h"
#include "System.h"
#include "Audio.h"
#include "WMAEncoder.h"
#include "ASFWriter.h"
#include "PropertyStore.h"

#define DEFAULT_STREAM_NUMBER 1

//=====================================================================
HRESULT AppendToByteStream (IMFByteStream* src, IMFByteStream* dest)
{
    const DWORD READ_SIZE = 4096;
    BYTE buffer[READ_SIZE];

    HRESULT hr = S_OK;

    while (SUCCEEDED (hr))
    {
        ULONG numRead = 0;
        ULONG numWrite = 0;

        if (SUCCEEDED (hr)) hr = src->Read (buffer, READ_SIZE, &numRead);
        if (numRead == 0) break;
        if (SUCCEEDED (hr)) hr = dest->Write (buffer, numRead, &numWrite);
        if (numRead < READ_SIZE) break;
    }

    if (FAILED (hr)) DBGAPI(hr);

    return hr;
}

//=====================================================================
HRESULT WriteBufferToByteStream (IMFByteStream* stream, IMFMediaBuffer* buffer, DWORD* numWritten)
{
    DWORD dataSize = 0;
    DWORD count = 0;
    BYTE* data = nullptr;

    HRESULT hr = buffer->Lock (&data, nullptr, &dataSize);
    if (SUCCEEDED (hr)) hr = stream->Write (data, dataSize, &count);
    if (SUCCEEDED (hr)) *numWritten = count;
    if (data) buffer->Unlock();

    return hr;
}

//=====================================================================
HRESULT CreateASFContentInfo (WMAEncoder* encoder, IMFASFContentInfo** asfContentInfo)
{
    IMFASFProfile* profile = nullptr;
    IMFMediaType* mediaType = nullptr;
    IMFASFStreamConfig* stream = nullptr;
    IMFASFContentInfo* contentInfo = nullptr;

    HRESULT hr = ::MFCreateASFProfile (&profile);

    if (SUCCEEDED (hr)) hr = encoder->GetOutputType (&mediaType);
    if (SUCCEEDED (hr)) hr = profile->CreateStream (mediaType, &stream);
    if (SUCCEEDED (hr)) hr = stream->SetStreamNumber (DEFAULT_STREAM_NUMBER);

    LeakyBucket leakyBucket;

    if (SUCCEEDED (hr)) hr = encoder->GetLeakyBucket1 (&leakyBucket);
    if (SUCCEEDED (hr)) hr = stream->SetBlob (MF_ASFSTREAMCONFIG_LEAKYBUCKET1, (UINT8*) &leakyBucket, sizeof (LeakyBucket));
    if (SUCCEEDED (hr)) hr = profile->SetStream (stream);
    if (SUCCEEDED (hr)) hr = ::MFCreateASFContentInfo (&contentInfo);

    if (SUCCEEDED (hr))
    {
        IPropertyStore* src = nullptr;
        IPropertyStore* dst = nullptr;

        if (SUCCEEDED (hr)) hr = encoder->GetPropertyStore (&src);
        if (SUCCEEDED (hr)) hr = contentInfo->GetEncodingConfigurationPropertyStore (DEFAULT_STREAM_NUMBER, &dst);

        if (SUCCEEDED (hr))
        {
            CopyValue (src, dst, MFPKEY_VBRENABLED);
            CopyValue (src, dst, MFPKEY_PASSESUSED);
            CopyValue (src, dst, MFPKEY_DESIRED_VBRQUALITY);
        }

        SafeRelease (&src);
        SafeRelease (&dst);

        IPropertyStore* store = nullptr;

        if (SUCCEEDED (hr)) hr = contentInfo->GetEncodingConfigurationPropertyStore (0, &store);
        if (SUCCEEDED (hr)) hr = SetBOOL (store, MFPKEY_ASFMEDIASINK_AUTOADJUST_BITRATE, TRUE);

        SafeRelease (&store);
    }

    if (SUCCEEDED (hr)) hr = contentInfo->SetProfile (profile);

    if (SUCCEEDED (hr))
    {
        *asfContentInfo = contentInfo;
        (*asfContentInfo)->AddRef();
    }

    SafeRelease (&profile);
    SafeRelease (&stream);
    SafeRelease (&mediaType);
    SafeRelease (&contentInfo);

    return hr;
}

//=====================================================================
HRESULT CreateASFMux (IMFASFContentInfo* contentInfo, IMFASFMultiplexer** multiplexer)
{
    IMFASFMultiplexer* mux = nullptr;

    HRESULT hr = ::MFCreateASFMultiplexer (&mux);
    if (SUCCEEDED (hr)) hr = mux->SetFlags (MFASF_MULTIPLEXER_AUTOADJUST_BITRATE);
    if (SUCCEEDED (hr)) hr = mux->Initialize (contentInfo);

    if (SUCCEEDED (hr))
    {
        *multiplexer = mux;
        (*multiplexer)->AddRef();
    }

    SafeRelease (&mux);

    return hr;
}

//=====================================================================
HRESULT EncodeData (WMAEncoder* encoder, IMFASFContentInfo* contentInfo, IMFASFMultiplexer* mux, IMFByteStream** dataStream)
{
    IMFByteStream* stream = nullptr;

    BOOL eof = FALSE;
    BOOL needInput = TRUE;

    HRESULT hr = ::MFCreateTempFile (MF_ACCESSMODE_READWRITE, MF_OPENMODE_DELETE_IF_EXIST, MF_FILEFLAGS_NONE, &stream);

    while (TRUE)
    {
        IMFSample* wmaSample = nullptr;
        IMFSample* inputSample = nullptr;

        if (needInput == TRUE)
        {
            if (SUCCEEDED (hr)) hr = GetNextAudioSample (eof, &inputSample);
            if (eof) break;
            if (!inputSample) continue;

            if (SUCCEEDED (hr)) hr = encoder->ProcessInput (inputSample);

            needInput = FALSE;
        }

        if (needInput == FALSE)
        {
            if (SUCCEEDED (hr)) hr = encoder->ProcessOutput (&wmaSample);

            if (wmaSample)
            {
                if (SUCCEEDED (hr)) hr = mux->ProcessSample (DEFAULT_STREAM_NUMBER, wmaSample, 0);
                if (SUCCEEDED (hr)) hr = GenerateASFDataPackets (mux, stream);
            }
            else
            {
                needInput = TRUE;
            }
        }

        SafeRelease (&inputSample);
        SafeRelease (&wmaSample);

        if (FAILED (hr)) break;
    }

    if (SUCCEEDED (hr)) hr = encoder->Drain();

    while (TRUE)
    {
        IMFSample* wmaSample = nullptr;

        if (SUCCEEDED (hr)) hr = encoder->ProcessOutput (&wmaSample);
        if (wmaSample == nullptr) break;

        if (SUCCEEDED (hr)) hr = mux->ProcessSample (DEFAULT_STREAM_NUMBER, wmaSample, 0);
        if (SUCCEEDED (hr)) hr = GenerateASFDataPackets (mux, stream);

        SafeRelease (&wmaSample);

        if (FAILED (hr)) break;
    }

    if (SUCCEEDED (hr)) hr = mux->Flush();
    if (SUCCEEDED (hr)) hr = GenerateASFDataPackets (mux, stream);
    if (SUCCEEDED (hr)) hr = mux->End (contentInfo);

    if (SUCCEEDED (hr))
    {
        *dataStream = stream;
        (*dataStream)->AddRef();
    }

    SafeRelease (&stream);

    if (FAILED (hr)) DBGAPI(hr);

    return hr;
}

//=====================================================================
HRESULT WriteASFFile (IMFASFContentInfo* contentInfo, IMFByteStream* dataStream, PCWSTR file)
{
    IMFMediaBuffer* headerBuffer = nullptr;
    IMFByteStream* wmaStream = nullptr;

    DWORD headerSize = 0;
    DWORD numWritten = 0;

    HRESULT hr = ::MFCreateFile (MF_ACCESSMODE_WRITE, MF_OPENMODE_DELETE_IF_EXIST, MF_FILEFLAGS_NONE, file, &wmaStream);
    if (SUCCEEDED (hr)) hr = contentInfo->GenerateHeader (nullptr, &headerSize);
    if (SUCCEEDED (hr)) hr = ::MFCreateMemoryBuffer (headerSize, &headerBuffer);
    if (SUCCEEDED (hr)) hr = contentInfo->GenerateHeader (headerBuffer, &headerSize);
    if (SUCCEEDED (hr)) hr = WriteBufferToByteStream (wmaStream, headerBuffer, &numWritten);
    if (SUCCEEDED (hr)) hr = dataStream->SetCurrentPosition (0);
    if (SUCCEEDED (hr)) hr = AppendToByteStream (dataStream, wmaStream);

    SafeRelease (&headerBuffer);
    SafeRelease (&wmaStream);

    return hr;
}

//=====================================================================
HRESULT GenerateASFDataPackets (IMFASFMultiplexer *mux, IMFByteStream *dataStream)
{
    HRESULT hr = S_OK;

    IMFSample *outputSample = NULL;
    IMFMediaBuffer *dataPacketBuffer = NULL;

    DWORD muxStatus = ASF_STATUSFLAGS_INCOMPLETE;

    while (muxStatus & ASF_STATUSFLAGS_INCOMPLETE)
    {
        hr = mux->GetNextPacket (&muxStatus, &outputSample);

        if (FAILED (hr))
        {
            break;
        }

        if (outputSample)
        {
            // Convert to contiguous buffer
            hr = outputSample->ConvertToContiguousBuffer (&dataPacketBuffer);

            if (FAILED (hr))
            {
                break;
            }

            DWORD numWritten = 0;

            // Write buffer to byte stream
            hr = WriteBufferToByteStream (dataStream, dataPacketBuffer, &numWritten);

            if (FAILED (hr))
            {
                break;
            }
        }

        SafeRelease (&dataPacketBuffer);
        SafeRelease (&outputSample);
    }

    SafeRelease (&outputSample);
    SafeRelease (&dataPacketBuffer);

    return hr;
}
