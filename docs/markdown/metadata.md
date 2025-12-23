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
| MFPKEY\_Content\_DLNA\_Profile\_ID 	| Digital Living Network Alliance (DLNA) profile identifier. |
| PKEY\_Audio\_ChannelCount 	| Number of audio channels. |
| PKEY\_Audio\_EncodingBitrate 	| Average audio bit rate, in bits per second. |
| PKEY\_Audio\_Format 	| Audio subtype (MF\_MT\_SUBTYPE) expressed as a string. |
| PKEY\_Audio\_IsVariableBitRate 	| Indicates whether the audio stream uses variable bit-rate encoding. |
| PKEY\_Audio\_PeakValue 	| Peak volume level of audio content. |
| PKEY\_Audio\_SampleRate 	| Audio sample rate in samples per second. Equivalent to the MF\_MT\_AUDIO\_SAMPLES\_PER\_SECOND attribute in the media type. |
| PKEY\_Audio\_SampleSize 	| Number of bits per audio sample. Equivalent to the MF\_MT\_AUDIO\_BITS\_PER\_SAMPLE attribute in the media type. |
| PKEY\_Audio\_StreamNumber 	| Identifier of the audio stream. |
| PKEY\_Author 	| Author. |
| PKEY\_Comment 	| A comment attached to a file, typically added by a user. |
| PKEY\_Copyright 	| Copyright information. |
| PKEY\_DRM\_IsProtected 	| Indicates whether the content is protected using digital rights management (DRM). |
| PKEY\_Keywords 	| Keywords. |
| PKEY\_Language 	| Language. |
| PKEY\_Media\_AuthorUrl 	| URL of the author's website. |
| PKEY\_Media\_AverageLevel 	| Average volume level of audio content. |
| PKEY\_Media\_ClassPrimaryID 	| The string representation of a GUID that identifies the primary class of media. For valid values, see the documentation for the WM/MediaClassPrimaryID attribute. |
| PKEY\_Media\_ClassSecondaryID 	| The string representation of a GUID that identifies the secondary class of media. For valid values, see the documentation for the WM/MediaClassSecondaryID attribute. |
| PKEY\_Media\_CollectionGroupID 	| The string representation of a GUID that identifies the collection group. |
| PKEY\_Media\_CollectionID 	| The string representation of a GUID that identifies the collection. |
| PKEY\_Media\_ContentDistributor 	| Distributor of the content. |
| PKEY\_Media\_ContentID 	| The string representation of a GUID that identifies the collection. |
| PKEY\_Media\_DateEncoded 	| Time when the content was encoded. |
| PKEY\_Media\_DateReleased 	| Original release date. |
| PKEY\_Media\_Duration 	| Duration, in 100-nanosecond units. Equivalent to the MF\_PD\_DURATION attribute in the presentation descriptor. |
| PKEY\_Media\_DVDID 	| Digital video disc identifier (DVDID). |
| PKEY\_Media\_EncodedBy 	| Name of the person or group that encoded the content. |
| PKEY\_Media\_EncodingSettings 	| Description of the settings used to encode the content. |
| PKEY\_Media\_MCDI 	| Music CD identifier. This value is used to identify a CD. |
| PKEY\_Media\_MetadataContentProvider 	| Name of the metadata content provider. (For example, metadata might be provided by a commercial service.) |
| PKEY\_Media\_Producer 	| Name of the producer of the content. |
| PKEY\_Media\_PromotionUrl 	| URL of a website offering a promotion related to the content. |
| PKEY\_Media\_ProviderRating 	| Rating of the content as assigned by the metadata content provider. |
| PKEY\_Media\_ProviderStyle 	| Style or genre of the content as assigned by the metadata content provider. |
| PKEY\_Media\_Publisher 	| Publisher. |
| PKEY\_Media\_SubTitle 	| Subtitle. |
| PKEY\_Media\_UniqueFileIdentifier 	| A generic string that can be to identify the file. |
| PKEY\_Media\_Writer 	| Writer. |
| PKEY\_Media\_Year 	| Year the content was published. |
| PKEY\_Music\_AlbumArtist 	| Primary artist for the album. This attribute can be used to distinguish the primary artist for an album from an artist who collaborated on a particular track. |
| PKEY\_Music\_AlbumTitle 	| Album title. |
| PKEY\_Music\_Artist 	| Artist. |
| PKEY\_Music\_BeatsPerMinute 	| Beats per minute. |
| PKEY\_Music\_Composer 	| Composer. |
| PKEY\_Music\_Conductor 	| Conductor. |
| PKEY\_Music\_ContentGroupDescription 	| Description of the content group (for example, boxed set or series). |
| PKEY\_Music\_Genre 	| Genre. |
| PKEY\_Music\_InitialKey 	| The initial key of the music. |
| PKEY\_Music\_IsCompilation 	| Indicates whether the music file is part of a compilation. |
| PKEY\_Music\_Lyrics 	| Lyrics. |
| PKEY\_Music\_Mood 	| Mood. |
| PKEY\_Music\_PartOfSet 	| The part number and the total number of parts in the set to which the file belongs, separated by a slash. |
| PKEY\_Music\_Period 	| Period. |
| PKEY\_Music\_TrackNumber 	| Track number. |
| PKEY\_ParentalRating 	| Parental rating. |
| PKEY\_ParentalRatingReason 	| Reasons for the assigned parental rating. |
| PKEY\_Rating 	| User rating. |
| PKEY\_ThumbnailStream 	| Thumbnail image. |
| PKEY\_Title 	| Title. |
| PKEY\_Video\_Compression 	| Video subtype (MF\_MT\_SUBTYPE) expressed as a string. |
| PKEY\_Video\_Director 	| Director. |
| PKEY\_Video\_EncodingBitrate 	| Average video bit rate, in bits per second. |
| PKEY\_Video\_FourCC 	| The FOURCC of the video encoding format. Applies only if the video subtype can be expressed as a FOURCC value. |
| PKEY\_Video\_FrameHeight 	| Video frame height. |
| PKEY\_Video\_FrameRate 	| Video frame rate, expressed as frames per second × 1000. |
| PKEY\_Video\_FrameWidth 	| Video frame width. |
| PKEY\_Video\_HorizontalAspectRatio 	| The horizontal component of the pixel aspect ratio. (Equivalent to the numerator of the MF\_MT\_PIXEL\_ASPECT\_RATIO attribute in the media type.) |
| PKEY\_Video\_IsStereo 	| Indicates whether the video stream contains stereo video content. |
| PKEY\_Video\_StreamNumber 	| Identifier of the video stream. |
| PKEY\_Video\_TotalBitrate 	| Total data rate for all video and audio streams, in bits per second. (Applies only to files with at least one video stream.) |
| PKEY\_Video\_VerticalAspectRatio 	| The vertical component of the pixel aspect ratio. (Equivalent to the denominator of the MF\_MT\_PIXEL\_ASPECT\_RATIO attribute in the media type.) |
