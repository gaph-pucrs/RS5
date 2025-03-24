import keras
import numpy as np
from tensorflow.keras.applications.mobilenet import preprocess_input
from tensorflow.keras.preprocessing import image

img_path = './img/rottweiler1.jpg'
img = keras.utils.load_img(img_path, target_size=(224, 224))

x = keras.utils.img_to_array(img)
x = np.expand_dims(x, axis=0)
x = preprocess_input(x)

np.set_printoptions(threshold=np.inf)

x_t = np.transpose(x, (0, 3, 1, 2))

print(f"{x_t.shape}")
print(f"{x_t}")
