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

#ifndef __MRLSJXLCODECWICWICBITMAPFRAMEDECODEJXL_H
#define __MRLSJXLCODECWICWICBITMAPFRAMEDECODEJXL_H

//----------------------------------------------------------------------------
// INCLUDES INTERNAL
//----------------------------------------------------------------------------
#include "common.h"
#include "wiccolorcontextjxl.h"
#include "decodinghandler.h"

//----------------------------------------------------------------------------
// NAMESPACE
//----------------------------------------------------------------------------
namespace mrls { namespace jxlcodec { namespace wic {



//============================================================================
//                        WIC BITMAP FRAME DECODE JXL 
//============================================================================
class WICBitmapFrameDecodeJXL : public IWICBitmapFrameDecode {
public:
    WICBitmapFrameDecodeJXL();
    virtual ~WICBitmapFrameDecodeJXL();
    HRESULT Initialize(IStream* pIStream, UINT index);
    HRESULT SetBufferOutput(void);

    //IUnknown
    ULONG STDMETHODCALLTYPE AddRef();
    ULONG STDMETHODCALLTYPE Release();
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);

    //IWICBitmapSource
    //-- REQUIRED
    virtual HRESULT STDMETHODCALLTYPE GetSize(UINT* pWidth, UINT* pHeight);
    virtual HRESULT STDMETHODCALLTYPE GetPixelFormat(
        WICPixelFormatGUID* pPixelFormat);
    virtual HRESULT STDMETHODCALLTYPE GetResolution(double* pDpiX,
        double* pDpiY);
    virtual HRESULT STDMETHODCALLTYPE CopyPixels(const WICRect* pRc,
        UINT stride, UINT bufferSize, BYTE* pBuffer);
    //-- OPTIONAL
    virtual HRESULT STDMETHODCALLTYPE CopyPalette(IWICPalette* pIPalette);

    //IWICBitmapFrameDecode
    virtual HRESULT STDMETHODCALLTYPE GetThumbnail(
        IWICBitmapSource** ppIThumbnail);
    virtual HRESULT STDMETHODCALLTYPE GetColorContexts(UINT cCount,
        IWICColorContext** ppIColorContexts, UINT* pcActualCount);
    virtual HRESULT STDMETHODCALLTYPE GetMetadataQueryReader(
        IWICMetadataQueryReader** ppIMetadataQueryReader);

private:
    int setHDRBuffer(void);
    int conv16To10(void* buf_in, void* buf_out, uint32_t width,
        uint32_t height);
    volatile ULONG num_ref;
    CRITICAL_SECTION criticalsection;
    WICColorContextJXL* wic_cc;
    DecodingHandler dechandler;
    bool flag_internal;
    BYTE* buf_hdr;
    size_t size_hdr;
};

}}}

#endif
