#include "i2c_lib.h"
#include "ads1015.h"
#include "api_os.h"

float getMultiplierToMilliVolts(uint16_t gain)
{
    float multiplierToVolts = 1.0F;
	switch (gain)
    {
    case (ADS1015_CONFIG_PGA_TWOTHIRDS):
        multiplierToVolts = 3.0F;
        break;
    case (ADS1015_CONFIG_PGA_1):
        multiplierToVolts = 2.0F;
        break;
    case (ADS1015_CONFIG_PGA_2):
        multiplierToVolts = 1.0F;
        break;
    case (ADS1015_CONFIG_PGA_4):
        multiplierToVolts = 0.5F;
        break;
    case (ADS1015_CONFIG_PGA_8):
        multiplierToVolts = 0.25F;
        break;
    case (ADS1015_CONFIG_PGA_16):
        multiplierToVolts = 0.125F;
        break;		
	default:
		multiplierToVolts = 1.0F;
    }

    return multiplierToVolts;
}

float convertToMilliVolts(uint16_t adc_val, uint16_t gain)
{
    float multiplier = getMultiplierToMilliVolts(gain);
    float millivolts = adc_val * multiplier;

    return millivolts;
}

//Returns the decimal value of sensor channel single-ended input
// uint16_t getSingleEnded(uint8_t channel, ADS1015_Sampling sample_rate, ADS1015_Gain gain)
uint16_t getSingleEnded(I2C_ID_t id, uint8_t channel, uint16_t sample_rate, uint16_t gain)
{
    if (channel > 3) {
		return 0;
	}
    
    // I2C_Error_t err;
    bool err;

    uint16_t adc_val = 0;
	uint32_t config = ADS1015_CONFIG_OS_SINGLE   |
					  ADS1015_CONFIG_MODE_CONT |
					  sample_rate;
			
	config |= gain;		  
	
	switch (channel)
    {
    case 0:
        config |= ADS1015_CONFIG_MUX_SINGLE_0;
        break;
    case 1:
        config |= ADS1015_CONFIG_MUX_SINGLE_1;
        break;
    case 2:
        config |= ADS1015_CONFIG_MUX_SINGLE_2;
        break;
    case 3:
        config |= ADS1015_CONFIG_MUX_SINGLE_3;
        break;
    }

    // Adding the Pointer Config Address to data to be transmitted
    config |= 0x010000;
    // uint32_t config_org = 0b000000011111010010000000;
    // config = 0b100000001111010000000001;
    // I2C_Transmit sends LS Byte first, and since the data is 3 bytes, the LS Byte and MS Byte is interchanged
    config = (config >> 16) | (((config >> 8) & 0xFF) << 8) | ((config & 0xFF) << 16);
    Trace(1,"CCCCC!");

    // err = I2C_Transmit(I2C_ADS, ADS1015_ADDRESS_GND, &config, 3, I2C_DEFAULT_TIME_OUT);
    err = i2cWrite(id, ADS1015_ADDRESS_GND, &config, 3);
    OS_Sleep(1);
    Trace(1,"DDDDD!");

    uint8_t conversion_register = 0x00;
    // TODO: Test with ADS1015_POINTER_CONVERT. If does not work, uncomment above line: uint8_t conversion_register = 0x00;
    // err = I2C_Transmit(I2C_ADS, ADS1015_ADDRESS_GND, ADS1015_POINTER_CONVERT, 1, I2C_DEFAULT_TIME_OUT);
    err = i2cWrite(id, ADS1015_ADDRESS_GND, &conversion_register, 1);
    Trace(1,"EEEEE!");

    // for (int i = 0; i <= 10; i++)
    // {
        // TODO: Remove len and test
    adc_val = (i2cRead16(id, ADS1015_ADDRESS_GND, 2) << 4);
        //  err = I2C_Receive(I2C_ADS, ADS1015_ADDRESS_GND, &adc_val, 2, I2C_DEFAULT_TIME_OUT);
    // }
    Trace(1,"FFFFF!");
    Trace(1,"ADC Value = %d!", adc_val);

    float milliVolts = convertToMilliVolts(adc_val, gain);

    Trace(1,"Corresponding Voltage= %f!", milliVolts);

    // float adc_val2 = adc_val / 10;
    // Trace(1,"ADC Value after div= %f!", adc_val2);
    

    // Trace(1,"Average ADC Read Value: %d", adc_val);

    return adc_val;
}

float getMilliVolts(I2C_ID_t id, uint8_t channel, uint16_t sample_rate, uint16_t gain)
{
    uint16_t adc_val = getSingleEnded(id, channel, sample_rate, gain);
    float mv = convertToMilliVolts(adc_val, gain);

    return mv;
}