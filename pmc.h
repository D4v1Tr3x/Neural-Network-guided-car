#ifndef PMC_H_
#define PMC_H_

#include "Arduino.h"

void PMCWriteProtection(uint8_t enable);

void EnablePeripheralClock(uint8_t ID);

void ConfigMainOSC(uint8_t OSC, uint8_t failDetection, uint8_t bypass=0, 
                   uint8_t RCFreq=0, uint8_t OSCXStartTime=0);

#endif
