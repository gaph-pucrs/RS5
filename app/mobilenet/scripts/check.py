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

layer_name = "conv1_bn"
m = tf.keras.Model (
    inputs = model.input,
    outputs = model.get_layer(layer_name).output
)

out = m(x)

# bn = tf.keras.Model (
#     inputs = model.input,
#     outputs = model.get_layer("conv1_bn").output
# )

# out2 = bn(out)

o = np.array(out)
# out_t = np.transpose(out, (3,2,1,0))
np.set_printoptions(threshold=np.inf)
# print(f"{out_t.flatten()}")
# print(f"{o.flatten()}")
print(f",\n".join(map(str, o.flatten())))
# print(f",\n".join(map(str, out_t.flatten())))
# print(f"{m.get_weights()}")
