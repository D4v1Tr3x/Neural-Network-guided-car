#include "NN.h"
#include "functions.h"

//Constructor
NN::NN(uint8_t nLayers, uint8_t* nInputs, uint8_t* nOutputs, 
       float** weights, float** biases, actFunc_t* actFuncs)
{
  Layer **layers = new Layer*[nLayers];

  for(uint8_t i = 0; i < nLayers; i++)
  {
    layers[i] = new Layer();
    layers[i]->Init(nInputs[i], nOutputs[i], weights[i], biases[i], actFuncs[i]);
  }
  this->AddLayers(layers, nLayers);
}
//Destructor
NN::~NN(void)
{
}

//The NN stores each layer through this method.
void NN::AddLayers(Layer **layer, uint8_t n)
{
  nLayers = n;
  Layers = layer;
}

//Predicts the output given the inputs.
void NN::Predict(float* inputs, float* outputs)
{
    
   uint8_t nIn = Layers[0]->GetNInputs();
   CopyArray(Layers[0]->GetData(), inputs, nIn);
   float* out = new float[nLayers-1];
   
   for(uint8_t layer = 0; layer < nLayers; layer++)
   {
    nIn = Layers[layer]->GetNOutputs();
    if(layer == nLayers-1)
    {
      Layers[layer]->ComputeLayer(Layers[layer]->GetData(), out);
    }
    else
    {
    Layers[layer]->ComputeLayer(Layers[layer]->GetData(), Layers[layer+1]->GetData());
    EraseData(Layers[layer]->GetData(), Layers[layer]->GetNInputs());
    }
   }
   CopyArray(outputs, out, nIn);
   delete[] out;

   Serial.print("Prediction: ");
   ReadArray(outputs, nIn);
}

/*Ignora este metodo era de debug
float NN::GetLayers()
{
  
  return this->Layers[nLayers]->GetData()[0];
}
*/
