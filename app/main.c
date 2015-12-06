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
	uint32_t  data;

	/****
	 *	Pin 2 = SPI_SCK
	 *	Pin 5 = SPI_MISO
	 *	Pin 6 = SPI_MOSI
	 ****/

	configurePin(GPIO_MODE_ALTFUNC, PIN_2, PORTE);
	pullUpDown(PIN_2, PORTE, GPIO_PULL_DOWN);
	altFunction(PIN_2, PORTE, AF5);
	outputType(PIN_2, PORTE, GPIO_PUSH_PULL);

	configurePin(GPIO_MODE_ALTFUNC, PIN_5, PORTE);
	pullUpDown(PIN_5, PORTE, GPIO_PULL_DOWN);
	altFunction(PIN_5, PORTE, AF5);
	outputType(PIN_5, PORTE, GPIO_PUSH_PULL);

	configurePin(GPIO_MODE_ALTFUNC, PIN_6, PORTE);
	pullUpDown(PIN_6, PORTE, GPIO_PULL_DOWN);
	altFunction(PIN_6, PORTE, AF5);
	outputType(PIN_6, PORTE, GPIO_PUSH_PULL);

	/****
	 * Pin 4 = SPI_NSS
	 ****/

	configurePin(GPIO_MODE_OUTPUT, PIN_4, PORTE);
	pullUpDown(PIN_4, PORTE, GPIO_PULL_UP);
	altFunction(PIN_4, PORTE, AF5);
	outputType(PIN_4, PORTE, GPIO_PUSH_PULL);

	//configureSPI(UniDirec_2_Line, Transmit, Receive_Only_Disable, TI_Mode, Master_Mode, Bit16, MSB, Clock1, CRCdisable, SSMenable, BR1, SSOE_Enable);
	configureSPI(UniDirec_2_Line, Receive, Receive_Only_Disable, TI_Mode, Bit8, MSB, Clock1, CRCdisable, SSMenable, BR1, SSOE_Enable);
	configureMode(Master_Mode);
	enableSPI(Enable);
	data = 0xAA;
	while(1){
		writeOne(PIN_4, PORTE);
		delay(10000);
		writeZero(PIN_4, PORTE);
		delay(10);
		SPI_reg->SPI_DR = data;
		delay(10000);
	}
}

