/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

namespace mole {

#if JUCE_WINDOWS || DOXYGEN

    //==========================================================================
    /** Windows Media Foundation WMA 8 audio format.
     *
     * - AudioFormatReader: Reads WMA file format.
     * - AudioFormatWriter: Writes WMA file format with Windows Media Audio 8 audio.
     *
     * For infomation about supported bitrates, number of channels and sample
     * rates see [Audio Encoders](markdown/encoders.md).
     */
    class WMA8AudioFormat final : public juce::AudioFormat
    {
        //==========================================================================
        public:
            /* Constructor. */
            WMA8AudioFormat() : juce::AudioFormat ("Windows Media Audio 8", {".wma", ".wmv"})
            {
            }

            /* Destructor. */
            ~WMA8AudioFormat() override
            {
            }

            /* Returns a set of sample rates that the format can read and write. */
            juce::Array<int> getPossibleSampleRates() override
            {
                return { 8000, 11025, 16000, 22050, 32000, 44100, 48000 };
            }

            /* Returns a set of bit depths that the format can read and write. */
            juce::Array<int> getPossibleBitDepths() override
            {
                return { 16, 32 };
            }

            /* Returns true if the format can do 2-channel audio. */
            bool canDoStereo() override
            {
                return true;
            }

            /* Returns true if the format can do 1-channel audio. */
            bool canDoMono() override
            {
                return true;
            }

            /* Returns true if the format uses compressed data. */
            bool isCompressed() override
            {
                return true;
            }

            /* Returns true if the channel layout is supported by this format. */
            bool isChannelLayoutSupported (const juce::AudioChannelSet& channelSet) override;

            /** Returns a list of different qualities that can be used when writing.
             *
             * The following values are supported:
             * - (0) 96 kbps per channel
             * - (N) N kbps
             *
             * Supported values for N: 8, 10, 12, 16, 20, 22, 24, 32, 40, 48,
             * 64, 80, 96, 128, 160, 192, 256, 320.
             */
            juce::StringArray getQualityOptions() override
            {
                return {
                    "0 - 96 kbps per channel",
                    "N - N kbps"
                };
            }

            /* Tries to create an object that can read from a stream containing audio data in this format.  */
            juce::AudioFormatReader* createReaderFor (
                    juce::InputStream* sourceStream, bool deleteStreamIfOpeningFails) override;

            /* Attempts to create a MemoryMappedAudioFormatReader, if possible for this format. */
            juce::MemoryMappedAudioFormatReader* createMemoryMappedReader (const juce::File& /*file*/) override
            {
                return nullptr;
            }

            /* Attempts to create a MemoryMappedAudioFormatReader, if possible for this format. */
            juce::MemoryMappedAudioFormatReader* createMemoryMappedReader (juce::FileInputStream* /*fin*/) override
            {
                return nullptr;
            }

            /* Tries to create an object that can write to a stream with this audio format. */
            std::unique_ptr<juce::AudioFormatWriter> createWriterFor (
                    std::unique_ptr<juce::OutputStream>& streamToWriteTo,
                    const juce::AudioFormatWriterOptions& options) override;

        private:
            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WMA8AudioFormat)
    };

#endif // JUCE_WINDOWS
} // namespace mole
