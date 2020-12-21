#include "modules.h"




Modules::Modules(CustomPMC* pmc, CustomPIO* pio, CustomPWM* pwm, CustomTC* tc, CustomADC* adc)
{
  ModulePMC = pmc;
  ModulePIO = pio;
  ModulePWM = pwm;
  ModuleADC = adc;
  ModuleTC = tc;
}

Modules::~Modules(){}

void Modules::InitUltrasounds(uint8_t* Pins, Pio** PinGroups, 
                              uint8_t* Channels)
{
  //------PWM trigger--------
  //Setup the pin
  ModulePIO->ActivatePeripheralControl(Pins[0], PinGroups[0]);
  ModulePIO->ChangePeripheral(Pins[0], PinGroups[0]);
  //Setup the PWM
  ModulePWM->SetupChannelMode(Channels[0], 0, 1, 0, 0, 0, 0, 0);
  ModulePWM->SetCPRD(1750, Channels[0]);
  ModulePWM->SetDuty(0.76, Channels[0], 1);
  ModulePWM->EnableChannel(Channels[0]);


  //-----Timer Counter Pin-----
  //Setup the pin
  ModulePIO->ActivatePeripheralControl(Pins[1], PinGroups[1]);
  ModulePIO->ChangePeripheral(Pins[1], PinGroups[1]);
  //Setup the TC
  ModulePMC->EnablePeripheralClock(33);
  ModuleTC->CaptureModeConfig(TC2, Channels[1], 1, 1, 0);


  //-----Echo PIO Pin-----
  //Setup the pin
  ModulePIO->DeactivatePeripheralControl(Pins[2], PinGroups[2]);
  ModulePIO->EnableInterrupts(Pins[2], PinGroups[2], true, false, ModulePMC); 
}

void Modules::IRInit(uint8_t* ADCChannels, uint8_t* ADCPins, 
                     Pio** ADCPinGroups)
{
  //Resets the ADC
  ModuleADC->Control(1, 0);
  
  //Sets the ADC to be triggered by Event Line 0
  ModuleADC->Config(true); 
  //TODO: Configurar interrupts y PWM event line
   
  //Interrupt enable
  
  //------Hardware trigger------
  
  //Recycles PWM channel 0 in order to save energy 

  //Configs the comparison register
  ModulePWM->ComparisonMode(1, 0, 4, 0);
   
  //Sets the value that triggers the comparison
  ModulePWM->SetComparisonValue(ModulePWM->GetCPRD(0), 1, 0);
  
  //Enables the interrupts
  ModulePWM->EnableComparisonMatchInterrupt(0);
  
  //Enables the ADC event-line
  ModulePWM->OpenEventLine(0, 0);
  NVIC_EnableIRQ(ADC_IRQn);
  NVIC_SetPriority(ADC_IRQn, 15);
  
  for(uint8_t i = 0; i < 5; i++)
  {
    ModuleADC->EnableEOCInterrupts(ADCChannels[i]);
    ModulePIO->ActivatePeripheralControl(ADCPins[i], ADCPinGroups[i]);
    ModuleADC->EnableChannel(ADCChannels[i]);
  }
  ModuleADC->DisableUnusedChannels();

  //Fires the ADC
  ModuleADC->Control(0, 1);
}

void Modules::MotorsInit(uint8_t frequency, uint8_t* motorPins, 
                         uint8_t* PWMChannels, uint8_t* PWMPins, 
                         Pio** motorGroups, Pio** PWMGroups)
{
  //-----PIO-----
  //Enables the pins
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
    ModulePWM->SetupChannelMode(PWMChannels[i], 0, 1, 0, 0, 0, 0, 0);
    ModulePWM->SetCPRD(CPRD, PWMChannels[i]);
    ModulePWM->SetDuty(0.7, PWMChannels[i], 1);
    ModulePIO->ActivatePeripheralControl(PWMPins[i], PWMGroups[i]);
    ModulePIO->ChangePeripheral(PWMPins[i], PWMGroups[i]); 
    ModulePWM->EnableChannel(PWMChannels[i]);
  }
  
}
