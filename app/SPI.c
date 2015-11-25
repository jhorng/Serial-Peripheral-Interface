#include "SPI.h"

void enableSPI(int SPE){
	if (SPE){
		SPI_reg->SPI_CR1 |= SPE << 6;
	}
	else {
		SPI_reg->SPI_CR1 &= ~(1 << 6);
	}
}

void configureSPI(int mode, int DFF, int FF, int MSB_LSB){
	configureMode(mode);
	configureDataFrame(DFF);
	configureFrameFormat(FF);
	configureLSBFIRST(MSB_LSB);
}

void configureMode(int mode){
	if (mode){
		SPI_reg->SPI_CR1 |= mode << 2;
	}
	else {
		SPI_reg->SPI_CR1 &= ~(1 << 2);
	}
}

void configureDataFrame(int DFF){
	if (DFF){
		SPI_reg->SPI_CR1 |= DFF << 11;
	}
	else {
		SPI_reg->SPI_CR1 &= ~(1 << 11);
	}
}

void configureFrameFormat(int FF){
	if (FF){
		SPI_reg->SPI_CR2 |= FF << 4;
	}
	else {
		SPI_reg->SPI_CR2 &= ~(1 << 4);
	}
}

void configureLSBFIRST(int MSB_LSB){
	if (MSB_LSB == 1){
		SPI_reg->SPI_CR1 |= MSB_LSB << 7;
	}
	else {
		SPI_reg->SPI_CR1 &= ~(1 << 7);
	}
}

void configureClock(int select){
	switch (select){
	case Clock1:
		SPI_reg->SPI_CR1 &= ~(1 << 1);
		SPI_reg->SPI_CR1 &= ~1;
		break;
	case Clock2:
		SPI_reg->SPI_CR1 &= ~(1 << 1);
		SPI_reg->SPI_CR1 |= 1;
		break;
	case Clock3:
		SPI_reg->SPI_CR1 |= 1 << 1;
		SPI_reg->SPI_CR1 &= ~1;
		break;
	case Clock4:
		SPI_reg->SPI_CR1 |= 1 << 1;
		SPI_reg->SPI_CR1 |= 1;
		break;
	default:
		SPI_reg->SPI_CR1 &= ~(1 << 1);
		SPI_reg->SPI_CR1 &= ~1;
	}
}
