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
    bool WMAVoiceAudioFormat::isChannelLayoutSupported (const juce::AudioChannelSet& channelSet)
    {
        return isChannelTagSupported (FormatTag::WMAVoice, channelSet);
    }

    //=================================================================
    /* Tries to create an object that can read from a stream containing audio data in this format. */
    juce::AudioFormatReader* WMAVoiceAudioFormat::createReaderFor (
            juce::InputStream* sourceStream, bool deleteStreamIfOpeningFails)
    {
        std::unique_ptr<juce::AudioFormatReader> p (
                Codec().createDecoderFor (MediaFormat::WMAVoice, sourceStream));

        if (p->bitsPerSample > 0)
            return p.release();

        if (! deleteStreamIfOpeningFails)
            p->input = nullptr;

        return nullptr;
    }

    //=================================================================
    /* Tries to create an object that can write to a stream with this audio format. */
    std::unique_ptr<juce::AudioFormatWriter> WMAVoiceAudioFormat::createWriterFor (
            std::unique_ptr<juce::OutputStream>& streamToWriteTo,
            const juce::AudioFormatWriterOptions& options)
    {
        UINT32 kbps = 0, chan = 0, rate = 0, bits = 0, vbrq = 0;

        rate = (UINT32) options.getSampleRate();
        chan = options.getNumChannels();
        bits = options.getBitsPerSample();

        switch (rate)
        {
            case 8000: kbps = 8; break;
            case 11025: kbps = 10; break;
            case 16000: kbps = 16; break;
            case 22050: kbps = 20; break;
            default:
                    DBGSTR("The specified sample rate is not supported.");
                    return nullptr;
        }

        switch (options.getQualityOptionIndex())
        {
            case 0: vbrq = 1; break;
            case 1: vbrq = 2; break;
            case 2: vbrq = 3; break;
            default:
                    DBGSTR("The specified quality option index is not supported.");
                    return nullptr;
        }

        std::unique_ptr<juce::AudioFormatWriter> p (
                Codec().createEncoderFor (MediaFormat::WMAVoice, streamToWriteTo, kbps, chan, rate, bits, vbrq));

        if (p && p->getBitsPerSample() > 0)
            return p;

        return nullptr;
    }

    //=================================================================
#endif
}
