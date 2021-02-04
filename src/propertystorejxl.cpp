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
#include "propertystorejxl.h"
#include "comcounter.h"

//----------------------------------------------------------------------------
// INCLUDES EXTERNAL
//----------------------------------------------------------------------------
#include <atlbase.h>
#include <shlobj.h>
#include <shlguid.h>
#include <propsys.h>
#include <propkey.h>

//----------------------------------------------------------------------------
// NAMESPACE
//----------------------------------------------------------------------------
namespace mrls { namespace jxlcodec { namespace wic {



//============================================================================
//                       WIC PROPERTY STORE JXL
//============================================================================
PropertyStoreJXL::PropertyStoreJXL() : num_ref(1) {
    InterlockedIncrement(&COMCounter::instance().num_obj_lock);
}
PropertyStoreJXL::~PropertyStoreJXL() {
    InterlockedDecrement(&COMCounter::instance().num_obj_lock);
}


//==[ AddRef ]================================================================
//============================================================================
ULONG PropertyStoreJXL::AddRef() {
    InterlockedIncrement(&num_ref);
    return num_ref;
}


//==[ Release ]===============================================================
//============================================================================
ULONG PropertyStoreJXL::Release() {
    InterlockedDecrement(&num_ref);
    if(num_ref == 0) {
        dechandler.release();
        delete this;
    }
    return num_ref;
}


//==[ QueryInterface ]========================================================
//============================================================================
HRESULT PropertyStoreJXL::QueryInterface(REFIID riid,
void** ppv) {
    HRESULT hres= S_OK;
    if(ppv == nullptr) return E_INVALIDARG;
    *ppv= nullptr;
    if(IsEqualGUID(riid, IID_IInitializeWithStream)) {
        *ppv= static_cast<IInitializeWithStream*>(this);
    } else
    if(IsEqualGUID(riid, IID_IPropertyStore)) {
        *ppv= static_cast<IPropertyStore*>(this);
    } else
    if(IsEqualGUID(riid, IID_IPropertyStoreCapabilities)) {
        *ppv= static_cast<IPropertyStoreCapabilities*>(this);
    } else hres= E_NOINTERFACE;
    if(SUCCEEDED(hres)) AddRef();
    return hres;
}


//==[ Initialize ]============================================================
//============================================================================
HRESULT PropertyStoreJXL::Initialize(IStream *pStream, DWORD grfMode) {
    HRESULT hres= S_OK;
    if(pStream == nullptr) {
        return E_INVALIDARG;
    }
    //CALCULATE STREAM SIZE
    STATSTG stat = { 0 };
    hres = pStream->Stat(&stat, STATFLAG_NONAME);
    if(FAILED(hres)) {
        return E_OUTOFMEMORY;
    }
    UINT64 size= stat.cbSize.QuadPart;
    //INITIALIE DECODER
    if(dechandler.init()) return E_UNEXPECTED;
    if(dechandler.recreateBufferInput(size)) return E_UNEXPECTED;
    //COPY STREAM TO BUFFER INPUT
    ULONG read= 0;
    hres= pStream->Read(dechandler.getBufferInput(), size, &read);
    if(FAILED(hres) || read != size) {
        return E_OUTOFMEMORY;
    }
    //DECODE
    if(dechandler.decodeMetadata()) return E_UNEXPECTED;
    return hres;
}


//==[ GetCount ]==============================================================
//============================================================================
HRESULT PropertyStoreJXL::GetCount(DWORD* cProps) {
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}


//==[ GetAt ]=================================================================
//============================================================================
HRESULT PropertyStoreJXL::GetAt(DWORD iProp, PROPERTYKEY* pkey) {
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}


//==[ GetValue ]==============================================================
//============================================================================
HRESULT PropertyStoreJXL::GetValue(REFPROPERTYKEY key, PROPVARIANT *pv) {
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}


//==[ SetValue ]==============================================================
//============================================================================
HRESULT PropertyStoreJXL::SetValue(REFPROPERTYKEY key, REFPROPVARIANT propvar){
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}


//==[ Commit ]================================================================
//============================================================================
HRESULT PropertyStoreJXL::Commit() {
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}


//==[ IsPropertyWritable ]====================================================
//============================================================================
HRESULT PropertyStoreJXL::IsPropertyWritable(REFPROPERTYKEY key) {
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}

}}}
