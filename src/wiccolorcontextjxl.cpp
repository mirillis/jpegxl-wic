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

//----------------------------------------------------------------------------
// INCLUDES INTERNAL
//----------------------------------------------------------------------------
#include "wiccolorcontextjxl.h"

//----------------------------------------------------------------------------
// NAMESPACE
//----------------------------------------------------------------------------
namespace mrls { namespace jxlcodec { namespace wic {



//============================================================================
//                       WIC COLOR CONTEXT JXL
//==[ constructor ]===========================================================
//============================================================================
WICColorContextJXL::WICColorContextJXL() : num_ref(1) {
    InitializeCriticalSection(&criticalsection);
}
WICColorContextJXL::~WICColorContextJXL() {
    DeleteCriticalSection(&criticalsection);
}


//==[ AddRef ]================================================================
//============================================================================
ULONG WICColorContextJXL::AddRef() {
    InterlockedIncrement(&num_ref);
    return num_ref;
}


//==[ Release ]===============================================================
//============================================================================
ULONG WICColorContextJXL::Release() {
    InterlockedDecrement(&num_ref);
    if(num_ref == 0) {
        delete this;
    }
    return num_ref;
}


//==[ QueryInterface ]========================================================
//============================================================================
HRESULT WICColorContextJXL::QueryInterface(REFIID riid, void** ppv) {
    HRESULT hres= S_OK;
    if(ppv == nullptr) return E_INVALIDARG;
    *ppv= nullptr;
    if(IsEqualGUID(riid, IID_IUnknown)) {
        AddRef();
        *ppv= static_cast<IUnknown*>(this);
    } else
    if(IsEqualGUID(riid, IID_IWICColorContext)) {
        AddRef();
        *ppv= static_cast<IWICColorContext*>(this);
    } else return E_NOINTERFACE;
    return hres;
}


//==[ InitializeFromFilename ]================================================
//============================================================================
HRESULT WICColorContextJXL::InitializeFromFilename(LPCWSTR wzFilename) {
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}


//==[ InitializeFromMemory ]==================================================
//============================================================================
HRESULT WICColorContextJXL::InitializeFromMemory(const BYTE* pbBuffer,
UINT cbBufferSize) {
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}


//==[ InitializeFromExifMemory ]==============================================
//============================================================================
HRESULT WICColorContextJXL::InitializeFromExifColorSpace(UINT value) {
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}


//==[ GetType ]===============================================================
//============================================================================
HRESULT WICColorContextJXL::GetType(WICColorContextType* pType) {
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}


//==[ GetProfileBytes ]=======================================================
//============================================================================
HRESULT WICColorContextJXL::GetProfileBytes(UINT cbBuffer, BYTE* pbBuffer,
UINT* pcbActual) {
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}


//==[ GetExifColorSpace ]=====================================================
//============================================================================
HRESULT WICColorContextJXL::GetExifColorSpace(UINT* pValue) {
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}

}}}
