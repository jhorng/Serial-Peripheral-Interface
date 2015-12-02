#include "stm32f4xx.h"
#include "SPI.h"
#include "RCC.h"
#include "GPIO.h"

int main(){
	uint16_t status1, status2, data;

	configurePin(GPIO_MODE_ALTFUNC, PIN_5, PORTA);
	pullUpDown(PIN_5, PORTE, GPIO_NO_PULL);
	altFunction(PIN_5, PORTE, AF5);

	configurePin(GPIO_MODE_OUTPUT, PIN_4, PORTE);
	pullUpDown(PIN_4, PORTE, GPIO_PULL_UP);
	altFunction(PIN_4, PORTE, AF5);

	configurePin(GPIO_MODE_ALTFUNC, PIN_6, PORTA);
	pullUpDown(PIN_6, PORTE, GPIO_NO_PULL);
	altFunction(PIN_6, PORTE, AF5);

	configurePin(GPIO_MODE_ALTFUNC, PIN_7, PORTA);
	pullUpDown(PIN_7, PORTE, GPIO_NO_PULL);
	altFunction(PIN_7, PORTE, AF5);

	configureSPI(UniDirec_2_Line, Transmit, Receive_Only_Disable, TI_Mode, Master_Mode, Bit8, MSB, Clock1, CRCdisable, SSMdisable, BR1, SSOE_Enable);
	enableSPI(Enable);
	data = 0x0043;
	while(1){
		SPI_reg->SPI_DR = data;
		status1 = SPI_reg->SPI_SR;
		//SPI_reg->SPI_DR = 0;
		//status2 = status1;
	}
}

