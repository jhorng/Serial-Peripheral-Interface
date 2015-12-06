#include "SPI.h"
#include "RCC.h"

void enableSPI(int SPE){
	SPI_reg->SPI_CR1 &= ~(1 << 6);
	SPI_reg->SPI_CR1 |= SPE << 6;
}

//void configureSPI(int direction, int TX_RX, int RX_ONLY, int FF, int mode, int DFF, int MSB_LSB, int clkSelect, int en_CRC, int en_SSM, int baudRate, int SS){
void configureSPI(int direction1, int TX_RX1, int RX_ONLY1, int FF1, int DFF1, int MSB_LSB1, int clkSelect1, int en_CRC1, int en_SSM1, int baudRate1, int SS1){

	spiUnresetEnableClock();

	configureDirection(direction1);
	configureOutput(TX_RX1);
	configureReceive(RX_ONLY1);
	configureFrameFormat(FF1);
	//configureMode(mode);
	configureDataFrame(DFF1);
	enableCRC(en_CRC1);
	configureBR(baudRate1);
	if(FF1 == Motorola_Mode){
		enableSSM(en_SSM1);
		configureLSBFIRST(MSB_LSB1);
		configureClock(clkSelect1);
		configureSS(SS1);
	}
}

void configureDirection(int direction){
	SPI_reg->SPI_CR1 &= ~(1 << 15);
	SPI_reg->SPI_CR1 |= (direction << 15);
}

void configureOutput(int TX_RX){
	SPI_reg->SPI_CR1 &= ~(1 << 14);
	SPI_reg->SPI_CR1 |= (TX_RX << 14);
}

void configureReceive(int RX_ONLY){
	SPI_reg->SPI_CR1 &= ~(1 << 10);
	SPI_reg->SPI_CR1 |= (RX_ONLY << 10);
}

void configureMode(int mode){
	SPI_reg->SPI_CR1 &= ~(1 << 2);
	SPI_reg->SPI_CR1 |= (mode << 2);
}

void configureDataFrame(int DFF){
	SPI_reg->SPI_CR1 &= ~(1 << 11);
	SPI_reg->SPI_CR1 |= (DFF << 11);
}

void configureFrameFormat(int FF){
	SPI_reg->SPI_CR2 &= ~(1 << 4);
	SPI_reg->SPI_CR2 |= (FF << 4);
}

void configureLSBFIRST(int MSB_LSB){
	SPI_reg->SPI_CR1 &= ~(1 << 7);
	SPI_reg->SPI_CR1 |= (MSB_LSB << 7);
}

void configureClock(int clkSelect){
	switch (clkSelect){
	case Clock1:
		SPI_reg->SPI_CR1 &= ~(1 << 1);
		SPI_reg->SPI_CR1 &= ~1;
		break;
	case Clock2:
		SPI_reg->SPI_CR1 &= ~(1 << 1);
		SPI_reg->SPI_CR1 |= 1;
		break;
	case Clock3:
		SPI_reg->SPI_CR1 |= (1 << 1);
		SPI_reg->SPI_CR1 &= ~1;
		break;
	case Clock4:
		SPI_reg->SPI_CR1 |= (1 << 1);
		SPI_reg->SPI_CR1 |= 1;
		break;
	default:
		SPI_reg->SPI_CR1 &= ~(1 << 1);
		SPI_reg->SPI_CR1 &= ~1;
	}
}

void enableCRC(int en_CRC){
	SPI_reg->SPI_CR1 &= ~(1 << 13);
	SPI_reg->SPI_CR1 |= (en_CRC << 13);
}

void enableSSM(int en_SSM){
	SPI_reg->SPI_CR1 &= ~(1 << 9);
	SPI_reg->SPI_CR1 |= (en_SSM << 9);
	SPI_reg->SPI_CR1 &= ~(1 << 8);
	SPI_reg->SPI_CR1 |= (en_SSM << 8);
}

void configureBR(int baudRate){
	SPI_reg->SPI_CR1 &= ~(7 << 3);
	SPI_reg->SPI_CR1 |= (baudRate << 3);
}

void configureSS(int SS){
	SPI_reg->SPI_CR2 &= ~(1 << 2);
	SPI_reg->SPI_CR2 |= (SS << 2);
}
