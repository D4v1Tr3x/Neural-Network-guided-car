#include "tests.h"


//----Instance declaration----
Modules *modules;
CustomPMC *pmc;
CustomPIO *pio;
CustomADC *adc;
CustomPWM *pwm;
CustomTC *tc;
NN *myNN;


bool flag = false;
//----Handler Functions----
void PIOC_Handler()
{
  //Clears bits
  status = PIOC->PIO_ISR;
  uStat = PIOC->PIO_PDSR;
  
  //Calculates the distance
  counter = TC2->TC_CHANNEL[0].TC_CV;
  y = (((counter*timeConst)-10)/58);
  distance = b*distance + (1-b)*y;

  //Determines if is the distance is dangerous for the system
  if(distance <= 20)
  {
    danger = true;
  }
  else
  {
    danger = false;
  }
}


void ADC_Handler()
{ 
  for(uint8_t i = 0; i < 5; i++)
  {
    //Stores the data
    dAdc = adc->LastChannelData(i);
    
    //Converts the data to voltage
    tension = (uRef*dAdc)/ADC_Resolution;
    
    //Determines if the read was from a black color or a white color
    
    if(tension <= 1.9)
    {
      uIn[i] = 0.0;
    }
    else{
      uIn[i] = 1.0;
    }
    
  }
  flag = true;
}

void WDT_Init(void)
{
}


//Initial Setup
void setup()
{
  //Serial init
  Serial.begin(115200); 
  
  //WatchDog Timer config (once per processor reset)
  WDT->WDT_MR = 0x0FFF6500;
  
  //-------------PERIPHERAL INIT----------------
  pmc = new CustomPMC;
  pio = new CustomPIO;
  pwm = new CustomPWM(pmc);
  adc = new CustomADC(pmc);
  tc = new CustomTC;
  myNN = new NN(nLayers, nInputs, nOutputs, weights, biases, actFuncs);

  //---------------MODULES INIT----------------
  modules = new Modules(pmc, pio, pwm, tc, adc);
  
  modules->MotorsInit(frequency, motorPins, PWMChannels, PWMPins, 
                      motorGroups, PWMGroups);
  modules->IRInit(ADCChannels, ADCPins, ADCPinGroups, ADCPWMChannel);
  modules->InitUltrasounds(PWMPinUS, PWMPinGroupUS, PWMChannelUS, TCPin,
                           TCPinGroup, TCChannel, echoPin, echoPinGroup);
  
  //Updates the duty of the channels to a default value
  pwm->SetDuty(0.8, 0, 0);
  pwm->SetDuty(0.9, 1, 0);
}


//----Execution loop----
void loop()
{
  
  WDT->WDT_CR = 0xA5000001;
  if(danger != true)
  {
    
  if(flag == true)
  {
    flag = false;
    
  myNN->Predict(uIn, prediction);
  
  if(prediction[0] == 0.00)
  {
    //pwm->SetDuty(0.8, 0, 0);
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
    MoveClockwise(motorPins[0], motorPins[1], motorGroups[0], motorGroups[1], pio);
  }
  else
  {
    Off(motorPins[0], motorPins[1], motorGroups[0], motorGroups[1], pio, 0);
  }
  
  if(prediction[0] == 1.00)
  {
    MoveClockwise(motorPins[2], motorPins[3], motorGroups[2], motorGroups[3], pio);
    //pwm->SetDuty(0.8, 0, 0);
    MoveClockwise(motorPins[0], motorPins[1], motorGroups[0], motorGroups[1], pio);
    if(lastMov != 1)
    {
      lastMov = 1;
    }
  }
  
  else if(prediction[0] == -1.00)
  {
    MoveCounterClockwise(motorPins[2], motorPins[3], motorGroups[2], motorGroups[3], pio);
    //pwm->SetDuty(0.8, 0, 0);
    MoveClockwise(motorPins[0], motorPins[1], motorGroups[0], motorGroups[1], pio);
    if(lastMov != -1)
    {
      lastMov = -1;
    }
  }
  else
  {
    Off(motorPins[2], motorPins[3], motorGroups[2], motorGroups[3], pio, lastMov);
    if(lastMov != 0)
    {
      lastMov = 0;
    }
    }
    }
  }
  else
  {
    Off(motorPins[0], motorPins[1], motorGroups[0], motorGroups[1], pio, 0);
    Serial.println("Emergency stop");  
  }
}
