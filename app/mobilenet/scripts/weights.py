import sys
import numpy as np
import tensorflow as tf
from tensorflow.keras.applications import MobileNet

type = ''
if len(sys.argv) > 1:
    type = sys.argv[1]
else:
    type = 'float'

multiplier = 1
if len(sys.argv) > 2:
    multiplier = int(sys.argv[2])

def create_c_array_bn(layer):
    params_bn = ["_gamma", "_beta", "_eps", "_mean", "_var"]
    k = {
        "_gamma": [x*multiplier for x in layer.gamma.numpy().flatten()],
        "_beta": [x*multiplier for x in layer.beta.numpy().flatten()],
        "_eps": layer.epsilon*multiplier,  
        "_mean": [x*multiplier for x in layer.moving_mean.numpy().flatten()],
        "_var": [x*multiplier for x in layer.moving_variance.numpy().flatten()]
    }

    for suffix in params_bn:
        name = layer.name + suffix
        filename = "../params/" + name + ".h"

        with open(filename, "w") as f:
            f.write(f"#ifndef   __{name}_h\n")
            f.write(f"#define   __{name}_h\n\n")
            if suffix == "_eps":
                f.write(f"const {type} {name} = {k[suffix]};")
            else:
                f.write(f"const {type} {name}[] = {{\n")
                f.write(f",\n".join(map(str, k[suffix])))
                f.write(f"\n}};")
            f.write(f"\n\n#endif")

        print(f"(+) BatchNormalization {name} data generated in {filename} file") 

def create_c_array_w(layer):
    filename = "../params/" + layer.name + ".h"
    ww = layer.get_weights()[0]
    weights = ww.flatten()
    weights = [x*multiplier for x in weights]

    with open(filename, "w") as f:
        f.write(f"#ifndef   __{layer.name}_h__\n")
        f.write(f"#define   __{layer.name}_h__\n\n")
        f.write(f"//{layer.name}: {ww.shape}\n")
        f.write(f"const {type} {layer.name}[{len(weights)}] = {{\n")
        f.write(f",\n".join(map(str, weights)))
        f.write(f"\n}};")
        f.write(f"\n\n#endif")
    print(f"(+) Weights generated in {filename} file")

    if layer.use_bias:
        filename = "../params/" + layer.name + "_bias.h"
        bb = layer.get_weights()[1]
        bias = bb.flatten()
        bias = [x*multiplier for x in bias]

        with open(filename, "w") as fb:
            fb.write(f"#ifndef   __{layer.name}_bias_h__\n")
            fb.write(f"#define   __{layer.name}_bias_h__\n\n")
            fb.write(f"//{layer.name}_bias: {bb.shape}\n")
            fb.write(f"const {type} {layer.name}_bias[{len(bias)}] = {{\n")
            fb.write(f",\n".join(map(str, bias)))
            fb.write(f"\n}};")
            fb.write(f"\n\n#endif")

        print(f"(+) Weights generated in {filename} file")


model = MobileNet()

for layer in model.layers:
    if layer.weights:
        if isinstance(layer, tf.keras.layers.BatchNormalization):
            create_c_array_bn(layer)
        else:
            create_c_array_w(layer)
    