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
     * - AudioFormatReader: Reads MP4, AAC and 3GP file format.
     * - AudioFormatWriter: Writes MP4 file format with AAC audio.
     *
     * For infomation about supported bitrates, number of channels and sample
     * rates see [Audio Encoders](markdown/encoders.md).
     */
    class MP4AudioFormat final : public juce::AudioFormat
    {
        //==========================================================================
        public:
            /* Constructor. */
            MP4AudioFormat() : juce::AudioFormat ("Advanced Audio Coding", {".mp4", ".aac", ".3gp"})
            {
            }

            /* Destructor. */
            ~MP4AudioFormat() override
            {
            }

            /* Returns a set of sample rates that the format can read and write. */
            juce::Array<int> getPossibleSampleRates() override
            {
                return { 11025, 16000, 22050, 24000, 32000, 44100, 48000, 96000 };
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
             * - (0) 96 kbps for mono and stereo, 576 kbps for 5.1, 768 for 7.1
             * - (N) N kilobits per second
             *
             * Supported values for N: 8, 12, 16, 24, 32, 48, 64, 96, 128, 160,
             * 192, 256, 320, 480, 512, 576, 640, 720, 768, 960, 1152.
             */
            juce::StringArray getQualityOptions() override
            {
                return {
                    "0 - 96 kbps mono/stereo, 576 kbps 5.1, 768 kbps 7.1",
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

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MP4AudioFormat)
    };

    //==========================================================================
    /** @example Any2Mp4/Source/Main.cpp
     *
     * This sample demonstrates how to perform simple audio transcoding.
     */

    //==========================================================================
#endif
}
