# NAME

ASFWriter -- C++ example

# SYNOPSIS

`ASFWriter input output`

# DESCRIPTION

Tutorial: Writing a WMA File by Using WMContainer Objects

This tutorial demonstrates writing a new audio file (.wma) by extracting media
content from an uncompressed audio file (.wav) and then compressing it in ASF
format. The encoding mode used for the conversion is Constant Bit Rate Encoding
(CBR). In this mode, before the encoding session, the application specifies a
target bit rate that the encoder must achieve.

In this tutorial, you will create a console application that takes the input
and output filenames as arguments. The application gets the uncompressed media
samples from a wave file parsing application, which is provided with this
tutorial. These samples are sent to the encoder for conversion to Windows Media
Audio 9 format. The encoder is configured for CBR encoding and uses the first
bit rate available during media type negotiation as the target bit rate. The
encoded samples are sent to the multiplexer for packetization in ASF data
format. These packets will be written to a byte stream that represents the ASF
Data Object. After the data section is ready, you will create an ASF audio file
and write the new ASF Header Object that consolidates all the header
information and then append the ASF Data Object byte stream.

# OPTIONS

* `input`
    - Input file name -- any audio file format supported by Media Foundation.
* `output`
    - Output file name -- Windows Media Audio file format ('.wma').
* `--cbr`
    - Use constant bitrate encoding mode.
    - Constant bitrate encoding mode uses 128 kbps.
* `--vbr`
    - Use variable bitrate encoding mode (default).
    - Variable bitrate encoding mode uses quality 90.
* `--help`
    - Show this message and exit.

# NOTES

Tutorial code is updated with support for variable bitrate encoding mode.

# LICENSE

The MIT License (MIT)

Copyright (c) Microsoft Corporation

# SEE ALSO

1. [WMContainer ASF Components](https://learn.microsoft.com/en-us/windows/win32/medfound/wmcontainer-asf-components)

