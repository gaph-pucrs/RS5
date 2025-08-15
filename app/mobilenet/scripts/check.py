import tensorflow as tf
import numpy as np
import keras
from tensorflow.keras.applications import MobileNet
from tensorflow.keras.models import Model
from tensorflow.keras.applications.mobilenet import preprocess_input
from tensorflow.keras.preprocessing import image

tf.config.set_visible_devices([], 'GPU')

img_path = '../img/rottweiler1.jpg'
img = keras.utils.load_img(img_path, target_size=(224,224))

x = keras.utils.img_to_array(img)
x = np.expand_dims(x, axis=0)
x = preprocess_input(x)

model = MobileNet()

np.set_printoptions(threshold=np.inf)
out = x

layers = [
    "conv1"
    # , "conv1_bn"
    # , "conv1_relu",

    # "conv_dw_1", "conv_dw_1_bn", "conv_dw_1_relu",
    # "conv_pw_1", "conv_pw_1_bn", "conv_pw_1_relu",
   
    # "conv_pad_2",
    # "conv_dw_2", "conv_dw_2_bn", "conv_dw_2_relu",
    # "conv_pw_2", "conv_pw_2_bn", "conv_pw_2_relu",

    # "conv_dw_3", "conv_dw_3_bn", "conv_dw_3_relu",
    # "conv_pw_3", "conv_pw_3_bn", "conv_pw_3_relu",

    # "conv_pad_4",
    # "conv_dw_4", "conv_dw_4_bn", "conv_dw_4_relu",
    # "conv_pw_4", "conv_pw_4_bn", "conv_pw_4_relu",

    # "conv_dw_5", "conv_dw_5_bn", "conv_dw_5_relu",
    # "conv_pw_5", "conv_pw_5_bn", "conv_pw_5_relu",

    # "conv_pad_6",
    # "conv_dw_6", "conv_dw_6_bn", "conv_dw_6_relu",
    # "conv_pw_6", "conv_pw_6_bn", "conv_pw_6_relu",

    # "conv_dw_7", "conv_dw_7_bn", "conv_dw_7_relu",
    # "conv_pw_7", "conv_pw_7_bn", "conv_pw_7_relu",

    # "conv_dw_8", "conv_dw_8_bn", "conv_dw_8_relu",
    # "conv_pw_8", "conv_pw_8_bn", "conv_pw_8_relu",

    # "conv_dw_9", "conv_dw_9_bn", "conv_dw_9_relu",
    # "conv_pw_9", "conv_pw_9_bn", "conv_pw_9_relu",

    # "conv_dw_10", "conv_dw_10_bn", "conv_dw_10_relu",
    # "conv_pw_10", "conv_pw_10_bn", "conv_pw_10_relu",

    # "conv_dw_11", "conv_dw_11_bn", "conv_dw_11_relu",
    # "conv_pw_11", "conv_pw_11_bn", "conv_pw_11_relu",

    # "conv_pad_12",
    # "conv_dw_12", "conv_dw_12_bn", "conv_dw_12_relu",
    # "conv_pw_12", "conv_pw_12_bn", "conv_pw_12_relu",

    # "conv_dw_13", "conv_dw_13_bn", "conv_dw_13_relu",
    # "conv_pw_13", "conv_pw_13_bn", "conv_pw_13_relu",

    # "global_average_pooling2d",
    
    # "conv_preds",
    
    # "predictions"
]

y = 0
for l in layers:
    y = model.get_layer(l)
    out = y(out)

o = np.array(out)
print(f",\n".join(map(str, o.flatten())))
