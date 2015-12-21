#include "stm32f4xx.h"
#include "SPI.h"
#include "RCC.h"
#include "GPIO.h"
#include "DMA.h"
#include <stdint.h>

void delay(uint32_t delayCount){
	while(delayCount != 0){
		delayCount--;
	}
}

void SPI4_IRQHandler(void){
	int status, readData;

	status = SPI_reg->SPI_SR;
	if (readyReceived){
		readData = receivedData();
	}
	else if (readyTransmit){
		sendData(0x69); // 8'b01101001
	}
}


/*****
 * @brief This function is the global interrupt for DMA reception.
 *
 ****/
/*
void DMA2_Stream0_IRQHandler(void){
	int status, readData;

	status = SPI_reg->SPI_SR;
	if (readyReceived){
		readData = receivedData();
	}
	clearFlag();
}*/

/*****
 * @brief This function is the global interrupt for DMA transmission.
 *
 ****/
void DMA2_Stream1_IRQHandler(void){
	int status, status2, readData;

	status = SPI_reg->SPI_SR;
	getStatus();
	if (readyTransmit){
		//interruptSPIwithDMA(DMA_TXEIE);
		//sendData(0x69); // 8'b01101001
	}
	//enableDMA2Transmit();
	clearFlag();
}

	/****
	 *	Port -> PORTE
	 *
	 *	Pin 2 = SPI4_SCK
	 *	Pin 4 = SPI4_NSS
	 *	Pin 5 = SPI4_MISO
	 *	Pin 6 = SPI4_MOSI
	 ****/

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
	dmaUnresetEnableClock(dma2);

	configureFrameFormat(TI_Mode);
	configureMode(Master_Mode);
	configureDirection(UniDirec_2_Line);
	//configureOutput(Transmit);
	configureReceive(Full_Duplex);
	enableCRC(CRCenable);
	CRCpolynomial(0x11);
	configureDataFrame(Bit16);
	configureBR(BR4);
	//interruptSPI(TXRXIE);
	//interruptSPIwithDMA(DMA_TXEIE);
	configDMA2Transmit();	// memory to Peripheral
	//configDMA2Receive();    // Peripheral to memory
}
/*
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
*/
int main(){
	uint32_t status1, status2, writeData, readData, AF_PIN_2, AF_PIN_6, tx, crc;

	uint32_t fsclk = HAL_RCC_GetClockConfig();
	uint32_t fhclk = HAL_RCC_GetHCLKFreq();
	uint32_t fpclk1 = HAL_RCC_GetPCLK1Freq();
	uint32_t fpclk2 = HAL_RCC_GetPCLK2Freq();

	//HAL_NVIC_EnableIRQ(SPI4_IRQn);
	//HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
	HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

	masterMode();
	//slaveMode();
	enableDMA2Transmit();
	interruptSPIwithDMA(DMA_TXRXIE);
	enableSPI(Enable);
	//enableDMA2Receive();

	while(1){
		//sendData(0x69); // 8'b01101001
		//readData = receivedData();
		//configureCRCNext(Next_Transfer);
		//crc = readCRC(Transmit);
		//sendData(0xAF);
		status1 = SPI_reg->SPI_SR;
	}
}
