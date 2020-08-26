#include "NN.h"



//Constructor
NN::NN(uint8_t nLayers, uint8_t* nInputs, uint8_t* nOutputs, 
       float** weights, float** biases, actFunc_t* actFuncs)
{
  Layer layers[nLayers];

  for(uint8_t i = 0; i < nLayers; i++)
  {
    layers[i].Init(nInputs[i], nOutputs[i], weights[i], biases[i], actFuncs[i]);
  }
  
  this->AddLayers(layers, nLayers);
}
//Destructor
NN::~NN(void)
{
}

//The NN stores each layer through this method.
void NN::AddLayers(Layer *layer, uint8_t n)
{
  nLayers = n;
  Layers = layer;
}

//Predicts the output given the inputs.
int8_t NN::Predict(float* inputs, float* outputs)
{
    uint8_t nIn = Layers[0].GetNInputs();
    //Iterates trough the list of layers.
    for(uint8_t layer = 0; layer < nLayers; layer++)
    {
        outputs = Layers[layer].ComputeLayer(inputs, outputs);
        nIn = Layers[layer].GetNOutputs();
        for(uint8_t i = 0; i < nIn; i++)
          {
            inputs[i] = outputs[i];
          }
    }
    return 0;
}
