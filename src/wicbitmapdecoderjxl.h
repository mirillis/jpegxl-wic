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

#ifndef __MRLSJXLCODECWICWICBITMAPDECODERJXL_H
#define __MRLSJXLCODECWICWICBITMAPDECODERJXL_H

//----------------------------------------------------------------------------
// INCLUDES INTERNAL
//----------------------------------------------------------------------------
#include "common.h"
#include "wicbitmapframedecodejxl.h"

//----------------------------------------------------------------------------
// NAMESPACE
//----------------------------------------------------------------------------
namespace mrls { namespace jxlcodec { namespace wic {



//============================================================================
//                       WIC BITMAP DECODER JXL
//============================================================================
//NOTE: For now HDR images needs to be converted from R16G16B16A16 pixel format
//      to R10G10B10A2 pixel format.
class WICBitmapDecoderJXL : public IWICBitmapDecoder {
public:
    WICBitmapDecoderJXL();
    virtual ~WICBitmapDecoderJXL();

    //IUnknown
    ULONG STDMETHODCALLTYPE AddRef();
    ULONG STDMETHODCALLTYPE Release();
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);

    //IWICBitmapDecoder
    //-- REQUIRED
    HRESULT STDMETHODCALLTYPE QueryCapability(IStream* pIStream,
        DWORD* pCapability);
    HRESULT STDMETHODCALLTYPE Initialize(IStream* pIStream,
        WICDecodeOptions cacheOptions);
    HRESULT STDMETHODCALLTYPE GetContainerFormat(GUID* pguidContainerFormat);
    HRESULT STDMETHODCALLTYPE GetDecoderInfo(
        IWICBitmapDecoderInfo** ppIDecoderInfo);
    HRESULT STDMETHODCALLTYPE GetFrameCount(UINT* pCount);
    HRESULT STDMETHODCALLTYPE GetFrame(UINT index,
        IWICBitmapFrameDecode** ppIBitmapFrame);
    //-- OPTIONAL
    HRESULT STDMETHODCALLTYPE CopyPalette(IWICPalette* pIPalette);
    HRESULT STDMETHODCALLTYPE GetMetadataQueryReader(
        IWICMetadataQueryReader** ppIMetadataQueryReader);
    HRESULT STDMETHODCALLTYPE GetPreview(IWICBitmapSource** ppIBitmapSource);
    HRESULT STDMETHODCALLTYPE GetColorContexts(UINT cCount,
        IWICColorContext** ppIColorContexts, UINT* pActualCount);
    HRESULT STDMETHODCALLTYPE GetThumbnail(IWICBitmapSource** ppIThumbnail);

private:
    volatile ULONG num_ref;
    CRITICAL_SECTION criticalsection;
    IWICImagingFactory* wic_fact;
    WICBitmapFrameDecodeJXL* wic_frame;
    UINT index;
};

}}}

#endif
