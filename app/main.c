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

int main(){
	uint32_t status, writeData, readData, AF_PIN_2, AF_PIN_6;

	/****
	 *	Pin 2 = SPI_SCK
	 *	Pin 5 = SPI_MISO
	 *	Pin 6 = SPI_MOSI
	 ****/

	configurePin(GPIO_MODE_ALTFUNC, PIN_2, PORTE);
	//pullUpDown(PIN_2, PORTE, GPIO_PULL_DOWN);
	AF_PIN_2 = altFunction(PIN_2, PORTE, AF5);
	//outputType(PIN_2, PORTE, GPIO_PUSH_PULL);

	configurePin(GPIO_MODE_ALTFUNC, PIN_5, PORTE);
	//pullUpDown(PIN_5, PORTE, GPIO_PULL_DOWN);
	altFunction(PIN_5, PORTE, AF5);
	//outputType(PIN_5, PORTE, GPIO_PUSH_PULL);

	configurePin(GPIO_MODE_ALTFUNC, PIN_6, PORTE);
	//pullUpDown(PIN_6, PORTE, GPIO_PULL_UP);
	AF_PIN_6 = altFunction(PIN_6, PORTE, AF5);
	//outputType(PIN_6, PORTE, GPIO_PUSH_PULL);

	/****
	 * Pin 4 = SPI_NSS
	 ****/

	configurePin(GPIO_MODE_ALTFUNC, PIN_4, PORTE);
	//pullUpDown(PIN_4, PORTE, GPIO_PULL_DOWN);
	altFunction(PIN_4, PORTE, AF5);
	//outputType(PIN_4, PORTE, GPIO_PUSH_PULL);

	//configureSPI(UniDirec_2_Line, Transmit, Receive_Only_Disable, TI_Mode, Master_Mode, Bit16, MSB, Clock1, CRCdisable, SSMenable, BR1, SSOE_Enable);
	//configureSPI(BiDirec_1_Line, Receive, Receive_Only_Disable, TI_Mode, Bit8, MSB, Clock1, CRCdisable, SSMenable, BR1, SSOE_Enable);
	spiUnresetEnableClock();
	configureFrameFormat(TI_Mode);
	configureMode(Master_Mode);
	configureDirection(BiDirec_1_Line);
	//configureOutput(Transmit);
	//configureOutput(Receive);
	configureReceive(Receive_Only_Disable);
	//configureReceive(Receive_Only_Enable);
	//configureDataFrame(Bit8);
	//enableCRC(CRCdisable);
	configureBR(BR4);
	//enableSSM(SSMdisable);
	//configureLSBFIRST(MSB);
	//configureClock(Clock1);
	//configureSS(SSOE_Enable);
	//configureMode(Slave_Mode);

	//SPI_reg->SPI_CR1 &= ~(0xFFFF);
	//SPI_reg->SPI_CR1 |= 0x401C;
	//SPI_reg->SPI_CR1 &= ~(1 << 6);
	//SPI_reg->SPI_CR1 |= (1 << 6);
	enableSPI(Enable);

	//writeData = 0x1;

	while(1){
		//writeOne(PIN_4, PORTE);
		//delay(10000);
		//writeZero(PIN_4, PORTE);
		//delay(10);
		delay(10000);
		sendData(0x8);
		//readData = SPI_reg->SPI_DR;
		delay(10000);
		status = SPI_reg->SPI_SR;
	}
}
