import keras
import numpy as np
from tensorflow.keras.applications import MobileNet, MobileNetV3Small, ResNet50, EfficientNetV2B0
from tensorflow.keras.applications.mobilenet import preprocess_input, decode_predictions
from tensorflow.keras.preprocessing import image

# img_path = 'img/rottweiler1.jpg'
# img = keras.utils.load_img(img_path, target_size=(224,224))

# x = keras.utils.img_to_array(img)
# x = preprocess_input(x)
# x = np.expand_dims(x, axis=0)

model = MobileNet()

# model = MobileNet(include_top=False, classes=100)
# pred = model(x)
# pred = decode_predictions(pred, top=3)
# print(f"{pred}")
# model = MobileNetV3Small(minimalistic=True)
# model = ResNet50()
# model = EfficientNetV2B0()

model.summary()
