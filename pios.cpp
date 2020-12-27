#include "pios.h" 

CustomPIO::CustomPIO(){}

CustomPIO::~CustomPIO(){}

void CustomPIO::DeactivatePeripheralControl(uint8_t pins, Pio* pioGroup)
{
  pioGroup->PIO_PER |= 1 << pins;
}

void CustomPIO::ActivatePeripheralControl(uint8_t pins, Pio* pioGroup)
{
  pioGroup->PIO_PDR |= 1 << pins;
}

void CustomPIO::SetOutputPins(uint8_t pins, Pio* pioGroup)
{
  pioGroup->PIO_OER |= 1 << pins;
}

void CustomPIO::SetOutputsHigh(uint8_t pins, Pio* pioGroup)
{
  pioGroup->PIO_SODR |= 1 << pins;
}

void CustomPIO::SetOutputsLow(uint8_t pins, Pio* pioGroup)
{
  pioGroup->PIO_CODR |= 1 << pins;
}

void CustomPIO::EnableWriteProtection(uint8_t enable, Pio* pioGroup)
{
  pioGroup->PIO_WPMR = 0x50494F00 | enable;
}

void CustomPIO::ChangePeripheral(uint8_t pins, Pio* pioGroup)
{
  pioGroup->PIO_ABSR |= 1 << pins;
}

bool CustomPIO::ReadInputPinStatus(uint32_t pin, Pio* pioGroup)
{
  if(pioGroup->PIO_PDSR && pin != 0){return true;}
  return false;
}

void CustomPIO::EnableInterrupts(uint8_t pins, Pio* pinGroups,
                                 bool additionalInterrupts, bool useHigh,
                                 CustomPMC* pmc)
{
    
    pmc->EnablePeripheralClock(ID_PIOA);
    NVIC_EnableIRQ(PIOA_IRQn);
    NVIC_SetPriority(PIOA_IRQn, 14);
    pmc->EnablePeripheralClock(ID_PIOB);
    NVIC_EnableIRQ(PIOB_IRQn);
    NVIC_SetPriority(PIOB_IRQn, 14);
    pmc->EnablePeripheralClock(ID_PIOC);
    NVIC_EnableIRQ(PIOC_IRQn);
    NVIC_SetPriority(PIOC_IRQn, 14);
    pmc->EnablePeripheralClock(ID_PIOD);
    NVIC_EnableIRQ(PIOD_IRQn);
    NVIC_SetPriority(PIOC_IRQn, 14);

    pinGroups->PIO_IER |= 1 << pins;
    if(additionalInterrupts)
    {
      pinGroups->PIO_ESR |= 1 << pins;
      if(useHigh)
      {  
        pinGroups->PIO_REHLSR |= 1 << pins;
      }
      else if(!useHigh)
      {
        pinGroups->PIO_FELLSR |= 1 << pins;
      }
      pinGroups->PIO_AIMER |= 1 << pins;
    }
  }
