#include "actfunctions.h"


//Activation Functions.

float ReLU(float input)
{
  return (input > 0) ? input : 0;
}

float Sigmoid(float input)
{
  return exp(input)/(exp(input)+1); 
}
float Identity(float input)
{
   return input;
}
