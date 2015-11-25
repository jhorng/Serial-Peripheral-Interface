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

#define Disable			0
#define Enable			1

#define Slave_Mode		0
#define Master_Mode		1

#define Bit8			0	// DFF = 8-bits
#define Bit16			1	// DFF = 16-bits

#define Motorola_Mode	0
#define TI_Mode			1

#define MSB				0
#define LSB				1

#define Clock1			1
#define Clock2			2
#define Clock3			3
#define Clock4			4

#define SPI_reg	((SPI*)0x40013000)

void enableSPI(int SPE);
void configureSPI(int mode, int DFF, int FF, int MSB_LSB);
void configureMode(int mode);
void configureDataFrame(int DFF);
void configureFrameFormat(int FF);
void configureLSBFIRST(int MSB_LSB);
void configureClock(int select);

#endif // __SPI_H__
