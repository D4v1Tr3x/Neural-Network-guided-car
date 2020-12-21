#ifndef ADC_H_
#define ADC_H_

#define ADC_ID 37

#include "pios.h"
#include "pmc.h"

class CustomADC
{
  public:
  
    CustomADC(CustomPMC* pmc);
    
    ~CustomADC(void);

    void Config(bool PWMConfig, uint8_t hardwareTriggers=0, 
                   uint8_t trigger=0, uint8_t lowRes=0, uint8_t sleepMode=0, 
                   uint8_t fastWKUP=0, uint8_t freeRun=0);

    void Control(uint8_t reset, uint8_t start);

    void WriteProtect(uint8_t enable);

    void EnableChannel(uint8_t channel);

    void DisableUnusedChannels(void);

    uint16_t LastConvertedData(void);

    void EnableEOCInterrupts(uint8_t channel);

    void DisableEOCInterrupts(uint16_t* channels, uint8_t len);

    void GetPin(uint16_t channel, uint32_t &pin, Pio* &pinGroup);
    
    uint16_t LastChannelData(uint8_t channel);
};

#endif
