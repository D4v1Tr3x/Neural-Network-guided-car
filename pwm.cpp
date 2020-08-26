#include "pwm.h"

void pwm_setup(uint16_t* channels, uint8_t len, bool EnableComparison, 
               uint8_t clockFreq)
{
  //Gets the pins and its groups corresponding to each channel
  uint32_t pins[len];
  Pio* pinGroups[len];
  for(uint8_t i = 0; i < len; i++)
  {
    GetPin(channels[i], pins[i], pinGroups[i]);
  }
  
  //Activates the PWM on those pins
  ActivatePeripheralControl(pins, len, pinGroups);
  ChangePeripheral(pins, len, pinGroups);
  
  //Enables the PWM to work on the designated channels
  EnablePeripheralClock(PWM_ID);
  EnablePWMChannels(channels, len);
  
  //Calculates the degree of precision that the PWM will have based on the
  //desired frecuency that we want as clock for all the channels.
  uint16_t CPRD = 84e3/(2*clockFreq);
  for(uint8_t i = 0; i < len; i++)
  {
    SetCPRD(CPRD, i);
  } 
  
  //Enables the comparison mode that will trigger the event line once the channel 
  //counter reaches a certain value so it can send a pulse to the ADC in order 
  //to start a new conversion
  if(EnableComparison)
  {
    PWM->PWM_CMP[0].PWM_CMPM = 0x401;

    PWM->PWM_CMP[0].PWM_CMPV = 1750;
  
    PWM->PWM_ELMR[0] = 0x1;
  
    PWM->PWM_IER2 = 0x10100;
  }
}

bool CheckWriteProtectStatus(uint8_t ID)
{
  uint16_t value = (1 << (ID+8)) + (1 << ID);
  if((PWM->PWM_WPSR && value) != 0){return true;}
  return false;
};

void SetCPRD(uint16_t CPRD, uint8_t channel)
{
  if(channel <= 7)
  {
    PWM->PWM_CH_NUM[channel].PWM_CPRD = CPRD;
  }
};

void SetDuty(float d, uint8_t channel)
{
  if(channel <= 7)
  {
    uint16_t CPRD = PWM->PWM_CH_NUM[channel].PWM_CPRD;
    PWM->PWM_CH_NUM[channel].PWM_CDTYUPD = (1-d) * CPRD;
  } 
};

void PWMClockGenerator(uint8_t divA, uint8_t preA, uint8_t divB, uint8_t preB)
{
  PWM->PWM_CLK = (preB << 24) + (divB << 16) + (preA << 8) + divA;
};

void EnablePWMChannels(uint16_t* channels, uint8_t len)
{
  for(uint8_t i = 0; i < len; i++)
  {
    PWM->PWM_ENA |= channels[i];
  }
  DisableUnusedPWMChannels();
};

void DisableUnusedPWMChannels()
{
  PWM->PWM_DIS = !PWM->PWM_SR;
};

void SetupChannelMode(uint8_t channel, uint8_t CPRE, uint8_t CALG, uint8_t CPOL, 
                      uint8_t CES, uint8_t DTE, uint8_t DTHI, uint8_t DLTI)
{
  uint32_t reg = (DLTI << 18) + (DTHI << 17) + (DTE << 16);
  reg |= (CES << 10) + (CPOL << 9) + (CALG << 8);
  reg |= CPRE;

  PWM->PWM_CH_NUM[channel].PWM_CMR = reg;
};

void EnableComparisonOnLine(uint8_t line, uint8_t channels)
{
  PWM->PWM_ELMR[line] = channels;
};

void ComparisonMode(uint32_t config, uint8_t channel)
{
  PWM->PWM_CMP[channel].PWM_CMPM = config;
};

void GetPin(uint8_t channel, uint32_t &pin, Pio* &pinGroup)
{
  switch(channel)
  {
    case 0x01:
      pin = 0x08;
      pinGroup = PIOC;
      break;

    case 0x02:
      pin = 0x20;
      pinGroup = PIOC;
  }
}
