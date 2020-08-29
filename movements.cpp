#include "movements.h"



void Off(uint8_t in1, uint8_t in2, Pio* pinGroup1, Pio* pinGroup2,
         CustomPIO* pio)
{
  pio->SetOutputsLow(in1, pinGroup1);
  pio->SetOutputsLow(in2, pinGroup2);
}


void MoveClockwise(uint8_t in1, uint8_t in2, Pio* pinGroup1, Pio* pinGroup2,
                   CustomPIO* pio)
{
  pio->SetOutputsHigh(in1, pinGroup1);
  pio->SetOutputsLow(in2, pinGroup2);
}


 void MoveCounterClockwise(uint8_t in1, uint8_t in2, Pio* pinGroup1, 
                           Pio* pinGroup2, CustomPIO* pio)
{
  pio->SetOutputsHigh(in2, pinGroup1);
  pio->SetOutputsLow(in1, pinGroup2);
}
