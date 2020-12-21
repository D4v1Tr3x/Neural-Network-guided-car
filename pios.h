#ifndef PIOS_H_
#define PIOS_H_

#include "pmc.h"

class CustomPIO
{
  public:
    
    CustomPIO();

    ~CustomPIO();

    void DeactivatePeripheralControl(uint8_t pins, Pio* pinGroup);

    void ActivatePeripheralControl(uint8_t pins, Pio* pioGroup);

    void SetOutputPins(uint8_t pins, Pio* pioGroup);

    void SetOutputsHigh(uint8_t pins, Pio* pioGroup);

    void SetOutputsLow(uint8_t pins, Pio* pioGroup);

    void EnableWriteProtection(uint8_t enable, Pio* pioGroup);

    void ChangePeripheral(uint8_t pins, Pio* pioGroup);
    
    bool ReadInputPinStatus(uint32_t pin ,Pio* pioGroup);

    void EnableInterrupts(uint8_t pins, Pio* pinGroups,
                          bool additionalInterrupts, bool useHigh,
                          CustomPMC* pmc);
};
#endif
