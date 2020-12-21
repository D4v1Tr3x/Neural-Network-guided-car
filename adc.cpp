#include "adc.h"


CustomADC::CustomADC(CustomPMC* pmc)
{
  pmc->EnablePeripheralClock(ADC_ID);
}

CustomADC::~CustomADC()
{
}

void CustomADC::Config(bool PWMConfig, uint8_t hardwareTriggers, 
                          uint8_t trigger, uint8_t lowRes, uint8_t sleepMode, 
                          uint8_t fastWKUP, uint8_t freeRun)
{
  if(PWMConfig)
  {
    ADC->ADC_MR = 0x9;
  }
  else
  {
  uint32_t configRegister;
    if(hardwareTriggers == 1)
    {
      configRegister |= (trigger << 1) + hardwareTriggers;
    }
    configRegister |= (freeRun << 7) + (fastWKUP << 6) + (sleepMode << 5) + (lowRes << 4);
  }
}

void CustomADC::Control(uint8_t reset, uint8_t start)
{
  ADC->ADC_CR = (start << 1) + reset;
}

void CustomADC::WriteProtect(uint8_t enable)
{
  ADC->ADC_WPMR = 0x04144430 | enable;
}

void CustomADC::EnableChannel(uint8_t channel)
{  
  ADC->ADC_CHER |= 1 << channel;
}

void CustomADC::DisableUnusedChannels()
{
  ADC->ADC_CHDR = !ADC->ADC_CHSR;  
}

uint16_t CustomADC::LastConvertedData()
{
  return ADC->ADC_LCDR;
}

void CustomADC::EnableEOCInterrupts(uint8_t channel)
{
    ADC->ADC_IER |= 1 << channel;
}

void CustomADC::DisableEOCInterrupts(uint16_t* channels, uint8_t len)
{
  for(uint8_t i = 0; i < len; i++)
  {
    ADC->ADC_IDR &= channels[i];
  }
}

void CustomADC::GetPin(uint16_t channel, uint32_t &pin, Pio* &pinGroup)
{
  switch(channel)
  {
    case 0x01:
      pin = 0x04;
      pinGroup = PIOA; 
      break;

    case 0x02:
      pin = 0x08;
      pinGroup = PIOA;
      break;

    case 0x04:
      pin = 0x10;
      pinGroup = PIOA;
      break;

    case 0x08:
      pin = 0x20;
      pinGroup = PIOA;
      break;

    case 0x10:
      pin = 0x400000;
      pinGroup = PIOA;
      break;
  }
}

uint16_t CustomADC::LastChannelData(uint8_t channel)
{ 
  return ADC->ADC_CDR[channel];
}
