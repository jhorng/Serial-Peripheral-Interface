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

#define Disable					0
#define Enable					1

#define Receive					0
#define Transmit				1

#define UniDirec_2_Line			0
#define BiDirec_1_Line			1

#define Full_Duplex				0
#define Output_Disable			1

#define Slave_Mode				0
#define Master_Mode				1

#define Bit8					0	// DFF = 8-bits
#define Bit16					1	// DFF = 16-bits

#define Motorola_Mode			0
#define TI_Mode					1

#define MSB						0
#define LSB						1

#define Clock1					1
#define Clock2					2
#define Clock3					3
#define Clock4					4

#define CRCdisable				0
#define CRCenable				1

#define No_Phase				0
#define Next_Transfer			1

#define SSMdisable				0
#define SSMenable				1

#define SSOE_Disable			0
#define SSOE_Enable				1

#define rxDMA					0
#define txDMA					1

#define BR0          	 		0	// Fpclk/2
#define BR1          			1	// Fpclk/4
#define BR2         			2	// Fpclk/8
#define BR3          			3	// Fpclk/16
#define BR4         	  		4	// Fpclk/32
#define BR5          			5	// Fpclk/64
#define BR6           			6	// Fpclk/128
#define BR7          		 	7	// Fpclk/256

#define RXNEIE					1
#define TXEIE					2
#define TXRXIE					3

#define DMA_RXNEIE				1
#define DMA_TXEIE				2
#define DMA_TXRXIE				3

#define FLAG_FRE				8
#define FLAG_BSY				7
#define FLAG_OVR				6
#define FLAG_MODF				5
#define FLAG_CRCERR				4
#define FLAG_UDR				3
#define FLAG_CHSIDE				2
#define FLAG_TXE				1
#define FLAG_RXNE				0

#define readyTransmit    		getSPI4Status(FLAG_TXE)
#define readyReceived    		getSPI4Status(FLAG_RXNE)
#define isBusy					getSPI4Status(FLAG_BSY)

#define SPI_reg					((SPI*)0x40013400)

int getSPI4Status(int posBit);
void sendData(uint8_t Data);
uint8_t receivedData(void);
uint32_t readCRC(int path);
void enableSPI(int SPE);
void disableSPI(int SPE);
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
void configureCRCNext(int phase);
void enableSSM(int en_SSM);
void configureBR(int baudRate);
void configureSS(int SS);
void CRCpolynomial(int polynomial);
void DMAenable(int dma, int enable);
void interruptSPI(int IE);

#endif // __SPI_H__
