#include "GPIO.h"
#include "RCC.h"

void configurePin(int mode, int pinNum, GPIO *port){

	gpioUnresetEnableClock(port);

	port->MODER &= ~(3 << (pinNum * 2));
	port->MODER |= (mode << (pinNum * 2));
	port->OSPEED &= ~(3 << (pinNum * 2));
	port->OSPEED |= (GPIO_VERY_HIGH_SPEED << (pinNum * 2));
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

void altFunction(int pinNum, GPIO *port, int AF){
	port->AFRL &= ~(16 << (pinNum * 4));
	port->AFRL |= AF << (pinNum * 4);
}

void outputType(int pinNum, GPIO *port, int type){
	port->OTYPER &= ~(1 << (pinNum));
	port->OTYPER |= (type << (pinNum));
}
