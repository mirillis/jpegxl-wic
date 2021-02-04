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

#ifndef __MRLSJXLCODECWICPROPERTYSTOREJXL_H
#define __MRLSJXLCODECWICPROPERTYSTOREJXL_H

//----------------------------------------------------------------------------
// INCLUDES INTERNAL
//----------------------------------------------------------------------------
#include "common.h"
#include "decodinghandler.h"

//----------------------------------------------------------------------------
// INCLUDES EXTERNAL
//----------------------------------------------------------------------------
#include <propsys.h>

//----------------------------------------------------------------------------
// NAMESPACE
//----------------------------------------------------------------------------
namespace mrls { namespace jxlcodec { namespace wic {



//============================================================================
//                       WIC PROPERTY STORE JXL
//============================================================================
class PropertyStoreJXL : public IInitializeWithStream, public IPropertyStore,
public IPropertyStoreCapabilities {
public:
    PropertyStoreJXL();
    virtual ~PropertyStoreJXL();

    //IUnknown
    ULONG STDMETHODCALLTYPE AddRef();
    ULONG STDMETHODCALLTYPE Release();
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);

    //IInitializeWithStream
    HRESULT STDMETHODCALLTYPE Initialize(IStream *pStream, DWORD grfMode);

    //IPropertyStore
    virtual HRESULT STDMETHODCALLTYPE GetCount(DWORD *cProps);
    virtual HRESULT STDMETHODCALLTYPE GetAt(DWORD iProp,
        PROPERTYKEY *pkey);
    virtual HRESULT STDMETHODCALLTYPE GetValue(REFPROPERTYKEY key,
        PROPVARIANT *pv);
    virtual HRESULT STDMETHODCALLTYPE SetValue(REFPROPERTYKEY key,
        REFPROPVARIANT propvar);
    virtual HRESULT STDMETHODCALLTYPE Commit(void);

    //IPropertyStoreCapabilities
    virtual HRESULT STDMETHODCALLTYPE IsPropertyWritable(REFPROPERTYKEY key);

private:
    volatile ULONG num_ref;
    DecodingHandler dechandler;
};

}}}

#endif
