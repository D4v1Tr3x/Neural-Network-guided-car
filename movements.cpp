#include "movements.h"



void Off(uint8_t in1, uint8_t in2, Pio* pinGroup1, Pio* pinGroup2)
{
  SetOutputsLow(in1, pinGroup1);
  SetOutputsLow(in2, pinGroup2);
}


void MoveClockwise(uint8_t in1, uint8_t in2, Pio* pinGroup1, Pio* pinGroup2)
{
  SetOutputsHigh(in1, pinGroup1);
  SetOutputsLow(in2, pinGroup2);
}


 void MoveCounterClockwise(uint8_t in1, uint8_t in2, Pio* pinGroup1, 
                                 Pio* pinGroup2)
{
  SetOutputsHigh(in2, pinGroup1);
  SetOutputsLow(in1, pinGroup2);
}
