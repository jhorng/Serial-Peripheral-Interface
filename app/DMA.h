#ifndef __DMA_H__
#define __DMA_H__

#include "SPI.h"
#include "RCC.h"
#include <stdint.h>

typedef enum{
	PERIPHERAL_TO_MEMORY,
	MEMORY_TO_PERIPHERAL,
	MEMORY_TO_MEMORY
}dataTransferDirection;

typedef struct DMA_Type DMA_t;

typedef struct{
	  volatile uint32_t CR;
	  volatile uint32_t NDTR;
	  volatile uint32_t PAR;
	  volatile uint32_t M0AR;
	  volatile uint32_t M1AR;
	  volatile uint32_t FCR;
}Stream_t;

struct DMA_Type{
  volatile uint32_t LISR;
  volatile uint32_t HISR;
  volatile uint32_t LIFCR;
  volatile uint32_t HIFCR;
  Stream_t	S0;
  Stream_t	S1;
  Stream_t	S2;
  Stream_t	S3;
  Stream_t	S4;
  Stream_t	S5;
  Stream_t	S6;
  Stream_t	S7;
};

#define DMA_ENABLE		1
#define FIFO_DISABLE	0

#define	ch0		0
#define	ch1		1
#define	ch2		2
#define	ch3		3
#define	ch4		4
#define	ch5		5
#define	ch6		6
#define	ch7		7

#define PRIORITY_LOW			(0 << 16)
#define PRIORITY_MEDIUM			(1 << 16)
#define PRIORITY_HIGH			(2 << 16)
#define PRIORITY_VERY_HIGH		(3 << 16)

#define MEMORY_BYTE_SIZE_DATA			(0 << 13)
#define MEMORY_HALF_WORD_SIZE_DATA		(1 << 13)
#define MEMORY_WORD_SIZE_DATA			(2 << 13)

#define PERIPHERAL_BYTE_SIZE_DATA			(0 << 11)
#define PERIPHERAL_HALF_WORD_SIZE_DATA		(1 << 11)
#define PERIPHERAL_WORD_SIZE_DATA			(2 << 11)

#define MEMORY_INCREMENT		(1 << 10)
#define PERIPHERAL_INCEREMENT	(1 << 9)

#define PERIPHERAL_MEMORY		0
#define MEMORY_PERIPHERAL		1
#define MEMORY_MEMORY			2

#define DMA_FLOW_CONTROL		~(1 << 5)
#define PERIPHERAL_FLOW_CONTROL	(1 << 5)

#define CLEAR_ALL_INTERRUPT		~(15 << 1)
#define ENABLE_ALL_INTERRUPT	(14 << 1)

#define FLAG_TCIF1   11
#define FLAG_HTIF1   10

#define HalfTransfer		getDMA2Status(FLAG_HTIF1)
#define CompleteTransfer	getDMA2Status(FLAG_TCIF1)

#define DMA1   ((DMA_t*)0x40026000)
#define DMA2   ((DMA_t*)0x40026400)

void transferDirection(int direction);
void configDMA2Transmit();
void configDMA2Receive();
void enableDMA2Transmit();
void enableDMA2Receive();
int getDMA2Status(int posBit);
void clearFlag();

#endif // __DMA_H__
