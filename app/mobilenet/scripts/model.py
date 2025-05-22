import os
import keras
import tensorflow as tf
import numpy as np
from tensorflow.keras.applications import MobileNet
from tensorflow.keras.applications.mobilenet import preprocess_input, decode_predictions
from tensorflow.keras.preprocessing import image

dataset_path = "../tiny_dataset/"
# dataset_path = "../dataset/"
image_size = [224, 224]

model = MobileNet()

preds = []

for _class in os.scandir(dataset_path):
    if _class.is_dir():
        for img in os.scandir(_class):
            x = keras.utils.load_img(img.path, target_size=image_size)
            x = keras.utils.img_to_array(x)
            x = preprocess_input(x)
            x = np.expand_dims(x, axis=0)
            pred = model(x)
            class_id = np.argmax(pred)
            pred = decode_predictions(pred, top=1)[0][0]
            imagenet_id, class_name, score = pred
            preds.append([score, class_id])  

for pred in preds:
    score, class_id = pred
    print(f"{class_id} {score}")