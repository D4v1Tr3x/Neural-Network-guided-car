#include "tests.h"

CustomPMC *pmc;
CustomPIO *pio;
CustomADC *adc;
CustomPWM *pwm;
NN *myNN;



void ADC_Handler()
{ 
  for(uint8_t i = offset; i < sensorsUsed+offset; i++)
  {
    dAdc = adc->LastChannelData(i);
    tension = (uRef*dAdc)/ADC_Resolution;
    if(tension <= 1.70)
    {
      uIn[i-offset] = 0.0;
    }
    else{
      uIn[i-offset] = 1.0;
    }
  }
}


void setup()
{
  Serial.begin(115200); 

  pmc = new CustomPMC;
  pio = new CustomPIO(MotorPins, nMotors*2, MotorPinGroups);
  adc = new CustomADC(sensors, sensorsUsed, EnableInterrupts, pio, pmc);
  pwm = new CustomPWM(pwmMotors, nMotors, EnableInterrupts, PWMFreq, pio, pmc);
  myNN = new NN(nLayers, nInputs, nOutputs, weights, biases, actFuncs);  
  
  
}


void loop()
{ 
  myNN->Predict(uIn, prediction);
  Serial.println("\n");

  /*
  if(prediction == 1)
  {
    MoveCounterClockwise(MotorPins[2], MotorPins[3], MotorPinGroups[2], MotorPinGroups[3]);
  }
  
  else if(prediction == -1)
  {
    MoveClockwise(MotorPins[2], MotorPins[3], MotorPinGroups[2], MotorPinGroups[3]);
  }
  */ 
}
