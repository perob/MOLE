/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

namespace mole {

#if JUCE_WINDOWS

    using namespace mole::WindowsMediaFoundation;

    //=================================================================
    /* Returns true if the channel layout is supported by this format. */
    bool WMA8AudioFormat::isChannelLayoutSupported (const juce::AudioChannelSet& channelSet)
    {
        return isChannelTagSupported (FormatTag::WMA8, channelSet);
    }

    //=================================================================
    /* Tries to create an object that can read from a stream containing audio data in this format. */
    juce::AudioFormatReader* WMA8AudioFormat::createReaderFor (
            juce::InputStream* sourceStream, bool deleteStreamIfOpeningFails)
    {
        std::unique_ptr<juce::AudioFormatReader> p (
                Codec().createDecoderFor (MediaFormat::WMA8, sourceStream));

        if (p->bitsPerSample > 0)
            return p.release();

        if (! deleteStreamIfOpeningFails)
            p->input = nullptr;

        return nullptr;
    }

    //=================================================================
    /* Tries to create an object that can write to a stream with this audio format. */
    std::unique_ptr<juce::AudioFormatWriter> WMA8AudioFormat::createWriterFor (
            std::unique_ptr<juce::OutputStream>& streamToWriteTo,
            const juce::AudioFormatWriterOptions& options)
    {
        UINT32 kbps = 0, chan = 0, rate = 0, bits = 0;

        rate = (UINT32) options.getSampleRate();
        chan = options.getNumChannels();
        bits = options.getBitsPerSample();

        switch (options.getQualityOptionIndex())
        {
            case 0:
                kbps = 96 * chan;
                break;
            case 8: case 10: case 12: case 16: case 20: case 22:
            case 24: case 32: case 40: case 48: case 64: case 80:
            case 96: case 128: case 160: case 192: case 256: case 320:
                kbps = options.getQualityOptionIndex();
                break;
            default:
                DBGSTR("The specified quality option index is not supported.");
                return nullptr;
        }

        if (kbps == 32 && chan == 2 && rate == 44100)
            kbps = 31;

        std::unique_ptr<juce::AudioFormatWriter> p (
                Codec().createEncoderFor (MediaFormat::WMA8, streamToWriteTo, kbps, chan, rate, bits));

        if (p && p->getBitsPerSample() > 0)
            return p;

        return nullptr;
    }

    //=================================================================
#endif
}
