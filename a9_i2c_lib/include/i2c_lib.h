#ifndef __I2C_LIB_H_
#define __I2C_LIB_H_

#include <stdint.h>
#include "api_hal_i2c.h"


/**
 * @brief  Write data to an I2C bus
 * 
 *
 * @param id                I2C ID of the bus used. Check I2C_ID_t
 * @param slaveAddr         Slave address
 * @param data              Data to be sent
 * @param len               Length of data to be sent in bytes
 * 
 * @note If len is greater than 1 byte , the function transmits LS byte first, so store bytes in "data" accordingly
 * 
 * @return
 *    - true:   Success
 *    - false:  Failure
 * 
 */
bool i2cWrite(I2C_ID_t id, uint16_t slaveAddr, void* data, uint8_t len);


/**
 * @brief  Read 8-bit data from an I2C bus
 * 
 *
 * @param id                I2C ID of the bus used. Check I2C_ID_t
 * @param slaveAddr         Slave address
 * @param len               Length of data to be sent in bytes
 * 
 * 
 * @return uint8_t: The data read
 * 
 */
uint8_t i2cRead8(I2C_ID_t id, uint16_t slaveAddr, uint8_t len);

/**
 * @brief  Read 16-bit data from an I2C bus
 * 
 *
 * @param id                I2C ID of the bus used. Check I2C_ID_t
 * @param slaveAddr         Slave address
 * @param len               Length of data to be sent in bytes
 * 
 * 
 * @return uint16_t: The data read
 * 
 */
uint16_t i2cRead16(I2C_ID_t id, uint16_t slaveAddr, uint8_t len);

/**
 * @brief  Check if the slave is available
 * 
 *
 * @param id                I2C ID of the bus used. Check I2C_ID_t
 * @param slaveAddr         Slave address
 * 
 * 
 * @return
 *    - true:   Success; received ACK
 *    - false:  Failure
 * 
 */
bool isConnected(I2C_ID_t id, uint16_t slaveAddr);


#endif
