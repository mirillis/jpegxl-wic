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
#include "common.h"
#include "comcounter.h"
#include "comfactory.h"
#include "propertystorejxl.h"

//----------------------------------------------------------------------------
// INCLUDES EXTERNAL
//----------------------------------------------------------------------------
#include <shlobj.h>

//----------------------------------------------------------------------------
// NAMESPACE
//----------------------------------------------------------------------------
using namespace mrls::jxlcodec::wic;

//----------------------------------------------------------------------------
// DLL HANDLES
//----------------------------------------------------------------------------
HMODULE hmodule_dll= nullptr;



//==[ DllRegisterServer ]=====================================================
//============================================================================
STDAPI DllRegisterServer() {
    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, nullptr, nullptr);
    return S_OK;
}


//==[ DllUnregisterServer ]===================================================
//============================================================================
STDAPI DllUnregisterServer() {
    /*empty*/
    return S_OK;
}


//==[ DllGetClassObject ]=====================================================
//============================================================================
STDAPI DllGetClassObject(REFCLSID clsid, REFIID iid, LPVOID* ppv) {
    HRESULT hres= S_OK;
    if(ppv == nullptr) return E_INVALIDARG;
    if(!IsEqualGUID(iid, IID_IClassFactory)) return E_INVALIDARG;
    if(IsEqualGUID(clsid, CLSID_JXLDecoder)
    || IsEqualGUID(clsid, GUID_PropertyStoreJXL)) {
        COMFactory* fact= new(std::nothrow) COMFactory();
        if(fact == nullptr) return E_OUTOFMEMORY;
        *ppv= (LPVOID)fact;
    } else {
        return CLASS_E_CLASSNOTAVAILABLE;
    }
    return S_OK;
}


//==[ DllCanUnloadNow ]=======================================================
//============================================================================
STDAPI DllCanUnloadNow() {
    if(COMCounter::instance().num_obj_lock == 0
    && COMCounter::instance().num_server_lock == 0) {
        return S_OK;
    } else {
        return S_FALSE;
    }
}


//==[ DllMain ]===============================================================
//============================================================================
BOOL WINAPI DllMain(HMODULE hmodule, DWORD id_reason, LPVOID reserved) {
    if(id_reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hmodule);    
        hmodule_dll= hmodule;
    }
    return TRUE;
}
