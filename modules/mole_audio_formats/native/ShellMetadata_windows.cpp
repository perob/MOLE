/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

namespace mole {

#if JUCE_WINDOWS

    using namespace mole::Windows;

    namespace {
        //============================================================================
        // Get property from property store.
        template<typename T> void GetProperty (IPropertyStore* propStore, PROPERTYKEY key,
                const char* s, juce::StringPairArray& metadata)
        {
            UINT32 value = 0; // default typename UINT32
            PROPVARIANT prop;
            PropVariantInit (&prop);

            HRESULT hr = propStore->GetValue (key, &prop);
            if (SUCCEEDED (hr)) hr = PropVariantToUInt32 (prop, &value);

            if (value > 0 && SUCCEEDED (hr))
                metadata.set (s, juce::String (value));

            ::PropVariantClear (&prop);
        }

        //============================================================================
        template<> void GetProperty<UINT64> (IPropertyStore* propStore, PROPERTYKEY key,
                const char* s, juce::StringPairArray& metadata)
        {
            UINT64 value = 0;
            PROPVARIANT prop;
            PropVariantInit (&prop);

            HRESULT hr = propStore->GetValue (key, &prop);
            if (SUCCEEDED (hr)) hr = PropVariantToUInt64 (prop, &value);

            if (value > 0 && SUCCEEDED (hr))
                metadata.set (s, juce::String (value));

            ::PropVariantClear (&prop);
        }

        //============================================================================
        template<> void GetProperty<LPWSTR> (IPropertyStore* propStore, PROPERTYKEY key,
                const char* s, juce::StringPairArray& metadata)
        {
            WCHAR value[80];
            PROPVARIANT prop;
            PropVariantInit (&prop);

            HRESULT hr = propStore->GetValue (key, &prop);
            if (SUCCEEDED (hr)) hr = PropVariantToString (prop, value, 80);

            if (value[0] != '\0' && SUCCEEDED (hr))
                metadata.set (s, juce::String (value));

            ::PropVariantClear (&prop);
        }

        //============================================================================
        template<> void GetProperty<FILETIME> (IPropertyStore* propStore, PROPERTYKEY key,
                const char* s, juce::StringPairArray& metadata)
        {
            FILETIME fileTime;
            DWORD flags = FDTF_DEFAULT;
            PROPVARIANT prop;
            PropVariantInit (&prop);

            HRESULT hr = propStore->GetValue (key, &prop);
            if (SUCCEEDED (hr)) hr = PropVariantToFileTime (prop, PSTF_LOCAL, &fileTime);

            if (SUCCEEDED (hr))
            {
                WCHAR value[80];

                const int len = ::SHFormatDateTimeW (&fileTime, &flags, value, 80);

                if (len > 0)
                    metadata.set (s, juce::String (value));
            }

            ::PropVariantClear (&prop);
        }
    } // namespace

    //==============================================================================
    // Windows shell properties
    juce::StringPairArray readMetadataFromFile (const juce::String& filepath)
    {
        juce::StringPairArray metadata;
        IPropertyStore* propStore = nullptr;

        HRESULT hr = ::SHGetPropertyStoreFromParsingName (filepath.toUTF16(), nullptr,
                GPS_HANDLERPROPERTIESONLY, __uuidof (IPropertyStore), (void**)&propStore);

        // TODO Refactor (IPropertyStore: GetCount(), GetAt(), GetValue()).
        if (SUCCEEDED (hr))
        {
#define GETPROPERTY(type,name) GetProperty<type> (propStore, name, #name, metadata)

            // Common Media Properties
            GETPROPERTY(LPWSTR, MFPKEY_Content_DLNA_Profile_ID);
            GETPROPERTY(UINT32, PKEY_Audio_ChannelCount);
            GETPROPERTY(UINT32, PKEY_Audio_EncodingBitrate);
            GETPROPERTY(LPWSTR, PKEY_Audio_Format);
            GETPROPERTY(BOOL, PKEY_Audio_IsVariableBitRate);
            GETPROPERTY(UINT32, PKEY_Audio_PeakValue);
            GETPROPERTY(UINT32, PKEY_Audio_SampleRate);
            GETPROPERTY(UINT32, PKEY_Audio_SampleSize);
            GETPROPERTY(UINT32, PKEY_Audio_StreamNumber);
            GETPROPERTY(LPWSTR, PKEY_Author);
            GETPROPERTY(LPWSTR, PKEY_Comment);
            GETPROPERTY(LPWSTR, PKEY_Copyright);
            GETPROPERTY(BOOL, PKEY_DRM_IsProtected);
            GETPROPERTY(LPWSTR, PKEY_Keywords);
            GETPROPERTY(LPWSTR, PKEY_Language);
            GETPROPERTY(LPWSTR, PKEY_Media_AuthorUrl);
            GETPROPERTY(UINT32, PKEY_Media_AverageLevel);
            GETPROPERTY(LPWSTR, PKEY_Media_ClassPrimaryID);
            GETPROPERTY(LPWSTR, PKEY_Media_ClassSecondaryID);
            GETPROPERTY(LPWSTR, PKEY_Media_CollectionGroupID);
            GETPROPERTY(LPWSTR, PKEY_Media_CollectionID);
            GETPROPERTY(LPWSTR, PKEY_Media_ContentDistributor);
            GETPROPERTY(LPWSTR, PKEY_Media_ContentID);
            GETPROPERTY(FILETIME, PKEY_Media_DateEncoded);
            GETPROPERTY(LPWSTR, PKEY_Media_DateReleased);
            GETPROPERTY(UINT64, PKEY_Media_Duration);
            GETPROPERTY(LPWSTR, PKEY_Media_DVDID);
            GETPROPERTY(LPWSTR, PKEY_Media_EncodedBy);
            GETPROPERTY(LPWSTR, PKEY_Media_EncodingSettings);
            GETPROPERTY(LPWSTR, PKEY_Media_MCDI);
            GETPROPERTY(LPWSTR, PKEY_Media_MetadataContentProvider);
            GETPROPERTY(LPWSTR, PKEY_Media_Producer);
            GETPROPERTY(LPWSTR, PKEY_Media_PromotionUrl);
            GETPROPERTY(LPWSTR, PKEY_Media_ProviderRating);
            GETPROPERTY(LPWSTR, PKEY_Media_ProviderStyle);
            GETPROPERTY(LPWSTR, PKEY_Media_Publisher);
            GETPROPERTY(LPWSTR, PKEY_Media_SubTitle);
            GETPROPERTY(LPWSTR, PKEY_Media_UniqueFileIdentifier);
            GETPROPERTY(LPWSTR, PKEY_Media_Writer);
            GETPROPERTY(UINT32, PKEY_Media_Year);
            GETPROPERTY(LPWSTR, PKEY_Music_AlbumArtist);
            GETPROPERTY(LPWSTR, PKEY_Music_AlbumTitle);
            GETPROPERTY(LPWSTR, PKEY_Music_Artist);
            GETPROPERTY(LPWSTR, PKEY_Music_BeatsPerMinute);
            GETPROPERTY(LPWSTR, PKEY_Music_Composer);
            GETPROPERTY(LPWSTR, PKEY_Music_Conductor);
            GETPROPERTY(LPWSTR, PKEY_Music_ContentGroupDescription);
            GETPROPERTY(LPWSTR, PKEY_Music_Genre);
            GETPROPERTY(LPWSTR, PKEY_Music_InitialKey);
            GETPROPERTY(BOOL, PKEY_Music_IsCompilation);
            GETPROPERTY(LPWSTR, PKEY_Music_Lyrics);
            GETPROPERTY(LPWSTR, PKEY_Music_Mood);
            GETPROPERTY(LPWSTR, PKEY_Music_PartOfSet);
            GETPROPERTY(LPWSTR, PKEY_Music_Period);
            GETPROPERTY(UINT32, PKEY_Music_TrackNumber);
            GETPROPERTY(LPWSTR, PKEY_ParentalRating);
            GETPROPERTY(LPWSTR, PKEY_ParentalRatingReason);
            GETPROPERTY(UINT32, PKEY_Rating);
            //GETPROPERTY(VT_STREAM, PKEY_ThumbnailStream);
            GETPROPERTY(LPWSTR, PKEY_Title);
            GETPROPERTY(LPWSTR, PKEY_Video_Compression);
            GETPROPERTY(LPWSTR, PKEY_Video_Director);
            GETPROPERTY(UINT32, PKEY_Video_EncodingBitrate);
            GETPROPERTY(UINT32, PKEY_Video_FourCC);
            GETPROPERTY(UINT32, PKEY_Video_FrameHeight);
            GETPROPERTY(UINT32, PKEY_Video_FrameRate);
            GETPROPERTY(UINT32, PKEY_Video_FrameWidth);
            GETPROPERTY(UINT32, PKEY_Video_HorizontalAspectRatio);
            GETPROPERTY(BOOL, PKEY_Video_IsStereo);
            GETPROPERTY(UINT32, PKEY_Video_StreamNumber);
            GETPROPERTY(UINT32, PKEY_Video_TotalBitrate);
            GETPROPERTY(UINT32, PKEY_Video_VerticalAspectRatio);
#undef GETPROPERTY
        }
        else
        {
            DBGAPI(hr);
        }

        SafeRelease (&propStore);

        return metadata;
    }

#endif // JUCE_WINDOWS
} // namespace mole
