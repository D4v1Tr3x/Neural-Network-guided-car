#ifndef NN_H_
#define NN_H_

#include "layer.h"

class NN
{
 private:

  uint8_t nLayers;
  Layer *Layers;                                 //Stores layer data.
  
 public:

   NN(uint8_t nLayers, uint8_t* nInputs, uint8_t* nOutputs, 
      float** weights, float** biases, actFunc_t* actFuncs);       
                                                 //Constructor
  ~NN(void);                                     //Destructor

  void AddLayers(Layer *layer, uint8_t n);       //Adds layers with them inputs,
                                                 //outputs and weights.

  int8_t Predict(float* inputs, float* outputs); //Predicts the result given
                                                 //the inputs.
};

#endif
