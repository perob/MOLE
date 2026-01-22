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
        /** Audio codec.  */
        class WMATransform
        {
            MediaFormat mediaFormat;

            COMLibrary library;
            MFPlatform platform;

            IMFTransform* transform = nullptr;

            DWORD inputStreamID = 0;
            DWORD outputStreamID = 0;

            public:

            //=============================================================================
            WMATransform();
            ~WMATransform();

            /** Create audio encoder for audio format.  */
            juce::AudioFormatWriter* createSinkFor (
                    const MediaFormat& format, std::unique_ptr<juce::OutputStream>& stream,
                    UINT32 vbrq, UINT32 chan, UINT32 rate, UINT32 bits);

            private:

            //=============================================================================
            /** Configure encoder.
             *
             * Initialize encoder for audio format and configure input and
             * output media type from audio attributes.
             */
            HRESULT configureEncoder (UINT32 vbrq, UINT32 chan, UINT32 rate, UINT32 bits);

            //=============================================================================
            HRESULT setProperties (UINT32 vbrQuality);
            HRESULT setMediaType (UINT32 chan, UINT32 rate, UINT32 bits);

            //=============================================================================
            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WMATransform)
        };

        //=============================================================================
    }
#endif
}
