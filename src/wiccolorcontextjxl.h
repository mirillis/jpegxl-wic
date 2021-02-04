//----------------------------------------------------------------------------
//
// Copyright 2021 Mirillis
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//----------------------------------------------------------------------------

#ifndef __MRLSJXLCODECWICWICCOLORCONTEXTJXL_H
#define __MRLSJXLCODECWICWICCOLORCONTEXTJXL_H

//----------------------------------------------------------------------------
// INCLUDES INTERNAL
//----------------------------------------------------------------------------
#include "common.h"

//----------------------------------------------------------------------------
// NAMESPACE
//----------------------------------------------------------------------------
namespace mrls { namespace jxlcodec { namespace wic {



//============================================================================
//                        WIC COLOR CONTEXT JXL
//============================================================================
//TODO Not implemented yet
class WICColorContextJXL : public IWICColorContext {
public:
    WICColorContextJXL();
    virtual ~WICColorContextJXL();

    //IUnknown
    ULONG STDMETHODCALLTYPE AddRef();
    ULONG STDMETHODCALLTYPE Release();
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject);

    //IWICColorContext
    HRESULT STDMETHODCALLTYPE InitializeFromFilename(LPCWSTR wzFilename);
    HRESULT STDMETHODCALLTYPE InitializeFromMemory(const BYTE* pbBuffer,
        UINT cbBufferSize);
    HRESULT STDMETHODCALLTYPE InitializeFromExifColorSpace(UINT value);
    HRESULT STDMETHODCALLTYPE GetType(WICColorContextType* pType);
    HRESULT STDMETHODCALLTYPE GetProfileBytes(UINT cbBuffer, BYTE* pbBuffer,
        UINT* pcbActual);
    HRESULT STDMETHODCALLTYPE GetExifColorSpace(UINT* pValue);

private:
    volatile ULONG num_ref;
    CRITICAL_SECTION criticalsection;
};

}}}

#endif
