/* mbed Microcontroller Library
* Copyright (c) 2006-2013 ARM Limited
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
*/
#include "InterruptIn.h"

#if DEVICE_INTERRUPTIN

namespace mbed {

    InterruptIn::InterruptIn(PinName pin) {
    }

    InterruptIn::~InterruptIn() {
    }

    int InterruptIn::read() {
        return 0;
    }

    void InterruptIn::mode(PinMode pull) {
    }

    void InterruptIn::rise(void(*fptr)(void)) {
    }

    void InterruptIn::fall(void(*fptr)(void)) {
    }

    void InterruptIn::_irq_handler(uint32_t id, gpio_irq_event event) {
    }

#ifdef MBED_OPERATORS
    InterruptIn::operator int() {
        return read();
    }
#endif

} // namespace mbed

#endif
