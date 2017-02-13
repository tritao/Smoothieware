#include <cstdint>
#include <ctime>
#include "port_api.h"

extern "C"
{

// Port stubs
PinName port_pin(PortName port, int pin_n)
{
    return (PinName)(LPC_GPIO0_BASE + ((port << PORT_SHIFT) | pin_n));
}

// Watchdog stubs
void WDT_Init() {}
void WDT_Start() {}
void WDT_Feed() {}
void WDT_ClrTimeOutFlag() {}

void PINSEL_ConfigPin() {}

void FIO_SetDir() {}
void FIO_SetValue() {}
void FIO_ClearValue() {}
void FIO_ReadValue() {}

void set_high_on_debug() {}

void wait_us() {}
uint32_t us_ticker_read()
{
    return clock() * CLOCKS_PER_SEC;
}

void pwmout_init() {}

// Interrupt controller stubs
void NVIC_SetVector(IRQn_Type IRQn, uint32_t vector) {}
uint32_t NVIC_GetVector(IRQn_Type IRQn) { return 0; }

//void NVIC_SetPriorityGrouping(uint32_t PriorityGroup) {}

uint32_t  __end__;
uint32_t  __malloc_free_list;
uint32_t  _sbrk(int size) { return 0; }

uint32_t SystemCoreClock = 0;

}
