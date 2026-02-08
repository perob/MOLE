# NAME

ASFWriter -- C++ example

# SYNOPSIS

`ASFWriter input output`

# DESCRIPTION

Writing a WMA File by Using WMContainer Objects

*This code demonstrates writing a new audio file (.wma) by extracting media
content from an uncompressed audio file (.wav) and then compressing it in ASF
format. The encoding mode used for the conversion is Constant Bit Rate Encoding
(CBR). In this mode, before the encoding session, the application specifies a
target bit rate that the encoder must achieve.*

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

Source code is updated with support for variable bitrate encoding mode.

# LICENSE

The MIT License (MIT)

Copyright (c) Microsoft Corporation

# SEE ALSO

1. [WMContainer ASF Components](https://learn.microsoft.com/en-us/windows/win32/medfound/wmcontainer-asf-components)

