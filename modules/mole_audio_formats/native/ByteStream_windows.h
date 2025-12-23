/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

namespace mole {

#if JUCE_WINDOWS || DOXYGEN

    namespace WindowsMediaFoundation {

        /** Create IMFByteStream instance or null pointer.
         *
         * @param p Receives a pointer to the IMFByteStream interface. The caller must release the interface.
         * @param stream Stream to read from. The caller must delete the stream.
         * @param mimeType Specifies the MIME type of a byte stream ("audio/mp4", "audio/aac").
         * @param originName Specifies the original file/URL for a byte stream.
         * @param usingNetwork Specifies if the byte stream is using a network source.
         */
        HRESULT ByteStreamFromInputStream (IMFByteStream** p, juce::InputStream* stream,
                const wchar_t* mimeType = nullptr,
                const wchar_t* originName = nullptr,
                bool usingNetwork = false);

        /** Create IMFByteStream instance or null pointer.
         *
         * @param p Receives a pointer to the IMFByteStream interface. The caller must release the interface.
         * @param stream Stream to write to. The caller must delete the stream.
         * @param mimeType Specifies the MIME type of a byte stream ("audio/mp4", "audio/aac").
         * @param originName Specifies the original file/URL for a byte stream.
         * @param usingNetwork Specifies if the byte stream is using a network source.
         */
        HRESULT ByteStreamFromOutputStream (IMFByteStream** p, juce::OutputStream* stream,
                const wchar_t* mimeType = nullptr,
                const wchar_t* originName = nullptr,
                bool usingNetwork = false);

    } // namespace WindowsMediaFoundation

#endif // JUCE_WINDOWS
} // namespace mole
