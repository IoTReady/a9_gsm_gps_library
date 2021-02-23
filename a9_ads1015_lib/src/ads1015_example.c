
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

#include "api_os.h"
#include "api_debug.h"
#include "api_event.h"
#include "api_hal_i2c.h"

#include "i2c_lib.h"
#include "ads1015.h"

#define I2C_ADS I2C3

#define MAIN_TASK_STACK_SIZE    (2048 * 2)
#define MAIN_TASK_PRIORITY      0
#define MAIN_TASK_NAME          "Main Test Task"

#define SECOND_TASK_STACK_SIZE    (2048 * 2)
#define SECOND_TASK_PRIORITY      1
#define SECOND_TASK_NAME          "Second Test Task"

static HANDLE mainTaskHandle = NULL;
static HANDLE secondTaskHandle = NULL;


void EventDispatch(API_Event_t* pEvent)
{
    switch(pEvent->id)
    {
        case API_EVENT_ID_NO_SIMCARD:
            Trace(10,"!!NO SIM CARD%d!!!!",pEvent->param1);
            break;

        case API_EVENT_ID_SYSTEM_READY:
            Trace(1,"system initialize complete");
            break;

        case API_EVENT_ID_NETWORK_REGISTERED_HOME:
        case API_EVENT_ID_NETWORK_REGISTERED_ROAMING:
            Trace(2,"network register success");
            break;

        default:
            break;
    }
}


void SecondTask(void *pData)
{
    uint16_t adc_val;
    float milliVolts;

    I2C_Config_t config;

    config.freq = I2C_FREQ_100K;
    bool err = I2C_Init(I2C_ADS, config);
    if (!err)
        Trace(1,"Failed to initialize I2C%d!", I2C_ADS);
    else
        Trace(1,"Successfully initialized I2C%d!", I2C_ADS);

    OS_Sleep(20);

    while (!isConnected(I2C_ADS, ADS1015_ADDRESS_GND))
    {
        OS_Sleep(500);
        Trace(1,"AAAAA!");
    }

    Trace(1,"BBBBB!");

    while(1)
    {
        adc_val = getSingleEnded(I2C_ADS, 3, ADS1015_CONFIG_RATE_1600HZ, ADS1015_CONFIG_PGA_2);
        milliVolts = getMilliVolts(I2C_ADS, 3, ADS1015_CONFIG_RATE_1600HZ, ADS1015_CONFIG_PGA_2);
        Trace(1,"Data Read: %d", adc_val);
        Trace(1,"mV: %f", milliVolts);
        OS_Sleep(1000);
    }
}

void MainTask(void *pData)
{
    API_Event_t* event=NULL;
    OS_Sleep(5000);

    secondTaskHandle = OS_CreateTask(SecondTask,
        NULL, NULL, SECOND_TASK_STACK_SIZE, SECOND_TASK_PRIORITY, 0, 0, SECOND_TASK_NAME);

    while(1)
    {
        if(OS_WaitEvent(mainTaskHandle, (void**)&event, OS_TIME_OUT_WAIT_FOREVER))
        {
            EventDispatch(event);
            OS_Free(event->pParam1);
            OS_Free(event->pParam2);
            OS_Free(event);
        }
    }
}

void a9_ads1015_lib_Main(void)
{
    mainTaskHandle = OS_CreateTask(MainTask,
        NULL, NULL, MAIN_TASK_STACK_SIZE, MAIN_TASK_PRIORITY, 0, 0, MAIN_TASK_NAME);
    OS_SetUserMainHandle(&mainTaskHandle);
}
