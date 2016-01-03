/* 
 *   Name : Chu Jaan Horng
 *   Title: Serial Interface Peripheral
 *   File : GPIO.c
 *
*/

#include "GPIO.h"
#include "RCC.h"

/****
 * @brief To configure the GPIO pins.
 *        The clock activation is included in this function.
 *        This is to ensure the clock is activated whenever this function is called.
 * @arg   mode, pinNum, *port
 ****/
void configurePin(int mode, int pinNum, GPIO *port){

	gpioUnresetEnableClock(port);

	port->MODER &= ~(3 << (pinNum * 2));
	port->MODER |= (mode << (pinNum * 2));
	port->OSPEED &= ~(3 << (pinNum * 2));
	port->OSPEED |= (GPIO_HIGH_SPEED << (pinNum * 2));
}

/****
 * @brief To configure the GPIO pins.
 *        This function is used whenever alternate function mode is used.
 *        altFunctionLow() is used for pin number =< 7.
 *        returnAFL - to read back the value in the reigster.
 * @arg   pinNum, *port, AF
 ****/
void altFunctionLow(int pinNum, GPIO *port, int AF){
	uint32_t returnAFL;
	port->AFRL &= ~(16 << (pinNum * 4));
	port->AFRL |= AF << (pinNum * 4);
	returnAFL = port->AFRL;
}

/****
 * @brief To configure the GPIO pins.
 *        This function is used whenever alternate function mode is used.
 *        altFunctionHigh() is used for pin number > 7.
 *        returnAFL - to read back the value in the reigster.
 * @arg   pinNum, *port, AF
 ****/
void altFunctionHigh(int pinNum, GPIO *port, int AF){
	uint32_t returnAFH;
	port->AFRH &= ~(16 << ((pinNum - 8) * 4));
	port->AFRH |= (AF << ((pinNum - 8) * 4));
	returnAFH = port->AFRH;
}
