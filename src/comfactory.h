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

#ifndef __MRLSJXLCODECWICCOMFACTORY_H
#define __MRLSJXLCODECWICCOMFACTORY_H

//----------------------------------------------------------------------------
// INCLUDES INTERNAL
//----------------------------------------------------------------------------
#include "common.h"

//----------------------------------------------------------------------------
// NAMESPACE
//----------------------------------------------------------------------------
namespace mrls { namespace jxlcodec { namespace wic {



//============================================================================
//                              COMFACTORY
//============================================================================
class COMFactory : public IClassFactory {
public:
    COMFactory();
    virtual ~COMFactory();

    //IUnknown
    virtual ULONG STDMETHODCALLTYPE AddRef(void);
    virtual ULONG STDMETHODCALLTYPE Release(void);
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);

    //IClassFactory
    virtual HRESULT STDMETHODCALLTYPE CreateInstance(LPUNKNOWN pUnk,
        const IID& iid, void** ppv);
    virtual HRESULT STDMETHODCALLTYPE LockServer(BOOL lock);

protected:
    LONG num_ref;
};

}}}

#endif
