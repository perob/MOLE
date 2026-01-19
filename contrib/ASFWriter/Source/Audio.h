/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

//=====================================================================
/** The OpenAudioFile function should open the media file specified by URL
 * and return a pointer to a media type that describes an audio stream.
 */
HRESULT OpenAudioFile (PCWSTR url, IMFMediaType** mediaType);

//=====================================================================
HRESULT CloseAudioFile();

//=====================================================================
/** The GetNextAudioSample function should read uncompressed PCM audio from the
 * file that was opened by OpenAudioFile. When the end of the file is reached,
 * EOS receives the value TRUE. Otherwise, ppSample receives a media sample
 * that contains the audio buffer.
 */
HRESULT GetNextAudioSample (BOOL& eos, IMFSample** sample);

//=====================================================================
