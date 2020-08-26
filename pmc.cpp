#include "pmc.h"

void PMCWriteProtection(uint8_t enable)
{
  REG_PMC_WPMR = 0x504D4300 | enable;
};

void EnablePeripheralClock(uint8_t ID)
{
  if(ID < 31)
  {
    REG_PMC_PCER0 |= 1 << (ID);
  }
  else
  {
    REG_PMC_PCER1 |= 1 << (ID-32);
  }
};

void ConfigMainOSC(uint8_t OSC, uint8_t failDetection, uint8_t bypass,
                   uint8_t RCFreq, uint8_t OSCXStartTime)
{
  uint32_t reg;
  switch(OSC)
  {
    case 0:
      reg  = failDetection << 25;
      reg |= OSC << 24;
      reg |= 3 << 20;
      reg |= 7 << 16;
      reg |= RCFreq << 4;
      reg |= 1 << 3;

      REG_PMC_WPMR = reg;
      break;

    case 1:
      reg  = failDetection << 25;
      reg |= OSC << 24;
      reg |= 3 << 20;
      reg |= 7 << 16;
      reg |= OSCXStartTime << 8;
      reg |= bypass << 1;
      reg |= 1;

      REG_PMC_WPMR = reg;
      break;
  }
};
