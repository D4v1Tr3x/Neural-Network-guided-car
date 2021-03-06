#ifndef PWM_H_
#define PWM_H_

#define PWM_ID 36

#include "pios.h"
#include "pmc.h"

class CustomPWM
{
  public:
    CustomPWM(CustomPMC* pmc);

    ~CustomPWM(void);

    bool CheckWriteProtectStatus(uint8_t ID);

    void SetDuty(float d, uint8_t channel, bool init);
    
    void SetCPRD(uint16_t CPRD, uint8_t channel);

    void ClockGenerator(uint8_t divA, uint8_t preA, uint8_t divB=0,
                       uint8_t preB=0);

    void EnableChannel(uint8_t channel);

    void DisableUnusedChannels();

    void SetupChannelMode(uint8_t channel, uint8_t CPRE, uint8_t CALG, 
                      uint8_t CPOL, uint8_t CES, uint8_t DTE, 
                      uint8_t DTHI, uint8_t DLTI);

    void OpenEventLine(uint8_t line, uint8_t comparisonChannel);

    void ComparisonMode(uint8_t CEN, uint8_t CPR, uint8_t CTR,
                        uint8_t channel);
    
    void EnableComparisonMatchInterrupt(uint8_t channel); 

    void SetComparisonValue(uint16_t val, uint8_t mode, uint8_t channel);
    
    uint16_t GetCPRD(uint8_t channel);
};
#endif
