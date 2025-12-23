//////////////////////////////////////////////////////////////////////////
// main.cpp - Defines the entry point for the console application.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// This sample demonstrates how to perform simple transcoding to WMA or WMV.
//
//////////////////////////////////////////////////////////////////////////
// Test custom IMFByteStream (ByteStreamFromInput and ByteStreamFromOutput).
//////////////////////////////////////////////////////////////////////////

#include <JuceHeader.h>
#include "Transcode.h"

using namespace mole::Windows;

#define APIERROR(hr) APIError::toString(hr).toRawUTF8()

int wmain(int argc, wchar_t* argv[])
{
    (void) HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    if (argc != 3)
    {
        printf("Arguments: input_file output_file\n");
        return 0;
    }

    const wchar_t* inputFile = argv[1];  // Input file name
    const wchar_t* outputFile = argv[2];  // Output file name

    std::unique_ptr<juce::InputStream> inputStream = juce::File(GetFullpath(inputFile)).createInputStream();
    std::unique_ptr<juce::OutputStream> outputStream = juce::File(GetFullpath(outputFile)).createOutputStream();

    HRESULT hr = (inputStream && outputStream) ? S_OK : E_INVALIDARG;

    COMLibrary library;
    MFPlatform platform;

    if (SUCCEEDED(hr)) hr = library.Initialize();
    if (SUCCEEDED(hr)) hr = platform.Initialize();

    if (SUCCEEDED(hr))
    {
        CTranscoder transcoder;

        // Create a media source for the input file.
        hr = transcoder.OpenFile(inputStream.get(), inputFile);
        if (SUCCEEDED(hr)) printf("Opened file: %ls\n", inputFile);

        // Configure the profile and build a topology.
        if (SUCCEEDED(hr)) hr = transcoder.ConfigureAudioOutput();
        if (SUCCEEDED(hr)) hr = transcoder.ConfigureVideoOutput();
        if (SUCCEEDED(hr)) hr = transcoder.ConfigureContainer();

        // Transcode and generate the output file.
        if (SUCCEEDED(hr)) hr = transcoder.EncodeToFile(outputStream.get(), outputFile);
        if (SUCCEEDED(hr)) printf("Output file created: %ls\n", outputFile);
    }

    if (FAILED(hr))
    {
        printf("Failed (0x%X)\n", hr);
        printf("%s\n", APIERROR(hr));
    }

    return SUCCEEDED(hr) ? 0 : 1;
}
