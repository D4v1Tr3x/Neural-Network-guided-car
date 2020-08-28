#include "layer.h"

//Constructor
Layer::Layer(void)
{
}

//Destructor
Layer::~Layer(void)
{
}

//Setups the layer
void Layer::Init(uint8_t inputs, uint8_t outputs, float* arr, float* arr2, 
                 actFunc_t ActFunc)
{
  NInputs = inputs;
  NOutputs = outputs;
  ActFunction = ActFunc;
  Weights = arr;
  Bias = arr2;
  inputData = new float[NInputs];
  outputData = new float[NOutputs];
}

void Layer::ComputeLayer(float* input, float* output)
{
    for(int j = 0; j < NOutputs; j++)
    {
        output[j] = 0;
        for (int i = 0; i < NInputs; i++)
        {
          output[j] += Weights[MAT_2_ARR(i, j, NOutputs)]*input[i];
        }
        output[j] += Bias[j];
        output[j] = ActFunction(output[j]);
    }
}

uint8_t Layer::GetNInputs()
{
  return NInputs;
}

uint8_t Layer::GetNOutputs()
{
  return NOutputs;
}

float* Layer::GetWeights()
{
  return Weights;
}

float* Layer::GetInputArray()
{
  return inputData;
}

float* Layer::GetOutputArray()
{
  return outputData;
}
