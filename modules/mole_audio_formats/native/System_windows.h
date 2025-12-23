/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

namespace mole {

#if JUCE_WINDOWS || DOXYGEN

    namespace Windows {

        //===========================================================================
        /** Release COM interface pointer.  */
        template<typename T> void SafeRelease (T** p)
        {
            if (*p != nullptr)
            {
                (*p)->Release();
                *p = nullptr;
            }
        }

        //===========================================================================
        /** Prints debug message and returns "Not implemented" error.  */
        inline HRESULT NotImplemented ([[maybe_unused]] const char* msg) { DBG (msg); return E_NOTIMPL; }

        //===========================================================================
        /** Creates an absolute or full path name for the specified relative path name.  */
        inline juce::String GetFullpath (const juce::String& relativePath)
        {
            wchar_t absolutePath[MAX_PATH];
            return juce::String (::_wfullpath (absolutePath, relativePath.toUTF16(), MAX_PATH));
        }

        //===========================================================================
        /** Creates string from the Windows API errors.  */
        struct APIError final
        {
            /** Returns string from the GetLastError() error code.  */
            static juce::String toString()
            {
                return toString (HRESULT_FROM_WIN32 (::GetLastError()));
            }

            /** Returns string from the HRESULT error code.  */
            static juce::String toString (HRESULT hr)
            {
                char errorString[256];

                const DWORD length = ::FormatMessageA (FORMAT_MESSAGE_FROM_SYSTEM,
                        nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), errorString, 256, nullptr);

                if (length > 0)
                {
                    for (DWORD pos = length - 1; pos >= 0; --pos)
                    {
                        const char c = errorString[pos];

                        if (c == '\n' || c == '\r')
                            errorString[pos] = '\0';
                        else
                            break;
                    }

                    return juce::String (errorString);
                }

                return juce::String();
            }
        };

        //===========================================================================
        /** Initialize the Windows COM library.  */
        class COMLibrary final
        {
            HRESULT hr = E_HANDLE;

            public:

            COMLibrary() = default;

            ~COMLibrary()
            {
                if (SUCCEEDED (hr)) ::CoUninitialize();
            }

            /** Initialize with default settings (InitializeSTA).  */
            HRESULT Initialize()
            {
                return InitializeSTA();
            }

            /** Initialize with 'apartmentthreaded' and 'disable ole1dde'.  */
            HRESULT InitializeSTA()
            {
                if (hr == E_HANDLE)
                    hr = ::CoInitializeEx (nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

                return hr;
            }

            /** Initialize with 'multithreaded' and 'disable ole1dde'.  */
            HRESULT InitializeMTA()
            {
                if (hr == E_HANDLE)
                    hr = ::CoInitializeEx (nullptr, COINIT_MULTITHREADED | COINIT_DISABLE_OLE1DDE);

                return hr;
            }
        };

        //===========================================================================
        /** Intialize the Windows Media Foundation platform.  */
        class MFPlatform final
        {
            HRESULT hr = E_HANDLE;

            public:

            MFPlatform() = default;

            ~MFPlatform()
            {
                if (SUCCEEDED (hr)) ::MFShutdown();
            }

            /** Initialize with default settings.  */
            HRESULT Initialize()
            {
                if (hr == E_HANDLE)
                    hr = ::MFStartup (MF_VERSION);

                return hr;
            }

            /** Initialize with lite settings (without sockets library).  */
            HRESULT InitializeLITE()
            {
                if (hr == E_HANDLE)
                    hr = ::MFStartup (MF_VERSION, MFSTARTUP_LITE);

                return hr;
            }
        };
    } // namespace Windows

#endif // JUCE_WINDOWS
} // namespace mole
