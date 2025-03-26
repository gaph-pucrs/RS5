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

img = [p*1 for p in x_t.flatten()]

filename = "params/data.h"

with open(filename, "w") as f:
    f.write(f"#ifndef   __IMG_H__\n")
    f.write(f"#define   __IMG_H__\n\n")
    f.write(f"//{x_t.shape}\n")
    f.write(f"const double img[{len(img)}] = {{\n")
    f.write(f",\n".join(map(str,img)))
    f.write(f"\n}};")
    f.write(f"\n\n#endif")
    print(f"(+) img generated in params/data.h file")

#print(f"{x_t.shape}")
#print(f"{x_t}")
