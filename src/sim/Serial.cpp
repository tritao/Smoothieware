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
#include "Serial.h"

#if DEVICE_SERIAL

namespace mbed {

    Serial::Serial(PinName tx, PinName rx, const char *name) : Stream(name) {
    }

    void Serial::baud(int baudrate) {
    }

    void Serial::format(int bits, Parity parity, int stop_bits) {
    }

    int Serial::readable() {
        return 0;
    }


    int Serial::writeable() {
        return 0;
    }

    void Serial::attach(void(*fptr)(void), IrqType type) {
    }


    void Serial::_irq_handler(uint32_t id, SerialIrq irq_type) {
    }

    int Serial::_getc() {
        return 0;
    }

    int Serial::_putc(int c) {
        return c;
    }

} // namespace mbed

#endif
