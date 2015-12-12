#include "DMA.h"
#include "RCC.h"
#include "SPI.h"

uint32_t buffer1[256];

void transferDirection(int direction){
	uint32_t returnDirection;
	dataTransferDirection TransDirec;

	TransDirec = direction;
	switch(TransDirec){
	case PERIPHERAL_TO_MEMORY:
		DMA2->S1.CR &= ~(3 << 6);
		break;
	case MEMORY_TO_PERIPHERAL:
		DMA2->S1.CR &= ~(3 << 6);
		DMA2->S1.CR |= (1 << 6);
		break;
	case MEMORY_TO_MEMORY:
		DMA2->S1.CR &= ~(3 << 6);
		DMA2->S1.CR |= (2 << 6);
		break;
	default: break;
	}

	returnDirection = DMA2->S1.CR;
}

void configDMA2(int direc){
	uint32_t returnDMA, returnPeriAddr, returnMemAddr;

	DMA2->S1.CR &= ~1; //Disable DMA

	DMA2->S1.CR &= ~(7 << 25);	 	// Clear bits Channel selection
	DMA2->S1.CR |= (ch4 << 25);		// Set Channel selection to channel 4
	returnDMA = DMA2->S1.CR;

	DMA2->S1.CR &= ~(1 << 19);		// Clear CT to target memory 0
	DMA2->S1.CR &= ~(1 << 18);		// Clear double buffer mode
	returnDMA = DMA2->S1.CR;

	DMA2->S1.CR &= ~(3 << 16);		// Clear priority
	DMA2->S1.CR |= PRIORITY_HIGH;	// Set priority to high
	returnDMA = DMA2->S1.CR;

	DMA2->S1.CR &= ~(3 << 13);					// Clear memory data size
	DMA2->S1.CR |= MEMORY_HALF_WORD_SIZE_DATA;	// Set Memory data size to half word data size
	returnDMA = DMA2->S1.CR;

	DMA2->S1.CR &= ~(3 << 11);					// Clear peripheral data size
	DMA2->S1.CR |= PERIPHERAL_HALF_WORD_SIZE_DATA;	// Set peripheral data size to half word data size
	returnDMA = DMA2->S1.CR;

	transferDirection(PERIPHERAL_MEMORY);
	returnDMA = DMA2->S1.CR;

	DMA2->S1.CR &= ~MEMORY_INCREMENT;			// Clear memory increment
	DMA2->S1.CR &= ~PERIPHERAL_INCEREMENT;		// Clear peripheral increment
	returnDMA = DMA2->S1.CR;

	DMA2->S1.CR &= DMA_FLOW_CONTROL;				// Clear flow controller
	//DMA2->S1.CR |= DMA_FLOW_CONTROL;
	//DMA2->S1.CR |= PERIPHERAL_FLOW_CONTROL;	// Set flow controller to peripheral flow control
	returnDMA = DMA2->S1.CR;

	DMA2->S1.CR &= CLEAR_ALL_INTERRUPT;
	DMA2->S1.CR |= ENABLE_ALL_INTERRUPT;		// Enable all interrupt except DMEIE
	returnDMA = DMA2->S1.CR;

	DMA2->S1.NDTR = 5;

	if (direc){
		DMA2->S1.PAR  = (uint32_t)(&(SPI_reg->SPI_DR));
		DMA2->S1.M0AR = (uint32_t)buffer1;
	}
	else {
		DMA2->S1.PAR  = (uint32_t)buffer1;
		DMA2->S1.M0AR = (uint32_t)(&(SPI_reg->SPI_DR));
	}

	DMA2->S1.PAR  = (uint32_t)(&(SPI_reg->SPI_DR));

	DMA2->S1.M0AR = (uint32_t)buffer1;

	DMA2->S1.FCR  = FIFO_DISABLE;

	returnDMA = DMA2->S1.CR;
	returnPeriAddr = DMA2->S1.PAR;
	returnMemAddr = DMA2->S1.M0AR;
}

void enableDMA2(){
	uint32_t returnDMA2;
	DMA2->S1.CR |= 1;

	returnDMA2 = DMA2->S1.CR;
}

uint32_t getStatus(){
	uint32_t returnHISR;
	returnHISR = DMA2->HISR;
	return returnHISR;
}
