#include "GPIO.h"
#include "RCC.h"

void configurePin(int mode, int pinNum, GPIO *port){

	gpioUnresetEnableClock(port);

	port->MODER &= ~(3 << (pinNum * 2));
	port->MODER |= (mode << (pinNum * 2));
	port->OSPEED &= ~(3 << (pinNum * 2));
	port->OSPEED |= (GPIO_HIGH_SPEED << (pinNum * 2));
}

void writeOne(uint16_t pinNum, GPIO *port){
	//port->ODR &= ~( 1 << (pinNum));
	//port->ODR |= 1 << (pinNum);
	port->BSRR = ( 1 << (pinNum));
}

void writeZero(uint16_t pinNum, GPIO *port){
	//port->ODR &= ~( 1 << (pinNum));
	//port->ODR |= 0 << (pinNum);
	port->BSRR = ( 1 << (pinNum+16));
}

void pullUpDown(int pinNum, GPIO *port, int pull){
	port->PUPDR &= ~(3 << (pinNum * 2));
	port->PUPDR |= pull << (pinNum * 2);
}

void altFunctionLow(int pinNum, GPIO *port, int AF){
	uint32_t returnAFL;
	port->AFRL &= ~(16 << (pinNum * 4));
	port->AFRL |= AF << (pinNum * 4);
	returnAFL = port->AFRL;
}

void altFunctionHigh(int pinNum, GPIO *port, int AF){
	uint32_t returnAFH;
	port->AFRH &= ~(16 << ((pinNum - 8) * 4));
	port->AFRH |= (AF << ((pinNum - 8) * 4));
	returnAFH = port->AFRH;
}

void outputType(int pinNum, GPIO *port, int type){
	port->OTYPER &= ~(1 << (pinNum));
	port->OTYPER |= (type << (pinNum));
}
