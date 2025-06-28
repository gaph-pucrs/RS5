import os
import sys
import torch
import numpy as np
import torchvision.transforms as transforms
from PIL import Image
from OurLMFRNet import LMFRNet

debug_layer = 'tran_ConvNormRelu1'

if len(sys.argv) > 1:
    debug_layer = sys.argv[1]
else:
    print(f"Usage: python test.py <debug_layer>")
    exit()

checkpoint = torch.load('./checkpoint/ckpt.pth')

device = 'cuda' if torch.cuda.is_available() else 'cpu'

model = LMFRNet()
model = model.to(device)
if device == 'cuda':
    model = torch.nn.DataParallel(model)

model.load_state_dict(checkpoint['net'])
model.eval()

transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize(
        mean=[0.4914, 0.4822, 0.4465],
        std=[0.2023, 0.1994, 0.2010]
    ),
])

classes = ('plane', 'car', 'bird', 'cat', 'deer',
           'dog', 'frog', 'horse', 'ship', 'truck')

# img = Image.open('./cifar-10/test/1298.png').convert('RGB') # horse
# img = Image.open('./cifar-10/test/226449.png').convert('RGB') # truck
img = Image.open('./cifar-10/test/3364.png').convert('RGB') # frog
img = transform(img)
img = img.unsqueeze(0)

def save(name, out):
    # NHWC format
    out_nhwc = out.permute(0, 2, 3, 1).numpy()
    x = out_nhwc.flatten()

    base = './cmp/'
    if not os.path.exists(base):
        os.makedirs(base)

    base += 'py/'
    if not os.path.exists(base):
        os.makedirs(base)

    filename = base + name + '.txt'
    with open(filename, "w") as f:
        f.write(f",\n".join(map(str,x)))

    print(f"[+] results for compare generated in {filename} file!")

debug = {}
def make_hook(layer_name):
    def hook_fn(module, input, output):
        debug[layer_name] = output.detach().cpu()
    return hook_fn

handles = []
for name, layer in model.module.features.named_children():
    hook = layer.register_forward_hook(make_hook(name))
    handles.append(hook)

with torch.no_grad():
    outputs = model(img)
    predicted_class = torch.argmax(outputs, dim=1).item()

for name, output in debug.items():
    #print(f"Layer {name}:\n {output.numpy().flatten()}")
    #save(name, output)
    if name == debug_layer:
        save(name, output)
        break;
    #break
    #print(f"Layer {name}: shape = {output.shape}")

#print(f"Predicted class: {classes[predicted_class]}")

for handle in handles:
    handle.remove()
