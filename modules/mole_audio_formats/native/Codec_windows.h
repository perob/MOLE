/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

namespace mole {

#if JUCE_WINDOWS || DOXYGEN

    namespace WindowsMediaFoundation {

        using namespace mole::Windows;

        //=============================================================================
        /** Available audio codecs.  */
        enum FormatTag
        {
            None        = 0,
            AAC         = 1,    ///< Advanced Audio Coding
            AC3         = 2,    ///< Dolby Digital Audio
            FLAC        = 4,    ///< Free Lossless Audio Codec
            Float       = 8,    ///< Uncompressed IEEE floating point audio
            MP1         = 16,   ///< MPEG Layer 1 audio
            MP2         = 32,   ///< MPEG Layer 2 audio
            MP3         = 64,   ///< MPEG Layer 3 audio
            PCM         = 128,  ///< Uncompressed PCM audio
            WMA8        = 256,  ///< Windows Media Audio 8
            WMA9        = 512,  ///< Windows Media Audio 9
            WMALossless = 1024, ///< Windows Media Audio Lossless
            WMAVoice    = 2048  ///< Windows Media Audio Voice
        };

        //=============================================================================
        /** Returns true if the codec supports an audio channel set.  */
        bool isChannelTagSupported (FormatTag formatTag, const juce::AudioChannelSet& channelSet);

        //=============================================================================
        /** Describes audio media format.  */
        struct MediaFormat
        {
            FormatTag tag = FormatTag::None;
            GUID guid = GUID_NULL;
            GUID container = GUID_NULL;
            juce::String name;
            juce::String mimeType;
            juce::StringArray fileExtensions;

            //=============================================================================
            MediaFormat() = default;

            MediaFormat (FormatTag t, REFGUID g, REFGUID c, const char* n, const char* mt, std::initializer_list<const char*> fe)
                : tag(t), guid(g), container(c), name(n), mimeType(mt), fileExtensions(fe)
            {
            }

            ~MediaFormat() = default;

            //=============================================================================
            const char* toUTF8() const { return name.toRawUTF8(); }
            juce::String toString() const { return name; }

            bool isEqual (FormatTag other) const { return tag == other; }
            bool isEqual (REFGUID other) const { return ::IsEqualGUID (guid, other); }

            bool isAAC() const { return tag == FormatTag::AAC; }
            bool isAC3() const { return tag == FormatTag::AC3; }
            bool isFLAC() const { return tag == FormatTag::FLAC; }
            bool isMP1() const { return tag == FormatTag::MP1; }
            bool isMP2() const { return tag == FormatTag::MP2; }
            bool isMP3() const { return tag == FormatTag::MP3; }
            bool isWMA8() const { return tag == FormatTag::WMA8; }
            bool isWMA9() const { return tag == FormatTag::WMA9; }
            bool isWMALossless() const { return tag == FormatTag::WMALossless; }
            bool isWMAVoice() const { return tag == FormatTag::WMAVoice; }

            bool isPCM() const { return tag == FormatTag::PCM; }
            bool isFLOAT() const { return tag == FormatTag::Float; }

            bool isLossless() const { return isFLAC() || isWMALossless(); }

            bool isWMA8orWMA9() const { return isWMA8() || isWMA9(); }
            bool isWMA8orWMA9orWMALossless() const { return isWMA8orWMA9() || isWMALossless(); }
            bool isWMA() const { return isWMA8orWMA9orWMALossless() || isWMAVoice(); }

            //=============================================================================
            static const MediaFormat AAC;
            static const MediaFormat AC3;
            static const MediaFormat FLAC;
            static const MediaFormat Float;
            static const MediaFormat MP1;
            static const MediaFormat MP2;
            static const MediaFormat MP3;
            static const MediaFormat PCM;
            static const MediaFormat WMA8;
            static const MediaFormat WMA9;
            static const MediaFormat WMALossless;
            static const MediaFormat WMAVoice;
        };

        //=============================================================================
        /** Set MPEG properties on IMFTransform codec API.  */
        struct MPEGCodec
        {
            static HRESULT setMPEGLayer1 (IMFSinkWriter* sinkWriter, DWORD streamIndex);
        };

        //=============================================================================
        /** Audio codec.  */
        class Codec
        {
            MediaFormat format;

            COMLibrary library;
            MFPlatform platform;

            IMFTransform* transform = nullptr;
            IMFMediaType* inputMediaType = nullptr;
            IMFMediaType* outputMediaType = nullptr;
            DWORD inputStreamID = 0;
            DWORD outputStreamID = 0;

            public:

            //=============================================================================
            Codec();
            ~Codec();

            /** Create audio decoder for audio media format.  */
            juce::AudioFormatReader* createDecoderFor (const MediaFormat& mediaFormat, juce::InputStream* stream);

            /** Create audio encoder for audio media format.  */
            juce::AudioFormatWriter* createEncoderFor (const MediaFormat& mediaFormat,
                    std::unique_ptr<juce::OutputStream>& stream,
                    UINT32 kbps, UINT32 chan, UINT32 rate, UINT32 bits);

            private:

            //=============================================================================
            /** Configure encoder.
             *
             * Initialize encoder from media format and configure input and
             * output media type from audio attributes.
             */
            HRESULT configureEncoder (UINT32 kbps, UINT32 chan, UINT32 rate, UINT32 bits);

            //=============================================================================
            HRESULT initEncoder();

            //=============================================================================
            HRESULT findInputMediaType (UINT32 chan, UINT32 rate, UINT32 bits);
            HRESULT findOutputMediaType (UINT32 kbps, UINT32 chan, UINT32 rate, UINT32 bits);

            //=============================================================================
            HRESULT setWMAProperties();

            //=============================================================================
            IMFMediaType* cloneMediaType (IMFMediaType* source);
            IMFMediaType* getInputMediaType();
            IMFMediaType* getOutputMediaType();

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Codec)
        };

        //=============================================================================
    }
#endif
}
