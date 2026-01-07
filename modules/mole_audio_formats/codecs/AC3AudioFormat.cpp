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
    bool AC3AudioFormat::isChannelLayoutSupported (const juce::AudioChannelSet& channelSet)
    {
        return isChannelTagSupported (FormatTag::AC3, channelSet);
    }

    //=================================================================
    /* Tries to create an object that can read from a stream containing audio data in this format. */
    juce::AudioFormatReader* AC3AudioFormat::createReaderFor (
            juce::InputStream* sourceStream, bool deleteStreamIfOpeningFails)
    {
        std::unique_ptr<juce::AudioFormatReader> p (
                Codec().createDecoderFor (MediaFormat::AC3, sourceStream));

        if (p->bitsPerSample > 0)
            return p.release();

        if (! deleteStreamIfOpeningFails)
            p->input = nullptr;

        return nullptr;
    }

    //=================================================================
    /* Tries to create an object that can write to a stream with this audio format. */
    std::unique_ptr<juce::AudioFormatWriter> AC3AudioFormat::createWriterFor (
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
                kbps = (chan == 1) ? 192 : 256;
                break;
            default:
                DBGSTR("The specified quality option index is not supported.");
                return nullptr;
        }

        std::unique_ptr<juce::AudioFormatWriter> p (
                Codec().createEncoderFor (MediaFormat::AC3, streamToWriteTo, kbps, chan, rate, bits));

        if (p && p->getBitsPerSample() > 0)
            return p;

        return nullptr;
    }

    //=================================================================
#endif
}
