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
#include "wicbitmapframedecodejxl.h"
#include "mutexlocker.h"

//----------------------------------------------------------------------------
// NAMESPACE
//----------------------------------------------------------------------------
namespace mrls { namespace jxlcodec { namespace wic {



//============================================================================
//                        WIC BITMAP FRAME DECODE JXL 
//==[ constructor ]===========================================================
//============================================================================
WICBitmapFrameDecodeJXL::WICBitmapFrameDecodeJXL() : num_ref(1), size_hdr(0),
wic_cc(nullptr), buf_hdr(nullptr) {
    InitializeCriticalSection(&criticalsection);
}
WICBitmapFrameDecodeJXL::~WICBitmapFrameDecodeJXL() {
    DeleteCriticalSection(&criticalsection);
}


//==[ Initialize ]============================================================
//============================================================================
HRESULT WICBitmapFrameDecodeJXL::Initialize(IStream* pIStream, UINT index)  {
    HRESULT hres= S_OK;
    wic_cc= new WICColorContextJXL();
    STATSTG stat = { 0 };
    hres = pIStream->Stat(&stat, STATFLAG_NONAME);
    if(FAILED(hres)) {
        return E_OUTOFMEMORY;
    }
    UINT64 size= stat.cbSize.QuadPart;
    if(dechandler.init()) return E_UNEXPECTED;
    if(dechandler.recreateBufferInput(size)) return E_UNEXPECTED;
    ULONG read= 0;
    hres= pIStream->Read(
        dechandler.getBufferInput(), dechandler.getBufferInputSize(), &read);
    if(FAILED(hres)) {
        return E_OUTOFMEMORY;
    }
    if(dechandler.decode()) return E_UNEXPECTED;
    if(setHDRBuffer()) return E_UNEXPECTED;
    return hres;
}


//==[ AddRef ]================================================================
//============================================================================
ULONG WICBitmapFrameDecodeJXL::AddRef() {
    InterlockedIncrement(&num_ref);
    return num_ref;
}


//==[ Release ]===============================================================
//============================================================================
ULONG WICBitmapFrameDecodeJXL::Release() {
    InterlockedDecrement(&num_ref);
    if(num_ref == 0) {
        size_hdr= 0;
        if(buf_hdr) {
            free(buf_hdr);
            buf_hdr= nullptr;
        }
        if(wic_cc) {
            wic_cc->Release();
            wic_cc= nullptr;
        }
        dechandler.release();
        delete this;
    }
    return num_ref;
}


//==[ QueryInterface ]========================================================
//============================================================================
HRESULT WICBitmapFrameDecodeJXL::QueryInterface(REFIID riid, void** ppv) {
    HRESULT hres= S_OK;
    if(ppv == nullptr) {
        return E_INVALIDARG;
    }
    *ppv= nullptr;
    if(IsEqualGUID(riid, IID_IUnknown)) {
        AddRef();
        *ppv= static_cast<IUnknown*>(this);
    } else
    if(IsEqualGUID(riid, IID_IWICBitmapSource)) {
        AddRef();
        *ppv= static_cast<IWICBitmapSource*>(this);
    } else
    if(IsEqualGUID(riid, IID_IWICBitmapFrameDecode)) {
        AddRef();
        *ppv= static_cast<IWICBitmapFrameDecode*>(this);
    } else {
        OLECHAR* str_guid;
        StringFromCLSID(riid, &str_guid);
        ::CoTaskMemFree(str_guid);
        return E_NOINTERFACE;
    }
    return hres;
}


//==[ GetSize ]===============================================================
//============================================================================
HRESULT WICBitmapFrameDecodeJXL::GetSize(UINT* pWidth, UINT* pHeight) {
    if(pWidth == nullptr || pHeight == nullptr) return E_INVALIDARG;
    *pWidth= dechandler.getMetadata().xsize;
    *pHeight= dechandler.getMetadata().ysize;
    return S_OK;
}


//==[ GetPixelFormat ]========================================================
//============================================================================
HRESULT WICBitmapFrameDecodeJXL::GetPixelFormat(
WICPixelFormatGUID* pPixelFormat) {
    if(pPixelFormat == nullptr) return E_INVALIDARG;
    if(dechandler.getOutputMetadata().size_chan == 1) {
        *pPixelFormat= GUID_WICPixelFormat24bppRGB;
    } else
    if(dechandler.getOutputMetadata().size_chan == 2) {
        *pPixelFormat= GUID_WICPixelFormat32bppR10G10B10A2HDR10;
    } else 
    //UNUSED
    /*if(dechandler.getOutputMetadata().size_chan == 2) {
        *pPixelFormat = GUID_WICPixelFormat64bppRGBA;
    } else*/
    {
        return E_UNEXPECTED;
    }
    return S_OK;
}


//==[ GetResolution ]=========================================================
//============================================================================
HRESULT WICBitmapFrameDecodeJXL::GetResolution(double* pDpiX, double* pDpiY) {
    if(pDpiX == nullptr || pDpiY == nullptr) return E_INVALIDARG;
    *pDpiX= 96;
    *pDpiY= 96;
    return S_OK;
}


//==[ CopyPixels ]============================================================
//============================================================================
HRESULT WICBitmapFrameDecodeJXL::CopyPixels(const WICRect* pRc, UINT stride,
UINT bufferSize, BYTE* pBuffer) {
    HRESULT hres= S_OK;
    if(pBuffer == nullptr) return E_INVALIDARG;
    WICRect rect = {
        0, 0,
        static_cast<int>(dechandler.getMetadata().xsize),
        static_cast<int>(dechandler.getMetadata().ysize)
    };
    if(pRc != nullptr) rect= *pRc;
    if((rect.Width < 0) || (rect.Height < 0) || (rect.X < 0) || (rect.Y < 0)) {
        return E_INVALIDARG;
    }
    if(((rect.X + rect.Width) > (int)(dechandler.getMetadata().xsize))
    || ((rect.Y + rect.Height) > (int)(dechandler.getMetadata().ysize))) {
        return E_INVALIDARG;
    }
    size_t size_pix= 0;
    if(!buf_hdr) size_pix= dechandler.getOutputMetadata().size_pix;
    else size_pix= 4;
    const size_t stride_src= dechandler.getMetadata().xsize*size_pix;
    const size_t stride_dst= rect.Width*size_pix;
    if(stride < stride_dst) return E_INVALIDARG;

    BYTE* line= NULL;
    if(!buf_hdr) {
        for(uint32_t i_src=rect.Y, i_dst=0; i_src<rect.Y+rect.Height; i_src++,
        i_dst++) {
            line= dechandler.getBufferOutput() + i_src*stride_src;
            memcpy(pBuffer+(size_t)i_dst*stride, line, stride_dst);
        }
    } else { 
        for(uint32_t i_src=rect.Y, i_dst=0; i_src<rect.Y+rect.Height; i_src++,
        i_dst++) {
            line= buf_hdr + i_src*stride_src;
            memcpy(pBuffer+(size_t)i_dst*stride, line, stride_dst);
        }
    }
    return hres;

}


//==[ CopyPalette ]===========================================================
//============================================================================
HRESULT WICBitmapFrameDecodeJXL::CopyPalette(IWICPalette* pIPalette) {
    return WINCODEC_ERR_PALETTEUNAVAILABLE;
}


//==[ GetThumbnail ]==========================================================
//============================================================================
HRESULT WICBitmapFrameDecodeJXL::GetThumbnail(IWICBitmapSource** ppIThumbnail){
    return WINCODEC_ERR_CODECNOTHUMBNAIL;
}


//==[ GetColorContexts ]======================================================
//============================================================================
HRESULT WICBitmapFrameDecodeJXL::GetColorContexts(UINT cCount,
IWICColorContext** ppIColorContexts, UINT* pcActualCount) {
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}


//==[ GetMetadataQueryReader ]================================================
//============================================================================
HRESULT WICBitmapFrameDecodeJXL::GetMetadataQueryReader(
IWICMetadataQueryReader** ppIMetadataQueryReader) {
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}


//==[ setHDROutput ]==[ private ]=============================================
//============================================================================
int WICBitmapFrameDecodeJXL::setHDRBuffer() {
    if(buf_hdr) return 1;
    if(dechandler.getOutputMetadata().size_chan == 2) {
        size_hdr= dechandler.getMetadata().xsize
            *dechandler.getMetadata().ysize*4;
        buf_hdr= (BYTE*)malloc(size_hdr);
        if(!buf_hdr) return 1;
        conv16To10(dechandler.getBufferOutput(), buf_hdr,
            dechandler.getMetadata().xsize,
            dechandler.getMetadata().ysize);
    }
    return 0;
}


//==[ conv16To10 ]==[ private ]===============================================
//============================================================================
int WICBitmapFrameDecodeJXL::conv16To10(void* buf_in, void* buf_out,
uint32_t width, uint32_t height) {
    const uint16_t* buf16_in= reinterpret_cast<const uint16_t*>(buf_in);
    uint32_t* buf32_out= reinterpret_cast<uint32_t*>(buf_out);
    const uint32_t num_channel= 4;
    double coeff[3]= {0.0, 0.0, 0.0};
    for(uint32_t i=0; i<width*height; i++) {
        coeff[0]= (double)buf16_in[i*num_channel+0]/0xFFFF;
        coeff[1]= (double)buf16_in[i*num_channel+1]/0xFFFF;
        coeff[2]= (double)buf16_in[i*num_channel+2]/0xFFFF;
        buf32_out[i]= (0x3<<30)
            | ((uint32_t)(coeff[0]*0x3FF))
            | ((uint32_t)(coeff[1]*0x3FF)<<10)
            | ((uint32_t)(coeff[2]*0x3FF)<<20);
    }
    return 0;
}

}}}
