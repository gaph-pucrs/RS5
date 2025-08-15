import os
import pickle
import torch
import numpy as np
import torchvision.transforms as transforms
from PIL import Image

path = '../autodl-tmp/data-cifar10/cifar-10-batches-py/'
filename = 'test_batch'

OUTPUT_DIRECTORY = '../test-dataset/'
type = 'int'
MULTIP = 1024*8

device = 'cuda' if torch.cuda.is_available() else 'cpu'

classes = ('plane', 'car', 'bird', 'cat', 'deer',
           'dog', 'frog', 'horse', 'ship', 'truck')

transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize(
        mean=[0.4914, 0.4822, 0.4465],
        std=[0.2023, 0.1994, 0.2010]
    ),
])

def unpickle(file):
    with open(file, 'rb') as fo:
        dict = pickle.load(fo, encoding='bytes')
    return dict

if not os.path.exists(OUTPUT_DIRECTORY):
        os.makedirs(OUTPUT_DIRECTORY)

test_dict = unpickle(path+filename)

n = 1
for image in test_dict[b'data']:
    out_file = OUTPUT_DIRECTORY + str(n) + '.bin' 
    # out_file = OUTPUT_DIRECTORY + 'image' + str(n) + '.h' 

    img = image.reshape(3, 32, 32).transpose(1, 2, 0)
    img = transform(img)
    img = img.unsqueeze(0)

    # x = (img.permute(0, 2, 3, 1).numpy().flatten()*MULTIP).astype(np.float32)
    x = (img.permute(0, 2, 3, 1).numpy().flatten()*MULTIP).astype(np.int32)

    with open(out_file, "wb") as f:
        f.write(x.tobytes())
    # with open(out_file, "w") as f:
    #     f.write(f"#ifndef __LMFRNET_INPUT_IMAGE__h\n")
    #     f.write(f"#define __LMFRNET_INPUT_IMAGE__h\n\n")
    #     f.write(f"const {type} image1[{x.size}] = {{\n")
    #     f.write(f",\n".join(map(str, x)))
    #     f.write(f"\n}};")
    #     f.write(f"\n\n#endif")

    print(f"[+] image generated in {out_file} file!")
    # break

    n = n + 1
