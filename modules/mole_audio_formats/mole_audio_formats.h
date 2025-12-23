/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

//============================================================================
// BEGIN_JUCE_MODULE_DECLARATION
//
// ID:              mole_audio_formats
// vendor:          mole
// version:         1.0.0
// name:            MOLE audio file format codecs
// description:     Classes for reading and writing audio file formats.
// website:         https://perob.github.com
// license:         Mozilla Public License Version 2.0
//
// dependencies:    juce_core, juce_audio_basics, juce_audio_formats
// windowsLibs:     mf mfplat mfreadwrite mfuuid propsys
//
// END_JUCE_MODULE_DECLARATION
//============================================================================

#pragma once
#define MOLE_AUDIO_FORMATS_INCLUDED

#include <juce_core/juce_core.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_formats/juce_audio_formats.h>

#if JUCE_WINDOWS || DOXYGEN

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <mferror.h>
#include <propkey.h>
#include <propvarutil.h>
#include <shobjidl.h>

#include "native/System_windows.h"
#include "native/ShellMetadata_windows.h"
#include "native/ByteStream_windows.h"
#include "codecs/MP4AudioFormat.h"

#endif // JUCE_WINDOWS
