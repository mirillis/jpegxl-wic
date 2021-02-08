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
#include "wicbitmapdecoderjxl.h"
#include "mutexlocker.h"

//----------------------------------------------------------------------------
// NAMESPACE
//----------------------------------------------------------------------------
namespace mrls { namespace jxlcodec { namespace wic {



//============================================================================
//                       WIC BITMAP DECODER JXL
//==[ constructor ]===========================================================
//============================================================================
WICBitmapDecoderJXL::WICBitmapDecoderJXL() : num_ref(1), index(0),
wic_frame(nullptr), wic_fact(nullptr) {
    InitializeCriticalSection(&criticalsection);
}
WICBitmapDecoderJXL::~WICBitmapDecoderJXL() {
    DeleteCriticalSection(&criticalsection);
}


//==[ AddRef ]================================================================
//============================================================================
ULONG WICBitmapDecoderJXL::AddRef() {
    InterlockedIncrement(&num_ref);
    return num_ref;
}


//==[ Release ]===============================================================
//============================================================================
ULONG WICBitmapDecoderJXL::Release() {
    InterlockedDecrement(&num_ref);
    if(num_ref == 0) {
        if(wic_fact) {
            wic_fact->Release();
            wic_fact= nullptr;
        }
        if(wic_frame) {
            wic_frame->Release();
            wic_frame= nullptr;
        }
        delete this;
    }
    return num_ref;
}


//==[ QueryInterface ]========================================================
//============================================================================
HRESULT WICBitmapDecoderJXL::QueryInterface(REFIID riid, void** ppv) {
    HRESULT hres= S_OK;
    if(ppv == nullptr) return E_INVALIDARG;
    *ppv= nullptr;
    if(IsEqualGUID(riid, IID_IUnknown)) {
        AddRef();
        *ppv= static_cast<IUnknown*>(this);
    } else
    if(IsEqualGUID(riid, IID_IWICBitmapDecoder)) {
        AddRef();
        *ppv= static_cast<IWICBitmapDecoder*>(this);
    } else return E_NOINTERFACE;
    return hres;
}


//==[ QueryCapability ]=======================================================
//============================================================================
HRESULT WICBitmapDecoderJXL::QueryCapability(IStream* pIStream,
DWORD* pCapability) {
    if((pIStream == nullptr) || (pCapability == nullptr)) return E_INVALIDARG;
    *pCapability= WICBitmapDecoderCapabilityCanDecodeSomeImages;
    return S_OK;
}


//==[ Initialize ]============================================================
//============================================================================
HRESULT WICBitmapDecoderJXL::Initialize(IStream* pIStream,
WICDecodeOptions cacheOptions) {
    if(pIStream == nullptr) {
        return E_INVALIDARG;
    }
    MutexLocker locker(&criticalsection);
    HRESULT hres= S_OK;
    if(wic_frame) {
        return WINCODEC_ERR_WRONGSTATE;
    }
    wic_frame= new(std::nothrow) WICBitmapFrameDecodeJXL();
    if(!wic_frame) {
        return E_OUTOFMEMORY;
    }
    hres= wic_frame->Initialize(pIStream, index);
    if(FAILED(hres)) {
        return hres;
    }
    return hres;
}


//==[ GetContainerFormat ]====================================================
//============================================================================
HRESULT WICBitmapDecoderJXL::GetContainerFormat(GUID* pguidContainerFormat) {
    if(pguidContainerFormat == nullptr) return E_INVALIDARG; 
    *pguidContainerFormat= GUID_ContainerFormatJXL;
    return S_OK;
}


//==[ GetDecoderInfo ]========================================================
//============================================================================
HRESULT WICBitmapDecoderJXL::GetDecoderInfo(
IWICBitmapDecoderInfo** ppIDecoderInfo) {
    HRESULT hres= S_OK;
    {
        MutexLocker locker(&criticalsection);
        if(!this->wic_fact) {
            hres= CoCreateInstance(CLSID_WICImagingFactory,
                NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory,
                (LPVOID*)&this->wic_fact);
            if(FAILED(hres)) {
                return hres;
            }
        }
    }
    IWICComponentInfo* wic_cinfo= nullptr;
    hres= this->wic_fact->CreateComponentInfo(CLSID_JXLDecoder, &wic_cinfo);
    if(FAILED(hres)) return hres;
    hres= wic_cinfo->QueryInterface(IID_IWICBitmapDecoderInfo,
        reinterpret_cast<void**>(ppIDecoderInfo));
    if(FAILED(hres)) {
        wic_cinfo->Release();
        return hres;
    }
    wic_cinfo->Release();
    return S_OK;
}


//==[ GetFrameCount ]=========================================================
//============================================================================
HRESULT WICBitmapDecoderJXL::GetFrameCount(UINT* pCount) {
    if(pCount == nullptr) return E_INVALIDARG;
    *pCount= 1;
    return S_OK;
}


//==[ GetFrame ]==============================================================
//============================================================================
HRESULT WICBitmapDecoderJXL::GetFrame(UINT index,
IWICBitmapFrameDecode** ppIBitmapFrame) {
    HRESULT hres= S_OK;
    if(ppIBitmapFrame == nullptr) return E_INVALIDARG;
    MutexLocker locker(&criticalsection);
    if(index >= 1) return WINCODEC_ERR_FRAMEMISSING;
    if(wic_frame == nullptr) return WINCODEC_ERR_FRAMEMISSING;
    wic_frame->AddRef();
    *ppIBitmapFrame= wic_frame;
    return hres;
}


//==[ CopyPalette ]===========================================================
//============================================================================
HRESULT WICBitmapDecoderJXL::CopyPalette(IWICPalette* pIPalette) {
    return WINCODEC_ERR_PALETTEUNAVAILABLE;
}


//==[ GetMetadataQueryReader ]================================================
//============================================================================
HRESULT WICBitmapDecoderJXL::GetMetadataQueryReader(
IWICMetadataQueryReader** ppIMetadataQueryReader) {
    HRESULT hres= S_OK;
    if(wic_frame == nullptr) {
        return WINCODEC_ERR_UNSUPPORTEDOPERATION;
    }
    hres= wic_frame->GetMetadataQueryReader(ppIMetadataQueryReader);
    return hres;
}


//==[ GetPreview ]============================================================
//============================================================================
HRESULT WICBitmapDecoderJXL::GetPreview(IWICBitmapSource** ppIBitmapSource) {
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}


//==[ GetColorContexts ]======================================================
//============================================================================
HRESULT WICBitmapDecoderJXL::GetColorContexts(UINT cCount,
IWICColorContext** ppIColorContexts, UINT* pActualCount) {
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}


//==[ GetThumbnail ]==========================================================
//============================================================================
HRESULT WICBitmapDecoderJXL::GetThumbnail(IWICBitmapSource** ppIThumbnail) {
    return WINCODEC_ERR_CODECNOTHUMBNAIL;
}

}}}
