#include "RCC.h"

void spiUnresetEnableClock(){
	Rcc_reg->RCC_APB2RSTR &= ~(1 << 13);
	Rcc_reg->RCC_APB2ENR |= 1 << 13;
}
