//////////////////////////////////////////////////////////////////////////
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.
//////////////////////////////////////////////////////////////////////////

#include <JuceHeader.h>

using namespace mole;

int wmain (int argc, wchar_t* argv[])
{
    if (argc != 3)
    {
        printf ("Usage: Any2Mp4 input.any output.mp4\n");
        return 1;
    }

    juce::File inputFile (juce::File::getCurrentWorkingDirectory()
           .getChildFile (juce::String (argv[1])));

    juce::File outputFile (juce::File::getCurrentWorkingDirectory()
           .getChildFile (juce::String (argv[2])));

    if (inputFile.existsAsFile() == false)
    {
        printf ("Input file not found.\n");
        return 1;
    }

    if (outputFile.existsAsFile() == true)
    {
        printf ("Output file moved to trash.\n");
        outputFile.moveToTrash();
    }

    std::unique_ptr<juce::InputStream> inputStream = inputFile.createInputStream();
    std::unique_ptr<juce::OutputStream> outputStream = outputFile.createOutputStream();

    if (! inputStream || ! outputStream)
    {
        printf ("One or more arguments are not valid.\n");
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
    else
    {
        MP4AudioFormat mp4Format;

        std::unique_ptr<juce::AudioFormatWriter> writer (
                mp4Format.createWriterFor (outputStream,
                    juce::AudioFormatWriterOptions{}
                    .withSampleRate (reader->sampleRate) // 44100 or 48000
                    .withNumChannels (reader->numChannels) // 1, 2 or 6
                    .withBitsPerSample (16) // 16
                    .withQualityOptionIndex (4) // 0-7, 4 = 96kbps per channel
                    ));

        if (writer == nullptr)
        {
            printf ("Error creating audio format writer.\n");
            return 1;
        }
        else
        {
            writer->writeFromAudioReader (*reader, 0, -1);
        }
    }

    printf ("\nThe operation completed successfully.\n");

    return 0;
}
