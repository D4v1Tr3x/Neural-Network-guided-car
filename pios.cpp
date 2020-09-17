#include "pios.h" 

CustomPIO::CustomPIO(){}

CustomPIO::~CustomPIO(){}

void CustomPIO::DeactivatePeripheralControl(uint32_t* pins, uint8_t len, 
                                            Pio** pioGroup)
{
  for(uint8_t i = 0; i < len; i++)
  {
    pioGroup[i]->PIO_PER |= pins[i];
  }
}

void CustomPIO::ActivatePeripheralControl(uint32_t* pins, uint8_t len, 
                                          Pio** pioGroup)
{
  for(uint8_t i = 0; i < len; i++)
  {
    pioGroup[i]->PIO_PDR |= pins[i];
  }
}

void CustomPIO::SetOutputPins(uint32_t* pins, uint8_t len, Pio** pioGroup)
{
  for(uint8_t i = 0; i < len; i++)
  {
    pioGroup[i]->PIO_OER |= pins[i];
  }
}

void CustomPIO::SetOutputsHigh(uint32_t pins, Pio* pioGroup)
{
  pioGroup->PIO_SODR = pins;
}

void CustomPIO::SetOutputsLow(uint32_t pins, Pio* pioGroup)
{
  pioGroup->PIO_CODR = pins;
}

void CustomPIO::EnableWriteProtection(uint8_t enable, Pio* pioGroup)
{
  pioGroup->PIO_WPMR = 0x50494F00 | enable;
}

void CustomPIO::ChangePeripheral(uint32_t* pins, uint8_t len, Pio** pioGroup)
{
  for(uint8_t i = 0; i < len; i++)
  {
    pioGroup[i]->PIO_ABSR |= pins[i];
  }
}

bool CustomPIO::ReadInputPinStatus(uint32_t pin, Pio* pioGroup)
{
  if(pioGroup->PIO_PDSR && pin != 0){return true;}
  return false;
}

void CustomPIO::EnableInterrupts(uint32_t* pins, uint8_t len, Pio** pinGroups,
                                 bool* additionalInterrupts, bool* useHigh,
                                 CustomPMC* pmc)
{
  for(uint8_t i = 0; i < len; i++)
  { 
    pmc->EnablePeripheralClock(ID_PIOA);
    NVIC_EnableIRQ(PIOA_IRQn);
    pmc->EnablePeripheralClock(ID_PIOB);
    NVIC_EnableIRQ(PIOB_IRQn);
    pmc->EnablePeripheralClock(ID_PIOC);
    NVIC_EnableIRQ(PIOC_IRQn);
    pmc->EnablePeripheralClock(ID_PIOD);
    NVIC_EnableIRQ(PIOD_IRQn);

    pinGroups[i]->PIO_IER |= pins[i];
    if(additionalInterrupts[i])
    {
      pinGroups[i]->PIO_ESR |= pins[i];
      if(useHigh[i])
      {  
        pinGroups[i]->PIO_REHLSR |= pins[i];
      }
      else if(!useHigh[i])
      {
        pinGroups[i]->PIO_FELLSR |= pins[i];
      }
      pinGroups[i]->PIO_AIMER |= pins[i];
    }
  }
}
