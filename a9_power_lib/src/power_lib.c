#include "api_hal_pm.h"
#include "api_debug.h"


void power_sleep()
{
    PM_SleepMode(true);
}

void power_wakeup()
{
    PM_SleepMode(false);
}

void power_restart()
{
    PM_Restart();
}

void power_shutdown()
{
    PM_ShutDown();
}

uint16_t power_get_battery(uint8_t* percent)
{
    uint16_t voltage = PM_Voltage(percent);
    return voltage;
}