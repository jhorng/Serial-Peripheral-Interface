#include "GPIO.h"
#include "RCC.h"

/****
 * @brief Unreset the clock and enable the clock of GPIO.
 *        This is the function to assert the peripheral clock.
 *        returnGPIOReset & returnGPIOClock - to read back the value in the reigster.
 * @arg   port
 ****/
void gpioUnresetEnableClock(GPIO* port){
	uint32_t returnGPIOReset, returnGPIOClock;

	int valShift = ((int)port - (0x40020000))/(0x400);
	Rcc_reg->RCC_AHB1RSTR &= ~(1 << (valShift));
	Rcc_reg->RCC_AHB1ENR |= (0x00100000 | (1 << (valShift)));

	returnGPIOReset = Rcc_reg->RCC_AHB1RSTR;
	returnGPIOClock = Rcc_reg->RCC_AHB1ENR;
}

/****
 * @brief Unreset the clock and enable the clock of SPI4.
 *        This is the function to assert the peripheral clock.
 *        returnReset4 & returnClk4 - to read back the value in the reigster.
 ****/
void spi4UnresetEnableClock(){
	uint32_t returnReset4, returnClk4;
	Rcc_reg->RCC_APB2RSTR &= ~(1 << 13);
	Rcc_reg->RCC_APB2ENR |= (1 << 13);

	returnReset4 = Rcc_reg->RCC_APB2RSTR;
	returnClk4 = Rcc_reg->RCC_APB2ENR;
}

/****
 * @brief Unreset the clock and enable the clock of DMA2.
 *        This is the function to assert the peripheral clock.
 *        returnDMAReset & returnDMAClock - to read back the value in the reigster.
 * @arg   dma
 ****/
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

