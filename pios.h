#ifndef PIOS_H_
#define PIOS_H_

#include "pmc.h"

class CustomPIO
{
  public:
    
    CustomPIO();

    ~CustomPIO();

    void DeactivatePeripheralControl(uint32_t* pins, uint8_t len, Pio** pinGroup);

    void ActivatePeripheralControl(uint32_t* pins, uint8_t len, Pio** pioGroup);

    void SetOutputPins(uint32_t* pins, uint8_t len, Pio** pioGroup);

    void SetOutputsHigh(uint32_t pins, Pio* pioGroup);

    void SetOutputsLow(uint32_t pins, Pio* pioGroup);

    void EnableWriteProtection(uint8_t enable, Pio* pioGroup);

    void ChangePeripheral(uint32_t* pins, uint8_t len, Pio** pioGroup);
    
    bool ReadInputPinStatus(uint32_t pin ,Pio* pioGroup);

    void EnableInterrupts(uint32_t* pins, uint8_t len, Pio** pinGroups,
                          bool* additionalInterrupts, bool* useHigh,
                          CustomPMC* pmc);
};
#endif
