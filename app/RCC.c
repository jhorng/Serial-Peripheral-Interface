#include "GPIO.h"
#include "RCC.h"

void gpioUnresetEnableClock(GPIO* port){
	uint32_t returnGPIOReset, returnGPIOClock;

	int valShift = ((int)port - (0x40020000))/(0x400);
	Rcc_reg->RCC_AHB1RSTR &= ~(1 << (valShift));
	Rcc_reg->RCC_AHB1ENR |= (0x00100000 | (1 << (valShift)));

	returnGPIOReset = Rcc_reg->RCC_AHB1RSTR;
	returnGPIOClock = Rcc_reg->RCC_AHB1ENR;
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

void dmaUnresetEnableClock(int dma){
	uint32_t returnDMAReset, returnDMAClock;
	if (dma){
		Rcc_reg->RCC_AHB1RSTR &= ~(1 << 22);
		Rcc_reg->RCC_AHB1ENR |= (1 << 22);
	}
	else{
		Rcc_reg->RCC_AHB1RSTR &= ~(1 << 21);
		Rcc_reg->RCC_AHB1ENR |= (1 << 21);
	}

	returnDMAReset = Rcc_reg->RCC_AHB1RSTR;
	returnDMAClock = Rcc_reg->RCC_AHB1ENR;
}

