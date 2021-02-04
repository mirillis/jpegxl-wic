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
#include "decodinghandler.h"

//----------------------------------------------------------------------------
// NAMESPACE
//----------------------------------------------------------------------------
namespace mrls { namespace jxlcodec { namespace wic {



//============================================================================
//                            DECODING HANDLER
//==[ constructor ]===========================================================
//============================================================================
const size_t DecodingHandler::NUM_CHAN_OUT= 4;
DecodingHandler::DecodingHandler() : size_in(0), size_out(0), flag_init(false),
buf_in(nullptr), buf_out(nullptr), jxl_dec(nullptr), jxl_runner(nullptr) {
    memset(&jxl_info, 0, sizeof(JxlBasicInfo));
    memset(&outmd, 0, sizeof(OutputMetadata));
}


//==[ init ]==================================================================
//============================================================================
int DecodingHandler::init() {
    if(flag_init) {
        return 1;
    }
    JxlDecoderStatus jxl_sts= JXL_DEC_SUCCESS;
    jxl_dec= JxlDecoderCreate(nullptr);
    if(!jxl_dec) {
        return 1;
    }
    jxl_runner= JxlThreadParallelRunnerCreate(
        nullptr, JxlThreadParallelRunnerDefaultNumWorkerThreads());
    if(!jxl_runner) {
        return 1;
    }
    jxl_sts= JxlDecoderSubscribeEvents(jxl_dec,
        JXL_DEC_BASIC_INFO | JXL_DEC_COLOR_ENCODING | JXL_DEC_FULL_IMAGE);
    if(jxl_sts != JXL_DEC_SUCCESS) {
        return 1;
    }
    jxl_sts= JxlDecoderSetParallelRunner(jxl_dec, JxlThreadParallelRunner,
        jxl_runner);
    if(jxl_sts != JXL_DEC_SUCCESS) {
        return 1;
    }
    flag_init= true;
    return 0;
}


//==[ release ]===============================================================
//============================================================================
int DecodingHandler::release() {
    recreateBufferInput(0);
    recreateBufferOutput(0);
    if(jxl_runner) {
        JxlThreadParallelRunnerDestroy(jxl_runner);
        jxl_runner= NULL;
    }
    if(jxl_dec) {
        JxlDecoderDestroy(jxl_dec);
        jxl_dec= NULL;
    }
    size_in= 0;
    size_out= 0;
    flag_init= false;
    return 0;
}


//==[ decode ]================================================================
//============================================================================
int DecodingHandler::decode() {
    JxlDecoderStatus jxl_sts= JXL_DEC_SUCCESS;
    if(decodeMetadata()) {
        return 1;
    }
    JxlPixelFormat jxl_pixfmt;
    memset(&jxl_pixfmt, 0, sizeof(JxlPixelFormat));
    jxl_pixfmt.num_channels= outmd.num_chan;
    jxl_pixfmt.data_type= outmd.jxl_datatype;
    jxl_pixfmt.endianness= JXL_NATIVE_ENDIAN;
    jxl_pixfmt.align= 0;
    jxl_sts= JxlDecoderSetInput(jxl_dec, buf_in, size_in);
    if(jxl_sts != JXL_DEC_SUCCESS) {
        return 1;
    }
    while(true) {
        jxl_sts= JxlDecoderProcessInput(jxl_dec);
        if(jxl_sts == JXL_DEC_ERROR || jxl_sts == JXL_DEC_NEED_MORE_INPUT) {
            return 1;
        } else
        if(jxl_sts == JXL_DEC_BASIC_INFO) {
            jxl_sts= JxlDecoderGetBasicInfo(jxl_dec, &jxl_info);
            if(jxl_sts != JXL_DEC_SUCCESS) {
                return 1;
            }
        } else
        if(jxl_sts == JXL_DEC_COLOR_ENCODING) {
            //TODO
        } else
        if(jxl_sts == JXL_DEC_NEED_IMAGE_OUT_BUFFER) {
            size_t size= 0;
            jxl_sts= JxlDecoderImageOutBufferSize(jxl_dec, &jxl_pixfmt, &size);
            if(jxl_sts != JXL_DEC_SUCCESS) {
                return 1;
            }
            if(size != jxl_info.xsize*jxl_info.ysize*outmd.size_pix) {
                return 1;
            }
            if(buf_out) {
                return 1;
            }
            if(recreateBufferOutput(size)) {
                return 1;
            }
            jxl_sts= JxlDecoderSetImageOutBuffer(jxl_dec, &jxl_pixfmt,
                buf_out, size_out);
            if(jxl_sts != JXL_DEC_SUCCESS) {
                return 1;
            }
        } else
        if(jxl_sts == JXL_DEC_FULL_IMAGE) {
        } else
        if(jxl_sts == JXL_DEC_SUCCESS) {
            break;
        } else {
            return 1;
        }
    }
    size_t size_remain= JxlDecoderReleaseInput(jxl_dec);
    return 0;
}


//==[ decodeMetadata ]========================================================
//============================================================================
int DecodingHandler::decodeMetadata() {
    JxlDecoderStatus jxl_sts= JXL_DEC_SUCCESS;
    memset(&jxl_info, 0, sizeof(JxlBasicInfo));
    JxlPixelFormat jxl_pixfmt;
    memset(&jxl_pixfmt, 0, sizeof(JxlPixelFormat));
    jxl_pixfmt.num_channels= NUM_CHAN_OUT;
    jxl_pixfmt.data_type= JXL_TYPE_FLOAT;
    jxl_pixfmt.endianness= JXL_NATIVE_ENDIAN;
    jxl_pixfmt.align= 0;
    jxl_sts= JxlDecoderSetInput(jxl_dec, buf_in, size_in);
    if(jxl_sts != JXL_DEC_SUCCESS) {
        return 1;
    }
    while(true) {
        jxl_sts= JxlDecoderProcessInput(jxl_dec);
        if(jxl_sts == JXL_DEC_ERROR || jxl_sts == JXL_DEC_NEED_MORE_INPUT) {
            return 1;
        } else
        if(jxl_sts == JXL_DEC_BASIC_INFO) {
            jxl_sts= JxlDecoderGetBasicInfo(jxl_dec, &jxl_info);
            if(jxl_sts != JXL_DEC_SUCCESS) {
                return 1;
            }
            break;
        }
    }
    size_t size_remain= JxlDecoderReleaseInput(jxl_dec);
    memset(&outmd, 0, sizeof(OutputMetadata));
    if(getOutputMetadata(jxl_info.bits_per_sample/8, &outmd));
    return 0;
}


//=[ recreateBufferInput ]====================================================
//============================================================================
int DecodingHandler::recreateBufferInput(size_t size) {
    if(size != size_in) {
        if(!buf_in) {
            free(buf_in);
            buf_in= nullptr;
        }
        if(size > 0) {
            buf_in= (uint8_t*)malloc(size);
            if(!buf_in) return E_OUTOFMEMORY;
        }
        size_in= size;
    }
    return 0;
}


//=[ recreateBufferOutput ]===================================================
//============================================================================
int DecodingHandler::recreateBufferOutput(size_t size) {
    if(size != size_out) {
        if(!buf_out) {
            free(buf_out);
            buf_out= nullptr;
        }
        if(size > 0) {
            buf_out= (uint8_t*)malloc(size);
            if(!buf_out) return E_OUTOFMEMORY;
        }
        size_out= size;
    }
    return 0;
}


//==[ getOutputMetadata ]==[ private ]========================================
//============================================================================
int DecodingHandler::getOutputMetadata(size_t size_chan,
OutputMetadata* outmd) {
    if(!outmd) return 1;
    switch(size_chan) {
        case 1: {
            outmd->jxl_datatype= JXL_TYPE_UINT8;
            outmd->size_chan= 1;
            outmd->num_chan= NUM_CHAN_OUT;
            outmd->size_pix= outmd->size_chan*outmd->num_chan;
            return 0;
        }
        case 2: {
            outmd->jxl_datatype= JXL_TYPE_UINT16;
            outmd->size_chan= 2;
            outmd->num_chan= NUM_CHAN_OUT;
            outmd->size_pix= outmd->size_chan*outmd->num_chan;
            return 0;
        }
    }
    return 1;
}

}}}
