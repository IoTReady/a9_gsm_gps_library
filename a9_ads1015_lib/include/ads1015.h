#ifndef __ADS1015_H_
#define __ADS1015_H_

#include <stdint.h>
#include "api_debug.h"

#define I2C_DEFAULT_TIME_OUT 10  //ms

// 7-bit unshifted default I2C Address
typedef enum{
    /// ADDR -> GND
    ADS1015_ADDRESS_GND = 0x48,
    /// ADDR -> VDD
    ADS1015_ADDRESS_VDD = 0x49,
    /// ADDR -> SDA
    ADS1015_ADDRESS_SDA = 0x4A,
    /// ADDR -> SCL
    ADS1015_ADDRESS_SCL = 0x4B,
} ADS1015_Address;


// PGA Setting
typedef enum{
    ADS1015_CONFIG_PGA_TWOTHIRDS = 0X0000,  // +/- 6.144v
    ADS1015_CONFIG_PGA_1 =  0X0200,         // +/- 4.096v
    ADS1015_CONFIG_PGA_2 =  0X0400,         // +/- 2.048v
    ADS1015_CONFIG_PGA_4 =  0X0600,         // +/- 1.024v
    ADS1015_CONFIG_PGA_8 =  0X0800,         // +/- 0.512v
    ADS1015_CONFIG_PGA_16 = 0X0A00,         // +/- 0.256v
} ADS1015_Gain;


// Sampling Rate Setting
typedef enum{
    ADS1015_CONFIG_RATE_128HZ =  0X0000,
    ADS1015_CONFIG_RATE_250HZ =  0x0020,
    ADS1015_CONFIG_RATE_490HZ =  0x0040,
    ADS1015_CONFIG_RATE_920HZ =  0x0060,
    ADS1015_CONFIG_RATE_1600HZ = 0x0080,
    ADS1015_CONFIG_RATE_2400HZ = 0x00A0,
    ADS1015_CONFIG_RATE_3300HZ = 0x00C0,

} ADS1015_Sampling;


//Pointer Register
#define ADS1015_POINTER_CONVERT      (0x00)
#define ADS1015_POINTER_CONFIG       (0x01)
#define ADS1015_POINTER_LOWTHRESH    (0x02)
#define ADS1015_POINTER_HITHRESH     (0x03)

#define ADS1015_CONFIG_MODE_CONT     (0x0000)
#define ADS1015_CONFIG_MODE_SINGLE   (0x0100)

#define ADS1015_CONFIG_OS_SINGLE       (0x8000)
#define ADS1015_CONFIG_MUX_SINGLE_0    (0x4000)
#define ADS1015_CONFIG_MUX_SINGLE_1    (0x5000)
#define ADS1015_CONFIG_MUX_SINGLE_2    (0x6000)
#define ADS1015_CONFIG_MUX_SINGLE_3    (0x7000)
#define ADS1015_CONFIG_MUX_DIFF_P0_N1  (0x0000)
#define ADS1015_CONFIG_MUX_DIFF_P0_N3  (0x1000)
#define ADS1015_CONFIG_MUX_DIFF_P1_N3  (0x2000)
#define ADS1015_CONFIG_MUX_DIFF_P2_N3  (0x3000)

/**
 * @brief  Get ADC raw reading for a single-ended analog input
 * 
 *
 * @param id                I2C ID of the bus used. Check I2C_ID_t
 * @param channel           ADC analog channel
 * @param sample_rate       Sampling rate. Check ADS1015_Sampling
 * @param gain              Programmable Gain Amplifier(PGA) setting. Check ADS1015_Gain
 * 
 * 
 * @return uint16_t: The raw reading for single-ended input
 * 
 */
uint16_t getSingleEnded(I2C_ID_t id, uint8_t channel, uint16_t sample_rate, uint16_t gain);

/**
 * @brief  Get ADC millivolts reading for a single-ended analog input
 * 
 *
 * @param id                I2C ID of the bus used. Check I2C_ID_t
 * @param channel           ADC analog channel
 * @param sample_rate       Sampling rate. Check ADS1015_Sampling
 * @param gain              Programmable Gain Amplifier(PGA) setting. Check ADS1015_Gain
 * 
 * 
 * @return float: The millivolt reading for single-ended input
 * 
 */
float getMilliVolts(I2C_ID_t id, uint8_t channel, uint16_t sample_rate, uint16_t gain);

#endif
