#include "adc.h"


void adc_setup(uint16_t* adcChannels, uint8_t pinsUsed, bool EnableADCInterrupts)
{
  //Gets the pins corresponding to each channel
  uint32_t adcPins[pinsUsed];
  Pio* pinGroups[pinsUsed];
  for(uint8_t i = 0; i < pinsUsed; i++)
  {
    GetPin(adcChannels[i], adcPins[i], pinGroups[i]);
  }
  //Activates peripheral control of the ADC pins by disabling the PIO control
  //register
  ActivatePeripheralControl(adcPins, pinsUsed, pinGroups);

  EnablePeripheralClock(ADC_ID);
  
  //Starts the ADC and sets its trigger to fire whenever the PWM event line
  //sends a pulse if the interrupts are enabled
  ADC_Control(1, 0);
  ADC_Config(EnableADCInterrupts);
  
  //Enables the specified channels and then disables the unused ones 
  EnableChannels(adcChannels, pinsUsed);  

  //Enables the ADC EOC interrupt for all the used ADC channels 
  if(EnableADCInterrupts)
  {
    NVIC_EnableIRQ(ADC_IRQn);
    NVIC_SetPriority(ADC_IRQn, 15);
    EnableEOCInterrupts(adcChannels, pinsUsed);
  }  
}

void ADC_Config(bool PWMConfig, uint8_t hardwareTriggers, uint8_t trigger,
                uint8_t lowRes, uint8_t sleepMode, uint8_t fastWKUP,
                uint8_t freeRun)
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
};

void ADC_Control(uint8_t reset, uint8_t start)
{
  ADC->ADC_CR = (start << 1) + reset;
};

void ADCWriteProtect(uint8_t enable)
{
  ADC->ADC_WPMR = 0x04144430 | enable;
};

void EnableChannels(uint16_t* channels, uint8_t len)
{
  for(uint8_t i = 0; i < len; i++)
  {
    ADC->ADC_CHER |= channels[i];
  }
  DisableUnusedChannels();
};

void DisableUnusedChannels()
{
  uint16_t unusedChannels = !ADC->ADC_CHSR;
  ADC->ADC_CHSR = unusedChannels;
  
};

uint16_t LastChannelData(uint8_t channel)
{
  return ADC->ADC_CDR[channel];
}

uint16_t LastConvertedData()
{
  return ADC->ADC_LCDR;
};

void EnableEOCInterrupts(uint16_t* channels, uint8_t len)
{
  for(uint8_t i = 0; i < len; i++)
  {
    ADC->ADC_IER |= channels[i];
  }
};

void DisableEOCInterrupts(uint16_t* channels, uint8_t len)
{
  for(uint8_t i = 0; i < len; i++)
  {
    ADC->ADC_IDR &= channels[i];
  }
};

void GetPin(uint16_t channel, uint32_t &pin, Pio* &pinGroup)
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
