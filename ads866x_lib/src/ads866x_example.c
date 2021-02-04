#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"
#include "time.h"
#include "api_os.h"
#include "api_debug.h"
#include "api_hal_spi.h"
#include "api_hal_uart.h"
#include "api_hal_gpio.h"
#include "api_hal_pm.h"
#include "string.h"

#include "spi_lib.h"
#include "gpio_lib.h"

// Please note that the pin nomenclature has been taken with respect to the ADC's perspective
#define SCLK_PIN     	GPIO_PIN2		// Power Down and Serial Clock Input Pin of the ADS8664
#define DOUT_PIN     	GPIO_PIN4		// Serial Data Output Pin of the ADS8664
#define DIN_PIN     	GPIO_PIN3		// Serial Data Input Pin of the ADS8664
#define RST_PD_PIN      GPIO_PIN5		// Hard Reset and Power Down Pin of the ADS8664
#define CS_PIN      	GPIO_PIN1		// Chip Select Pin for the ADS8664

#define LSBFIRST 0
#define MSBFIRST 1

#define MAIN_TASK_STACK_SIZE    (1024 * 2)
#define MAIN_TASK_PRIORITY      0
#define MAIN_TASK_NAME          "Spi Test Task"

static HANDLE mainTaskHandle = NULL;

typedef enum{
    ADC_CHANNEL0 = 0,   // output    mode
    ADC_CHANNEL1,       // input     mode
    ADC_CHANNEL2,    	// interrupt mode
    ADC_CHANNEL3
}ADC_CHANNEL;

bool initialize_spi_pins()
{
	// for(uint8_t i=0;i<POWER_TYPE_MAX;++i)
    //     PM_PowerEnable(i,true);

	PM_PowerEnable(POWER_TYPE_VPAD, true);

	bool err;

	GPIO_config_t sclk_conf = {
		.mode         = GPIO_MODE_OUTPUT,
		.pin          = SCLK_PIN,
		.defaultLevel = GPIO_LEVEL_LOW
	};

	GPIO_config_t dout_conf = {
		.mode         = GPIO_MODE_INPUT,
		.pin          = DOUT_PIN,
		.defaultLevel = GPIO_LEVEL_LOW
	};

	GPIO_config_t din_conf = {
		.mode         = GPIO_MODE_OUTPUT,
		.pin          = DIN_PIN,
		.defaultLevel = GPIO_LEVEL_LOW
	};

	GPIO_config_t rst_pd_conf = {
		.mode         = GPIO_MODE_OUTPUT,
		.pin          = RST_PD_PIN,
		.defaultLevel = GPIO_LEVEL_HIGH
	};

	GPIO_config_t cs_conf = {
		.mode         = GPIO_MODE_OUTPUT,
		.pin          = CS_PIN,
		.defaultLevel = GPIO_LEVEL_HIGH
	};

	err = GPIO_Init(sclk_conf);
	if(!err)
	{
		Trace(1,"Initializing GPIO %d failed!", sclk_conf.pin);
		return false;
	}

	err = GPIO_Init(dout_conf);
	if(!err)
	{
		Trace(1,"Initializing GPIO %d failed!", dout_conf.pin);
		return false;
	}

	err = GPIO_Init(din_conf);
	if(!err)
	{
		Trace(1,"Initializing GPIO %d failed!", din_conf.pin);
		return false;
	}

	err = GPIO_Init(rst_pd_conf);
	if(!err)
	{
		Trace(1,"Initializing GPIO %d failed!", rst_pd_conf.pin);
		return false;
	}

	err = GPIO_Init(cs_conf);
	if(!err)
	{
		Trace(1,"Initializing GPIO %d failed!", cs_conf.pin);
		return false;
	}

	return true;
}

void yield(void) {};

void select_channel_0()
{
	Trace(1,"Selecting ADS866x channel 0!");

	gpio_set_state(CS_PIN, GPIO_LEVEL_LOW);
	for(uint8_t i = 0; i < 32; ++i)
	{
		if (i <= 2)
			gpio_set_state(DIN_PIN, GPIO_LEVEL_HIGH);
		else
			gpio_set_state(DIN_PIN, GPIO_LEVEL_LOW);
		
		gpio_set_state(SCLK_PIN, GPIO_LEVEL_HIGH);
		OS_Sleep(10);

		gpio_set_state(SCLK_PIN, GPIO_LEVEL_LOW);
		OS_Sleep(10);

	}
	gpio_set_state(CS_PIN, GPIO_LEVEL_HIGH);
}

uint16_t shiftIn(uint8_t dout, uint8_t sclk, uint8_t bitOrder)
{
	uint16_t value = 0;
    for(uint16_t i = 0; i < 12; ++i) 
	{
		gpio_set_state(SCLK_PIN, GPIO_LEVEL_HIGH);
		OS_Sleep(10);
        if(bitOrder == LSBFIRST)
            value |= gpio_get_state(DOUT_PIN) << i;
        else
        	value |= gpio_get_state(DOUT_PIN) << (11 - i);
		
		gpio_set_state(SCLK_PIN, GPIO_LEVEL_LOW);
		OS_Sleep(10);

    }
    return value;	
} 


long read_value()
{

	uint32_t value = 0;
	uint16_t data = 0;

	// Trace(1, "Reading Value");

	// Driving the CS Pin low to initiate a read
	gpio_set_state(CS_PIN, GPIO_LEVEL_LOW);
	OS_Sleep(50);


	// Pulse the clock pin 16 times to allow conversion
	for (uint8_t i = 0; i < 16; i++)
	// for (uint8_t i = 0; i < 32; i++)
	{
		gpio_set_state(SCLK_PIN, GPIO_LEVEL_HIGH);
		OS_Sleep(10);
        gpio_set_state(SCLK_PIN, GPIO_LEVEL_LOW);
		OS_Sleep(10);
	}

	// Pulse the clock pin 12 times to read_value the data
	data = shiftIn(DOUT_PIN, SCLK_PIN, MSBFIRST);

	for (uint8_t i = 0; i < 4; i++)
	{
		gpio_set_state(SCLK_PIN, GPIO_LEVEL_HIGH);
		OS_Sleep(10);
        gpio_set_state(SCLK_PIN, GPIO_LEVEL_LOW);
		OS_Sleep(10);
	}

	// Driving the CS Pin high to end the read
	gpio_set_state(CS_PIN, GPIO_LEVEL_HIGH);
	OS_Sleep(50);

	value = (uint32_t)data;
	Trace(1,"Read Value: %u", value);

	// Minimum width of CS high is 20us for a valid reading
	OS_SleepUs(20);

	return value;
}

long read_average( uint8_t times)
{

	long avg, sum = 0;
	for ( uint8_t i = 0; i < times; i++) 
	{
		sum += read_value();
		yield();
	}

	avg = sum / times;
    Trace(1, "Average value = %ld", avg);

	return avg;
}


void read_adc_MainTask()
{
	OS_Sleep(10000);

	bool err = initialize_spi_pins();
	if (!err)
    {
        Trace(1, "SPI Pins Initialization Failed!");
        return;
    }
    else
        Trace(1, "SPI Pins Initialization Successful!");

    // err = init_spi_direct_polling(SPI1, SPI_CS_0, 1000000, SPI_LINE_4, false, 0, 0, true, SPI_DATA_BITS_8);
    // if (err == false)
    // {
    //     Trace(1, "SPI Initialization Failed!");
    //     return;
    // }
    // else
    //     Trace(1, "SPI Initialization Successful!");
		
	// select_channel(ADC_CHANNEL0);
	select_channel_0();

	while(1)
	{
		read_average(10);
		// OS_Sleep(500);
	}
}

void ads866x_lib_Main()
{
    mainTaskHandle = OS_CreateTask(read_adc_MainTask, NULL, NULL, MAIN_TASK_STACK_SIZE, MAIN_TASK_PRIORITY, 0, 0, MAIN_TASK_NAME);
    OS_SetUserMainHandle(&mainTaskHandle);
}


