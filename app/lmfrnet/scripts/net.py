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

device = 'cuda' if torch.cuda.is_available() else 'cpu'
model = LMFRNet()

if device == 'cuda':
    model = torch.nn.DataParallel(model)
    # cudnn.benchmark = True

m, u = model.load_state_dict(checkpoint['net'])


for name, l in model.named_parameters():
    print(f"{name} : {l.shape}")
    
# print(f"{m}")