import tensorflow as tf
from tensorflow.keras.applications import MobileNet
import numpy as np

def create_c_array_bn(layer):
    params_bn = ["_gamma", "_beta", "_eps", "_mean", "_var"]
    k = {
        "_gamma": layer.gamma.numpy().flatten(),
        "_beta": layer.beta.numpy().flatten(),
        "_eps": layer.epsilon,  
        "_mean": layer.moving_mean.numpy().flatten(),
        "_var": layer.moving_variance.numpy().flatten(),
    }

    for suffix in params_bn:
        name = layer.name + suffix
        # filename = "/sim/RS5/app/tiny-ml/mobilenet/py/v2/params/" + name + ".h"
        filename = "../params/" + name + ".h"
        with open(filename, "w") as f:
            f.write(f"#ifndef   __{name}_h\n")
            f.write(f"#define   __{name}_h\n\n")
            if suffix == "_eps":
                f.write(f"const double {name} = {k[suffix]};")
            else:
                f.write(f"const double {name}[] = {{\n")
                f.write(f",\n".join(map(str, k[suffix])))
                f.write(f"\n}};")
            f.write(f"\n\n#endif")
        print(f"(+) BatchNormalization {name} data generated in {filename} file") 

def create_c_array_w(layer):
    # filename = "/sim/RS5/app/tiny-ml/mobilenet/py/v2/params/" + layer.name + ".h"
    filename = "../params/" + layer.name + ".h"
    ww = layer.get_weights()[0]
    weights = ww.flatten()
    with open(filename, "w") as f:
        f.write(f"#ifndef   __{layer.name}_h__\n")
        f.write(f"#define   __{layer.name}_h__\n\n")
        f.write(f"//{layer.name}: {ww.shape}\n")
        f.write(f"const double {layer.name}[{len(weights)}] = {{\n")
        f.write(f",\n".join(map(str, weights)))
        f.write(f"\n}};")
        f.write(f"\n\n#endif")
    print(f"(+) Weights generated in {filename} file")
    
model = MobileNet()

for layer in model.layers:
    if layer.weights:
        if isinstance(layer, tf.keras.layers.BatchNormalization):
            # create_c_array_bn(layer)
            continue
        else:
            create_c_array_w(layer)
    