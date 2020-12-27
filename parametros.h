#ifndef PARAMETROS_H_
#define PARAMETROS_H_

#include "pios.h"
#include "TC.h"

//------HANDLER PARAMETERS-------

//PIOC_Handler
uint32_t status; //Variables to read a status and clear a bit
uint32_t uStat;  

uint32_t counter;         //Variable that stores how much the timer has counted
float timeConst = 0.024;  //Variable that determines how much millisecons there are 
                          //per count (24kHz = 0.024mS)

float distance = 0;   //Variable that stores how much distance the sensor detects with
                      //a digital filter on it
float y;              //Same as the previous variable but without the filter
float b = 0.949;      //Variable that stores the value of the digital filter
bool danger = false;  //Determines if the distance measured is dangerous for the system


//ADC_Handler

const uint8_t sensorsUsed = 5;        //How many sensors are used
const float uRef = 3.3;               //Reference HIGH voltage for the ADC
const float ADC_Resolution = 4095.0;  //Bits of resolution (12)

float tension;                        //Voltage seen by the ADC
float uIn[sensorsUsed];               //Array of the voltages seen
uint16_t dAdc;                        //Channel data of the ADC


//----NN CONTROL PARAMETERS----

float prediction[1];                  //Prediction of the NN
uint8_t lastMov;                      //Last movement made by the system
bool motorFlag = false;               //Boolean that determines if the car moves or not



//-----MODULES PARAMETERS-----

//UltraSounds
uint8_t PWMPinUS = 7;
Pio* PWMPinGroupUS = PIOC;
uint8_t PWMChannelUS = 2;

uint8_t TCPin = 25;
Pio* TCPinGroup = PIOC;
uint8_t TCChannel = 0;

uint8_t echoPin = 23;
Pio* echoPinGroup = PIOC;

//Motor Parameters
uint8_t frequency = 24; //In kHz

uint8_t motorPins[] = {1, 2, 3, 6};
Pio* motorGroups[] = {PIOD, PIOD, PIOD, PIOD};


uint8_t PWMChannels[] = {0, 1};
uint8_t PWMPins[] = {3, 5};
Pio* PWMGroups[] = {PIOC, PIOC};

//IR Parameters
uint8_t ADCPWMChannel = 3;
uint8_t ADCChannels[] = {0, 1, 2, 3, 4};
uint8_t ADCPins[] = {16, 24, 23, 22, 6};
Pio* ADCPinGroups[] = {PIOA, PIOA, PIOA, PIOA, PIOA};

#endif
