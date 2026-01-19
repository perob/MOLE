/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

//=====================================================================
HRESULT SetBOOL (IPropertyStore* store, PROPERTYKEY key, BOOL value);
HRESULT SetINT32 (IPropertyStore* store, PROPERTYKEY key, INT32 value);
HRESULT SetUINT32 (IPropertyStore* store, PROPERTYKEY key, UINT32 value);

//=====================================================================
HRESULT CopyValue (IPropertyStore* src, IPropertyStore* dst, PROPERTYKEY key);

//=====================================================================
