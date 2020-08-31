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
  
  pwm->SetDuty(1, 1);
}

void loop()
{ 
  myNN->Predict(uIn, prediction);
  Serial.println("\n");

  
  if((prediction[0] > 0.5) && (prediction[0] < 1.9))
  {
    MoveCounterClockwise(MotorPins[2], MotorPins[3], MotorPinGroups[2], MotorPinGroups[3], pio);
    if(lastMov != 1)
    {
      lastMov = 1;
    }
  }
  
  else if(prediction[0] < -0.5)
  {
    MoveClockwise(MotorPins[2], MotorPins[3], MotorPinGroups[2], MotorPinGroups[3], pio);
    if(lastMov != -1)
    {
      lastMov = -1;
    }
  }
  else
  {
    Off(MotorPins[2], MotorPins[3], MotorPinGroups[2], MotorPinGroups[3], pio, lastMov);
    if(lastMov != 0)
    {
      lastMov = 0;
    }
  }
  
}
