import torch
import numpy as np
import torchvision.transforms as transforms
from PIL import Image
from OurLMFRNet import LMFRNet

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

with torch.no_grad():
    outputs = model(img)
    predicted_class = torch.argmax(outputs, dim=1).item()

print(f"Predicted class: {classes[predicted_class]}")