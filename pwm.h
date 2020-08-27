#ifndef PWM_H_
#define PWM_H_

#define PWM_ID 36

#include "pios.h"
#include "pmc.h"

class CustomPWM
{
  public:
    CustomPWM(uint16_t* channels, uint8_t len, bool EnableComparison, 
              uint8_t clockFreq, CustomPIO pio);

    ~CustomPWM(void);

    bool CheckWriteProtectStatus(uint8_t ID);

    void SetDuty(float d, uint8_t channel);
    
    void SetCPRD(uint16_t CPRD, uint8_t channel);

    void PWMClockGenerator(uint8_t divA, uint8_t preA, uint8_t divB=0,
                       uint8_t preB=0);

    void EnablePWMChannels(uint16_t* channel, uint8_t len);

    void DisableUnusedPWMChannels();

    void SetupChannelMode(uint8_t channel, uint8_t CPRE, uint8_t CALG, 
                      uint8_t CPOL, uint8_t CES, uint8_t DTE, 
                      uint8_t DTHI, uint8_t DLTI);

    void EnableComparisonOnLine(uint8_t line, uint8_t channels);

    void ComparisonMode(uint32_t config, uint8_t channel);

    void SetComparisonValue(uint16_t val, uint8_t mode, uint8_t channel);

    void GetPin(uint8_t channel, uint32_t &pin, Pio* &pinGroup);

};
#endif
