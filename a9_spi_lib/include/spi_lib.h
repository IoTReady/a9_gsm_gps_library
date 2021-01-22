#ifndef __SPI_LIB_H_
#define __SPI_LIB_H_

#include <stdint.h>
#include "api_hal_spi.h"


/**
  * @brief Initialize SPI with direct polling
  * 
  * The application sends/receives the data directly to/from the hardware module. The number of bytes actually sent/received is returned.
  * 
  * @param SPIx:            SPI number
  * @param chip_select:     Select the CS pin
  * @param freq:            SPI clock frequency in bits/s; up to 13Mbits/s (SPI_FREQ_MAX)
  * @param line:            Number of SPI Lines
  * @param tx_only:         SPI tx only
  *                         false: tx only disable
  *                         true: tx only enable
  * @param clk_polarity: 	SPI Clk Polarity
  *                         0: when SPI is free,clk line is in low level
  *                         1: when SPI is free,clk line is in high level
  * @param clk_phase: 	    SPI Clk Phase
  *                         0: SPI sampling data at the first edge
  *                         1: SPI sampling data at the second edge
  * @param cs_active_low: 	SPI CS Active Polarity
  *                         true: CS Active Low
  *                         false: CS Active High
  * @param data_bits:       SPI framesize
  * 
  * @return bool: return true if init success or false
  */
bool init_spi_direct_polling(SPI_ID_t SPIx, SPI_CS_t chip_select, uint32_t freq, SPI_Line_t line, bool tx_only, uint8_t clk_polarity, uint8_t clk_phase, bool cs_active_low, SPI_Data_Bits_t data_bits);

/**
  * @brief Initialize SPI with DMA polling
  * 
  * The application sends/receives the data through a DMA to the hardware module. The function returns 0 when no DMA channel is available. No bytes are sent. The function returns the number of bytes to send when a DMA resource is available. They will all be sent. A function allows to check if the previous DMA transfer is finished. No new DMA transfer in the same direction will be allowed before the end of the previous transfer.
  * 
  * @param SPIx:            SPI number
  * @param chip_select:     Select the CS pin
  * @param freq:            SPI clock frequency in bits/s; up to 13Mbits/s (SPI_FREQ_MAX)
  * @param line:            Number of SPI Lines
  * @param tx_only:         SPI tx only
  *                         false: tx only disable
  *                         true: tx only enable
  * @param clk_polarity: 	SPI Clk Polarity
  *                         0: when SPI is free,clk line is in low level
  *                         1: when SPI is free,clk line is in high level
  * @param clk_phase: 	    SPI Clk Phase
  *                         0: SPI sampling data at the first edge
  *                         1: SPI sampling data at the second edge
  * @param cs_active_low: 	SPI CS Active Polarity
  *                         true: CS Active Low
  *                         false: CS Active High
  * @param data_bits:       SPI framesize
  * 
  * @return bool: return true if init success or false
  */
bool init_spi_dma_polling(SPI_ID_t SPIx, SPI_CS_t chip_select, uint32_t freq, SPI_Line_t line, bool tx_only, uint8_t clk_polarity, uint8_t clk_phase, bool cs_active_low, SPI_Data_Bits_t data_bits);

/**
  * @brief Initialize SPI with Direct IRQ
  * 
  * The application sends/receives the data directly to/from the hardware module. The number of bytes actually sent/received is returned. An Irq can be generated when the Tx/Rx FIFO reaches the pre-programmed level.
  * 
  * @param SPIx:            SPI number
  * @param chip_select:     Select the CS pin
  * @param freq:            SPI clock frequency in bits/s; up to 13Mbits/s (SPI_FREQ_MAX)
  * @param line:            Number of SPI Lines
  * @param tx_only:         SPI tx only
  *                         false: tx only disable
  *                         true: tx only enable
  * @param clk_polarity: 	SPI Clk Polarity
  *                         0: when SPI is free,clk line is in low level
  *                         1: when SPI is free,clk line is in high level
  * @param clk_phase: 	    SPI Clk Phase
  *                         0: SPI sampling data at the first edge
  *                         1: SPI sampling data at the second edge
  * @param cs_active_low: 	SPI CS Active Polarity
  *                         true: CS Active Low
  *                         false: CS Active High
  * @param data_bits:       SPI framesize
  * @param irq_handler:     Interrupt Handler
  * @param irq_mask:        SPI Interrupt flags: check SPI_Irq_Flags_t struct
  * 
  * @return bool: return true if init success or false
  */
bool init_spi_direct_irq(SPI_ID_t SPIx, SPI_CS_t chip_select, uint32_t freq, SPI_Line_t line, bool tx_only, uint8_t clk_polarity, uint8_t clk_phase, bool cs_active_low, SPI_Data_Bits_t data_bits, SPI_Irq_Handler_t irq_handler, SPI_Irq_Flags_t irq_mask);

/**
  * @brief Initialize SPI with DMA IRQ
  * 
  * The application sends/receives the data through a DMA to the hardware module. The function returns 0 when no DMA channel is available. No bytes are sent. The function returns the number of bytes to send when a DMA resource is available. They will all be sent. An IRQ is generated when the current transfer is finished. No new DMA transfer in the same direction will be allowed before the end of the previous transfer.
  * 
  * @param SPIx:            SPI number
  * @param chip_select:     Select the CS pin
  * @param freq:            SPI clock frequency in bits/s; up to 13Mbits/s (SPI_FREQ_MAX)
  * @param line:            Number of SPI Lines
  * @param tx_only:         SPI tx only
  *                         false: tx only disable
  *                         true: tx only enable
  * @param clk_polarity: 	SPI Clk Polarity
  *                         0: when SPI is free,clk line is in low level
  *                         1: when SPI is free,clk line is in high level
  * @param clk_phase: 	    SPI Clk Phase
  *                         0: SPI sampling data at the first edge
  *                         1: SPI sampling data at the second edge
  * @param cs_active_low: 	SPI CS Active Polarity
  *                         true: CS Active Low
  *                         false: CS Active High
  * @param data_bits:       SPI framesize
  * @param irq_handler:     Interrupt Handler
  * @param irq_mask:        SPI Interrupt flags: check SPI_Irq_Flags_t struct
  * 
  * @return bool: return true if init success or false
  */
bool init_spi_dma_irq(SPI_ID_t SPIx, SPI_CS_t chip_select, uint32_t freq, SPI_Line_t line, bool tx_only, uint8_t clk_polarity, uint8_t clk_phase, bool cs_active_low, SPI_Data_Bits_t data_bits, SPI_Irq_Handler_t irq_handler, SPI_Irq_Flags_t irq_mask);

/**
  * @brief Read one byte from the SPI
  * 
  * @param SPIx:    SPI number
  * 
  * @return uint8_t: One byte data read from SPI
  */
uint8_t SPI_ReadOneByte(SPI_ID_t SPIx);

/**
  * @brief Read one byte from the SPI
  * 
  * @param SPIx:    SPI number
  * @param data:    Data byte to be written
  * 
  * @return uint8_t: One byte data read from SPI
  */
uint8_t SPI_WriteReadByte(SPI_ID_t SPIx, uint8_t data);


/**
  * @brief Read and Write data to SPI
  * 
  * @param SPIx:    SPI number
  * @param s_data:  Data to be sent
  * @param r_data:  Data receive buffer
  * @param length:  The length of data to be read/sent
  * 
  * @return uint32_t: The length of data written/read
  */
uint32_t SPI_WriteReadData(SPI_ID_t SPIx, uint8_t *s_data, uint8_t *r_data, uint32_t length);

/**
  * @brief Read and Write data to SPI in DMA mode
  * 
  * @param SPIx:    SPI number
  * @param s_addr:  Starting address of data to be sent
  * @param r_addr:  Starting address of data receive buffer
  * @param length:  The length of data to be read/sent
  * 
  * @return uint32_t: The length of data written/read
  */
uint32_t SPI_DmaReadWriteData(SPI_ID_t SPIx, uint8_t *s_addr, uint8_t *r_addr, uint32_t length);

#endif
