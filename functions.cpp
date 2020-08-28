#include "functions.h"


void CopyArray(float* arr1, float* arr2, uint8_t len)
{
  for(uint8_t i = 0; i < len; i++)
  {
    arr1[i] = arr2[i];
  }
}

void EraseData(float* arr, uint8_t len)
{
  for(uint8_t i = 0; i < len; i++)
  {
    arr[i] = 0;
  }
}

void ReadArray(float* arr, uint8_t len)
{
  for(uint8_t i = 0; i < len; i++)
  {
    Serial.println(arr[i]);
  }
}
