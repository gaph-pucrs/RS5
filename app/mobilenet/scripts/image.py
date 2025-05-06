import numpy as np
import keras
from tensorflow.keras.applications.mobilenet import preprocess_input
from tensorflow.keras.preprocessing import image

img_path = '../img/rottweiler1.jpg'
img = keras.utils.load_img(img_path, target_size=(224,224))

x = keras.utils.img_to_array(img)
x = preprocess_input(x)
# x = np.pad(x, pad_width=((1,1), (1,1), (0,0)), mode='constant', constant_values=0)
x = np.pad(x, pad_width=((0,1), (0,1), (0,0)), mode='constant', constant_values=0)
x = np.expand_dims(x, axis=0)

img_input = x.flatten()

filename = "../params/data.h"

with open(filename, "w") as f:
    f.write(f"#ifndef   __IMG_H__\n")
    f.write(f"#define   __IMG_H__\n\n")
    f.write(f"//{x.shape}\n")
    f.write(f"const double img[{len(img_input)}] = {{\n")
    f.write(f",\n".join(map(str,img_input)))
    f.write(f"\n}};")
    f.write(f"\n\n#endif")
    print(f"(+) Image generated in params/data.h file")