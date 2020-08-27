#include "tests.h"

CustomPIO pio(MotorPins, nMotors*2, MotorPinGroups);
CustomADC adc(sensors, sensorsUsed, EnableInterrupts, pio);
CustomPWM pwm(pwmMotors, nMotors, EnableInterrupts, PWMFreq, pio);
NN myNN(nLayers, nInputs, nOutputs, weights, biases, actFuncs);

void ADC_Handler()
{
  for(uint8_t i = 0; i < sensorsUsed; i++)
  {
    flag = true;
    dAdc = adc.LastChannelData(i);
    uIn[i] = (uRef*dAdc)/ADC_Resolution;
  }
}

void setup()
{
  Serial.begin(9600); 
}

void loop()
{ 
}
