#ifndef TC_H_
#define TC_H_

#define TC_ID 27


#include "pios.h"
#include "pmc.h"
#include "pwm.h"
#include "/home/david/.arduino15/packages/arduino/hardware/sam/1.6.12/system/CMSIS/Device/ATMEL/sam3xa/include/component/component_tc.h"

#define A0_PIO PIOB
#define A0_Pin 25
#define A0_Per 1

#define A1_PIO PIOA
#define A1_Pin 2
#define A1_Per 0

#define A6_PIO PIOC
#define A6_Pin 25
#define A6_Per 1

#define A7_PIO PIOC
#define A7_Pin 28
#define A7_Per 1

#define A8_PIO PIOD
#define A8_Pin 8
#define A8_Per 1

#define B1_PIO PIOA
#define B1_Pin 3
#define B1_Per 0

#define B2_PIO PIOA
#define B2_Pin 6
#define B2_Per 0

#define B8_PIO PIOD
#define B8_Pin 8
#define B8_Per 1


class CustomTC
{
  public:
    CustomTC();

    ~CustomTC(void);

    void CaptureModeConfig(Tc* instance, uint8_t channel, uint8_t edgeSel=3, 
                           bool trigSel=0, uint8_t clock=0);
};  
#endif
