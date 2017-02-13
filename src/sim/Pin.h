#ifndef SIMPIN_H
#define SIMPIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "PinNames.h"

namespace mbed {
    class PwmOut;
    class InterruptIn;
}

class Pin {
public:
    Pin();

    Pin* from_string(std::string value);

    inline bool connected() {
        return this->valid;
    }

    inline bool equals(const Pin& other) const {
        return (this->pin == other.pin) && (this->port == other.port);
    }

    inline Pin* as_output() {
        return this;
    }

    inline Pin* as_input() {
        return this;
    }

    Pin* as_open_drain(void);

    Pin* as_repeater(void);

    Pin* pull_up(void);

    Pin* pull_down(void);

    Pin* pull_none(void);

    inline bool get() const {
        if (!this->valid) return false;
        return true;
    }

    inline void set(bool value)
    {
        if (!this->valid) return;
    }

    mbed::PwmOut *hardware_pwm();

    mbed::InterruptIn *interrupt_pin();

    bool is_inverting() const { return inverting; }
    void set_inverting(bool f) { inverting = f; }

    LPC_GPIO_TypeDef* port;

    unsigned char pin;
    char port_number;

private:
    struct {
        bool inverting : 1;
        bool valid : 1;
    };
};

#endif
