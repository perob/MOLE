# Metadata Properties for Media Files

## Common Media Properties

The Shell property system defines a set of common metadata properties for all
types of shell objects. A subset of these are applicable to media files. The
following table lists the most common Shell properties for media. Media files
might support additional properties not listed here. Also, not every file
format supports every property listed. For a complete list of Shell properties,
see Shell Properties.

| PROPERTYKEY | Description |
|-------------|-------------|
| `MFPKEY_Content_DLNA_Profile_ID` 	| Digital Living Network Alliance (DLNA) profile identifier. |
| `PKEY_Audio_ChannelCount` 	| Number of audio channels. |
| `PKEY_Audio_EncodingBitrate` 	| Average audio bit rate, in bits per second. |
| `PKEY_Audio_Format` 	| Audio subtype (`MF_MT_SUBTYPE`) expressed as a string. |
| `PKEY_Audio_IsVariableBitRate` 	| Indicates whether the audio stream uses variable bit-rate encoding. |
| `PKEY_Audio_PeakValue` 	| Peak volume level of audio content. |
| `PKEY_Audio_SampleRate` 	| Audio sample rate in samples per second. Equivalent to the `MF_MT_AUDIO_SAMPLES_PER_SECOND` attribute in the media type. |
| `PKEY_Audio_SampleSize` 	| Number of bits per audio sample. Equivalent to the `MF_MT_AUDIO_BITS_PER_SAMPLE` attribute in the media type. |
| `PKEY_Audio_StreamNumber` 	| Identifier of the audio stream. |
| `PKEY_Author` 	| Author. |
| `PKEY_Comment` 	| A comment attached to a file, typically added by a user. |
| `PKEY_Copyright` 	| Copyright information. |
| `PKEY_DRM_IsProtected` 	| Indicates whether the content is protected using digital rights management (DRM). |
| `PKEY_Keywords` 	| Keywords. |
| `PKEY_Language` 	| Language. |
| `PKEY_Media_AuthorUrl` 	| URL of the author's website. |
| `PKEY_Media_AverageLevel` 	| Average volume level of audio content. |
| `PKEY_Media_ClassPrimaryID` 	| The string representation of a GUID that identifies the primary class of media. For valid values, see the documentation for the WM/MediaClassPrimaryID attribute. |
| `PKEY_Media_ClassSecondaryID` 	| The string representation of a GUID that identifies the secondary class of media. For valid values, see the documentation for the WM/MediaClassSecondaryID attribute. |
| `PKEY_Media_CollectionGroupID` 	| The string representation of a GUID that identifies the collection group. |
| `PKEY_Media_CollectionID` 	| The string representation of a GUID that identifies the collection. |
| `PKEY_Media_ContentDistributor` 	| Distributor of the content. |
| `PKEY_Media_ContentID` 	| The string representation of a GUID that identifies the collection. |
| `PKEY_Media_DateEncoded` 	| Time when the content was encoded. |
| `PKEY_Media_DateReleased` 	| Original release date. |
| `PKEY_Media_Duration` 	| Duration, in 100-nanosecond units. Equivalent to the MF_PD_DURATION attribute in the presentation descriptor. |
| `PKEY_Media_DVDID` 	| Digital video disc identifier (DVDID). |
| `PKEY_Media_EncodedBy` 	| Name of the person or group that encoded the content. |
| `PKEY_Media_EncodingSettings` 	| Description of the settings used to encode the content. |
| `PKEY_Media_MCDI` 	| Music CD identifier. This value is used to identify a CD. |
| `PKEY_Media_MetadataContentProvider` 	| Name of the metadata content provider. (For example, metadata might be provided by a commercial service.) |
| `PKEY_Media_Producer` 	| Name of the producer of the content. |
| `PKEY_Media_PromotionUrl` 	| URL of a website offering a promotion related to the content. |
| `PKEY_Media_ProviderRating` 	| Rating of the content as assigned by the metadata content provider. |
| `PKEY_Media_ProviderStyle` 	| Style or genre of the content as assigned by the metadata content provider. |
| `PKEY_Media_Publisher` 	| Publisher. |
| `PKEY_Media_SubTitle` 	| Subtitle. |
| `PKEY_Media_UniqueFileIdentifier` 	| A generic string that can be to identify the file. |
| `PKEY_Media_Writer` 	| Writer. |
| `PKEY_Media_Year` 	| Year the content was published. |
| `PKEY_Music_AlbumArtist` 	| Primary artist for the album. This attribute can be used to distinguish the primary artist for an album from an artist who collaborated on a particular track. |
| `PKEY_Music_AlbumTitle` 	| Album title. |
| `PKEY_Music_Artist` 	| Artist. |
| `PKEY_Music_BeatsPerMinute` 	| Beats per minute. |
| `PKEY_Music_Composer` 	| Composer. |
| `PKEY_Music_Conductor` 	| Conductor. |
| `PKEY_Music_ContentGroupDescription` 	| Description of the content group (for example, boxed set or series). |
| `PKEY_Music_Genre` 	| Genre. |
| `PKEY_Music_InitialKey` 	| The initial key of the music. |
| `PKEY_Music_IsCompilation` 	| Indicates whether the music file is part of a compilation. |
| `PKEY_Music_Lyrics` 	| Lyrics. |
| `PKEY_Music_Mood` 	| Mood. |
| `PKEY_Music_PartOfSet` 	| The part number and the total number of parts in the set to which the file belongs, separated by a slash. |
| `PKEY_Music_Period` 	| Period. |
| `PKEY_Music_TrackNumber` 	| Track number. |
| `PKEY_ParentalRating` 	| Parental rating. |
| `PKEY_ParentalRatingReason` 	| Reasons for the assigned parental rating. |
| `PKEY_Rating` 	| User rating. |
| `PKEY_ThumbnailStream` 	| Thumbnail image. |
| `PKEY_Title` 	| Title. |
| `PKEY_Video_Compression` 	| Video subtype (MF_MT_SUBTYPE) expressed as a string. |
| `PKEY_Video_Director` 	| Director. |
| `PKEY_Video_EncodingBitrate` 	| Average video bit rate, in bits per second. |
| `PKEY_Video_FourCC` 	| The FOURCC of the video encoding format. Applies only if the video subtype can be expressed as a FOURCC value. |
| `PKEY_Video_FrameHeight` 	| Video frame height. |
| `PKEY_Video_FrameRate` 	| Video frame rate, expressed as frames per second × 1000. |
| `PKEY_Video_FrameWidth` 	| Video frame width. |
| `PKEY_Video_HorizontalAspectRatio` 	| The horizontal component of the pixel aspect ratio. (Equivalent to the numerator of the MF_MT_PIXEL_ASPECT_RATIO attribute in the media type.) |
| `PKEY_Video_IsStereo` 	| Indicates whether the video stream contains stereo video content. |
| `PKEY_Video_StreamNumber` 	| Identifier of the video stream. |
| `PKEY_Video_TotalBitrate` 	| Total data rate for all video and audio streams, in bits per second. (Applies only to files with at least one video stream.) |
| `PKEY_Video_VerticalAspectRatio` 	| The vertical component of the pixel aspect ratio. (Equivalent to the denominator of the MF_MT_PIXEL_ASPECT_RATIO attribute in the media type.) |
