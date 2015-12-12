#include "stm32f4xx.h"
#include "SPI.h"
#include "RCC.h"
#include "GPIO.h"
#include <stdint.h>

void delay(uint32_t delayCount){
	while(delayCount != 0){
		delayCount--;
	}
}

	/****
	 *	Pin 2 = SPI4_SCK
	 *	Pin 4 = SPI4_NSS
	 *	Pin 5 = SPI4_MISO
	 *	Pin 6 = SPI4_MOSI
	 ****/
/*
void masterMode(){

	configurePin(GPIO_MODE_ALTFUNC, PIN_2, PORTE);
	altFunction(PIN_2, PORTE, AF5);

	configurePin(GPIO_MODE_ALTFUNC, PIN_4, PORTE);
	altFunction(PIN_4, PORTE, AF5);

	configurePin(GPIO_MODE_ALTFUNC, PIN_5, PORTE);
	altFunction(PIN_5, PORTE, AF5);

	configurePin(GPIO_MODE_ALTFUNC, PIN_6, PORTE);
	altFunction(PIN_6, PORTE, AF5);

	spi4UnresetEnableClock();
	configureFrameFormat(TI_Mode);
	configureMode(Master_Mode);
	configureDirection(BiDirec_1_Line);
	configureOutput(Transmit);
	configureDataFrame(Bit16);
	configureBR(BR4);
}
*/
void slaveMode(){

	configurePin(GPIO_MODE_ALTFUNC, PIN_2, PORTE);
	altFunction(PIN_2, PORTE, AF5);

	configurePin(GPIO_MODE_ALTFUNC, PIN_4, PORTE);
	altFunction(PIN_4, PORTE, AF5);

	configurePin(GPIO_MODE_ALTFUNC, PIN_5, PORTE);
	altFunction(PIN_5, PORTE, AF5);

	configurePin(GPIO_MODE_ALTFUNC, PIN_6, PORTE);
	altFunction(PIN_6, PORTE, AF5);

	spi4UnresetEnableClock();
	configureFrameFormat(TI_Mode);
	configureMode(Slave_Mode);
	configureDirection(UniDirec_2_Line);
	configureReceive(Output_Disable);
	enableCRC(CRCenable);
	CRCpolynomial(0x11);
	//configureOutput(Receive);
	configureDataFrame(Bit16);
	configureBR(BR4);
}

int main(){
	uint32_t status, writeData, readData, AF_PIN_2, AF_PIN_6, tx;

	uint32_t fsclk = HAL_RCC_GetClockConfig();
	uint32_t fhclk = HAL_RCC_GetHCLKFreq();
	uint32_t fpclk1 = HAL_RCC_GetPCLK1Freq();
	uint32_t fpclk2 = HAL_RCC_GetPCLK2Freq();

	/****
	 *	Pin 2 = SPI_SCK
	 *	Pin 4 = NSS
	 *	Pin 5 = SPI_MISO
	 *	Pin 6 = SPI_MOSI
	 ****/
/*
	configurePin(GPIO_MODE_ALTFUNC, PIN_2, PORTE);
	//pullUpDown(PIN_2, PORTE, GPIO_PULL_DOWN);
	altFunction(PIN_2, PORTE, AF5);
	//outputType(PIN_2, PORTE, GPIO_PUSH_PULL);

	configurePin(GPIO_MODE_ALTFUNC, PIN_4, PORTE);
	//pullUpDown(PIN_4, PORTE, GPIO_PULL_DOWN);
	altFunction(PIN_4, PORTE, AF5);
	//outputType(PIN_4, PORTE, GPIO_PUSH_PULL);

	configurePin(GPIO_MODE_ALTFUNC, PIN_5, PORTE);
	//pullUpDown(PIN_5, PORTE, GPIO_PULL_DOWN);
	altFunction(PIN_5, PORTE, AF5);
	//outputType(PIN_5, PORTE, GPIO_PUSH_PULL);

	configurePin(GPIO_MODE_ALTFUNC, PIN_6, PORTE);
	//pullUpDown(PIN_6, PORTE, GPIO_PULL_UP);
	altFunction(PIN_6, PORTE, AF5);
	//outputType(PIN_6, PORTE, GPIO_PUSH_PULL);
*/
	//configureSPI(UniDirec_2_Line, Transmit, Receive_Only_Disable, TI_Mode, Master_Mode, Bit16, MSB, Clock1, CRCdisable, SSMenable, BR1, SSOE_Enable);
	//configureSPI(BiDirec_1_Line, Receive, Receive_Only_Disable, TI_Mode, Bit8, MSB, Clock1, CRCdisable, SSMenable, BR1, SSOE_Enable);

	//spiUnresetEnableClock();
	//configureFrameFormat(TI_Mode);
	//configureMode(Master_Mode);
	//configureDirection(BiDirec_1_Line);
	//configureOutput(Transmit);
	//configureOutput(Receive);
	//configureReceive(Receive_Only_Disable);
	//configureReceive(Receive_Only_Enable);
	//configureDataFrame(Bit16);
	//enableCRC(CRCenable);
	//CRCpolynomial(0x28);
	//configureCRCNext(Next_Transfer);
	//configureBR(BR4);
	//enableSSM(SSMdisable);
	//configureLSBFIRST(MSB);
	//configureClock(Clock1);
	//configureSS(SSOE_Enable);
	//configureMode(Slave_Mode);

	//masterMode();
	slaveMode();
	enableSPI(Enable);

//	while(1){
		// = SPI_reg->SPI_TXCRCR;
		//configureCRCNext(Next_Transfer);
		//sendData(0x69); // 8'b01101001
		readData = receivedByte();
		configureCRCNext(Next_Transfer);
		//sendData(0xAF);
		//tx = SPI_reg->SPI_TXCRCR;
		//disableSPI(Disable);
		//readData = SPI_reg->SPI_DR;
		//delay(1000);
		status = SPI_reg->SPI_SR;
//	}
}
