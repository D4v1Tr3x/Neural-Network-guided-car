#include "tests.h"

CustomPMC *pmc;
CustomPIO *pio;
CustomADC *adc;
CustomPWM *pwm;
NN *myNN;



void ADC_Handler()
{
  flag = true;
  
  for(uint8_t i = offset; i < sensorsUsed+offset; i++)
  {
    dAdc = adc->LastChannelData(i);
    //uIn[i-offset] = (uRef*dAdc)/ADC_Resolution;
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

  uIn[0] = 1.0;
  uIn[1] = 1.0;
  uIn[2] = 0.0;

  float s = myNN->Predict(uIn, prediction);
  Serial.println(s);
}


void loop()
{ 
  /*
  if(flag)
  {
    flag=false;
    Serial.println("INTERRUPT");
    for(uint8_t i = 0; i < sensorsUsed; i++)
    {
      if(uIn[i] <= 1.70)
      {
        uIn[i] = 0;
      }
      else if(uIn[i] > 1.70)
      {
        uIn[i] = 1;
      }
      Serial.println(uIn[i]);
    }
  }
  prediction = myNN->Predict(uIn, outputs);
  //Serial.println("\n");
  Serial.println(prediction);
  delay(1000);
  
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
