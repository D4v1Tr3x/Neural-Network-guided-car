#include "pwm.h"


CustomPWM::CustomPWM(CustomPMC* pmc)
{ 
  pmc->EnablePeripheralClock(PWM_ID);
}

CustomPWM::~CustomPWM(){}

bool CustomPWM::CheckWriteProtectStatus(uint8_t ID)
{
  uint16_t value = (1 << (ID+8)) + (1 << ID);
  if((PWM->PWM_WPSR && value) != 0){return true;}
  return false;
}

void CustomPWM::SetCPRD(uint16_t CPRD, uint8_t channel)
{
  if(channel <= 7)
  {
    PWM->PWM_CH_NUM[channel].PWM_CPRD = CPRD;
  }
}

void CustomPWM::SetDuty(float d, uint8_t channel, bool init)
{
  if(channel <= 7)
  {
    uint16_t CPRD = PWM->PWM_CH_NUM[channel].PWM_CPRD;
    if(init)
    {
      PWM->PWM_CH_NUM[channel].PWM_CDTY = (1-d) * CPRD;
    }
    else
    {
      PWM->PWM_CH_NUM[channel].PWM_CDTYUPD = (1-d) * CPRD;
    }
  } 
}

void CustomPWM::ClockGenerator(uint8_t divA, uint8_t preA, uint8_t divB, 
                                  uint8_t preB)
{
  PWM->PWM_CLK = (preB << 24) + (divB << 16) + (preA << 8) + divA;
}

void CustomPWM::EnableChannel(uint8_t channel)
{

    PWM->PWM_ENA |= 1 << channel;
    DisableUnusedChannels();
}

void CustomPWM::DisableUnusedChannels()
{
  PWM->PWM_DIS = !PWM->PWM_SR;
};

void CustomPWM::SetupChannelMode(uint8_t channel, uint8_t CPRE, uint8_t CALG, 
                                 uint8_t CPOL, uint8_t CES, uint8_t DTE, 
                                 uint8_t DTHI, uint8_t DLTI)
{
  uint32_t reg = (DLTI << 18) + (DTHI << 17) + (DTE << 16);
  reg |= (CES << 10) + (CPOL << 9) + (CALG << 8);
  reg |= CPRE;

  PWM->PWM_CH_NUM[channel].PWM_CMR = reg;
}

void CustomPWM::OpenEventLine(uint8_t line, uint8_t comparisonChannel)
{
  PWM->PWM_ELMR[line] |= 1 << comparisonChannel;
}

void CustomPWM::ComparisonMode(uint8_t CEN, uint8_t CPR, uint8_t CTR, 
                               uint8_t channel)
{
  PWM->PWM_CMP[channel].PWM_CMPM = (CTR << 8) + (CPR << 4) + CEN;
}

void CustomPWM::EnableComparisonMatchInterrupt(uint8_t channel)
{
  PWM->PWM_IER2 = (1 << (16+channel)) + (1 << (8+channel));
}

void CustomPWM::SetComparisonValue(uint16_t val, uint8_t mode, uint8_t channel)
{
  PWM->PWM_CMP[channel].PWM_CMPV = val;
}

void CustomPWM::GetPin(uint8_t channel, uint32_t &pin, Pio* &pinGroup)
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

uint16_t CustomPWM::GetCPRD(uint8_t channel)
{
  return PWM->PWM_CH_NUM[channel].PWM_CPRD;
}
