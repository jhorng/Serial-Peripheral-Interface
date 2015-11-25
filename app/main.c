#include "stm32f4xx.h"
#include "SPI.h"
#include "RCC.h"

int main(){
	spiUnresetEnableClock();
	enableSPI(Enable);
	//configureSPI(Slave_Mode);
	while(1){

	}
}

