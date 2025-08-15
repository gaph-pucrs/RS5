import os
import keras
import tensorflow as tf
import numpy as np
from tensorflow.keras.preprocessing import image
from tensorflow.keras.applications.mobilenet import preprocess_input


dataset_path = "../tiny_dataset/"
bin_path = "../data/"

image_size = [224, 224]

for _class in os.scandir(dataset_path):
    if _class.is_dir():
        for img in os.scandir(_class):
            x = keras.utils.load_img(img.path, target_size=image_size)
            x = keras.utils.img_to_array(x)
            x = preprocess_input(x)
            x = np.expand_dims(x, axis=0)
            x = x.flatten()
            substr = os.path.splitext(img.name)[0]
            x.tofile(bin_path + substr + '.bin')
            print(f"{substr}")
