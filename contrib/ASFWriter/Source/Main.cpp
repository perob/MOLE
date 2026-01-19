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
#include "Audio.h"
#include "WMAEncoder.h"
#include "ASFWriter.h"

#pragma comment(lib, "mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "propsys.lib")
#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "wmcodecdspuuid.lib")

int help()
{
    printf ("Usage: 'ASFWriter [OPTIONS] input output'\n");
    printf ("   input   Input file name - any audio file format\n");
    printf ("   output  Output file name - ASF file format with WMA audio (.wma)\n");
    printf ("Options:\n");
    printf ("   --cbr   Use constant bitrate encoding mode\n");
    printf ("   --vbr   Use variable bitrate encoding mode\n");
    printf ("   --help  Show this message and exit\n");
    return 0;
}

int usage (const wchar_t* option = nullptr)
{
    if (option) printf ("Invalid option: '%ls'\n", option);
    printf ("Usage: 'ASFWriter [OPTIONS] input output'\n");
    printf ("For more information use: 'ASFWriter --help'\n");
    return 1;
}

//=====================================================================
BOOL FileExists (LPCTSTR path)
{
    const DWORD attrib = GetFileAttributes (path);
    return (attrib != INVALID_FILE_ATTRIBUTES && !(attrib & FILE_ATTRIBUTE_DIRECTORY));
}

//=====================================================================
int wmain (int argc, wchar_t* argv[])
{
    HeapSetInformation (nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);

    if (argc == 2 && wcscmp (L"--help", argv[1]) == 0) return help();

    EncodeMode mode = EncodeMode_None;
    const wchar_t* inputFileName = nullptr;
    const wchar_t* outputFileName = nullptr;

    for (int i = 1, argLast = argc - 1; i < argc; ++i)
    {
        if (wcsstr (argv[i], L"--") == argv[i])
        {
            if (wcscmp (L"--cbr", argv[i]) == 0)      { mode = EncodeMode_CBR; }
            else if (wcscmp (L"--vbr", argv[i]) == 0) { mode = EncodeMode_VBR_Quality; }
            else return usage (argv[i]);
        }
        else if (i < argLast)
        {
            inputFileName = argv[i];
            outputFileName = argv[++i];
        }
        else return usage (argv[i]);
    }

    HRESULT hr = (inputFileName && outputFileName) ? S_OK : E_INVALIDARG;

    if (mode == EncodeMode_None) mode = EncodeMode_VBR_Quality;

    IMFASFMultiplexer* mux = nullptr;
    IMFMediaType* inputType = nullptr;
    IMFByteStream* dataStream = nullptr;
    IMFASFContentInfo* contentInfo = nullptr;

    WMAEncoder* encoder = nullptr;

    COMLibrary library;
    MFPlatform platform;

    if (SUCCEEDED (hr)) hr = library.Initialize();
    if (SUCCEEDED (hr)) hr = platform.Initialize();

    if (SUCCEEDED (hr)) hr = OpenAudioFile (inputFileName, &inputType);

    if (SUCCEEDED (hr)) 
    {
        encoder = new (std::nothrow) WMAEncoder();
        hr = (encoder) ? S_OK : E_OUTOFMEMORY;
    }

    if (SUCCEEDED (hr)) hr = encoder->Initialize();
    if (SUCCEEDED (hr)) hr = encoder->SetEncodingType (mode);
    if (SUCCEEDED (hr)) hr = encoder->SetInputType (inputType);
    if (SUCCEEDED (hr)) hr = CreateASFContentInfo (encoder, &contentInfo);
    if (SUCCEEDED (hr)) hr = CreateASFMux (contentInfo, &mux);
    if (SUCCEEDED (hr)) hr = EncodeData (encoder, contentInfo, mux, &dataStream);
    if (SUCCEEDED (hr)) hr = encoder->PostEncodeUpdate (contentInfo);
    if (SUCCEEDED (hr)) hr = WriteASFFile (contentInfo, dataStream, outputFileName);
    if (SUCCEEDED (hr)) hr = CloseAudioFile();

    SafeRelease (&inputType);
    SafeRelease (&contentInfo);
    SafeRelease (&mux);
    SafeRelease (&dataStream);

    delete encoder;

    if (FAILED (hr)) DBGAPI(hr);
    else printf ("Transcode success.\n");

    return 0;
}
