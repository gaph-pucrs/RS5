import os
import sys
import torch

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

from OurLMFRNet import *

checkpoint = torch.load('../checkpoint/ckpt.pth')
# print(checkpoint.keys())

# layer = checkpoint['net']['module.features.stemBlock.stemConv.0.weight']
# layer = checkpoint['net']['module.features.stemBlock.stemConv.1.running_mean']
# print(f"{layer.shape}")

model = LMFRNet()
m, u = model.load_state_dict(checkpoint['net'], strict=False)

for name, l in model.named_parameters():
    print(f"{name} : {l.shape}")

# print(f"{m}")