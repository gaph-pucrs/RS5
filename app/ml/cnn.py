import keras
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense, Flatten
from keras.layers import Conv2D, AveragePooling2D
from keras import backend as K

import matplotlib.pyplot as plt
import altair as alt
import numpy as np
import pandas as pd

# unpack data into training and test
(x_train, y_train), (x_test, y_test) = mnist.load_data()
#print(f'x_train shape: {x_train.shape}')
#print(f'x_test shape: {x_test.shape}')

fig = plt.figure()
for i in range(6):
    plt.subplot(2, 3, i+1)
    plt.imshow(x_train[i], cmap=plt.get_cmap('gray'))

# reshaping data
img_rows, img_cols, channels = 28, 28, 1

if K.image_data_format() == 'channels_first':
    x_train = x_train.reshape(x_train.shape[0], channels, img_rows, img_cols)
    x_test = x_test.reshape(x_test.shape[0], channels, img_rows, img_cols)
    input_shape = (channels, img_rows, img_cols)
else:
    x_train = x_train.reshape(x_train.shape[0], img_rows, img_cols, channels)
    x_test = x_test.reshape(x_test.shape[0], img_rows, img_cols, channels)
    input_shape = (img_rows, img_cols, channels)

#print(f'x_train shape: {x_train.shape}')
#print(f'x_test shape: {x_test.shape}')

# normalizing data (converge faster)
x_train = x_train.astype('float32')
x_test = x_test.astype('float32')
x_train /= 255
x_test /= 255

# v[n_samples] => m[n_samples][n_classes]
num_classes = 10 # 0-9
y_train = keras.utils.to_categorical(y_train, num_classes)
y_test = keras.utils.to_categorical(y_test, num_classes)

#print(f'y_train shape *after* one-hot encoding: {y_train.shape}')
#print(f'y_test shape *after* one-hot encoding: {y_test.shape}')

#----------------------------
#       LeNet-5
#----------------------------

# define the network as a linear STACK of layers
model = Sequential()

# 1st conv layer
model.add(
    Conv2D(
       filters = 6,     # feature maps
       kernel_size = (5,5),     # kernel shape
       activation = 'tanh',
       input_shape = input_shape
    )
)

# 1st pooling layer 2x2
model.add(AveragePooling2D(pool_size = (2,2)))

# 2nd conv layer
model.add(
    Conv2D(
        filters = 16,
        kernel_size = (5,5),
        activation = 'tanh'
    )
)

# 2nd pooling layer 2x2
model.add(AveragePooling2D(pool_size = (2,2)))

# flatten the feature maps
model.add(Flatten())

# 1st fully-connected layer
model.add(
    Dense(
        120,
        activation = 'sigmoid'
    )
)

# 2nd fully-connected layer
model.add(
    Dense(
        84,
        activation = 'sigmoid'
    )
)

# output layer with softmax activation and 10 output classes
model.add(
    Dense(
        num_classes,
        activation = 'softmax'
    )
)

#model.summary()

model.compile(
    loss = keras.losses.categorical_crossentropy,
    optimizer = keras.optimizers.Adadelta(),    # variation of backpropagation
    metrics = ['accuracy']
)

#------------------------------
#         training
#------------------------------

epochs = 12
batch_size = 8

history = model.fit(
    x_train,
    y_train,
    batch_size = batch_size,
    epochs = epochs,
    verbose = 1,
    validation_data = (x_test,y_test)
)
