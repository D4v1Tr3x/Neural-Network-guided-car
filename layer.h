#ifndef LAYER_H_
#define LAYER_H_


#define MAT_2_ARR(i, j, n) (j + n*i)
#include <cstdint>
#include "actfunctions.h"
#include "Arduino.h"

typedef float(*actFunc_t)(float);


class Layer{
 private:
  //Layer specs
  uint8_t NInputs;
  uint8_t NOutputs;
  float* Weights;
  actFunc_t ActFunction;
  float* Bias;
  float* inputData;
  

 public:
  //Constructor
  Layer(void);

  //Destructor
  ~Layer(void);

  //Setups the layer
  void Init(uint8_t inputs, uint8_t outputs, float* arr, float* arr2, 
            actFunc_t ActFunc);

  void ComputeLayer(float* input, float* output);

  //Getters
  uint8_t GetNInputs();
  uint8_t GetNOutputs();
  float* GetWeights();
  float* GetData();
  
};

#endif
