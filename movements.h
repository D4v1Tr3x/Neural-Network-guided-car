#ifndef MOVEMENTS_H_
#define MOVEMENTS_H_

#include "pios.h"

extern void Off(uint8_t in1, uint8_t in2, Pio* pinGroup1, Pio* pinGroup2);

extern void MoveClockwise(uint8_t in1, uint8_t in2, Pio* pinGroup1, 
                          Pio* pinGroup2);

extern void MoveCounterClockwise(uint8_t in1, uint8_t in2, Pio* pinGroup1, 
                                 Pio* pinGroup2);

#endif
