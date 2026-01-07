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
    bool WMA9AudioFormat::isChannelLayoutSupported (const juce::AudioChannelSet& channelSet)
    {
        return isChannelTagSupported (FormatTag::WMA9, channelSet);
    }

    //=================================================================
    /* Tries to create an object that can read from a stream containing audio data in this format. */
    juce::AudioFormatReader* WMA9AudioFormat::createReaderFor (
            juce::InputStream* sourceStream, bool deleteStreamIfOpeningFails)
    {
        std::unique_ptr<juce::AudioFormatReader> p (
                Codec().createDecoderFor (MediaFormat::WMA9, sourceStream));

        if (p->bitsPerSample > 0)
            return p.release();

        if (! deleteStreamIfOpeningFails)
            p->input = nullptr;

        return nullptr;
    }

    //=================================================================
    /* Tries to create an object that can write to a stream with this audio format. */
    std::unique_ptr<juce::AudioFormatWriter> WMA9AudioFormat::createWriterFor (
            std::unique_ptr<juce::OutputStream>& streamToWriteTo,
            const juce::AudioFormatWriterOptions& options)
    {
        UINT32 kbps = 0, chan = 0, rate = 0, bits = 0, vbrq = 0;

        rate = (UINT32) options.getSampleRate();
        chan = options.getNumChannels();
        bits = options.getBitsPerSample();

        switch (options.getQualityOptionIndex())
        {
#if 0
            case 0: vbrq = 75; kbps = (chan == 2) ? 192 : (rate == 44100) ? 320 : 256; break;

            case 10: vbrq = 10; kbps = (chan == 2) ? 64 : 128; break;
            case 25: vbrq = 25; kbps = (chan == 2) ? 96 : 192; break;
            case 50: vbrq = 50; kbps = (chan == 2) ? 128 : 256; break;
            case 75: vbrq = 75; kbps = (chan == 2) ? 192 : (rate == 44100) ? 320 : 256; break;
            case 90: vbrq = 90; kbps = (chan == 2) ? 256 : 384; break;
            case 98: vbrq = 98; kbps = 384; break;
#else
            case 0: kbps = 96 * chan; break;
#endif
            case 32: case 48: case 64: case 80: case 96:
            case 128: case 160: case 192: case 256: case 320:
            case 384: case 440: case 640: case 768:
                kbps = options.getQualityOptionIndex();
                break;

            default:
                DBGSTR("The specified quality option index is not supported.");
                return nullptr;
        }

#if 0
        if (vbrq > 0 && chan != 2 && chan != 6)
        {
            DBGSTR("The specified VBR quality and number of channels are not supported.");
            return nullptr;
        }
#endif

        std::unique_ptr<juce::AudioFormatWriter> p (
                Codec().createEncoderFor (MediaFormat::WMA9, streamToWriteTo, kbps, chan, rate, bits, vbrq));

        if (p && p->getBitsPerSample() > 0)
            return p;

        return nullptr;
    }

    //=================================================================
#endif
}
