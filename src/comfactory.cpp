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
#include "comfactory.h"
#include "comcounter.h"
#include "wicbitmapdecoderjxl.h"
#include "propertystorejxl.h"

//----------------------------------------------------------------------------
// NAMESPACE
//----------------------------------------------------------------------------
namespace mrls { namespace jxlcodec { namespace wic {



//============================================================================
//                              COMFACTORY
//==[ constructor ]===========================================================
//============================================================================
COMFactory::COMFactory() : num_ref(1) {
    InterlockedIncrement(&COMCounter::instance().num_obj_lock);
}
COMFactory::~COMFactory() {
    InterlockedDecrement(&COMCounter::instance().num_obj_lock);
}


//==[ AddRef ]================================================================
//============================================================================
ULONG COMFactory::AddRef() {
    InterlockedIncrement(&num_ref);
    return num_ref;
}


//==[ Release ]===============================================================
//============================================================================
ULONG COMFactory::Release() {
    InterlockedDecrement(&num_ref);
    if(num_ref == 0) {
        delete this;
    }
    return num_ref;
}


//==[ QueryInterface ]========================================================
//============================================================================
HRESULT COMFactory::QueryInterface(REFIID riid, void** ppv) {
    HRESULT hres= S_OK;
    if(ppv == nullptr) return E_INVALIDARG;
    *ppv= nullptr;
    if(IsEqualGUID(riid, IID_IUnknown)) {
        *ppv= static_cast<IUnknown*>(this);
    } else
    if(IsEqualGUID(riid, IID_IClassFactory)) {
        *ppv= static_cast<IClassFactory*>(this);
    } else hres= E_NOINTERFACE;
    if(SUCCEEDED(hres)) AddRef();
    return hres;
}


//==[ CreateInstance ]========================================================
//============================================================================
HRESULT COMFactory::CreateInstance(LPUNKNOWN pUnk,
const IID& iid, void** ppv) {
    HRESULT hres= S_OK;
    if(ppv == nullptr) return E_INVALIDARG;
    if(pUnk != nullptr) return CLASS_E_NOAGGREGATION;
    if(IsEqualGUID(iid, IID_IWICBitmapDecoder)) {
        WICBitmapDecoderJXL* wic_dec= new(std::nothrow) WICBitmapDecoderJXL();
        if(wic_dec == nullptr) return E_OUTOFMEMORY;
        hres= wic_dec->QueryInterface(iid, ppv);
        wic_dec->Release();
        if(FAILED(hres)) return hres;
    } else
    if(IsEqualGUID(iid, IID_IPropertyStore)) {
        PropertyStoreJXL* prop= new(std::nothrow) PropertyStoreJXL();
        if(prop == nullptr) return E_OUTOFMEMORY;
        hres= prop->QueryInterface(iid, ppv);
        prop->Release();
        if(FAILED(hres)) return hres;
    } else {
        return E_UNEXPECTED;
    }
    return hres; 
}


//==[ LockServer ]============================================================
//============================================================================
HRESULT COMFactory::LockServer(BOOL lock) {
    if(lock) InterlockedIncrement(&COMCounter::instance().num_server_lock);
    else InterlockedDecrement(&COMCounter::instance().num_server_lock);
    return S_OK;
}

}}}
