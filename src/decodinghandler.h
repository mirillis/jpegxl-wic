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

#ifndef __MRLSJXLCODECWICDECODINGHANDLER_H
#define __MRLSJXLCODECWICDECODINGHANDLER_H

//----------------------------------------------------------------------------
// INCLUDES INTERNAL
//----------------------------------------------------------------------------
#include "common.h"
#include "jxl/decode.h"
#include "jxl/thread_parallel_runner.h"

//----------------------------------------------------------------------------
// NAMESPACE
//----------------------------------------------------------------------------
namespace mrls { namespace jxlcodec { namespace wic {



//============================================================================
//                            DECODING HANDLER
//============================================================================
class DecodingHandler {
public:
    struct OutputMetadata {
        JxlDataType jxl_datatype;
        size_t size_chan;
        size_t num_chan;
        size_t size_pix;
    };
    DecodingHandler();
    int init(void);
    int release(void);
    int decode(void);
    int decodeMetadata(void);
    int recreateBufferInput(size_t size);
    int recreateBufferOutput(size_t size);
    inline uint8_t* getBufferInput(void) const { return buf_in; }
    inline uint8_t* getBufferOutput(void) const { return buf_out; }
    inline size_t getBufferInputSize(void) const { return size_in; }
    inline size_t getBufferOutputSize(void) const { return size_out; }
    inline const OutputMetadata& getOutputMetadata(void) const {
        return outmd;
    }
    inline const JxlBasicInfo& getMetadata(void) const { return jxl_info; };

private:
    int getOutputMetadata(size_t size_chan, OutputMetadata* outmd);
    static const size_t NUM_CHAN_OUT;
    OutputMetadata outmd;
    JxlBasicInfo jxl_info;
    JxlDecoder* jxl_dec;
    void* jxl_runner;
    uint8_t* buf_in;
    uint8_t* buf_out;
    size_t size_in;
    size_t size_out;
    bool flag_init;
};

}}}

#endif
