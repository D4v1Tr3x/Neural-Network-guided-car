#include "tests.h"


CustomPMC *pmc;
CustomPIO *pio;
CustomADC *adc;
CustomPWM *pwm;
CustomTC *tc;
NN *myNN;


bool PIOCflag = false;
uint32_t status;
uint32_t uStat;
uint32_t counter;
float timeConst = 0.024;
float distance;


void PIOC_Handler()
{
  status = PIOC->PIO_ISR;
  uStat = PIOC->PIO_PDSR;
  counter = TC2->TC_CHANNEL[0].TC_CV;
  distance = (counter*timeConst)/58;
  
  PIOCflag = true;
}


/*
void ADC_Handler()
{ 
  for(uint8_t i = offset; i < sensorsUsed+offset; i++)
  {
    dAdc = adc->LastChannelData(i);
    tension = (uRef*dAdc)/ADC_Resolution;
    if(tension <= 1.9)
    {
      uIn[i-offset] = 0.0;
    }
    else{
      uIn[i-offset] = 1.0;
    }
  }
}
*/
void setup()
{
  Serial.begin(115200); 
  
  pmc = new CustomPMC;
  pio = new CustomPIO;
  //adc = new CustomADC(sensors, sensorsUsed, EnableInterrupts, pio, pmc);
  //pwm = new CustomPWM(pwmMotors, nMotors, EnableInterrupts, PWMFreq, pio, pmc);
  //myNN = new NN(nLayers, nInputs, nOutputs, weights, biases, actFuncs);  

  //Motors Init
  pio->DeactivatePeripheralControl(MotorPins, nMotors*2, MotorPinGroups);
  pio->SetOutputPins(MotorPins, nMotors*2, MotorPinGroups);

  //Ultrasounds init
  pio->DeactivatePeripheralControl(digitalPins, nDigitalPins, digitalPinsGroups);
  pio->SetOutputPins(outPins, outputPins, outPio);
  pio->SetOutputsHigh(outPins[0], outPio[0]);
  
  Serial.println(PIOC->PIO_PSR); 
  Serial.println(PIOC->PIO_OSR);
  Serial.println(PIOC->PIO_ODSR);
  
  pio->EnableInterrupts(interruptPins, nInterruptPins, interruptsPinGroups, 
                        additionalInterrupts, useHigh, pmc);
  //PIOC->PIO_PUDR = 0xFFFFFFFF;
  //PIOC->PIO_PUER = d6;
  //Serial.println(PIOC->PIO_PUSR); 

  Serial.println(PIOC->PIO_IMR);
  
  Serial.println(PIOC->PIO_AIMMR);
  Serial.println(PIOC->PIO_ELSR);
  Serial.println(PIOC->PIO_FRLHSR);

  
  Serial.println("TC");
  //tc = new CustomTC(TcChannels, TcLength, groups, numbers, peripherals, pmc, pio);

  pmc->EnablePeripheralClock(33);
  TC2->TC_CHANNEL[0].TC_CMR = 0x0500;
  //TC2->TC_CHANNEL[0].TC_RC = 42;
  Serial.println(TC2->TC_CHANNEL[0].TC_SR);
  TC2->TC_CHANNEL[0].TC_CCR = 0x1;
  TC2->TC_CHANNEL[0].TC_CCR = 0x4;
  Serial.println(TC2->TC_CHANNEL[0].TC_SR);
  

  
 // pwm->SetDuty(0.65, 0);
 // pwm->SetDuty(0.9, 1);
}

void loop()
{
  //Serial.println(TC2->TC_CHANNEL[0].TC_CV);
  //Serial.println("HIGH");
  pio->SetOutputsHigh(outPins[0], outPio[0]);
  delay(1);
  //Serial.println("LOW");
  pio->SetOutputsLow(outPins[0], outPio[0]);
  delayMicroseconds(10);
  if(PIOCflag)
  {
    PIOCflag = false;
    //Serial.println("INTERRUPT");
    Serial.println(distance);
  }
  /*
  for(uint8_t i = 0; i < sensorsUsed; i++)
  {
    Serial.println(uIn[i]);
  }
  myNN->Predict(uIn, prediction);
  Serial.println("\n");
  if(prediction[0] == 0.00)
  {
    pwm->SetDuty(0.65, 0);
    if(motorFlag != true)
    {
      motorFlag = true;
    }
  }
  else if(prediction[0] == 2.00)
  {
    if(motorFlag != false)
    {
      motorFlag = false;
    }
  }

  if(motorFlag)
  {
    MoveClockwise(MotorPins[0], MotorPins[1], MotorPinGroups[0], MotorPinGroups[1], pio);
  }
  else
  {
    Off(MotorPins[0], MotorPins[1], MotorPinGroups[0], MotorPinGroups[1], pio, 0);
  }
  
  if(prediction[0] == 1.00)
  {
    MoveCounterClockwise(MotorPins[2], MotorPins[3], MotorPinGroups[2], MotorPinGroups[3], pio);
    pwm->SetDuty(0.8, 0);
    MoveClockwise(MotorPins[0], MotorPins[1], MotorPinGroups[0], MotorPinGroups[1], pio);
    if(lastMov != 1)
    {
      lastMov = 1;
    }
  }
  
  else if(prediction[0] == -1.00)
  {
    MoveClockwise(MotorPins[2], MotorPins[3], MotorPinGroups[2], MotorPinGroups[3], pio);
    pwm->SetDuty(0.8, 0);
    MoveClockwise(MotorPins[0], MotorPins[1], MotorPinGroups[0], MotorPinGroups[1], pio);
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
  */
}
