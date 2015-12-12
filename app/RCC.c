#include "GPIO.h"
#include "RCC.h"

void gpioUnresetEnableClock(GPIO* port){
	int valShift = ((int)port - (0x40020000))/(0x400);
	Rcc_reg->RCC_AHB1RSTR &= ~(1 << (valShift));
	Rcc_reg->RCC_AHB1ENR |= (0x00100000 | ~(0 << (valShift)));
}

void spi1UnresetEnableClock(){
	uint32_t returnReset1, returnClk1;
	Rcc_reg->RCC_APB2RSTR &= ~(1 << 12);
	Rcc_reg->RCC_APB2ENR |= (1 << 12);

	returnReset1 = Rcc_reg->RCC_APB2RSTR;
	returnClk1 = Rcc_reg->RCC_APB2ENR;
}

void spi4UnresetEnableClock(){
	uint32_t returnReset4, returnClk4;
	Rcc_reg->RCC_APB2RSTR &= ~(1 << 13);
	Rcc_reg->RCC_APB2ENR |= (1 << 13);

	returnReset4 = Rcc_reg->RCC_APB2RSTR;
	returnClk4 = Rcc_reg->RCC_APB2ENR;
}
