#pragma once

#include <windows.h>
#include <shobjidl.h>
#include <mfapi.h>
#include <mferror.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <wmcodecdsp.h>
#include <wmcontainer.h>
#include <propkey.h>
#include <propvarutil.h>
#include <codecapi.h>

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
