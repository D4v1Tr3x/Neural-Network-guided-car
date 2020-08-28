#include "NN.h"
#include "functions.h"

//Constructor
NN::NN(uint8_t nLayers, uint8_t* nInputs, uint8_t* nOutputs, 
       float** weights, float** biases, actFunc_t* actFuncs)
{
  Layer *layers = new Layer[nLayers];

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
float NN::Predict(float* inputs, float* outputs)
{
  
   uint8_t nIn = Layers[0].GetNInputs();
   CopyArray(Layers[0].GetInputArray(), inputs, nIn);
   
   for(uint8_t layer = 0; layer < nLayers; layer++)
   {
    nIn = Layers[layer].GetNOutputs();
    Layers[layer].ComputeLayer(Layers[layer].GetInputArray(), Layers[layer].GetOutputArray());
    ReadArray(Layers[layer].GetOutputArray(), nIn);
    Serial.println("\n");
    ReadArray(Layers[layer].GetOutputArray(), nIn);
    Serial.println("\n");
    if(layer < nLayers)
      {
        CopyArray(Layers[layer+1].GetInputArray(), Layers[layer].GetOutputArray(), nIn);
      }
   }
   
   
   return Layers[nLayers].GetOutputArray()[0];
}
