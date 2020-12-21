#ifndef PARAMETROS_H_
#define PARAMETROS_H_

#include "pios.h"
#include "TC.h"

//ADC_Handler

const uint8_t sensorsUsed = 5;
const float uRef = 3.3;
const float ADC_Resolution = 4095.0;

float tension;
float uIn[sensorsUsed];
float prediction[1];
uint16_t dAdc;

uint8_t lastMov;
bool motorFlag = false;

//UltraSounds
uint8_t USPins[]     = {7, 25, 23};
Pio* USPinGroups[]   = {PIOC, PIOC, PIOC};
uint8_t USChannels[] = {2, 0};


//Motor Parameters
uint8_t frequency = 24; //In kHz

uint8_t motorPins[] = {1, 2, 3, 6};
Pio* motorGroups[] = {PIOD, PIOD, PIOD, PIOD};


uint8_t PWMChannels[] = {0, 1};
uint8_t PWMPins[] = {3, 5};
Pio* PWMGroups[] = {PIOC, PIOC};

//IR Parameters
uint8_t ADCChannels[] = {0, 1, 2, 3, 4};
uint8_t ADCPins[] = {16, 24, 23, 22, 6};
Pio* ADCPinGroups[] = {PIOA, PIOA, PIOA, PIOA, PIOA};

#endif
