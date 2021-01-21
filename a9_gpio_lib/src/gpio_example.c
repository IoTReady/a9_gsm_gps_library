#include "api_hal_gpio.h"
#include "stdint.h"
#include "stdbool.h"
#include "api_debug.h"
#include "api_os.h"
#include "api_hal_pm.h"
#include "api_os.h"
#include "api_event.h"

#include "gpio_lib.h"

#define BUTTON_GPIO       GPIO_PIN4
#define DEBOUNCE_TIME     500
#define LED_GPIO          GPIO_PIN27
#define INPUT_PIN         GPIO_PIN2

#define MAIN_TASK_STACK_SIZE    (1024 * 2)
#define MAIN_TASK_PRIORITY      0 
#define MAIN_TASK_NAME         "MAIN Test Task"

#define TEST_TASK_STACK_SIZE    (1024 * 2)
#define TEST_TASK_PRIORITY      1
#define TEST_TASK_NAME         "GPIO Test Task"

static HANDLE mainTaskHandle = NULL;
static HANDLE secondTaskHandle = NULL;


void callback_example(GPIO_INT_callback_param_t* param)
{
    Trace(1,"Interrupt triggered on pin %d", param->pin);

    GPIO_LEVEL statusNow;
    uint8_t pin_state = gpio_get_state(INPUT_PIN);
    Trace(1,"GPIO %d status now: %d", INPUT_PIN, pin_state);
}

void GPIO_TestTask()
{
    static GPIO_LEVEL ledLevel = GPIO_LEVEL_LOW;

    Trace(1,"GPIO Example main");

    bool err = gpio_enable_pin_isr(BUTTON_GPIO, GPIO_LEVEL_HIGH, DEBOUNCE_TIME, GPIO_INT_TYPE_FALLING_EDGE, callback_example);
    if (!err)
    {
        Trace(1,"Setting up interrupt failed!");
    }

    GPIO_config_t led_conf = {
        .mode         = GPIO_MODE_OUTPUT,
        .pin          = LED_GPIO,
        .defaultLevel = GPIO_LEVEL_LOW
    };
    err = GPIO_Init(led_conf);
    if (!err)
        Trace(1,"Initializing GPIO %d failed!", led_conf.pin);

    while(1)
    {
        ledLevel = (ledLevel == GPIO_LEVEL_HIGH) ? GPIO_LEVEL_LOW : GPIO_LEVEL_HIGH;
        Trace(1,"Setting LED Level toggle: %d",ledLevel);
        GPIO_SetLevel(led_conf, ledLevel);               //Set level
        OS_Sleep(1000);                                  //Sleep 1000 ms
    }
}

void EventDispatch(API_Event_t* pEvent)
{
    switch(pEvent->id)
    {
        default:
            break;
    }
}

void MainTask(void *pData)
{
    API_Event_t* event=NULL;

    secondTaskHandle = OS_CreateTask(GPIO_TestTask,
        NULL, NULL, TEST_TASK_STACK_SIZE, TEST_TASK_PRIORITY, 0, 0, TEST_TASK_NAME);

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


void a9_gpio_lib_Main()
{
    mainTaskHandle = OS_CreateTask(MainTask ,
        NULL, NULL, MAIN_TASK_STACK_SIZE, MAIN_TASK_PRIORITY, 0, 0, MAIN_TASK_NAME);
    OS_SetUserMainHandle(&mainTaskHandle);
}
