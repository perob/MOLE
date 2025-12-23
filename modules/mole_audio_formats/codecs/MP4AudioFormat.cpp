/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

namespace mole {

#if JUCE_WINDOWS

    using namespace mole::WindowsMediaFoundation;

    /* Tries to create an object that can read from a stream containing audio data in this format. */
    juce::AudioFormatReader* MP4AudioFormat::createReaderFor (
            juce::InputStream* sourceStream, bool deleteStreamIfOpeningFails)
    {
        std::unique_ptr<juce::AudioFormatReader> p (new MP4AudioFormatReader (sourceStream, false));

        if (p->bitsPerSample == 32 && p->sampleRate > 0 && p->numChannels > 0 && p->lengthInSamples > 0)
            return p.release();

        if (! deleteStreamIfOpeningFails)
            p->input = nullptr;

        return nullptr;
    }

    /* Tries to create an object that can write to a stream with this audio format. */
    std::unique_ptr<juce::AudioFormatWriter> MP4AudioFormat::createWriterFor (
            std::unique_ptr<juce::OutputStream>& streamToWriteTo,
            const juce::AudioFormatWriterOptions& options)
    {
        switch ((int) options.getSampleRate())
        {
            case 44100: case 48000:
                break;
            default:
                DBGSTR("The specified sample rate is not supported.");
                return nullptr;
        }

        if (options.getChannelLayout().has_value())
        {
            if (isChannelLayoutSupported (options.getChannelLayout().value()) == false)
            {
                DBGSTR("The specified channel layout is not supported.");
                return nullptr;
            }
        }
        else
        {
            switch ((int) options.getNumChannels())
            {
                case 1: case 2: case 6:
                    break;
                default:
                    DBGSTR("The specified number of channels is not supported.");
                    return nullptr;
            }
        }

        switch ((int) options.getBitsPerSample())
        {
            case 16:
                break;
            default:
                DBGSTR("The specified bits per sample is not supported.");
                return nullptr;
        }

        if (options.getMetadataValues().size() > 0)
        {
            DBGSTR("Writing metadata values is not supported.");
            return nullptr;
        }

        switch ((int) options.getQualityOptionIndex())
        {
            case 0: case 1: case 2: case 3:
            case 4: case 5: case 6: case 7:
                break;
            default:
                DBGSTR("The specified quality option index is not supported.");
                return nullptr;
        }

        return std::make_unique<MP4AudioFormatWriter> (streamToWriteTo.release(),
                options.getChannelLayout().has_value()
                ? options.withNumChannels (options.getChannelLayout().value().size()) : options);
    }

#endif // JUCE_WINDOWS
} // namespace mole
