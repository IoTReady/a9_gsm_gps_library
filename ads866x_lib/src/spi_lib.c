#include "stdint.h"
#include "stdbool.h"
#include "time.h"
#include "api_os.h"
#include "api_debug.h"
#include "api_hal_spi.h"
#include "api_hal_uart.h"
#include "string.h"


bool init_spi_direct_polling(SPI_ID_t SPIx, SPI_CS_t chip_select, uint32_t freq, SPI_Line_t line, bool tx_only, uint8_t clk_polarity, uint8_t clk_phase, bool cs_active_low, SPI_Data_Bits_t data_bits)
{
    SPI_Config_t spi_cfg =
    {
	    .cs = chip_select,
        .txMode = SPI_MODE_DIRECT_POLLING,
        .rxMode = SPI_MODE_DIRECT_POLLING,
        .freq = freq,
        .line = line,
        .txOnly = tx_only,
        .cpol = clk_polarity,
        .cpha = clk_phase,
        .csActiveLow = cs_active_low,
        .dataBits = data_bits,
        .irqHandler = NULL,
        .irqMask = {0,0,0,0,0}
    };

    bool err = SPI_Init(SPIx, spi_cfg);
    if (!err)
        Trace(1, "Could not initialize SPI %d!", SPIx);
    
    return err;

}

bool init_spi_dma_polling(SPI_ID_t SPIx, SPI_CS_t chip_select, uint32_t freq, SPI_Line_t line, bool tx_only, uint8_t clk_polarity, uint8_t clk_phase, bool cs_active_low, SPI_Data_Bits_t data_bits)
{
    SPI_Config_t spi_cfg =
    {
	    .cs = chip_select,
        .txMode = SPI_MODE_DMA_POLLING,
        .rxMode = SPI_MODE_DMA_POLLING,
        .freq = freq,
        .line = line,
        .txOnly = tx_only,
        .cpol = clk_polarity,
        .cpha = clk_phase,
        .csActiveLow = cs_active_low,
        .dataBits = data_bits,
        .irqHandler = NULL,
        .irqMask = {0,0,0,0,0}
    };

    bool err = SPI_Init(SPIx, spi_cfg);
    if (!err)
        Trace(1, "Could not initialize SPI %d!", SPIx);
    
    return err;

}

bool init_spi_direct_irq(SPI_ID_t SPIx, SPI_CS_t chip_select, uint32_t freq, SPI_Line_t line, bool tx_only, uint8_t clk_polarity, uint8_t clk_phase, bool cs_active_low, SPI_Data_Bits_t data_bits, SPI_Irq_Handler_t irq_handler, SPI_Irq_Flags_t irq_mask)
{
    SPI_Config_t spi_cfg =
    {
	    .cs = chip_select,
        .txMode = SPI_MODE_DIRECT_IRQ,
        .rxMode = SPI_MODE_DIRECT_IRQ,
        .freq = freq,
        .line = line,
        .txOnly = tx_only,
        .cpol = clk_polarity,
        .cpha = clk_phase,
        .csActiveLow = cs_active_low,
        .dataBits = data_bits,
        .irqHandler = irq_handler,
        .irqMask = irq_mask
    };

    bool err = SPI_Init(SPIx, spi_cfg);
    if (!err)
        Trace(1, "Could not initialize SPI %d!", SPIx);
    
    return err;

}

bool init_spi_dma_irq(SPI_ID_t SPIx, SPI_CS_t chip_select, uint32_t freq, SPI_Line_t line, bool tx_only, uint8_t clk_polarity, uint8_t clk_phase, bool cs_active_low, SPI_Data_Bits_t data_bits, SPI_Irq_Handler_t irq_handler, SPI_Irq_Flags_t irq_mask)
{
    SPI_Config_t spi_cfg =
    {
	    .cs = chip_select,
        .txMode = SPI_MODE_DMA_IRQ,
        .rxMode = SPI_MODE_DMA_IRQ,
        .freq = freq,
        .line = line,
        .txOnly = tx_only,
        .cpol = clk_polarity,
        .cpha = clk_phase,
        .csActiveLow = cs_active_low,
        .dataBits = data_bits,
        .irqHandler = irq_handler,
        .irqMask = irq_mask
    };

    bool err = SPI_Init(SPIx, spi_cfg);
    if (!err)
        Trace(1, "Could not initialize SPI %d!", SPIx);
    
    return err;

}

uint8_t SPI_ReadOneByte(SPI_ID_t SPIx)
{
	uint8_t r_byte,temp = 0xff;

	SPI_Write(SPIx, &temp, 1);
	while(!SPI_IsTxDone(SPIx));
	SPI_Read(SPIx, &r_byte, 1);

	return r_byte;
}

uint32_t SPI_WriteReadData(SPI_ID_t SPIx, uint8_t *s_data, uint8_t *r_data, uint32_t length)
{
	uint8_t *r_data_ptr = r_data;

	for(uint32_t i=0; i<length; i++)
	{
		SPI_Write(SPIx, s_data++, 1);
		while(!SPI_IsTxDone(SPIx));
		SPI_Read(SPIx, r_data_ptr++, 1);
	}

	return length;
}

uint8_t SPI_WriteReadByte(SPI_ID_t SPIx, uint8_t data)
{
	uint8_t r;

	SPI_Write(SPIx, &data, 1);
	while(!SPI_IsTxDone(SPIx));
	SPI_Read(SPIx, &r, 1);

	return r;
}

uint32_t SPI_DmaReadWriteData(SPI_ID_t SPIx, uint8_t *s_addr, uint8_t *r_addr, uint32_t length)
{
	uint32_t len;
	
	if(NULL != r_addr)
		len = SPI_Read(SPIx, r_addr, length);
	len = SPI_Write(SPIx, s_addr, length);

	return len;
}
