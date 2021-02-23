#include "api_hal_gpio.h"
#include "api_debug.h"


uint8_t gpio_get_state(GPIO_PIN gpio_num)
{
    GPIO_LEVEL state;
    GPIO_Get(gpio_num, &state);
    // Trace(1,"Get GPIO PIN NUM %d state = %d", gpio_num , state);

    return state;
}

bool gpio_set_state(GPIO_PIN gpio_num, GPIO_LEVEL state)
{
    // GPIO_LEVEL state = &level;
    bool err = GPIO_Set(gpio_num, state);
    // Trace(1,"Set GPIO PIN NUM %d state = %d", gpio_num , state);

    return err;
}

bool gpio_enable_pin_isr(GPIO_PIN gpio_num, GPIO_LEVEL default_level, uint16_t debounce_time, GPIO_INT_TYPE interrupt_type, PCallbackINT callback)
{
    Trace(1, "Configuring GPIO NUM %d", gpio_num);

    GPIO_config_t io_conf = {
        .mode               = GPIO_MODE_INPUT_INT,
        .pin                = gpio_num,
        .defaultLevel       = default_level,
        .intConfig.debounce = debounce_time,
        .intConfig.type     = interrupt_type,
        .intConfig.callback = callback
    };
    
    bool err = GPIO_Init(io_conf);

    return err;
}
