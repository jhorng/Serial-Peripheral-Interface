#include "DMA.h"
#include "RCC.h"
#include "SPI.h"
#include <stdint.h>

//uint8_t buffer1[100];
uint8_t txBuffer[] = "ABC";
uint8_t rxBuffer[100];

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
		//DMA2->S1.CR &= ~(3 << 6);
		//DMA2->S1.CR |= (2 << 6);
		break;
	default: break;
	}

	returnDirection1 = DMA2->S1.CR;
	returnDirection2 = DMA2->S0.CR;
}

void configDMA2Transmit(){
	uint32_t returnDMATransmit, returnPeriAddr1, returnMemAddr1, returnFlagIE1, readBuffer1;

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
	//DMA2->S1.CR |= MEMORY_HALF_WORD_SIZE_DATA;	// Set Memory data size to half word data size
	returnDMATransmit = DMA2->S1.CR;

	DMA2->S1.CR &= ~(3 << 11);					// Clear peripheral data size
	//DMA2->S1.CR |= PERIPHERAL_HALF_WORD_SIZE_DATA;	// Set peripheral data size to half word data size
	returnDMATransmit = DMA2->S1.CR;

	//transferDirection(PERIPHERAL_MEMORY);
	transferDirection(MEMORY_PERIPHERAL);
	returnDMATransmit = DMA2->S1.CR;

	DMA2->S1.CR &= ~MEMORY_INCREMENT;			// Clear memory increment
	DMA2->S1.CR |= MEMORY_INCREMENT;

	DMA2->S1.CR &= ~PERIPHERAL_INCEREMENT;		// Clear peripheral increment
	//DMA2->S1.CR |= PERIPHERAL_INCEREMENT;
	returnDMATransmit = DMA2->S1.CR;

	DMA2->S1.CR &= DMA_FLOW_CONTROL;				// Clear flow controller
	//DMA2->S1.CR |= PERIPHERAL_FLOW_CONTROL;	// Set flow controller to peripheral flow control
	returnDMATransmit = DMA2->S1.CR;

	DMA2->S1.CR &= CLEAR_ALL_INTERRUPT;
	//DMA2->S1.CR |= ENABLE_ALL_INTERRUPT;		// Enable all interrupt except DMEIE
	returnDMATransmit = DMA2->S1.CR;

	DMA2->S1.NDTR = 4;

	//buffer1[0] = 'A';

	DMA2->S1.PAR  = (uint32_t)(&(SPI_reg->SPI_DR));  // Destination
	DMA2->S1.M0AR = (uint32_t)txBuffer;				 // Source

	DMA2->S1.FCR  &= ~FIFO_DISABLE;

	returnDMATransmit = DMA2->S1.CR;
	returnPeriAddr1 = DMA2->S1.PAR;
	returnMemAddr1 = DMA2->S1.M0AR;
	returnFlagIE1 = DMA2->LISR;
}

void configDMA2Receive(){
	uint32_t returnDMAReceive, returnPeriAddr2, returnMemAddr2, returnFlagIE2, readBuffer2;

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
	//DMA2->S0.CR |= MEMORY_HALF_WORD_SIZE_DATA;	// Set Memory data size to half word data size
	returnDMAReceive = DMA2->S0.CR;

	DMA2->S0.CR &= ~(3 << 11);					// Clear peripheral data size
	//DMA2->S0.CR |= PERIPHERAL_HALF_WORD_SIZE_DATA;	// Set peripheral data size to half word data size
	returnDMAReceive = DMA2->S0.CR;

	transferDirection(PERIPHERAL_MEMORY);
	returnDMAReceive = DMA2->S0.CR;

	DMA2->S0.CR &= ~MEMORY_INCREMENT;			// Clear memory increment
	//DMA2->S0.CR |= MEMORY_INCREMENT;

	DMA2->S0.CR &= ~PERIPHERAL_INCEREMENT;		// Clear peripheral increment
	DMA2->S0.CR |= PERIPHERAL_INCEREMENT;
	returnDMAReceive = DMA2->S0.CR;

	DMA2->S0.CR &= DMA_FLOW_CONTROL;				// Clear flow controller
	//DMA2->S0.CR |= PERIPHERAL_FLOW_CONTROL;	// Set flow controller to peripheral flow control
	returnDMAReceive = DMA2->S0.CR;

	DMA2->S0.CR &= CLEAR_ALL_INTERRUPT;
	//DMA2->S1.CR |= ENABLE_ALL_INTERRUPT;		// Enable all interrupt except DMEIE
	returnDMAReceive = DMA2->S0.CR;

	DMA2->S0.NDTR = 4;

	//buffer1[0] = 'A';

	DMA2->S0.M0AR = (uint32_t)(&(SPI_reg->SPI_DR));  // Destination
	DMA2->S0.PAR = (uint32_t)rxBuffer;				 // Source

	DMA2->S0.FCR  &= ~FIFO_DISABLE;

	returnDMAReceive = DMA2->S0.CR;
	returnMemAddr2 = DMA2->S0.PAR;
	returnPeriAddr2 = DMA2->S0.M0AR;
	returnFlagIE2 = DMA2->LISR;
}

void enableDMA2Transmit(){
	uint32_t returnDMA2;
	DMA2->S1.CR |= 1;

	returnDMA2 = DMA2->S1.CR;
}

void enableDMA2Receive(){
	uint32_t returnDMA2;
	DMA2->S0.CR |= 1;

	returnDMA2 = DMA2->S0.CR;
}

int getDMA2Status(int posBit){
  uint32_t checkSR = DMA2->LISR;
  return ((DMA2->LISR  >> posBit) & 1 );
}

void clearFlag(){
	uint32_t returnFLag;
	DMA2->LIFCR |= (15 << 8);
	DMA2->LIFCR |= (1 << 6);

	returnFLag = DMA2->LISR;
}
