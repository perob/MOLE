/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

namespace mole {

#if JUCE_WINDOWS || DOXYGEN

    //==========================================================================
    /** Windows Media Foundation MP2 audio format.
     *
     * - AudioFormatReader: Reads MPEG file format.
     * - AudioFormatWriter: Writes MPEG file format with MPEG Layer 2 audio.
     *
     * For infomation about supported bitrates, number of channels and sample
     * rates see [Audio Encoders](markdown/encoders.md).
     */
    class MP2AudioFormat final : public juce::AudioFormat
    {
        //==========================================================================
        public:
            /* Constructor. */
            MP2AudioFormat() : juce::AudioFormat ("MPEG Layer 2", {".mp2", ".mpa", ".mpg", ".mpeg"})
            {
            }

            /* Destructor. */
            ~MP2AudioFormat() override
            {
            }

            /* Returns a set of sample rates that the format can read and write. */
            juce::Array<int> getPossibleSampleRates() override
            {
                return { 16000, 22050, 24000, 32000, 44100, 48000 };
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
             * - (0) 192 kbps for mono, 224 kbps for stereo, 160 kbps for LSF (low sampling frequency)
             */
            juce::StringArray getQualityOptions() override
            {
                return {
                    "0 - 192 kbps mono, 224 kbps stereo, 160 kbps LSF",
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

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MP2AudioFormat)
    };

#endif // JUCE_WINDOWS
} // namespace mole
