/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

namespace mole {

#if JUCE_WINDOWS || DOXYGEN

    //==========================================================================
    /** Windows Media Foundation MP4 audio format.
     *
     * - AudioFormatReader: Read MP4, AAC and 3GP file formats.
     * - AudioFormatWriter: Write MP4 file format with AAC audio.
     */
    class MP4AudioFormat final : public juce::AudioFormat
    {
        //==========================================================================
        public:
            /* Constructor. */
            MP4AudioFormat() : AudioFormat ("MP4 file", {".mp4", ".aac", ".3gp"})
            {
            }

            /* Destructor. */
            ~MP4AudioFormat() override
            {
            }

            /* Returns a set of sample rates that the format can read and write. */
            juce::Array<int> getPossibleSampleRates() override
            {
                return { 44100, 48000 }; // encoder sample rates
            }

            /* Returns a set of bit depths that the format can read and write. */
            juce::Array<int> getPossibleBitDepths() override
            {
                return { 16, 32 }; // encoder 16, decoder 32 bits per sample
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
            bool isChannelLayoutSupported (const juce::AudioChannelSet& channelSet) override
            {
                if (channelSet == juce::AudioChannelSet::mono()) return true;
                if (channelSet == juce::AudioChannelSet::stereo()) return true;
                if (channelSet == juce::AudioChannelSet::create5point1()) return true;

                return false;
            }

            /** Returns a list of different qualities that can be used when writing.
             *
             * The following values are supported:
             * - (0) 12000 bytes per second (96 kilobits per second) total
             * - (1) 16000 bytes per second (128 kilobits per second) total
             * - (2) 20000 bytes per second (160 kilobits per second) total
             * - (3) 24000 bytes per second (192 kilobits per second) total
             * - (4) 12000 bytes per second (96 kilobits per second) per channel
             * - (5) 16000 bytes per second (128 kilobits per second) per channel
             * - (6) 20000 bytes per second (160 kilobits per second) per channel
             * - (7) 24000 bytes per second (192 kilobits per second) per channel
             */
            juce::StringArray getQualityOptions() override
            {
                return {
                    "0 - 96 kbps",
                    "1 - 128 kbps",
                    "2 - 160 kbps",
                    "3 - 192 kbps",
                    "4 - 96 kbps per channel",
                    "5 - 128 kbps per channel",
                    "6 - 160 kbps per channel",
                    "7 - 192 kbps per channel"
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

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MP4AudioFormat)
    };

    //==========================================================================
    /** @example Any2Mp4/Source/Main.cpp
     *
     * This sample demonstrates how to perform simple transcoding to MP4.
     */

#endif // JUCE_WINDOWS
} // namespace mole
