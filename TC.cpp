#include "TC.h"


CustomTC::CustomTC(){}

CustomTC::~CustomTC(){}


void CustomTC::CaptureModeConfig(Tc* instance, uint8_t channel, uint8_t edgeSel, 
                                 bool trigSel, uint8_t clock)
{
  instance->TC_CHANNEL[channel].TC_CMR = (trigSel << 10) | (edgeSel << 8) | clock;
  instance->TC_CHANNEL[channel].TC_CCR = 0x1;
  instance->TC_CHANNEL[channel].TC_CCR = 0x4;
}
