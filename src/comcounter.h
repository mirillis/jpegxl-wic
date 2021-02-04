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

#ifndef __MRLSJXLCODECWICCOMCOUNTER_H
#define __MRLSJXLCODECWICCOMCOUNTER_H

//----------------------------------------------------------------------------
// NAMESPACE
//----------------------------------------------------------------------------
namespace mrls { namespace jxlcodec { namespace wic {



//============================================================================
//                              COMCOUNTER
//============================================================================
class COMCounter {
public:
    inline static COMCounter& instance(void) {
        static COMCounter obj;
        return obj;
    }
    LONG num_obj_lock;
    LONG num_server_lock;

private:
    COMCounter() : num_obj_lock(0), num_server_lock(0) { /*empty*/ }
    COMCounter(const COMCounter& obj) { /*empty*/ }
    COMCounter& operator=(const COMCounter& obj) { /*empty*/ return *this; }
};

}}}

#endif
