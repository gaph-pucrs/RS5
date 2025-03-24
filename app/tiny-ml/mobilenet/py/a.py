from tensorflow.keras.applications import MobileNet
import numpy as np

# Load MobileNet with ImageNet weights
model = MobileNet(weights="imagenet")

# Find the depthwise convolution layer
for layer in model.layers:
    if "conv1" in layer.name:  # Look for the depthwise layer
        weights = layer.get_weights()[0]  # First element contains kernel weights
        weights_t = np.transpose(weights, (3, 0, 1, 2))
        print(f"Layer Name: {layer.name}")
        print(f"weights_t.shape: {weights_t.shape}")
        #print(f"Kernel Shape: {weights.shape}")  # Should be (3, 3, 32, 1) for depthwise conv
        print(f"Kernel Weights:\n{weights_t}")  # Print the actual weights
        break  # Stop after finding the first match

