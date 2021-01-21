#ifndef __POWER_LIB_H_
#define __POWER_LIB_H_

#include <stdint.h>


/**
 * @brief  Put to sleep mode
 */
void power_sleep();

/**
 * @brief  Wake up from sleep mode
 */
void power_wakeup();

/**
 * @brief  Reboot the device
 */
void power_restart();

/**
 * @brief  Shut down the device
 */
void power_shutdown();

/**
 * @brief  Get the battery status
 * 
 * @param percent         Address of a variable to store the battery percent
 * 
 * @return
 *     - Voltage of battery in mV
 * 
 */
uint16_t power_get_battery(uint8_t* percent);

#endif
