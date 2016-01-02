/* 
 *   Name : Chu Jaan Horng
 *   Title: Serial Interface Peripheral
 *
*/

#include "stm32f4xx.h"
#include "SPI.h"
#include "RCC.h"
#include "GPIO.h"
#include "DMA.h"
#include <stdint.h>

uint8_t txBuffer[] = "A";
uint8_t rxBuffer[100];

void delay(uint32_t delayCount){
	while(delayCount != 0){
		delayCount--;
	}
}

/****
 * @brief To check the status flag for half transfer and complete transfer.
 *        This function will keep on polling until the data is completely sent.
 ****/
void DMA2Transfer(){
	int statusSPI, statusDMA;

	statusSPI = SPI_reg->SPI_SR;
	statusDMA = DMA2->LISR;

	while(! (HalfTransfer & CompleteTransfer));
	clearFlag();
	statusDMA = DMA2->LISR;
}

/*****
 * @brief This function is the global interrupt for SPI transmission & reception.
 *        Once interrupt is generated, data will be either write/sent or read/received.
 ****/
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
 ****/

void DMA2_Stream0_IRQHandler(void){
	int readData;

	readData = rxBuffer[0];
}

/*****
 * @brief This function is the global interrupt for DMA transmission.
 ****/
void DMA2_Stream1_IRQHandler(void){

	DMA2Transfer();
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
	altFunctionLow(PIN_2, PORTE, AF5);

	configurePin(GPIO_MODE_ALTFUNC, PIN_4, PORTE);
	altFunctionLow(PIN_4, PORTE, AF5);

	configurePin(GPIO_MODE_ALTFUNC, PIN_5, PORTE);
	altFunctionLow(PIN_5, PORTE, AF5);

	configurePin(GPIO_MODE_ALTFUNC, PIN_6, PORTE);
	altFunctionLow(PIN_6, PORTE, AF5);

	spi4UnresetEnableClock();
	dmaUnresetEnableClock(dma2);

	configureFrameFormat(TI_Mode);
	configureMode(Master_Mode);
	configureDirection(UniDirec_2_Line);
	configureOutput(Transmit);
	configureReceive(Full_Duplex);
	enableCRC(CRCenable);
	CRCpolynomial(0x11);
	configureDataFrame(Bit8);
	configureBR(BR4);
	interruptSPI(TXRXIE);
	DMArequest(DMA_TXRX);
	configDMA2Transmit(txBuffer);	// memory to Peripheral
	configDMA2Receive(rxBuffer);    // Peripheral to memory
}


/****
	 *	Port -> PORTE
	 *
	 *	Pin 11 = SPI4_NSS
	 *	Pin 12 = SPI4_SCK
	 *	Pin 13 = SPI4_MISO
	 *	Pin 14 = SPI4_MOSI
	 ****/

void slaveMode(){

	configurePin(GPIO_MODE_ALTFUNC, PIN_11, PORTE);
	altFunctionHigh(PIN_11, PORTE, AF5);

	configurePin(GPIO_MODE_ALTFUNC, PIN_12, PORTE);
	altFunctionHigh(PIN_12, PORTE, AF5);

	configurePin(GPIO_MODE_ALTFUNC, PIN_13, PORTE);
	altFunctionHigh(PIN_13, PORTE, AF5);

	configurePin(GPIO_MODE_ALTFUNC, PIN_14, PORTE);
	altFunctionHigh(PIN_14, PORTE, AF5);

	spi4UnresetEnableClock();
	dmaUnresetEnableClock(dma2);

	configureFrameFormat(TI_Mode);
	configureMode(Slave_Mode);
	configureDirection(UniDirec_2_Line);
	configureOutput(Transmit);
	configureReceive(Full_Duplex);
	enableCRC(CRCenable);
	CRCpolynomial(0x11);
	configureDataFrame(Bit8);
	configureBR(BR4);
	interruptSPI(TXRXIE);
	DMArequest(DMA_RX);
	configDMA2Transmit(txBuffer);	// memory to Peripheral
	configDMA2Receive(rxBuffer);    // Peripheral to memory
}

int main(){
	uint32_t status1, status2, writeData, readData, AF_PIN_2, AF_PIN_6, tx, crc;

	uint32_t fsclk = HAL_RCC_GetClockConfig();
	uint32_t fhclk = HAL_RCC_GetHCLKFreq();
	uint32_t fpclk1 = HAL_RCC_GetPCLK1Freq();
	uint32_t fpclk2 = HAL_RCC_GetPCLK2Freq();

	HAL_NVIC_EnableIRQ(SPI4_IRQn);
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
	HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

	masterMode();
  slaveMode();
	enableDMA2Transmit();
	enableDMA2Receive();
	enableSPI(Enable);

	DMA2Transfer();

	while(1){
		sendData(0x69); // 8'b01101001
		readData = receivedData();
		configureCRCNext(Next_Transfer);
		crc = readCRC(Transmit);
		status1 = SPI_reg->SPI_SR;
	}
}
