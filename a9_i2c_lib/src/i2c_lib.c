#include "stdint.h"
#include "stdbool.h"
#include "time.h"
#include "api_os.h"
#include "api_debug.h"
#include "api_hal_i2c.h"
#include "api_hal_uart.h"
#include "string.h"

// Note: If len is greater than 1 byte , the function transmits LS byte first, so store bytes in "data" accordingly
bool i2cWrite(I2C_ID_t id, uint16_t slaveAddr, void* data, uint8_t len)
{
	I2C_Error_t res = I2C_Transmit(id, slaveAddr, data, len, I2C_DEFAULT_TIME_OUT);
	if(res != I2C_ERROR_NONE)
    {
		Trace(1, "I2C2 write err: %d", res);
        return false;
    }
    return true;    
}

uint8_t i2cRead8(I2C_ID_t id, uint16_t slaveAddr, uint8_t len)
{
    uint8_t buff;
	I2C_Error_t res = I2C_Receive(id, slaveAddr, &buff, len, I2C_DEFAULT_TIME_OUT);
	if(res != I2C_ERROR_NONE)
		Trace(1, "I2C2 read err: %d", res);
    return buff;
}

uint16_t i2cRead16(I2C_ID_t id, uint16_t slaveAddr, uint8_t len)
{
    uint16_t buff;
	I2C_Error_t res = I2C_Receive(id, slaveAddr, &buff, len, I2C_DEFAULT_TIME_OUT);
	if(res != I2C_ERROR_NONE)
		Trace(1, "I2C2 read err: %d", res);
    return buff;
}

bool isConnected(I2C_ID_t id, uint16_t slaveAddr)
{
    uint8_t dummy_data = 0x01;
    I2C_Error_t err = I2C_Transmit(id, slaveAddr, &dummy_data, 1, I2C_DEFAULT_TIME_OUT);
    if (err != I2C_ERROR_NONE)
        return (false); //Sensor did not ACK
    return (true);
}