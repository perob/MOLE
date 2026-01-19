//////////////////////////////////////////////////////////////////////////
// Transcode.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// This sample demonstrates how to perform simple transcoding to WMA or WMV.
////////////////////////////////////////////////////////////////////////// 

#pragma once

class CTranscoder
{
    public:

        CTranscoder();
        virtual ~CTranscoder();

        HRESULT OpenFile(juce::InputStream *stream, const wchar_t* s);
        HRESULT ConfigureAudioOutput();
        HRESULT ConfigureVideoOutput();
        HRESULT ConfigureContainer();
        HRESULT EncodeToFile(juce::OutputStream *stream, const wchar_t* s);

    private:

        HRESULT Shutdown();
        HRESULT Transcode();
        HRESULT Start();

        IMFMediaSession*        m_pSession;
        IMFMediaSource*         m_pSource;
        IMFTopology*            m_pTopology;
        IMFTranscodeProfile*    m_pProfile;
};
