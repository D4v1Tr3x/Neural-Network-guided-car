#ifndef ADC_H_
#define ADC_H_

#define ADC_ID 37

#include "pios.h"
#include "pmc.h"

class CustomADC
{
  public:
  
    CustomADC(uint16_t* adcChannels, uint8_t pinsUsed, 
              bool EnableADCInterrupts, CustomPIO pio);
    
    ~CustomADC(void);

    void ADCConfig(bool PWMConfig, uint8_t hardwareTriggers=0, 
                   uint8_t trigger=0, uint8_t lowRes=0, uint8_t sleepMode=0, 
                   uint8_t fastWKUP=0, uint8_t freeRun=0);

    void ADCControl(uint8_t reset, uint8_t start);

    void ADCWriteProtect(uint8_t enable);

    void EnableChannels(uint16_t* channel, uint8_t len);

    void DisableUnusedChannels(void);
  
    uint16_t LastChannelData(uint8_t channel);

    uint16_t LastConvertedData(void);

    void EnableEOCInterrupts(uint16_t* channels, uint8_t len);

    void DisableEOCInterrupts(uint16_t* channels, uint8_t len);

    void GetPin(uint16_t channel, uint32_t &pin, Pio* &pinGroup);

};

#endif
