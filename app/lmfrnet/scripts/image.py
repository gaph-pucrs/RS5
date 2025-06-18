import torch
import numpy as np
import torchvision.transforms as transforms
from PIL import Image

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

print(f",\n".join(map(str, x)))