import keras
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense, Flatten, BatchNormalization, Dropout
from keras.layers import Conv2D, MaxPooling2D
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

img_rows, img_cols, channels = 32, 32, 3
input_shape = (img_rows, img_cols, channels)

#-------------------------------------------
#                AlexNet
#-------------------------------------------

model = Sequential()

# 1st conv layer
model.add(
    Conv2D(
        filters = 96,
        kernel_size = (11,11),
        activation = 'relu',
        strides = (4,4),
        input_shape = input_shape
    )
)

model.add(BatchNormalization())
model.add(
    MaxPooling2D(
        pool_size = (3,3),
        strides = (2,2)
    )
)

# 2nd conv layer
model.add(
    Conv2D(
        filters = 256,
        kernel_size = (5,5),
        activation = 'relu',
        strides = (1,1),
        padding = 'same'
    )
)

model.add(BatchNormalization())
model.add(
    MaxPooling2D(
        pool_size = (3,3),
        strides = (2,2),
        padding = 'same'
    )
)

# 3rd conv layer
model.add(
    Conv2D(
        filters = 384,
        kernel_size = (3,3),
        activation = 'relu',
        strides = (1,1),
        padding = 'same'
    )
)

# 4th conv layer
model.add(
    Conv2D(
        filters = 384,
        kernel_size = (3,3),
        activation = 'relu',
        strides = (1,1),
        padding = 'same'
    )
)

model.add(
    MaxPooling2D(
        pool_size = (3,3),
        strides = (2,2),
        padding = 'same'
    )
)

model.add(Flatten())
model.add(
    Dense(
        4096,
        activation = 'relu'
    )
)
model.add(Dropout(0.5))

model.add(
    Dense(
        4096,
        activation = 'relu'
    )
)
model.add(Dropout(0.5))

model.add(
    Dense(
        num_classes,
        activation = 'softmax'
    )
)

model.summary()
