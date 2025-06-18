import os
import torch
import numpy as np
import torchvision.transforms as transforms
from PIL import Image

OUTPUT_DIRECTORY = '../c-dataset/'
filename = OUTPUT_DIRECTORY + 'image1.h'
type = 'float'

if not os.path.exists(OUTPUT_DIRECTORY):
        os.makedirs(OUTPUT_DIRECTORY)
transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize(
        mean=[0.4914, 0.4822, 0.4465],
        std=[0.2023, 0.1994, 0.2010]
    ),
])

img = Image.open('../cifar-10/test/3364.png').convert('RGB')
img = transform(img)
img = img.unsqueeze(0)

x = img.permute(0, 2, 3, 1).numpy().flatten()

with open(filename, "w") as f:
    f.write(f"#ifndef __LMFRNET_INPUT_IMAGE__h\n")
    f.write(f"#define __LMFRNET_INPUT_IMAGE__h\n\n")
    f.write(f"const {type} image1[{x.size}] = {{\n")
    f.write(f",\n".join(map(str, x)))
    f.write(f"\n}};")
    f.write(f"\n\n#endif")

print(f"[+] parameters generated in {filename} file!")

# print(f",\n".join(map(str, x)))