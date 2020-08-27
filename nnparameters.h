#ifndef NNPARAMETERS_H_
#define NNPARAMETERS_H_

const uint8_t nLayers = 3;

uint8_t nInputs[]  = {3, 5, 3};
uint8_t nOutputs[] = {5, 3, 1};

actFunc_t actFuncs[] = {ReLU, ReLU, Identity};

float w1[] = {-0.34, -0.06,  1.53, -0.34, -0.35,
               0.39, -0.05,  0.28, -1.03,  0.64,
              -0.64, -0.47, -1.04, -0.93, -0.78};

float w2[] = {0.77, 0.25,  -0.32,
              0.25, -0.24, -0.58,
              1.03, -1.23,  0.34,
              0.33,  1.37, -0.17,
              0.56, -0.22, -0.20};

float w3[] = {-0.86,
               1.42,
               0.14};

float b1[] = {-0.14, -0.56,  0.15, 0.85, -0.14};
float b2[] = { 0.95,  0.14, -0.10};
float b3[] = { 1.62};

float *weights[nLayers] = {w1, w2, w3};
float *biases[nLayers] = {b1, b2, b3};


#endif
