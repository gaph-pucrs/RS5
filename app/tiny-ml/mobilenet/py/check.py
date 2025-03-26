import tensorflow as tf
import keras
from tensorflow.keras.applications import MobileNet
import numpy as np
from tensorflow.keras.applications.mobilenet import preprocess_input

img_path = './img/rottweiler1.jpg'
img = keras.utils.load_img(img_path, target_size=(224, 224))

x = keras.utils.img_to_array(img)
x = np.expand_dims(x, axis=0)
x = preprocess_input(x)

model = MobileNet()

#model.summary()

l = tf.keras.Model (
    inputs = model.input,
    outputs = model.get_layer("conv1").output
)

out = l(x)
out_t = np.transpose(out, (0, 3, 1, 2))
img = out_t.flatten()

# shape: (1, 112, 112, 32)
#print(f"shape: {out.shape}")
#np.set_printoptions(threshold=np.inf)
#print(f"{out_t}")

filename = "gab"
with open(filename, "w") as f:
    f.write(f",\n".join(map(str,img)))

