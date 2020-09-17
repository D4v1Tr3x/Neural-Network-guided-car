#ifndef PARAMETROS_H_
#define PARAMETROS_H_

#include "pios.h"
#include "TC.h"

//ADC
const uint8_t sensorsUsed = 5;

const uint8_t sensor1 = 0x01;
const uint8_t sensor2 = 0x02;
const uint8_t sensor3 = 0x04;
const uint8_t sensor4 = 0x08;
const uint8_t sensor5 = 0x10;

uint16_t sensors[sensorsUsed] = {sensor1, sensor2, sensor3, sensor4, sensor5};

bool EnableInterrupts = true;

//PWM
const uint8_t nMotors = 2;

const uint8_t tractionMotorPWM = 0x01;
const uint8_t directionMotorPWM = 0x02;
uint16_t pwmMotors[nMotors] = {tractionMotorPWM, directionMotorPWM};

uint8_t PWMFreq = 24; //in kHz

//PIO Motors
const uint8_t tractionMotor1 = 0x02;
const uint8_t tractionMotor2 = 0x04;

const uint8_t directionMotor1 = 0x08;
const uint8_t directionMotor2 = 0x40;

uint32_t MotorPins[nMotors*2] = {tractionMotor1, tractionMotor2, 
                                 directionMotor1, directionMotor2};

Pio* MotorPinGroups[nMotors*2] = {PIOD, PIOD, PIOD, PIOD};


//ADC_Handler

const float uRef = 3.3;
const float ADC_Resolution = 4095.0;

float tension;
float uIn[sensorsUsed];
float prediction[1];
uint16_t dAdc;

uint8_t lastMov;
bool motorFlag = false;

//PIO Digital Pins
const uint8_t nDigitalPins = 3;
const uint8_t nInterruptPins = 2;
const uint8_t outputPins = 1;

uint32_t d7 = 0x800000;
uint32_t d6 = 0x1000000;

uint32_t digitalPins[nDigitalPins] = {d6, d7};
Pio* digitalPinsGroups[nDigitalPins] = {PIOC, PIOC};

uint32_t outPins[outputPins] = {d6};
Pio* outPio[outputPins] = {PIOC};

uint32_t interruptPins[nInterruptPins] = {d7};
Pio* interruptsPinGroups[nInterruptPins] = {PIOC};

bool additionalInterrupts[nInterruptPins] = {true};
bool useHigh[nInterruptPins] = {false};


//TC

const uint8_t TcLength = 1;
uint8_t TcChannels[TcLength] = {0};

Pio* groups[TcLength] = {A6_PIO};
uint8_t numbers[TcLength] = {A6_Pin};
bool peripherals[TcLength] = {A6_Per};


#endif
