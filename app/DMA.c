#include "DMA.h"
#include "RCC.h"
#include "SPI.h"

uint16_t buffer1[256];
uint16_t buffer2[256];
uint16_t buffer3[256];

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

void configDMA(){
	uint32_t returnDMA, returnPeriAddr, returnMemAddr;

	dmaUnresetEnableClock();

	DMA2->S1.CR &= ~1; //Disable DMA

	DMA2->S1.CR &= ~(7 << 25);	 	// Clear bits Channel selection
	DMA2->S1.CR |= (ch4 << 25);		// Set Channel selection to channel 4

	DMA2->S1.CR &= ~(1 << 19);		// Clear CT to target memory 0
	DMA2->S1.CR &= ~(1 << 18);		// Clear double buffer mode

	DMA2->S1.CR &= ~(3 << 16);		// Clear priority
	DMA2->S1.CR |= PRIORITY_HIGH;	// Set priority to high

	DMA2->S1.CR &= ~(3 << 13);					// Clear memory data size
	DMA2->S1.CR |= DEST_HALF_WORD_SIZE_DATA;		// Set Memory data size to half word data size

	DMA2->S1.CR &= ~(3 << 11);					// Clear peripheral data size
	DMA2->S1.CR |= DEST_HALF_WORD_SIZE_DATA;		// Set peripheral data size to half word data size

	DMA2->S1.CR &= ~MEMORY_INCREMENT;			// Clear memory increment
	DMA2->S1.CR &= ~PERIPHERAL_INCEREMENT;		// Clear peripheral increment

	DMA2->S1.CR &= ~(1 << 5);				// Clear flow controller
	DMA2->S1.CR |= PERIPHERAL_FLOW_CONTROL;	// Set flow controller to peripheral flow control

	DMA2->S1.CR &= CLEAR_ALL_INTERRUPT;
	DMA2->S1.CR |= ENABLE_ALL_INTERRUPT;		// Enable all interrupt except DMEIE

	DMA2->S1.NDTR = 5;
	DMA2->S1.PAR  = (uint32_t)(&(SPI_reg->SPI_DR));
	DMA2->S1.M0AR = (uint32_t)buffer1;
	DMA2->S1.FCR  = FIFO_DISABLE;

	returnDMA = DMA2->S1.CR;
	returnPeriAddr = DMA2->S1.PAR;
	returnMemAddr = DMA2->S1.M0AR;
}
