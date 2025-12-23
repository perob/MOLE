/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

namespace mole {

#if JUCE_WINDOWS || DOXYGEN

    namespace WindowsMediaFoundation {

        using namespace mole::Windows;

        //==========================================================================
        /** IMFByteStream interface implementation with juce::OutputStream.  */
        class OutputByteStream : public IMFByteStream, public IMFAsyncCallback, public IMFAttributes
        {
            juce::OutputStream* output = nullptr;
            IMFAttributes* attributes = nullptr;

            LONG refCount = 1;
            bool isRemote = false;
            juce::int64 totalLength = 0;

            juce::CriticalSection criticalSection;

            //==========================================================================
            public:

            OutputByteStream() = delete;
            OutputByteStream (juce::OutputStream* stream,
                    const wchar_t* mimeType = nullptr,
                    const wchar_t* originName = nullptr,
                    bool usingNetwork = false)
                : output (stream), isRemote (usingNetwork), totalLength (0)
            {
                HRESULT hr = ::MFCreateAttributes (&attributes, 2);
                if (mimeType && SUCCEEDED (hr)) hr = attributes->SetString (MF_BYTESTREAM_CONTENT_TYPE, mimeType);
                if (originName && SUCCEEDED (hr)) hr = attributes->SetString (MF_BYTESTREAM_ORIGIN_NAME, originName);
            }

            ~OutputByteStream()
            {
                SafeRelease (&attributes);
            }

            //==========================================================================
            /// @name IUnknown interface
            /// @{

            /** Increments the reference count for an interface pointer to a COM object.  */
            STDMETHODIMP_(ULONG) AddRef() override
            {
                return (ULONG) ::InterlockedIncrement(&refCount);
            }

            /** Retrieves pointers to the supported interfaces on an object.  */
            STDMETHODIMP QueryInterface(REFIID iid, void** ptr) override
            {
                if (ptr == nullptr) { return E_POINTER; }

                if (iid == IID_IMFByteStream) { *ptr = static_cast<IMFByteStream*> (this); }
                else if (iid == IID_IMFAsyncCallback) { *ptr = static_cast<IMFAsyncCallback*> (this); }
                else if (iid == IID_IMFAttributes) { *ptr = static_cast<IMFAttributes*> (this); }
                else { *ptr = nullptr; return E_NOINTERFACE; }

                AddRef();
                return S_OK;
            }

            /** Decrements the reference count for an interface on a COM object.  */
            STDMETHODIMP_(ULONG) Release() override
            {
                LONG count = ::InterlockedDecrement (&refCount);
                if (count == 0)
                {
                    delete this;
                }
                return (ULONG) count;
            }
            /// @}

            //==========================================================================
            /// @name IMFAsyncCallback interface
            /// @{

            /** Provides configuration information to the dispatching thread for a callback.  */
            STDMETHODIMP GetParameters (DWORD* flags, DWORD* queue) override
            {
                if (isRemote)
                {
                    *flags = MFASYNC_BLOCKING_CALLBACK;
                }
                else
                {
                    // The callback does not take a long time to complete, but has no
                    // specific restrictions on what system calls it makes. The callback
                    // generally takes less than 30 milliseconds to complete. 
                    *flags = 0;
                }

                // This work queue is used for asynchronous operations throughout Media Foundation.
                *queue = MFASYNC_CALLBACK_QUEUE_MULTITHREADED;

                return S_OK;
            }

            /** Called when an asynchronous operation is completed.  */
            STDMETHODIMP Invoke (IMFAsyncResult* result) override
            {
                IMFAsyncResult* callback = nullptr;
                IUnknown* punk = nullptr;
                IUnknown* state = nullptr;

                HRESULT hr = result->GetState (&state);

                if (SUCCEEDED (hr)) hr = state->QueryInterface (IID_IMFAsyncResult, (void**) &callback);
                if (SUCCEEDED (hr)) hr = callback->GetObject (&punk);

                if (SUCCEEDED (hr))
                {
                    AsyncArguments* args = static_cast<AsyncArguments*> (punk);

                    if (args)
                    {
                        const juce::ScopedLock lock (criticalSection);
                        args->isWritten = output->write (args->buffer, (size_t) args->bufferSize);

                        if (args->isWritten) totalLength += (juce::int64) args->bufferSize;
                    }
                    else
                    {
                        hr = E_UNEXPECTED;
                    }
                }

                if (callback)
                {
                    callback->SetStatus (hr); 
                    ::MFInvokeCallback (callback);
                }

                SafeRelease (&punk);
                SafeRelease (&callback);
                SafeRelease (&state);

                return hr;
            }
            /// @}

            //==========================================================================
            /// @name IMFByteStream interface
            /// @{

            /** Begins an asynchronous read operation from the byte stream.  */
            STDMETHODIMP BeginRead (BYTE*, ULONG, IMFAsyncCallback*, IUnknown*) override { return NotImplemented (__FUNCTION__); }

            /** Begins an asynchronous write operation to the stream.  */
            STDMETHODIMP BeginWrite (const BYTE* buffer, ULONG bufferSize, IMFAsyncCallback* callback, IUnknown* state) override
            {
                IUnknown* args = AsyncArguments::Create (buffer, bufferSize);

                if (args == nullptr)
                {
                    return E_OUTOFMEMORY;
                }

                IMFAsyncResult* result = nullptr;

                HRESULT hr = ::MFCreateAsyncResult (args, callback, state, &result);

                if (SUCCEEDED (hr))
                {
                    hr = ::MFPutWorkItem (MFASYNC_CALLBACK_QUEUE_MULTITHREADED, this, result);
                }

                SafeRelease (&result);
                SafeRelease (&args);

                return hr;
            }

            /** Closes the stream and releases any resources associated with the stream.  */
            STDMETHODIMP Close() override
            {
                if (output->setPosition (0))
                    return S_OK;

                return E_FAIL;
            }

            /** Completes an asynchronous read operation.  */
            STDMETHODIMP EndRead (IMFAsyncResult*, ULONG*) override { return NotImplemented (__FUNCTION__); }

            /** Completes an asynchronous write operation.  */
            STDMETHODIMP EndWrite (IMFAsyncResult* result, ULONG* bytesWritten) override
            {
                IUnknown* punk = nullptr;

                HRESULT hr = result->GetStatus();

                if (SUCCEEDED (hr)) hr = result->GetObject (&punk);

                if (SUCCEEDED (hr))
                {
                    AsyncArguments* args = static_cast<AsyncArguments*> (punk);

                    if (args && args->isWritten)
                    {
                        *bytesWritten = args->bufferSize;
                    }
                    else
                    {
                        hr = E_UNEXPECTED;
                    }
                }

                SafeRelease (&punk);

                return hr;
            }

            /** Clears any internal buffers used by the stream.  */
            STDMETHODIMP Flush() override
            {
                output->flush();
                return S_OK;
            }

            /** Retrieves the characteristics of the byte stream.  */
            STDMETHODIMP GetCapabilities (DWORD* cap) override
            {
                if (isRemote)
                {
                    *cap = MFBYTESTREAM_IS_REMOTE | MFBYTESTREAM_IS_WRITABLE | MFBYTESTREAM_IS_SEEKABLE | MFBYTESTREAM_HAS_SLOW_SEEK;
                }
                else
                {
                    *cap = MFBYTESTREAM_IS_WRITABLE | MFBYTESTREAM_IS_SEEKABLE;
                }

                return S_OK;
            }

            /** Retrieves the current read or write position in the stream.  */
            STDMETHODIMP GetCurrentPosition (QWORD* pos) override
            {
                *pos = (QWORD) output->getPosition();
                return S_OK;
            }

            /** Retrieves the length of the stream.  */
            STDMETHODIMP GetLength (QWORD* len) override
            {
                *len = (QWORD) totalLength;
                return S_OK;
            }

            /** Queries whether the current position has reached the end of the stream.  */
            STDMETHODIMP IsEndOfStream (BOOL* isEnd) override
            {
                *isEnd = totalLength == output->getPosition();
                return S_OK;
            }

            /** Reads data from the stream.  */
            STDMETHODIMP Read (BYTE*, ULONG, ULONG*) override { return NotImplemented (__FUNCTION__); }

            /** Moves the current position in the stream by a specified offset.  */
            STDMETHODIMP Seek (MFBYTESTREAM_SEEK_ORIGIN mso, LONGLONG offset, DWORD /*flags*/, QWORD* currentPosition) override
            {
                HRESULT hr = E_FAIL;

                if (mso == msoCurrent)
                    offset += (LONGLONG) output->getPosition();

                if (offset >= 0 && (juce::int64) offset <= totalLength)
                {
                    if (output->setPosition ((juce::int64) offset))
                    {
                        hr = S_OK;
                        *currentPosition = (QWORD) offset;
                    }
                    else
                    {
                        *currentPosition = (QWORD) output->getPosition();
                    }
                }

                return hr;
            }

            /** Sets the current read or write position.  */
            STDMETHODIMP SetCurrentPosition (QWORD pos) override
            {
                if (output->setPosition ((juce::int64) pos))
                    return S_OK;

                return E_FAIL;
            }

            /** Sets the length of the stream.  */
            STDMETHODIMP SetLength (QWORD) override { return NotImplemented (__FUNCTION__); }

            /** Writes data to the stream.  */
            STDMETHODIMP Write (const BYTE* buffer, ULONG bufferSize, ULONG *bytesWritten) override
            {
                const juce::ScopedLock lock (criticalSection);

                if (output->write (buffer, (size_t) bufferSize))
                {
                    *bytesWritten = bufferSize;
                    totalLength += (juce::int64) bufferSize;
                    return S_OK;
                }

                *bytesWritten = 0;

                return E_FAIL;
            }
            /// @}

            //==========================================================================
            /// @name IMFAttributes interface
            /// @{
            STDMETHODIMP Compare (IMFAttributes* pTheirs, MF_ATTRIBUTES_MATCH_TYPE MatchType, BOOL* pbResult) override { return attributes->Compare (pTheirs, MatchType, pbResult); }
            STDMETHODIMP CompareItem (REFGUID guidKey, REFPROPVARIANT Value, BOOL* pbResult) override { return attributes->CompareItem (guidKey, Value, pbResult); }
            STDMETHODIMP CopyAllItems (IMFAttributes* pDest) override { return attributes->CopyAllItems (pDest); }
            STDMETHODIMP DeleteAllItems() override { return attributes->DeleteAllItems(); }
            STDMETHODIMP DeleteItem (REFGUID guidKey) override { return attributes->DeleteItem (guidKey); }
            STDMETHODIMP GetAllocatedBlob (REFGUID guidKey, UINT8** ppBuf, UINT32* pcbSize) override { return attributes->GetAllocatedBlob (guidKey, ppBuf, pcbSize); }
            STDMETHODIMP GetAllocatedString (REFGUID guidKey, LPWSTR* ppwszValue, UINT32* pcchLength) override { return attributes->GetAllocatedString (guidKey, ppwszValue, pcchLength); }
            STDMETHODIMP GetBlob (REFGUID guidKey, UINT8* pBuf, UINT32 cbBufSize, UINT32* pcbBlobSize) override { return attributes->GetBlob (guidKey, pBuf, cbBufSize, pcbBlobSize); }
            STDMETHODIMP GetBlobSize (REFGUID guidKey, UINT32* pcbBlobSize) override { return attributes->GetBlobSize (guidKey, pcbBlobSize); }
            STDMETHODIMP GetCount (UINT32* pcItems) override { return attributes->GetCount (pcItems); }
            STDMETHODIMP GetDouble (REFGUID guidKey, double* pfValue) override { return attributes->GetDouble (guidKey, pfValue); }
            STDMETHODIMP GetGUID (REFGUID guidKey, GUID* pguidValue) override { return attributes->GetGUID (guidKey, pguidValue); }
            STDMETHODIMP GetItem (REFGUID guidKey, PROPVARIANT* pValue) override { return attributes->GetItem (guidKey, pValue); }
            STDMETHODIMP GetItemByIndex (UINT32 unIndex, GUID* pguidKey, PROPVARIANT* pValue) override { return attributes->GetItemByIndex (unIndex, pguidKey, pValue); }
            STDMETHODIMP GetItemType (REFGUID guidKey, MF_ATTRIBUTE_TYPE* pType) override { return attributes->GetItemType (guidKey, pType); }
            STDMETHODIMP GetString (REFGUID guidKey, LPWSTR pwszValue, UINT32 cchBufSize, UINT32* pcchLength) override { return attributes->GetString (guidKey, pwszValue, cchBufSize, pcchLength); }
            STDMETHODIMP GetStringLength (REFGUID guidKey, UINT32* pcchLength) override { return attributes->GetStringLength (guidKey, pcchLength); }
            STDMETHODIMP GetUINT32 (REFGUID guidKey, UINT32* punValue) override { return attributes->GetUINT32 (guidKey, punValue); }
            STDMETHODIMP GetUINT64 (REFGUID guidKey, UINT64* punValue) override { return attributes->GetUINT64 (guidKey, punValue); }
            STDMETHODIMP GetUnknown (REFGUID guidKey, REFIID riid, LPVOID* ppv) override { return attributes->GetUnknown (guidKey, riid, ppv); }
            STDMETHODIMP LockStore() override { return attributes->LockStore(); }
            STDMETHODIMP SetBlob (REFGUID guidKey, const UINT8* pBuf, UINT32 cbBufSize) override { return attributes->SetBlob (guidKey, pBuf, cbBufSize); }
            STDMETHODIMP SetDouble (REFGUID guidKey, double fValue) override { return attributes->SetDouble (guidKey, fValue); }
            STDMETHODIMP SetGUID (REFGUID guidKey, REFGUID guidValue) override { return attributes->SetGUID (guidKey, guidValue); }
            STDMETHODIMP SetItem (REFGUID guidKey, REFPROPVARIANT Value) override { return attributes->SetItem (guidKey, Value); }
            STDMETHODIMP SetString (REFGUID guidKey, LPCWSTR wszValue) override { return attributes->SetString (guidKey, wszValue); }
            STDMETHODIMP SetUINT32 (REFGUID guidKey, UINT32 unValue) override { return attributes->SetUINT32 (guidKey, unValue); }
            STDMETHODIMP SetUINT64 (REFGUID guidKey,UINT64 unValue) override { return attributes->SetUINT64 (guidKey, unValue); }
            STDMETHODIMP SetUnknown (REFGUID guidKey, IUnknown* pUnknown) override { return attributes->SetUnknown (guidKey, pUnknown); }
            STDMETHODIMP UnlockStore() override { return attributes->UnlockStore(); }
            /// @}

            //==========================================================================
            private:

            //==========================================================================
            /** Async callback arguments.  */
            class AsyncArguments : public IUnknown
            {
                LONG refCount = 1;

                AsyncArguments() = delete;
                AsyncArguments (const BYTE* buf, ULONG size) : buffer (buf), bufferSize (size)
                {
                }

                //==========================================================================
                public:

                const BYTE* buffer = nullptr;
                ULONG bufferSize = 0;
                BOOL isWritten = false;

                ~AsyncArguments() = default;

                static AsyncArguments* Create (const BYTE* buffer, ULONG bufferSize)
                {
                    return new (std::nothrow) AsyncArguments (buffer, bufferSize);
                }

                //==========================================================================
                /// @name IUnknown interface
                /// @{

                /** Increments the reference count for an interface pointer to a COM object.  */
                STDMETHODIMP_(ULONG) AddRef() override
                {
                    return (ULONG) ::InterlockedIncrement (&refCount);
                }

                /** Retrieves pointers to the supported interfaces on an object.  */
                STDMETHODIMP QueryInterface (REFIID iid, void** ptr) override
                {
                    if (ptr == nullptr) { return E_POINTER; }

                    if (iid == IID_IUnknown) { *ptr = static_cast<IUnknown*> (this); }
                    else { *ptr = nullptr; return E_NOINTERFACE; }

                    AddRef();
                    return S_OK;
                }

                /** Decrements the reference count for an interface on a COM object.  */
                STDMETHODIMP_(ULONG) Release() override
                {
                    LONG count = ::InterlockedDecrement (&refCount);
                    if (count == 0)
                    {
                        delete this;
                    }
                    return (ULONG) count;
                }
                /// @}
            };

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputByteStream);
        };
    } // namespace WindowsMediaFoundation

#endif // JUCE_WINDOWS
} // namespace mole
