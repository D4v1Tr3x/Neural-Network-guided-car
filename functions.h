#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <cstdint>
#include "Arduino.h"

extern void CopyArray(float* arr1, float* arr2, uint8_t len);

extern void EraseData(float* arr, uint8_t len);

extern void ReadArray(float* arr, uint8_t len);
#endif
