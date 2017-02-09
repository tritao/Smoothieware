#include "ADC/adc.h"

namespace mbed {

ADC::ADC(int sample_rate, int cclk_div) {}

//Enable/disable ADC on pin according to state
//and also select/de-select for next conversion
void ADC::setup(PinName pin, int state) {}

//Return enabled/disabled state of ADC on pin
int ADC::setup(PinName pin) { return 0;  }

//Enable/disable burst mode according to state
void ADC::burst(int state) {}

//Select channel already setup
void ADC::select(PinName pin) {}

//Return burst mode enabled/disabled
int ADC::burst(void) { return 0; }

//Set interrupt enable/disable for pin to state
void ADC::interrupt_state(PinName pin, int state) {}

//Append custom interrupt handler for pin
void ADC::append(PinName pin, void(*fptr)(uint32_t value)) {}

//Unappend custom interrupt handler for pin
void ADC::unappend(PinName pin) {}

//Append custom global interrupt handler
void ADC::append(void(*fptr)(int chan, uint32_t value)) {}

int ADC::_pin_to_channel(PinName pin) { return 0; }

}
