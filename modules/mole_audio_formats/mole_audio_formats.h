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
// version:         2.0.0
// name:            MOLE audio file format codecs
// description:     Classes for reading and writing audio file formats.
// website:         https://perob.github.com
// license:         Mozilla Public License Version 2.0
//
// dependencies:    juce_core, juce_audio_basics, juce_audio_formats
// windowsLibs:     mf mfplat mfreadwrite mfuuid propsys strmiids
//
// END_JUCE_MODULE_DECLARATION
//============================================================================

#pragma once
#define MOLE_AUDIO_FORMATS_INCLUDED

#include <juce_core/juce_core.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_formats/juce_audio_formats.h>

#if JUCE_WINDOWS || DOXYGEN

/** Config: MOLE_MEDIAFOUNDATION_HEADERS
 
  Include Media Foundation headers and helper classes.
  */
#ifndef MOLE_MEDIAFOUNDATION_HEADERS
#define MOLE_MEDIAFOUNDATION_HEADERS 0
#endif

#if MOLE_MEDIAFOUNDATION_HEADERS
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <mferror.h>
#include <propkey.h>
#include <propvarutil.h>
#include <shobjidl.h>
#include <wmcodecdsp.h>
#include <codecapi.h>

#include "native/System_windows.h"
#include "native/ByteStream_windows.h"
#include "native/Codec_windows.h"
#endif

#include "native/ShellMetadata_windows.h"
#include "codecs/AC3AudioFormat.h"
#include "codecs/FLACAudioFormat.h"
#include "codecs/MP1AudioFormat.h"
#include "codecs/MP2AudioFormat.h"
#include "codecs/MP3AudioFormat.h"
#include "codecs/MP4AudioFormat.h"
#include "codecs/WMA8AudioFormat.h"
#include "codecs/WMA9AudioFormat.h"
#include "codecs/WMALosslessAudioFormat.h"
#include "codecs/WMAVoiceAudioFormat.h"

#endif // JUCE_WINDOWS
