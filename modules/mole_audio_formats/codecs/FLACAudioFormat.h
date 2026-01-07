/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

namespace mole {

#if JUCE_WINDOWS || DOXYGEN

    //==========================================================================
    /** Windows Media Foundation FLAC audio format.
     *
     * - AudioFormatReader: Reads FLAC file format.
     * - AudioFormatWriter: Writes MP4 file format with Free Lossless Audio Codec audio.
     *
     * For infomation about supported bitrates, number of channels and sample
     * rates see [Audio Encoders](markdown/encoders.md).
     *
     * Note that audio is written to MP4 file format.
     */
    class FLACAudioFormat final : public juce::AudioFormat
    {
        //==========================================================================
        public:
            /* Constructor. */
            FLACAudioFormat() : juce::AudioFormat ("Free Lossless Audio Codec", ".flac")
            {
            }

            /* Destructor. */
            ~FLACAudioFormat() override
            {
            }

            /* Returns a set of sample rates that the format can read and write. */
            juce::Array<int> getPossibleSampleRates() override
            {
                return { 44100, 48000, 88200, 96000, 176400, 192000 };
            }

            /* Returns a set of bit depths that the format can read and write. */
            juce::Array<int> getPossibleBitDepths() override
            {
                return { 8, 16, 24, 32 };
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
             * - (0) 8, 16 or 24 bit audio
             */
            juce::StringArray getQualityOptions() override
            {
                return {
                    "0 - 8, 16 or 24 bit audio"
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
            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FLACAudioFormat)
    };

#endif
}
