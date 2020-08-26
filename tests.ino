//Components imports
#include "Arduino.h"
#include "pios.h"
#include "pwm.h"
#include "adc.h"

//Neural Network
#include "NN.h"

//Parameters
#include "parametros.h"
#include "nnparameters.h"

//Motor movements
#include "movements.h"

void ADC_Handler()
{
  for(uint8_t i = 0; i < sensorsUsed; i++)
  {
    flag = true;
    dAdc = LastChannelData(i);
    uIn[i] = (uRef*dAdc)/ADC_Resolution;
  }
}

void setup()
{
  Serial.begin(9600);
  pio_setup(MotorPins, nMotors*2, MotorPinGroups);
  adc_setup(sensors, sensorsUsed, EnableInterrupts);
  pwm_setup(pwmMotors, nMotors, EnableInterrupts, PWMFreq);
  NN myNN(nLayers, nInputs, nOutputs, weights, biases, actFuncs);
}

void loop()
{ 
}
