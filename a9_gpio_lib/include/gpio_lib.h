#ifndef __GPIO_LIB_H_
#define __GPIO_LIB_H_

#include "api_hal_gpio.h"

/**
 * @brief  Get the state from a GPIO
 * 
 *
 * @param gpio_num              GPIO number to get state
 * 
 * @return
 *     - 0 the GPIO input level is low
 *     - 1 the GPIO input level is high
 * 
 */
uint8_t gpio_get_state(GPIO_PIN gpio_num);

/**
 * @brief  Initialize GPIO as input and setup ISR
 * 
 *
 * @param gpio_num              GPIO number to set/reset
 * @param state                 Can be one of GPIO_LEVEL_LOW (0) or GPIO_LEVEL_HIGH (1)
 * 
 * @return
 *    - true:   Success
 *    - false:  Failure
 * 
 */
bool gpio_set_state(GPIO_PIN gpio_num, GPIO_LEVEL state);

/**
 * @brief  Initialize GPIO as input and setup ISR
 * 
 *
 * @param gpio_num                GPIO number to initialize ISR
 * @param default_level           Can be one of GPIO_LEVEL_LOW (0) or GPIO_LEVEL_HIGH (1)
 * @param debounce_time           Debounce time in milliseconds
 * @param interrupt_type          Interrupt type. Refer to the GPIO_INT_TYPE struct
 * @param callback                Interrupt callback function
 * 
 * @return
 *    - true:   Success
 *    - false:  Failure
 * 
 */
bool gpio_enable_pin_isr(GPIO_PIN gpio_num, GPIO_LEVEL default_level, uint16_t debounce_time, GPIO_INT_TYPE interrupt_type, PCallbackINT callback);

#endif