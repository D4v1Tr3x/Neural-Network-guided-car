#ifndef PARAMETROS_H_
#define PARAMETROS_H_

#include "pios.h"

//ADC
const uint8_t sensorsUsed = 3;

const uint8_t offset = 1;

const uint8_t sensor2 = 0x02;
const uint8_t sensor3 = 0x04;
const uint8_t sensor4 = 0x08;

uint16_t sensors[sensorsUsed] = {sensor2, sensor3, sensor4};

bool EnableInterrupts = true;

//PWM
const uint8_t nMotors = 2;

const uint8_t tractionMotorPWM = 0x01;
const uint8_t directionMotorPWM = 0x02;
uint16_t pwmMotors[nMotors] = {tractionMotorPWM, directionMotorPWM};

uint8_t PWMFreq = 24; //in kHz

//PIO
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

#endif
