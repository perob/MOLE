/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

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

#define DBGSTR(s) do { DBG(__FUNCTION__); DBG(s); } while(0)

#define DBGAPI(h) do { DBG(__FUNCTION__); DBG(APIError::toString(h)); } while(0)

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
