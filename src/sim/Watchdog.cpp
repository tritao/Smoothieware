#include "Watchdog.h"
#include "Kernel.h"

Watchdog::Watchdog(uint32_t timeout, WDT_ACTION action)
{
}

void Watchdog::feed()
{
}

void Watchdog::on_module_loaded()
{
    register_for_event(ON_IDLE);
    feed();
}

void Watchdog::on_idle(void*)
{
    feed();
}
