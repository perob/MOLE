/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

namespace mole {

#if JUCE_WINDOWS

    namespace WindowsMediaFoundation {

        /* Creates IMFByteStream instance or null pointer.  */
        HRESULT ByteStreamFromInputStream (IMFByteStream** p, juce::InputStream* stream,
                const wchar_t* mimeType, const wchar_t* originName, bool usingNetwork)
        {
            if (stream != nullptr)
            {
                *p = new (std::nothrow) InputByteStream (stream, mimeType, originName, usingNetwork);
                return (*p != nullptr) ? S_OK : E_OUTOFMEMORY;
            }

            *p = nullptr;
            return E_INVALIDARG;
        }

        /* Creates IMFByteStream instance or null pointer.  */
        HRESULT ByteStreamFromOutputStream (IMFByteStream** p, juce::OutputStream* stream,
                const wchar_t* mimeType, const wchar_t* originName, bool usingNetwork)
        {
            if (stream != nullptr)
            {
                *p = new (std::nothrow) OutputByteStream (stream, mimeType, originName, usingNetwork);
                return (*p != nullptr) ? S_OK : E_OUTOFMEMORY;
            }

            *p = nullptr;
            return E_POINTER;
        }
    } // namespace WindowsMediaFoundation

#endif // JUCE_WINDOWS
} // namespace mole
