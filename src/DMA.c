/* 
 *   Name : Chu Jaan Horng
 *   Title: Serial Interface Peripheral
 *   File : DMA.c
 *
*/

#include "DMA.h"
#include "RCC.h"
#include "SPI.h"
#include <stdint.h>

/****
 *  @brief transferDirection() is used to determine the transfer direction of DMA.
 *         returnDirection1 & returnDirection2 - to read back the value in the reigster.
 *  @arg   direction
 ****/
void transferDirection(int direction){
	uint32_t returnDirection1, returnDirection2;
	dataTransferDirection TransDirec;

	TransDirec = direction;
	switch(TransDirec){
	case PERIPHERAL_TO_MEMORY:
		DMA2->S0.CR &= ~(3 << 6);
		break;
	case MEMORY_TO_PERIPHERAL:
		DMA2->S1.CR &= ~(3 << 6);
		DMA2->S1.CR |= (1 << 6);
		break;
	case MEMORY_TO_MEMORY:
		break;
	default: break;
	}

	returnDirection1 = DMA2->S1.CR;
	returnDirection2 = DMA2->S0.CR;
}

/****
 *  @brief configDMA2Transmit() is the configuration function for DMA transmission.
 *         argument source is used to assign the DMA source or destination.
 *         returnDMATransmit, returnPeriAddr1 & returnMemAddr1  - to read back the value in the reigster.
 *         returnFlagIE1  - to read back the value in the reigster.
 *  @arg   source
 ****/
void configDMA2Transmit(uint32_t source){
	uint32_t returnDMATransmit, returnPeriAddr1, returnMemAddr1, returnFlagIE1;

	DMA2->S1.CR &= ~1; //Disable DMA

	DMA2->S1.CR &= ~(7 << 25);	 	// Clear bits Channel selection
	DMA2->S1.CR |= (ch4 << 25);		// Set Channel selection to channel 4
	returnDMATransmit = DMA2->S1.CR;

	DMA2->S1.CR &= ~(1 << 19);		// Clear CT to target memory 0
	DMA2->S1.CR &= ~(1 << 18);		// Clear double buffer mode
	returnDMATransmit = DMA2->S1.CR;

	DMA2->S1.CR &= ~(3 << 16);		// Clear priority
	DMA2->S1.CR |= PRIORITY_HIGH;	// Set priority to high
	returnDMATransmit = DMA2->S1.CR;

	DMA2->S1.CR &= ~(3 << 13);					// Clear memory data size
	returnDMATransmit = DMA2->S1.CR;

	DMA2->S1.CR &= ~(3 << 11);					// Clear peripheral data size
	returnDMATransmit = DMA2->S1.CR;
  
	transferDirection(MEMORY_PERIPHERAL);
	returnDMATransmit = DMA2->S1.CR;

	DMA2->S1.CR &= ~MEMORY_INCREMENT;			// Clear memory increment
	DMA2->S1.CR |= MEMORY_INCREMENT;

	DMA2->S1.CR &= ~PERIPHERAL_INCEREMENT;		// Clear peripheral increment
	returnDMATransmit = DMA2->S1.CR;

	DMA2->S1.CR &= DMA_FLOW_CONTROL;				// Clear flow controller
	returnDMATransmit = DMA2->S1.CR;

	DMA2->S1.CR &= CLEAR_ALL_INTERRUPT;
	DMA2->S1.CR |= ENABLE_ALL_INTERRUPT;		// Enable all interrupt except DMEIE
	returnDMATransmit = DMA2->S1.CR;

	DMA2->S1.NDTR = 1;  // Data size 

	DMA2->S1.M0AR = (uint32_t)source;				 // Source
	DMA2->S1.PAR  = (uint32_t)(&(SPI_reg->SPI_DR));  // Destination

	DMA2->S1.FCR  &= ~FIFO_DISABLE;

	returnDMATransmit = DMA2->S1.CR;
	returnPeriAddr1 = DMA2->S1.PAR;
	returnMemAddr1 = DMA2->S1.M0AR;
	returnFlagIE1 = DMA2->LISR;
}

/****
 *  @brief configDMA2Receive() is the configuration function for DMA reception.
 *         argument source is used to assign the DMA source or destination.
 *         returnDMAReceive, returnPeriAddr2 & returnMemAddr2  - to read back the value in the reigster.
 *         returnFlagIE2  - to read back the value in the reigster.
 *  @arg   source
 ****/
void configDMA2Receive(uint32_t source){
	uint32_t returnDMAReceive, returnPeriAddr2, returnMemAddr2, returnFlagIE2;

	DMA2->S0.CR &= ~1; //Disable DMA

	DMA2->S0.CR &= ~(7 << 25);	 	// Clear bits Channel selection
	DMA2->S0.CR |= (ch4 << 25);		// Set Channel selection to channel 4
	returnDMAReceive = DMA2->S0.CR;

	DMA2->S0.CR &= ~(1 << 19);		// Clear CT to target memory 0
	DMA2->S0.CR &= ~(1 << 18);		// Clear double buffer mode
	returnDMAReceive = DMA2->S0.CR;

	DMA2->S0.CR &= ~(3 << 16);		// Clear priority
	DMA2->S0.CR |= PRIORITY_HIGH;	// Set priority to high
	returnDMAReceive = DMA2->S0.CR;

	DMA2->S0.CR &= ~(3 << 13);					// Clear memory data size
	returnDMAReceive = DMA2->S0.CR;

	DMA2->S0.CR &= ~(3 << 11);					// Clear peripheral data size
	returnDMAReceive = DMA2->S0.CR;

	transferDirection(PERIPHERAL_MEMORY);
	returnDMAReceive = DMA2->S0.CR;

	DMA2->S0.CR &= ~MEMORY_INCREMENT;			// Clear memory increment
	DMA2->S0.CR |= MEMORY_INCREMENT;

	DMA2->S0.CR &= ~PERIPHERAL_INCEREMENT;		// Clear peripheral increment
	returnDMAReceive = DMA2->S0.CR;

	DMA2->S0.CR &= DMA_FLOW_CONTROL;				// Clear flow controller
	returnDMAReceive = DMA2->S0.CR;

	DMA2->S0.CR &= CLEAR_ALL_INTERRUPT;
	DMA2->S0.CR |= ENABLE_ALL_INTERRUPT;		// Enable all interrupt except DMEIE
	returnDMAReceive = DMA2->S0.CR;

	DMA2->S0.NDTR = 1;  // data size

	DMA2->S0.PAR  = (uint32_t)(&(SPI_reg->SPI_DR));  // Source
	DMA2->S0.M0AR = (uint32_t)source;				 // Destination

	DMA2->S0.FCR  &= ~FIFO_DISABLE;

	returnDMAReceive = DMA2->S0.CR;
	returnMemAddr2 = DMA2->S0.PAR;
	returnPeriAddr2 = DMA2->S0.M0AR;
	returnFlagIE2 = DMA2->LISR;
}

/****
 *  @brief  To enable DMA2 for transmision.
 *          returnDMA2  - to read back the value in the reigster.
 ****/
void enableDMA2Transmit(){
	uint32_t returnDMA2;
	DMA2->S1.CR |= 1;

	returnDMA2 = DMA2->S1.CR;
}

/****
 *  @brief  To enable DMA2 for reception.
 *          returnDMA2  - to read back the value in the reigster.
 ****/
void enableDMA2Receive(){
	uint32_t returnDMA2;
	DMA2->S0.CR |= 1;

	returnDMA2 = DMA2->S0.CR;
}

/****
 *  @brief  To get the status flag DMA2.
 *  @arg    posBit
 *  @retval the wanted bit in LISR.
 ****/
int getDMA2Status(int posBit){
  uint32_t checkSR = DMA2->LISR;
  return ((DMA2->LISR  >> posBit) & 1 );
}

/****
 *  @brief  To clear the status flag by setting the bits clear register.
 *          returnFLag  - to read back the value in the reigster.
 ****/
void clearFlag(){
	uint32_t returnFLag;
	DMA2->LIFCR |= (15 << 8);
	DMA2->LIFCR |= (1 << 6);

	returnFLag = DMA2->LISR;
}
