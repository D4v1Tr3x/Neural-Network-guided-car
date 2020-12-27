#include "modules.h"




Modules::Modules(CustomPMC* pmc, CustomPIO* pio, CustomPWM* pwm, CustomTC* tc, CustomADC* adc)
{
  ModulePMC = pmc;
  ModulePIO = pio;
  ModulePWM = pwm;
  ModuleADC = adc;
  ModuleTC  = tc;
}

Modules::~Modules(){}

void Modules::InitUltrasounds(uint8_t PWMPin, Pio* PWMPinGroup, uint8_t PWMChannel,
                              uint8_t TCPin, Pio* TCPinGroup, uint8_t TCChannel,
                              uint8_t echoPin, Pio* echoPinGroup)
{
  //------PWM trigger--------
  //Setups the pin to be controlled by the PWM
  ModulePIO->ActivatePeripheralControl(PWMPin, PWMPinGroup);
  ModulePIO->ChangePeripheral(PWMPin, PWMPinGroup);
  //Setups the PWM with the desired parameters to send a 10uS pulse that triggers the
  //Ultrasonic Sensor
  ModulePWM->SetupChannelMode(PWMChannel, 0, 1, 0, 0, 0, 0, 0);
  ModulePWM->SetCPRD(1750, PWMChannel);     //24 kHz = 41.6667 uS of Total Period
  ModulePWM->SetDuty(0.76, PWMChannel, 1); //41.6667uS*(1-0.76) = 10uS of TLow 
  //Enables the PWM trigger
  ModulePWM->EnableChannel(PWMChannel);


  //-----Timer Counter Pin-----
  //Setups the pin to be controlled by the peripheral
  ModulePIO->ActivatePeripheralControl(TCPin, TCPinGroup);
  ModulePIO->ChangePeripheral(TCPin, TCPinGroup);
  //Setups the TC in capture mode to track the time of the Echo signal
  ModulePMC->EnablePeripheralClock(33);
  ModuleTC->CaptureModeConfig(TC2, TCChannel, 1, 1, 0);


  //-----Echo PIO Pin-----
  //Setups the pin to be controlled by the PIO peripheral acting as a trigger to the TC
  //to start counting every time the echo signal arrives
  ModulePIO->DeactivatePeripheralControl(echoPin, echoPinGroup);
  ModulePIO->EnableInterrupts(echoPin, echoPinGroup, true, false, ModulePMC); 
}

void Modules::IRInit(uint8_t* ADCChannels, uint8_t* ADCPins, 
                     Pio** ADCPinGroups, uint8_t PWMChannel)
{
  //Resets the ADC
  ModuleADC->Control(1, 0);
  
  //Sets the ADC to be triggered by Event Line 0
  ModuleADC->Config(true); 
  
  //------Hardware trigger config------
  
  ModulePWM->SetupChannelMode(PWMChannel, 0, 1, 0, 0, 0, 0, 0);
  
  //Sets CPRD to match desired frequency (24kHz)
  ModulePWM->SetCPRD(1750, PWMChannel);
  ModulePWM->SetDuty(0.7, PWMChannel, 1);
  ModulePWM->EnableChannel(PWMChannel);

  //Configs the comparison register
  ModulePWM->ComparisonMode(1, 0, 4, PWMChannel);
   
  //Sets the value that triggers the comparison interrupt
  ModulePWM->SetComparisonValue(1750, 1, PWMChannel);
  
  //Enables the interrupts so it can send a signal to the Event Line 0
  ModulePWM->EnableComparisonMatchInterrupt(PWMChannel);
  
  //Enables the ADC Event Line 0 to trigger the ADC
  ModulePWM->OpenEventLine(0, PWMChannel);

  //-----------ADC CONFIG------------
  
  //Enables the interrupts on the ADC peripheral so it can stop the main program
  //execution to read the values of the signals provided once the conversion is ready.
  NVIC_EnableIRQ(ADC_IRQn);
  NVIC_SetPriority(ADC_IRQn, 15);
 
  //---------ADC Pins and Interrupts config---------
  for(uint8_t i = 0; i < 5; i++)
  {
    //Makes the ADC trigger an interrupt every time a conversion is done
    ModuleADC->EnableEOCInterrupts(ADCChannels[i]);
    
    //Makes the GPIO multiplexed with the ADC be controlled by the peripheral 
    ModulePIO->ActivatePeripheralControl(ADCPins[i], ADCPinGroups[i]);
    
    //Enables the ADC channels making them ready to be fired
    ModuleADC->EnableChannel(ADCChannels[i]);
  }
  //Disables the unused channels
  ModuleADC->DisableUnusedChannels();
  
  //Fires the ADC
  ModuleADC->Control(0, 1);
}

void Modules::MotorsInit(uint8_t frequency, uint8_t* motorPins, 
                         uint8_t* PWMChannels, uint8_t* PWMPins, 
                         Pio** motorGroups, Pio** PWMGroups)
{
  //-----GPIO-----
  //Enables the pins and puts them in output mode
  for(uint8_t i = 0; i < 4; i++)
  {
    ModulePIO->DeactivatePeripheralControl(motorPins[i], motorGroups[i]);
    ModulePIO->SetOutputPins(motorPins[i], motorGroups[i]);
  }
  

  //-----PWM-----
  //Sets CPRD to match desired frequency
  //CPRD = MCLK/(2*Frequency) (in kHz)
  uint16_t CPRD = 84e3/(2*frequency);
  
  for(uint8_t i = 0; i < 2; i++)
  {
    //Setups the PWM with the desired parameters
    ModulePWM->SetupChannelMode(PWMChannels[i], 0, 1, 0, 0, 0, 0, 0);
    ModulePWM->SetCPRD(CPRD, PWMChannels[i]);
    ModulePWM->SetDuty(0.7, PWMChannels[i], 1);
    
    //Makes the GPIO multiplexed with the PWM be controlled by the peripheral
    ModulePIO->ActivatePeripheralControl(PWMPins[i], PWMGroups[i]);
    ModulePIO->ChangePeripheral(PWMPins[i], PWMGroups[i]); 
    
    //The PWM starts working
    ModulePWM->EnableChannel(PWMChannels[i]);
  }
  
}
