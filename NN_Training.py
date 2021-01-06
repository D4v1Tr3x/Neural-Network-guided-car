import random
import numpy as np
from keras.layers import Dense
from keras.models import Sequential
from keras.optimizers import SGD

#*PARAMETERS
trainingSamples = 20000
validationSamples = 100000

#*CODIFICATION 3 sensor mode
#! [0,1,0] -->  0   (Recto)
#! [1,0,0] -->  -1  (Izquierda)
#! [1,1,0] -->  -1  (Izquierda)
#! [0,0,1] -->  1   (Derecha)
#! [0,1,1] -->  1   (Derecha)
#? [0,0,0] -->  2   (Parar)
#? [1,0,1] -->  2   (Parar)

#*CODIFICATION 5 sensor mode
#! [0,1,1,1,0] -->  0   (Recto)
#! [1,1,0,0,0] -->  -1  (Izquierda)
#! [1,1,1,0,0] -->  -1  (Izquierda)
#! [0,0,0,1,1] -->  1   (Derecha)
#! [0,0,1,1,1] -->  1   (Derecha)
#? [0,0,0,0,0] -->  2   (Parar)
#? [1,0,0,0,1] -->  2   (Parar)

def CreateInputs():
  action = random.randint(0,3)
  choice = random.randint(0,1)
  
  if action == 0:
    output = [0,1,0, 0]  if choice == 0 else [1,1,1, 0]
    return output
  if action == 3:
    output = [1,1,0, -1] if choice == 0 else [1,0,0, -1]
    return output
  if action == 1:
    output = [0,1,1, 1] if choice == 0 else [0,0,1, 1]
    return output
  if action == 2:
    output = [0,0,0, 2] #if choice == 0 else [1,0,1,2]
    return output

dataX = []
dataY = []
for _ in range(trainingSamples):
  data = CreateInputs()
  dataX.append(data[:3])
  dataY.append(data[3])

tX = np.array(dataX)
tY = np.array(dataY)


#*NN

opt = SGD(lr=0.04, momentum=0.9)
model = Sequential()
#! For 5 sensors mode uncomment the line below and comment the input shape 3 one.
#model.add(Dense(units=5, activation='relu', input_shape=(5,)))

model.add(Dense(units=5, activation='relu', input_shape=(3,)))
model.add(Dense(units=1, activation='linear'))

model.compile(optimizer=opt, loss='mean_squared_error', metrics=['accuracy'])
model.fit(x=tX, y=tY, epochs=25, verbose=2, shuffle=True)


matrix = np.zeros((4,4))
for _ in range(validationSamples):
  data = CreateInputs()
  valX = data[0:3]
  prediction = model.predict([[valX]])

  result = prediction.tolist()
  result = round(result[0][0])

  if result == 0:
    matrix[data[3], result] += 1
  if result == 1:
    matrix[data[3], result] += 1
  if result == 2:
    matrix[data[3], result] += 1
  if result == -1:
    matrix[data[3], result] += 1

for i in range(4):
  for j in range(4):
    matrix[i][j] /= validationSamples

print(matrix)
print(f'Samples: {validationSamples}')

print(model.get_weights())
print('\n')
for layerNum, layer in enumerate(model.layers):
    weights = layer.get_weights()[0]
    biases = layer.get_weights()[1]
    
    for toNeuronNum, bias in enumerate(biases):
        print(f'{layerNum}B -> L{layerNum+1}N{toNeuronNum}: {bias}')
    
    for fromNeuronNum, wgt in enumerate(weights):
        for toNeuronNum, wgt2 in enumerate(wgt):
            print(f'L{layerNum}N{fromNeuronNum} \
                  -> L{layerNum+1}N{toNeuronNum} = {wgt2}')
#model.save(
#          filepath='C:\\Users\\Usuario\\Desktop\\Code\\modelotesttest.h5',
#          overwrite=False,
#          include_optimizer=True
#          )