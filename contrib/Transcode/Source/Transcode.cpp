//////////////////////////////////////////////////////////////////////////
// Transcode.cpp
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

#include <JuceHeader.h>
#include "Transcode.h"

using namespace mole::Windows;
using namespace mole::WindowsMediaFoundation;

#define APIERROR(hr) APIError::toString(hr).toRawUTF8()

HRESULT CreateMediaSource(juce::InputStream*, const wchar_t* s, IMFMediaSource**);

//-------------------------------------------------------------------
//  CTranscoder constructor
//-------------------------------------------------------------------

CTranscoder::CTranscoder() :
    m_pSession(NULL),
    m_pSource(NULL),
    m_pTopology(NULL),
    m_pProfile(NULL)
{
}

//-------------------------------------------------------------------
//  CTranscoder destructor
//-------------------------------------------------------------------

CTranscoder::~CTranscoder()
{
    Shutdown();

    SafeRelease(&m_pProfile);
    SafeRelease(&m_pTopology);
    SafeRelease(&m_pSource);
    SafeRelease(&m_pSession);
}

//-------------------------------------------------------------------
//  OpenFile
//
//  1. Creates a media source for the caller specified URL.
//  2. Creates the media session.
//  3. Creates a transcode profile to hold the stream and
//     container attributes.
//
//  stream: juce::InputStream
//-------------------------------------------------------------------

HRESULT CTranscoder::OpenFile(juce::InputStream* stream, const wchar_t* s)
{
    if (!stream)
    {
        return E_INVALIDARG;
    }

    // Create the media source.
    HRESULT hr = CreateMediaSource(stream, s, &m_pSource);

    // Create the media session.
    if (SUCCEEDED(hr)) hr = MFCreateMediaSession(NULL, &m_pSession);

    // Create an empty transcode profile.
    if (SUCCEEDED(hr)) hr = MFCreateTranscodeProfile(&m_pProfile);

    return hr;
}

//-------------------------------------------------------------------
//  ConfigureAudioOutput
//
//  Configures the audio stream attributes.
//  These values are stored in the transcode profile.
//-------------------------------------------------------------------

HRESULT CTranscoder::ConfigureAudioOutput()
{
    jassert (m_pProfile);

    DWORD dwMTCount = 0;

    IMFCollection   *pAvailableTypes = NULL;
    IUnknown        *pUnkAudioType = NULL;
    IMFMediaType    *pAudioType = NULL;
    IMFAttributes   *pAudioAttrs = NULL;

    // Get the list of output formats supported by the Windows Media
    // audio encoder.

    HRESULT hr = MFTranscodeGetAudioOutputAvailableTypes(
            MFAudioFormat_WMAudioV9,
            MFT_ENUM_FLAG_ALL,
            NULL,
            &pAvailableTypes
            );

    // Get the number of elements in the list.
    if (SUCCEEDED(hr))  hr = pAvailableTypes->GetElementCount(&dwMTCount);
    if (dwMTCount == 0) hr = E_UNEXPECTED;

    // In this simple case, use the first media type in the collection.
    if (SUCCEEDED(hr)) hr = pAvailableTypes->GetElement(0, &pUnkAudioType);
    if (SUCCEEDED(hr)) hr = pUnkAudioType->QueryInterface(IID_PPV_ARGS(&pAudioType));

    // Create a copy of the attribute store so that we can modify it safely.
    if (SUCCEEDED(hr)) hr = MFCreateAttributes(&pAudioAttrs, 0);
    if (SUCCEEDED(hr)) hr = pAudioType->CopyAllItems(pAudioAttrs);

    // Set the encoder to be Windows Media audio encoder, so that the
    // appropriate MFTs are added to the topology.
    if (SUCCEEDED(hr)) hr = pAudioAttrs->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_WMAudioV9);

    // Set the attribute store on the transcode profile.
    if (SUCCEEDED(hr)) hr = m_pProfile->SetAudioAttributes( pAudioAttrs );

    SafeRelease(&pAvailableTypes);
    SafeRelease(&pAudioType);
    SafeRelease(&pUnkAudioType);
    SafeRelease(&pAudioAttrs);

    return hr;
}

//-------------------------------------------------------------------
//  ConfigureVideoOutput
//
//  Configures the Video stream attributes.
//  These values are stored in the transcode profile.
//-------------------------------------------------------------------

HRESULT CTranscoder::ConfigureVideoOutput()
{
    jassert (m_pProfile);

    IMFAttributes* pVideoAttrs = NULL;

    // Configure the video stream

    // Create a new attribute store.
    HRESULT hr = MFCreateAttributes( &pVideoAttrs, 5 );

    // Set the encoder to be Windows Media video encoder, so that the appropriate MFTs are added to the topology.
    if (SUCCEEDED(hr)) hr = pVideoAttrs->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_WMV3);

    // Set the frame rate.
    if (SUCCEEDED(hr)) hr = MFSetAttributeRatio(pVideoAttrs, MF_MT_FRAME_RATE, 30, 1);

    // Set the frame size.
    if (SUCCEEDED(hr)) hr = MFSetAttributeSize(pVideoAttrs, MF_MT_FRAME_SIZE, 320, 240);

    // Set the pixel aspect ratio
    if (SUCCEEDED(hr)) hr = MFSetAttributeRatio(pVideoAttrs, MF_MT_PIXEL_ASPECT_RATIO, 1, 1);

    // Set the bit rate.
    if (SUCCEEDED(hr)) hr = pVideoAttrs->SetUINT32(MF_MT_AVG_BITRATE, 300000);

    // Set the attribute store on the transcode profile.
    if (SUCCEEDED(hr)) hr = m_pProfile->SetVideoAttributes( pVideoAttrs );

    SafeRelease(&pVideoAttrs);

    return hr;
}

//-------------------------------------------------------------------
//  ConfigureContainer
//
//  Configures the container attributes.
//  These values are stored in the transcode profile.
//
//  Note: Setting the container type does not insert the required
//  MFT node in the transcode topology. The MFT node is based on the
//  stream settings stored in the transcode profile.
//-------------------------------------------------------------------

HRESULT CTranscoder::ConfigureContainer()
{
    jassert (m_pProfile);

    IMFAttributes* pContainerAttrs = NULL;

    // Set container attributes
    HRESULT hr = MFCreateAttributes(&pContainerAttrs, 2);

    // Set the output container to be ASF type
    if (SUCCEEDED(hr)) hr = pContainerAttrs->SetGUID(
            MF_TRANSCODE_CONTAINERTYPE,
            MFTranscodeContainerType_ASF
            );

    // Use the default setting. Media Foundation will use the stream
    // settings set in ConfigureAudioOutput and ConfigureVideoOutput.
    if (SUCCEEDED(hr)) hr = pContainerAttrs->SetUINT32(
            MF_TRANSCODE_ADJUST_PROFILE,
            MF_TRANSCODE_ADJUST_PROFILE_DEFAULT
            );

    // Set the attribute store on the transcode profile.
    if (SUCCEEDED(hr)) hr = m_pProfile->SetContainerAttributes(pContainerAttrs);

    SafeRelease(&pContainerAttrs);

    return hr;
}

//-------------------------------------------------------------------
//  EncodeToFile
//
//  Builds the transcode topology based on the input source,
//  configured transcode profile, and the output container settings.
//-------------------------------------------------------------------

HRESULT CTranscoder::EncodeToFile(juce::OutputStream* stream, const wchar_t* s)
{
    jassert (m_pSession);
    jassert (m_pSource);
    jassert (m_pProfile);

    if (!stream)
    {
        return E_INVALIDARG;
    }

    IMFByteStream* pByteStream = NULL;
    
    // Create the byte stream
    HRESULT hr = ByteStreamFromOutputStream(&pByteStream, stream, nullptr, s);

    // Create the transcode topology
    if (SUCCEEDED(hr)) hr = MFCreateTranscodeTopologyFromByteStream(m_pSource, pByteStream, m_pProfile, &m_pTopology);

    // Set the topology on the media session.
    if (SUCCEEDED(hr)) hr = m_pSession->SetTopology(0, m_pTopology);

    // Get media session events. This will start the encoding session.
    if (SUCCEEDED(hr)) hr = Transcode();

    SafeRelease(&pByteStream);

    return hr;
}

//-------------------------------------------------------------------
//  Name: Transcode
//
//  Start the encoding session by controlling the media session.
//
//  The encoding starts when the media session raises the
//  MESessionTopologySet event. The media session is closed after
//  receiving MESessionEnded. The encoded file is finalized after
//  the session is closed.
//
//  For simplicity, this sample uses the synchronous method for
//  getting media session events.
//-------------------------------------------------------------------

HRESULT CTranscoder::Transcode()
{
    jassert (m_pSession);

    IMFMediaEvent* pEvent = NULL;
    MediaEventType meType = MEUnknown;  // Event type

    HRESULT hr = S_OK;
    HRESULT hrStatus = S_OK;            // Event status

    // Get media session events synchronously
    while (meType != MESessionClosed)
    {
        hr = m_pSession->GetEvent(0, &pEvent);

        if (FAILED(hr)) { break; }

        // Get the event type.
        hr = pEvent->GetType(&meType);

        if (FAILED(hr)) { break; }

        hr = pEvent->GetStatus(&hrStatus);

        if (FAILED(hr)) { break; }

        if (FAILED(hrStatus))
        {
            printf("Failed. 0x%X error condition triggered this event.\n", hrStatus);
            printf("%s\n", APIERROR(hrStatus));
            hr = hrStatus;
            break;
        }

        switch (meType)
        {
            case MESessionTopologySet:
                hr = Start();
                if (SUCCEEDED(hr))
                {
                    printf("Topology set.\n");
                }
                break;

            case MESessionStarted:
                printf("Started encoding.\n");
                break;

            case MESessionEnded:
                hr = m_pSession->Close();
                if (SUCCEEDED(hr))
                {
                    printf("Ended encoding.\n");
                }
                break;

            case MESessionClosed:
                printf("Closed encoding.\n");
                break;
        }

        if (FAILED(hr))
        {
            break;
        }

        SafeRelease(&pEvent);
    }

    SafeRelease(&pEvent);

    return hr;
}

//-------------------------------------------------------------------
//  Start
//
//  Starts the encoding session.
//-------------------------------------------------------------------

HRESULT CTranscoder::Start()
{
    jassert (m_pSession != NULL);

    PROPVARIANT varStart;
    PropVariantInit(&varStart);

    HRESULT hr = m_pSession->Start(&GUID_NULL, &varStart);

    if (FAILED(hr)) printf("Failed to start the session...\n");

    return hr;
}

//-------------------------------------------------------------------
//  Shutdown
//
//  Handler for the MESessionClosed event.
//  Shuts down the media session and the media source.
//-------------------------------------------------------------------

HRESULT CTranscoder::Shutdown()
{
    HRESULT hr = S_OK;

    // Shut down the media source
    if (m_pSource) m_pSource->Shutdown();

    // Shut down the media session. (Synchronous operation, no events.)
    if (m_pSession) m_pSession->Shutdown();

    return hr;
}

///////////////////////////////////////////////////////////////////////
//  CreateMediaSource
//
//  Creates a media source from a juce::InputStream.
///////////////////////////////////////////////////////////////////////

HRESULT CreateMediaSource(
        juce::InputStream* stream,      // Stream to read from.
        const wchar_t* s,               // IMFByteStream origin name.
        IMFMediaSource** ppMediaSource  // Receives a pointer to the media source.
        )
{
    if (!stream)
    {
        return E_INVALIDARG;
    }

    if (!ppMediaSource)
    {
        return E_POINTER;
    }

    MF_OBJECT_TYPE ObjectType = MF_OBJECT_INVALID;

    IMFSourceResolver* pSourceResolver = NULL;
    IMFByteStream* pByteStream = NULL;
    IUnknown* pUnkSource = NULL;

    // Create the source resolver.
    HRESULT hr = MFCreateSourceResolver(&pSourceResolver);

    // Create the byte stream.
    if (SUCCEEDED(hr)) hr = ByteStreamFromInputStream(&pByteStream, stream, nullptr, s);

    if (SUCCEEDED(hr)) hr = pSourceResolver->CreateObjectFromByteStream(
            pByteStream,
            NULL,
            MF_RESOLUTION_MEDIASOURCE | MF_RESOLUTION_READ,
            NULL,
            &ObjectType,
            &pUnkSource
            );

    // Get the IMFMediaSource from the IUnknown pointer.
    if (SUCCEEDED(hr)) hr = pUnkSource->QueryInterface(IID_PPV_ARGS(ppMediaSource));

    SafeRelease(&pSourceResolver);
    SafeRelease(&pByteStream);
    SafeRelease(&pUnkSource);

    return hr;
}
