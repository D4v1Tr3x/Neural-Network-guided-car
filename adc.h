#ifndef ADC_H_
#define ADC_H_

#define ADC_ID 37

#include "pios.h"
#include "pmc.h"

void adc_setup(uint16_t* adcChannels, uint8_t pinsUsed, bool EnableADCInterrupts);

void ADC_Config(bool PWMConfig, uint8_t hardwareTriggers=0, uint8_t trigger=0,
                uint8_t lowRes=0, uint8_t sleepMode=0, uint8_t fastWKUP=0,
                uint8_t freeRun=0);

void ADC_Control(uint8_t reset, uint8_t start);

void ADCWriteProtect(uint8_t enable);

void EnableChannels(uint16_t* channel, uint8_t len);

void DisableUnusedChannels();

uint16_t LastChannelData(uint8_t channel);

uint16_t LastConvertedData();

void EnableEOCInterrupts(uint16_t* channels, uint8_t len);

void DisableInterrupts(uint16_t* channels, uint8_t len);

void GetPin(uint16_t channel, uint32_t &pin, Pio* &pinGroup);

#endif
