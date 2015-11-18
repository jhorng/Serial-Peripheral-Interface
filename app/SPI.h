#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>

typedef struct SPI_t SPI;
struct SPI_t{
	volatile uint32_t SPI_CR1;
	volatile uint32_t SPI_CR2;
	volatile uint32_t SPI_SR;
	volatile uint32_t SPI_DR;
	volatile uint32_t SPI_CRCPR;
	volatile uint32_t SPI_RXCRCR;
	volatile uint32_t SPI_TXCRCR;
	volatile uint32_t SPI_I2SCFGR;
	volatile uint32_t SPI_I2SPR;
};

#define SPI_reg	((SPI*)0x40013000)

#endif // __SPI_H__
