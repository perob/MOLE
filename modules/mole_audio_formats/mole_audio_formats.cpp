/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifdef MOLE_AUDIO_FORMATS_INCLUDED
#error "Incorrect usage of MOLE headers"
#endif

#define MOLE_MEDIAFOUNDATION_HEADERS 1
#include "mole_audio_formats.h"

#if JUCE_WINDOWS

// Prints string message with function/method name.
#define DBGSTR(s)    do { DBG(__FUNCTION__); DBG(s); } while(0)

// Prints HRESULT API error message with function/method name.
#define DBGAPI(hr)   do { DBG(__FUNCTION__); DBG(mole::Windows::APIError::toString(hr)); } while(0)

#include "native/ShellMetadata_windows.cpp"
#include "native/ByteStreamInput_windows.h"
#include "native/ByteStreamOutput_windows.h"
#include "native/ByteStream_windows.cpp"
#include "codecs/MP4AudioFormatReader.h"
#include "codecs/MP4AudioFormatWriter.h"
#include "codecs/MP4AudioFormat.cpp"

#endif // JUCE_WINDOWS
