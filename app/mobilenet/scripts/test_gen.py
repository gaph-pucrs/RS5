import os
import subprocess
import sys
import keras
import tensorflow as tf
import numpy as np
from tensorflow.keras.applications import MobileNet
from tensorflow.keras.applications.mobilenet import preprocess_input, decode_predictions
from tensorflow.keras.preprocessing import image

dataset_path = "../tiny_dataset/"
# dataset_path = "../img2/"
bin_path = "../data/"
image_size = [224, 224]

model = MobileNet()

if not os.path.exists (bin_path):
    subprocess.run(['mkdir', bin_path])


type = ''
if len(sys.argv) > 1:
    type = sys.argv[1]
else:
    type = 'float'

preds = []
test_number = 0
for _class in os.scandir(dataset_path):
    if _class.is_dir():
        for img in os.scandir(_class):
            x = keras.utils.load_img(img.path, target_size=image_size)
            x = keras.utils.img_to_array(x)
            x = preprocess_input(x)
            x = np.expand_dims(x, axis=0)
            pred = model(x)
            x.flatten()
            x = np.array(x, dtype = type)
            test_name = bin_path + str(test_number) + '.bin'
            x.tofile(test_name)
            test_number = test_number + 1
            class_id = np.argmax(pred)
            pred = decode_predictions(pred, top=1)[0][0]
            imagenet_id, class_name, score = pred
            preds.append([score, class_id])  

print(f"{test_number}")
for pred in preds:
    score, class_id = pred
    print(f"{class_id} {score}")