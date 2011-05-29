/*
* Copyright (c) 2008-2009 Apple Inc. All rights reserved.
* Copyright (c) 2011 MLBA. All rights reserved.
*
* @MLBA_OPEN_LICENSE_HEADER_START@
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* @MLBA_OPEN_LICENSE_HEADER_END@
*/


#include "../include/xdispatch/dispatch"
#include "../core/platform/atomic.h"
#include "cxx_tests.h"

struct BeFreed {

    BeFreed() : ref_ct(new ATOMIC_INT) {
        *ref_ct = 1;
    }
    BeFreed(const BeFreed& other) : ref_ct(other.ref_ct){
        dispatch_atomic_inc(ref_ct);
    }
    ~BeFreed(){
        if(dispatch_atomic_dec(ref_ct) == 0) {
            delete ref_ct;
            MU_PASS("");
        }
    }

    void someFunction() const { /* Do nothing (tm) */ }

    ATOMIC_INT* ref_ct;
};

void dispatch_outer(){
#ifdef XDISPATCH_HAS_BLOCKS
    BeFreed outer;

    xdispatch::main_queue().async(${
        outer.someFunction();
    });
#endif
}

# include <tr1/functional>

std::tr1::function<void(void)>* func;

void create_lambda(){
    BeFreed f;

    func = new std::tr1::function<void(void)>([=](){ f.someFunction(); });
}

void run_lambda(){
    (*func)();
    delete func;
}

extern "C" void cxx_free_lambda(){
    MU_BEGIN_TEST(cxx_free_lambda);

    dispatch_outer();
    xdispatch::exec();

    //create_lambda();
    //run_lambda();
    //sleep(100);

    MU_END_TEST;
}
