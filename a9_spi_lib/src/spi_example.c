#include "stdint.h"
#include "stdbool.h"
#include "time.h"
#include "api_os.h"
#include "api_debug.h"
#include "api_hal_spi.h"
#include "api_hal_uart.h"
#include "string.h"

#include "spi_lib.h"

/// Only one DEMO can be selected for each compilation !!!
// #define SPI_DIRECT_DEMO
// #define SPI_DMA_DEMO
#define SPI_IRQ_DEMO

#define MAIN_TASK_STACK_SIZE    (1024 * 2)
#define MAIN_TASK_PRIORITY      0
#define MAIN_TASK_NAME          "Spi Test Task"

static HANDLE mainTaskHandle = NULL;


/// SPI DIRECT Polling Demo
#if defined(SPI_DIRECT_DEMO)
void Spi_MainTask()
{
	uint8_t *send_buff,*rev_buff;

    bool err = init_spi_direct_polling(SPI1, SPI_CS_0, 1000000, SPI_LINE_4, false, 0, 0, true, SPI_DATA_BITS_8);
    if (err == false)
    {
        Trace(1, "SPI Initialization Failed!");
        return;
    }
    else
        Trace(1, "SPI Initialization Successful!");
    

	send_buff = OS_Malloc(10);
	rev_buff = OS_Malloc(10);
	memset(send_buff, 0, sizeof(send_buff));
	memset(rev_buff, 0, sizeof(rev_buff));

	strcpy(send_buff, "123456789");

	while(1)
	{
		SPI_WriteReadData(SPI1, send_buff, rev_buff, 9);
		OS_Sleep(100);
	}
}

/// SPI DMA Polling Demo
#elif defined(SPI_DMA_DEMO)
void Spi_MainTask()
{
	uint8_t *send_buff,*rev_buff;
    OS_Sleep(10000);
    Trace(1, "SPI Initialization STARTED!");
    bool err = init_spi_dma_polling(SPI1, SPI_CS_0, 1000000, SPI_LINE_4, false, 0, 0, true, SPI_DATA_BITS_8);
    if (err == false)
    {
        Trace(1, "SPI Initialization Failed!");
        return;
    }
    else
        Trace(1, "SPI Initialization Successful!");

	send_buff = OS_Malloc(4000);
	rev_buff = OS_Malloc(4000);
	memset(send_buff, 0xaa, sizeof(send_buff));
    memset(rev_buff, 0, sizeof(rev_buff));
    
	while(1)
	{
		SPI_DmaReadWriteData(SPI1, send_buff, rev_buff, sizeof(send_buff));

		while((!SPI_IsTxDmaDone(SPI1))&&(!SPI_IsRxDmaDone(SPI1)));
		SPI_ClearTxDmaDone(SPI1);
		SPI_ClearRxDmaDone(SPI1);
		OS_Sleep(100);
	}
}

/// SPI IRQ DEMO
#elif defined(SPI_IRQ_DEMO)
uint8_t spi_finish_flag = 0;
#define SPI_START "Spi Irq Test Start"
#define SPI_FINISH "Spi Irq Tx Finished"
void Spi_Handler(SPI_Irq_Flags_t Flags)
{
	if(Flags.txDmaDone)
	{
		SPI_ClearTxDmaDone(SPI1);
		spi_finish_flag = 1;
	}
}

void Spi_MainTask()
{
	uint8_t *send_buff;
	send_buff = OS_Malloc(4000);
	memset(send_buff, 0xab, 4000);

	OS_Sleep(5000);

    SPI_Irq_Flags_t irq_flags = {0,0,1,0,0};
    bool err = init_spi_dma_irq(SPI1, SPI_CS_0, 1000000, SPI_LINE_4, false, 0, 0, true, SPI_DATA_BITS_8, Spi_Handler, irq_flags);
    if (err == false)
    {
        Trace(1, "SPI Initialization Failed!");
        return;
    }
    else
        Trace(1, "SPI Initialization Successful!");
    Trace(2, SPI_START);
	SPI_Write(SPI1, send_buff, 4000);

	while(!spi_finish_flag)
	{
		OS_Sleep(100); //must sleep for a period of time,otherwise other tasks can't run
	}

	OS_Free(send_buff);
    SPI_Close(SPI1);
    Trace(2,SPI_FINISH);
    
	while(1)
	{
		OS_Sleep(3000);
	}
}
#endif

void a9_spi_lib_Main()
{
    mainTaskHandle = OS_CreateTask(Spi_MainTask ,
        NULL, NULL, MAIN_TASK_STACK_SIZE, MAIN_TASK_PRIORITY, 0, 0, MAIN_TASK_NAME);
    OS_SetUserMainHandle(&mainTaskHandle);
}


