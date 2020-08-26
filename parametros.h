#ifndef PARAMETROS_H_
#define PARAMETROS_H_

#include "pios.h"
//ADC

const uint8_t sensorsUsed = 3;

uint8_t sensor2 = 0x02;
uint8_t sensor3 = 0x04;
uint8_t sensor4 = 0x08;

uint16_t sensors[sensorsUsed] = {sensor2, sensor3, sensor4};

bool EnableInterrupts = true;

//PWM
const uint8_t nMotors = 2;

uint8_t tractionMotorPWM = 0x01;
uint8_t directionMotorPWM = 0x02;
uint16_t pwmMotors[nMotors] = {tractionMotorPWM, directionMotorPWM};

uint8_t PWMFreq = 24; //in kHz
//PIO

uint8_t tractionMotor1 = 0x02;
uint8_t tractionMotor2 = 0x04;

uint8_t directionMotor1 = 0x08;
uint8_t directionMotor2 = 0x40;

uint32_t MotorPins[nMotors*2] = {tractionMotor1, tractionMotor2, directionMotor1,
                                directionMotor2};
Pio* MotorPinGroups[nMotors*2] = {PIOD, PIOD, PIOD, PIOD};


//ADC_Handler

float uRef = 3.3;
float ADC_Resolution = 4095.0;

float uIn[sensorsUsed];
uint16_t dAdc;
bool flag = false;

#endif
