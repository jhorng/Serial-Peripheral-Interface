#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"

void configurePort(GPIO_TypeDef *port , uint32_t pinNumber){

	GPIO_InitTypeDef gpio;
	gpio.Pin = GPIO_PIN_13;
	gpio.Mode =GPIO_MODE_OUTPUT_PP;
	gpio.Speed = GPIO_SPEED_MEDIUM;
	HAL_GPIO_Init(port,&gpio);
}

int main(){


	//int a = 4;
	////double d = 1;
	//d = d + a;
	configurePort(GPIOG,GPIO_PIN_13);
	while(1){
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_13,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_13,GPIO_PIN_RESET);
	}

}
