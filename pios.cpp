#include "pios.h"



void pio_setup(uint32_t* digitalPins, uint8_t len, Pio** pinGroups)
{
  DeactivatePeripheralControl(digitalPins, len, pinGroups);
  SetOutputPins(digitalPins, len, pinGroups);
}

void DeactivatePeripheralControl(uint32_t* pins, uint8_t len, Pio** pioGroup)
{
  for(uint8_t i = 0; i < len; i++)
  {
    pioGroup[i]->PIO_PER |= pins[i];
  }
};

void ActivatePeripheralControl(uint32_t* pins, uint8_t len, Pio** pioGroup)
{
  for(uint8_t i = 0; i < len; i++)
  {
    pioGroup[i]->PIO_PDR |= pins[i];
  }
}

void SetOutputPins(uint32_t* pins, uint8_t len, Pio** pioGroup)
{
  for(uint8_t i = 0; i < len; i++)
  {
    pioGroup[i]->PIO_OER |= pins[i];
  }
};

void SetOutputsHigh(uint32_t pins, Pio* pioGroup)
{
  pioGroup->PIO_SODR = pins;
};

void SetOutputsLow(uint32_t pins, Pio* pioGroup)
{
  pioGroup->PIO_CODR = pins;
};

void EnableWriteProtection(uint8_t enable, Pio* pioGroup)
{
  pioGroup->PIO_WPMR = 0x50494F00 | enable;
};

void ChangePeripheral(uint32_t* pins, uint8_t len, Pio** pioGroup)
{
  for(uint8_t i = 0; i < len; i++)
  {
    pioGroup[i]->PIO_ABSR |= pins[i];
  }
};
