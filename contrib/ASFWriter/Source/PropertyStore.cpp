/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <JuceHeader.h>

#include "Platform.h"

//=====================================================================
HRESULT SetBOOL (IPropertyStore* store, PROPERTYKEY key, BOOL value)
{
    PROPVARIANT prop;
    ::InitPropVariantFromBoolean (value, &prop);
    HRESULT hr = store->SetValue (key, prop);
    ::PropVariantClear (&prop);
    return hr;
}

//=====================================================================
HRESULT SetINT32 (IPropertyStore* store, PROPERTYKEY key, INT32 value)
{
    PROPVARIANT prop;
    ::InitPropVariantFromInt32 (value, &prop);
    HRESULT hr = store->SetValue (key, prop);
    ::PropVariantClear (&prop);
    return hr;
}

//=====================================================================
HRESULT SetUINT32 (IPropertyStore* store, PROPERTYKEY key, UINT32 value)
{
    PROPVARIANT prop;
    ::InitPropVariantFromUInt32 (value, &prop);
    HRESULT hr = store->SetValue (key, prop);
    ::PropVariantClear (&prop);
    return hr;
}

//=====================================================================
HRESULT CopyValue (IPropertyStore* src, IPropertyStore* dst, PROPERTYKEY key)
{
    PROPVARIANT prop;
    PropVariantInit (&prop);
    HRESULT hr = src->GetValue (key, &prop);
    if (SUCCEEDED (hr)) hr = dst->SetValue (key, prop);
    ::PropVariantClear (&prop);
    return hr;
}

//=====================================================================
