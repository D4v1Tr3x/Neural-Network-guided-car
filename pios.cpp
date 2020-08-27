#include "pios.h"


CustomPIO::CustomPIO(uint32_t* digitalPins, uint8_t len, Pio** pinGroups)
{
  DeactivatePeripheralControl(digitalPins, len, pinGroups);
  SetOutputPins(digitalPins, len, pinGroups);
}

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
