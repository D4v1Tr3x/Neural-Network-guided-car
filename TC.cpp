#include "TC.h"


CustomTC::CustomTC(uint8_t* channels, uint8_t len, Pio** groups, uint8_t* numbers, 
                   bool* peripherals, CustomPMC* pmc, CustomPIO* pio)
{
  MyPMC = pmc;                        //PMC instance
  MyPIO = pio;
  for(uint8_t i = 0; i < len; i++)
  {
    ConfigureChannel(TC2, channels[i], groups[i], numbers[i], peripherals[i]);  //Configures all the selected channels
  }
}

CustomTC::~CustomTC(){}

void CustomTC::ConfigureChannel(Tc* instance, uint8_t channel, Pio* group, uint8_t number, 
                                bool peripheral, bool interrupt, bool mode)
{
  //Allows to trigger the TC using software if softTrigger bit is set to 1 
  instance->TC_CHANNEL[channel].TC_CCR = 0x1;
  if(mode)
  {
    //TODO: Waveform Mode
  }
  else
  {
    CaptureModeConfig(instance, channel, 2, 1); //FIXME: FIX YOUR SHIT no puedes usar el peripheral como parametro para el trigger selection 
  }

  if(interrupt)
  {
    InterruptConfig(instance, channel, 1);
  }
  TIOConfig(group, number, peripheral);  

}

void CustomTC::CaptureModeConfig(Tc* instance, uint8_t channel, uint8_t edgeSel, 
                                 bool trigSel, uint8_t clock)
{
  instance->TC_CHANNEL[channel].TC_CMR = (trigSel << 10) | (edgeSel << 8) | clock;
}

void CustomTC::InterruptConfig(Tc* instance, uint8_t channel, bool externalTrig)
{
  if(externalTrig)
  {
    MyPMC->EnablePeripheralClock(27);
    MyPMC->EnablePeripheralClock(29);
  }
  NVIC_EnableIRQ(TC6_IRQn);
  instance->TC_CHANNEL[channel].TC_IER = (externalTrig << 7);
}

void CustomTC::TIOConfig(Pio* pinGroup, uint8_t pinNumber, bool peripheral)
{
     pinGroup->PIO_PDR |= (1 << pinNumber);
     pinGroup->PIO_ABSR |= (peripheral << pinNumber);
}

void CustomTC::WriteProtection(Tc* instance,bool enable)
{
  instance->TC_WPMR = 0x54494D00 | enable;
}

Tc* CustomTC::GetInstance(uint8_t channel)
{
  if(channel < 3)
  {
    return TC0;
  }
  
  else if((channel > 2) && (channel < 6))
  {
    return TC1;
  }

  else
  {
    return TC2;
  }
}
