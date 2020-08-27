#ifndef PIOS_H_
#define PIOS_H_

#include "Arduino.h"

class CustomPIO
{
  public:
    
    CustomPIO(uint32_t* digitalPins, uint8_t len, Pio** pinGroups);

    ~CustomPIO();

    void DeactivatePeripheralControl(uint32_t* pins, uint8_t len, Pio** pinGroup);

    void ActivatePeripheralControl(uint32_t* pins, uint8_t len, Pio** pioGroup);

    void SetOutputPins(uint32_t* pins, uint8_t len, Pio** pioGroup);

    void SetOutputsHigh(uint32_t pins, Pio* pioGroup);

    void SetOutputsLow(uint32_t pins, Pio* pioGroup);

    void EnableWriteProtection(uint8_t enable, Pio* pioGroup);

    void ChangePeripheral(uint32_t* pins, uint8_t len, Pio** pioGroup);

};
#endif
