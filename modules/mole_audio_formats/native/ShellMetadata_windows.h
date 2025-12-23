/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

namespace mole {

#if JUCE_WINDOWS || DOXYGEN

    /** Read Windows shell properties from file.
     *
     *  @see [Metadata Properties for Media Files](markdown/metadata.md)
     */
    juce::StringPairArray readMetadataFromFile (const juce::String& filepath);

#endif // JUCE_WINDOWS
} // namespace mole
