#ifndef __Registers_H__
#define __Registers_H__

//#include "HostRCC.h"
#include <stdint.h>

#ifndef HOST
#define RCC_BASE_ADDRESS 0x40023800

#else
  
#define RCC_BASE_ADDRESS  (&HostRCC)

#endif // HOST

#endif // __Registers_H__
