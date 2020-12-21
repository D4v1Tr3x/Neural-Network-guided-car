#ifndef MODULES_H_
#define MODULES_H_

#include "TC.h"
#include "adc.h"
#include "pwm.h"
#include "pmc.h"
#include "pios.h"



class Modules
{
  private:
    CustomPMC* ModulePMC;
    CustomPIO* ModulePIO;
    CustomPWM* ModulePWM;
    CustomADC* ModuleADC;
    CustomTC* ModuleTC;

  public:
    Modules(CustomPMC* pmc, CustomPIO* pio, CustomPWM* pwm, CustomTC* tc, 
            CustomADC* adc);

    ~Modules();
        
    void InitUltrasounds(uint8_t* Pins, Pio** PinGroups, uint8_t* Channels);
    
    void IRInit(uint8_t* ADCChannels, uint8_t* ADCPins, Pio** ADCPinGroups);

    void MotorsInit(uint8_t frequency, uint8_t* motorPins, uint8_t* PWMChannels,
                    uint8_t* PWMPins, Pio** motorGroups, Pio** PWMGroups);
};


#endif
