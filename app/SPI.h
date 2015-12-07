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

#define Disable				0
#define Enable				1

#define Receive				0
#define Transmit			1

#define UniDirec_2_Line		0
#define BiDirec_1_Line		1

#define Receive_Only_Disable	0
#define Receive_Only_Enable		1

#define Slave_Mode			0
#define Master_Mode			1

#define Bit8				0	// DFF = 8-bits
#define Bit16				1	// DFF = 16-bits

#define Motorola_Mode		0
#define TI_Mode				1

#define MSB					0
#define LSB					1

#define Clock1				1
#define Clock2				2
#define Clock3				3
#define Clock4				4

#define CRCenable			0
#define CRCdisable			1

#define SSMdisable			0
#define SSMenable			1

#define SSOE_Disable		0
#define SSOE_Enable			1

#define BR0          	 	000
#define BR1          		001
#define BR2         		010
#define BR3          		011
#define BR4         	  	100
#define BR5          		101
#define BR6           		110
#define BR7          	 	111

#define FLAG_TXE  1

#define readyTransmit    getSPI4Status(FLAG_TXE)

#define SPI_reg	((SPI*)0x40013400)

int getSPI4Status( int posBit );
void sendData(uint8_t Data);
void enableSPI(int SPE);
//void configureSPI(int direction, int TX_RX, int RX_ONLY, int FF, int mode, int DFF, int MSB_LSB, int clkSelect, int en_CRC, int en_SSM, int baudRate, int SS);
void configureSPI(int direction1, int TX_RX1, int RX_ONLY1, int FF1, int DFF1, int MSB_LSB1, int clkSelect1, int en_CRC1, int en_SSM1, int baudRate1, int SS1);
void configureDirection(int direction);
void configureOutput(int TX_RX);
void configureMode(int mode);
void configureDataFrame(int DFF);
void configureFrameFormat(int FF);
void configureLSBFIRST(int MSB_LSB);
void configureClock(int clkSelect);
void enableCRC(int en_CRC);
void enableSSM(int en_SSM);
void configureBR(int baudRate);
void configureSS(int SS);

#endif // __SPI_H__
