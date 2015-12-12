#include "SPI.h"
#include "RCC.h"

void sendData(uint8_t Data){
	while( !readyTransmit );
	SPI_reg->SPI_DR = Data;
}

int getSPI4Status( int posBit ){
  uint32_t checkSR = SPI_reg->SPI_SR;
  return (( SPI_reg->SPI_SR  >> posBit) & 1 );
}

void enableSPI(int SPE){
	uint32_t returnEnSPI;
	SPI_reg->SPI_CR1 &= ~(1 << 6);
	SPI_reg->SPI_CR1 |= SPE << 6;

	returnEnSPI = SPI_reg->SPI_CR1;
}

void disableSPI(int SPE){
	uint32_t returnDisSPI, statusReg;
	statusReg = SPI_reg->SPI_SR;
	while( !(((SPI_reg->SPI_SR) >> FLAG_TXE) & 1) );
	while( (((SPI_reg->SPI_SR) >> FLAG_BSY) & 1) );
	SPI_reg->SPI_CR1 &= ~(1 << 6);
	SPI_reg->SPI_CR1 |= SPE << 6;

	returnDisSPI = SPI_reg->SPI_CR1;
}
/*
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
*/
void configureDirection(int direction){
	uint32_t returnDirection;
	SPI_reg->SPI_CR1 &= ~(1 << 15);
	SPI_reg->SPI_CR1 |= (direction << 15);

	returnDirection = SPI_reg->SPI_CR1;
}

void configureOutput(int TX_RX){
	uint32_t returnOutput;
	SPI_reg->SPI_CR1 &= ~(1 << 14);
	SPI_reg->SPI_CR1 |= (TX_RX << 14);

	returnOutput = SPI_reg->SPI_CR1;
}

void configureReceive(int RX_ONLY){
	uint32_t returnReceive;
	SPI_reg->SPI_CR1 &= ~(1 << 10);
	SPI_reg->SPI_CR1 |= (RX_ONLY << 10);

	returnReceive = SPI_reg->SPI_CR1;
}

void configureMode(int mode){
	uint32_t returnMode;
	SPI_reg->SPI_CR1 &= ~(1 << 2);
	SPI_reg->SPI_CR1 |= (mode << 2);

	returnMode = SPI_reg->SPI_CR1;
}

void configureDataFrame(int DFF){
	uint32_t returnDFF;
	SPI_reg->SPI_CR1 &= ~(1 << 11);
	SPI_reg->SPI_CR1 |= (DFF << 11);

	returnDFF = SPI_reg->SPI_CR1;
}

void configureFrameFormat(int FF){
	uint32_t returnFF;
	SPI_reg->SPI_CR2 &= ~(1 << 4);
	SPI_reg->SPI_CR2 |= (FF << 4);

	returnFF = SPI_reg->SPI_CR2;
}

void configureLSBFIRST(int MSB_LSB){
	uint32_t returnLSBFIRST;
	SPI_reg->SPI_CR1 &= ~(1 << 7);
	SPI_reg->SPI_CR1 |= (MSB_LSB << 7);

	returnLSBFIRST = SPI_reg->SPI_CR1;
}

void configureClock(int clkSelect){
	uint32_t returnClock;
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

	returnClock = SPI_reg->SPI_CR1;
}

void enableCRC(int en_CRC){
	uint32_t returnCRC;
	SPI_reg->SPI_CR1 &= ~(1 << 13);
	SPI_reg->SPI_CR1 |= (en_CRC << 13);

	returnCRC = SPI_reg->SPI_CR1;
}

void configureCRCNext(int phase){
	uint32_t returnPhase;
	SPI_reg->SPI_CR1 &= ~(1 << 12);
	SPI_reg->SPI_CR1 |= (phase << 12);

	returnPhase = SPI_reg->SPI_CR1;
}

void enableSSM(int en_SSM){
	uint32_t returnSSM;
	SPI_reg->SPI_CR1 &= ~(1 << 9);
	SPI_reg->SPI_CR1 |= (en_SSM << 9);

	returnSSM = SPI_reg->SPI_CR1;
}

void configureBR(int baudRate){
	uint32_t returnBR;
	SPI_reg->SPI_CR1 &= ~(7 << 3);
	SPI_reg->SPI_CR1 |= (baudRate << 3);

	returnBR = SPI_reg->SPI_CR1;
}

void configureSS(int SS){
	uint32_t returnSS;
	SPI_reg->SPI_CR2 &= ~(1 << 2);
	SPI_reg->SPI_CR2 |= (SS << 2);

	returnSS = SPI_reg->SPI_CR2;
}

void CRCpolynomial(int polynomial){
	uint32_t returnPolynomial;
	SPI_reg->SPI_CRCPR = polynomial;

	returnPolynomial = SPI_reg->SPI_CRCPR;
}
