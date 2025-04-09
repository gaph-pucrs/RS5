import tensorflow as tf
import numpy as np
import keras
from tensorflow.keras.applications import MobileNet
from tensorflow.keras.models import Model
from tensorflow.keras.applications.mobilenet import preprocess_input
from tensorflow.keras.preprocessing import image

img_path = '../img/rottweiler1.jpg'
img = keras.utils.load_img(img_path, target_size=(224,224))

x = keras.utils.img_to_array(img)
x = np.expand_dims(x, axis=0)
x = preprocess_input(x)

model = MobileNet()

# model.summary()
# exit()

np.set_printoptions(threshold=np.inf)
out = x

layers = [
    "conv1", "conv1_bn", "conv1_relu", 
    "conv_dw_1"
    # "conv_dw_1", "conv_dw_1_bn"
    # "conv_dw_1", "conv_dw_1_bn", "conv_dw_1_relu"
]

for l in layers:
    y = model.get_layer(l)
    out = y(out)
    print(f"{y.name}")
    # if l == "conv_dw_1":
    #     o = np.array(y.get_weights()[0])
    #     # o = np.array(out)
    #     print(f",\n".join(map(str, o.flatten())))

exit()
o = np.array(out)
print(f",\n".join(map(str, o.flatten())))