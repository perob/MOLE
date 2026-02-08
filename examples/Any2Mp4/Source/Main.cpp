//////////////////////////////////////////////////////////////////////////
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.
//////////////////////////////////////////////////////////////////////////

#include <JuceHeader.h>

using namespace mole;

int help()
{
    printf ("Transcode audio file formats.\n");
    printf ("Usage: 'Any2Mp4 [OPTION] input output'\n");
    printf ("Options:\n");
    printf ("    --mp4       Transcode to MP4 file format with AAC audio (default).\n");
    printf ("    --mp3       Transcode to MP3 file format with MPEG Layer 3 audio.\n");
    printf ("    --mp2       Transcode to MPEG file format with MPEG Layer 2 audio.\n");
    printf ("    --mp1       Transcode to MPEG file format with MPEG Layer 1 audio.\n");
    printf ("    --flac      Transcode to MP4 file format with FLAC audio.\n");
    printf ("    --wma8      Transcode to ASF file format with Windows Media Audio 8 audio.\n");
    printf ("    --wma9      Transcode to ASF file format with Windows Media Audio 9 audio.\n");
    printf ("    --wmal      Transcode to ASF file format with Windows Media Audio Lossless audio.\n");
    printf ("    --wmsp      Transcode to ASF file format with Windows Media Audio Voice audio.\n");
    printf ("    --kbps NUM  Set kilobits per second.\n");
    printf ("    --vbrq NUM  Set variable bitrate quality.\n");
    printf ("    --help      Show this message and exit.\n");
    return 0;
}

int usage (const wchar_t* option = nullptr)
{
    if (option) printf ("Invalid option: '%ls'\n", option);
    printf ("Usage: 'Any2Mp4 [OPTION] input output'\n");
    printf ("For more information use: 'Any2Mp4 --help'\n");
    return 1;
}

int wmain (int argc, wchar_t* argv[])
{
    int kbps = 0, vbrq = 0;

    const wchar_t* input = nullptr;
    const wchar_t* output = nullptr;

    enum AudioFormat { MP4, MP3, MP2, MP1, FLAC, WMA8, WMA9, WMAL, WMSP };
    AudioFormat target = AudioFormat::MP4;

    if (argc < 3) return usage();

    for (int i = 1, argLast = argc - 1; i < argc; ++i)
    {
        if (wcsstr (argv[i], L"--") == argv[i])
        {
            if (wcscmp (L"--mp4", argv[i]) == 0) target = AudioFormat::MP4;
            else if (wcscmp (L"--mp3", argv[i]) == 0) target = AudioFormat::MP3;
            else if (wcscmp (L"--mp2", argv[i]) == 0) target = AudioFormat::MP2;
            else if (wcscmp (L"--mp1", argv[i]) == 0) target = AudioFormat::MP1;
            else if (wcscmp (L"--flac", argv[i]) == 0) target = AudioFormat::FLAC;
            else if (wcscmp (L"--wma8", argv[i]) == 0) target = AudioFormat::WMA8;
            else if (wcscmp (L"--wma9", argv[i]) == 0) target = AudioFormat::WMA9;
            else if (wcscmp (L"--wmal", argv[i]) == 0) target = AudioFormat::WMAL;
            else if (wcscmp (L"--wmsp", argv[i]) == 0) target = AudioFormat::WMSP;
            else if (wcscmp (L"--kbps", argv[i]) == 0 && i < argLast) kbps = juce::String(argv[++i]).getIntValue();
            else if (wcscmp (L"--vbrq", argv[i]) == 0 && i < argLast) vbrq = juce::String(argv[++i]).getIntValue();
            else if (wcscmp (L"--help", argv[i]) == 0) return help();
            else return usage (argv[i]);
        }
        else if (i < argLast)
        {
            input = argv[i];
            output = argv[++i];
        }
        else
        {
            return usage (argv[i]);
        }
    }

    if (kbps && vbrq) return usage (L"kbps/vbrq");

    printf ("Transcode: '%ls' -> '%ls'\n", input, output);

    juce::File inputFile (juce::File::getCurrentWorkingDirectory()
            .getChildFile (juce::String (input)));

    juce::File outputFile (juce::File::getCurrentWorkingDirectory()
            .getChildFile (juce::String (output)));

    if (inputFile.existsAsFile() == false)
    {
        printf ("Input file not found.\n");
        return 1;
    }

    if (outputFile.existsAsFile() == true)
    {
        printf ("Output file exists, moved to trash.\n");
        outputFile.moveToTrash();
    }

    std::unique_ptr<juce::InputStream> inputStream = inputFile.createInputStream();
    std::unique_ptr<juce::OutputStream> outputStream = outputFile.createOutputStream();

    if (! inputStream || ! outputStream)
    {
        printf ("One or more arguments are invalid.\n");
        return 1;
    }

    juce::AudioFormatManager manager;
    manager.registerBasicFormats();
    manager.registerFormat (new MP4AudioFormat(), false);

    std::unique_ptr<juce::AudioFormatReader> reader (manager.createReaderFor (std::move(inputStream)));

    if (reader == nullptr)
    {
        printf ("Error creating audio format reader.\n");
        return 1;
    }

    std::unique_ptr<juce::AudioFormat> audioFormat = nullptr;

    switch (target)
    {
        case MP4: audioFormat.reset (new MP4AudioFormat()); break;
        case MP3: audioFormat.reset (new MP3AudioFormat()); break;
        case MP2: audioFormat.reset (new MP2AudioFormat()); break;
        case MP1: audioFormat.reset (new MP1AudioFormat()); break;
        case FLAC: audioFormat.reset (new FLACAudioFormat()); break;
        case WMA8: audioFormat.reset (new WMA8AudioFormat()); break;
        case WMA9: audioFormat.reset (new WMA9AudioFormat()); break;
        case WMAL: audioFormat.reset (new WMALosslessAudioFormat()); break;
        case WMSP: audioFormat.reset (new WMAVoiceAudioFormat()); break;
        default:
                  audioFormat.reset (new MP4AudioFormat());
                  break;
    }

    int option = (kbps) ? kbps : vbrq;

    std::unique_ptr<juce::AudioFormatWriter> writer (
            audioFormat->createWriterFor (outputStream,
                juce::AudioFormatWriterOptions{}
                .withSampleRate (reader->sampleRate)
                .withNumChannels (reader->numChannels)
                .withBitsPerSample (reader->bitsPerSample)
                .withQualityOptionIndex (option)
                ));

    if (writer == nullptr)
    {
        printf ("Error creating audio format writer.\n");
        return 1;
    }

    const bool success = writer->writeFromAudioReader (*reader, 0, -1);

    if (success)
        printf ("Transcode completed successfully.\n");
    else
        printf ("Transcode failed.\n");

    return (success) ? 0 : 1;
}
