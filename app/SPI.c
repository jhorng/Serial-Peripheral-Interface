#include "SPI.h"
#include "RCC.h"

void enableSPI(int SPE){
	if (SPE){
		SPI_reg->SPI_CR1 |= SPE << 6;
	}
	else {
		SPI_reg->SPI_CR1 &= ~(1 << 6);
	}
}

void configureSPI(int direction, int TX_RX, int RX_ONLY, int FF, int mode, int DFF, int MSB_LSB, int clkSelect, int en_CRC, int en_SSM, int baudRate, int SS){

	spiUnresetEnableClock();

	configureDirection(direction);
	configureOutput(TX_RX);
	configureReceive(RX_ONLY);
	configureMode(mode);
	configureDataFrame(DFF);
	configureFrameFormat(FF);
	enableCRC(en_CRC);
	configureBR(baudRate);
	if(!FF){
		enableSSM(en_SSM);
		configureLSBFIRST(MSB_LSB);
		configureClock(clkSelect);
		configureSS(SS);
	}
}

void configureDirection(int direction){
	if(direction){
		SPI_reg->SPI_CR1 |= (direction << 15);
	}
	else{
		SPI_reg->SPI_CR1 &= ~(1 << 15);
	}
}

void configureOutput(int TX_RX){
	if (TX_RX){
		SPI_reg->SPI_CR1 |= (TX_RX << 14);
	}
	else {
		SPI_reg->SPI_CR1 &= ~(1 << 14);
	}
}

void configureReceive(int RX_ONLY){
	if (RX_ONLY){
		SPI_reg->SPI_CR1 |= (RX_ONLY << 10);
	}
	else {
		SPI_reg->SPI_CR1 &= ~(1 << 10);
	}
}

void configureMode(int mode){
	if (mode){
		SPI_reg->SPI_CR1 |= (mode << 2);
	}
	else {
		SPI_reg->SPI_CR1 &= ~(1 << 2);
	}
}

void configureDataFrame(int DFF){
	if (DFF){
		SPI_reg->SPI_CR1 |= (DFF << 11);
	}
	else {
		SPI_reg->SPI_CR1 &= ~(1 << 11);
	}
}

void configureFrameFormat(int FF){
	if (FF){
		SPI_reg->SPI_CR2 |= (FF << 4);
	}
	else {
		SPI_reg->SPI_CR2 &= ~(1 << 4);
	}
}

void configureLSBFIRST(int MSB_LSB){
	if (MSB_LSB){
		SPI_reg->SPI_CR1 |= (MSB_LSB << 7);
	}
	else {
		SPI_reg->SPI_CR1 &= ~(1 << 7);
	}
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
	if (en_CRC){
		SPI_reg->SPI_CR1 |= (en_CRC << 13);
	}
	else {
		SPI_reg->SPI_CR1 &= ~(1 << 13);
	}
}

void enableSSM(int en_SSM){
	if (en_SSM){
		SPI_reg->SPI_CR1 |= (en_SSM << 9);
	}
	else {
		SPI_reg->SPI_CR1 &= ~(1 << 9);
	}
}

void configureBR(int baudRate){
	SPI_reg->SPI_CR1 &= ~(7 << 3);
	SPI_reg->SPI_CR1 |= (baudRate << 3);
}

void configureSS(int SS){
	SPI_reg->SPI_CR2 &= ~(1 << 2);
	SPI_reg->SPI_CR2 |= (SS << 2);
}
