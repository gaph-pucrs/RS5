import tensorflow as tf
from tensorflow.keras.applications import MobileNet
import numpy as np

model = MobileNet(weights="imagenet")

def create_avg_array(layer):
    filename = "params/" + layer.name + "_avg.h"
    x = layer.moving_mean.numpy()
    avg = [m*1000 for m in x]

    with open(filename, "w") as f:
        f.write(f"#ifndef   __{layer.name}_avg_h\n")
        f.write(f"#define   __{layer.name}_avg_h\n\n")
        f.write(f"const int {layer.name}_avg[{len(avg)}] = {{\n")
        f.write(f",\n".join(map(str, avg)))
        f.write(f"\n}};")
        f.write(f"\n\n#endif")

def create_var_array(layer):
    filename = "params/" + layer.name + "_variance.h"
    x = layer.moving_variance.numpy()
    var = [v*1000 for v in x]

    with open(filename, "w") as f:
        f.write(f"#ifndef   __{layer.name}_variance.h\n")
        f.write(f"#define   __{layer.name}_variance.h\n\n")
        f.write(f"const int {layer.name}_variance[{len(var)}] = {{\n")
        f.write(f",\n".join(map(str, var)))
        f.write(f"\n}};")
        f.write(f"\n\n#endif")

for layer in model.layers:
    if isinstance(layer, tf.keras.layers.BatchNormalization):
        create_avg_array(layer)
        print(f"(+) BatchNormalization mean data generated in params/{layer.name}_avg.h file") 
        create_var_array(layer)
        print(f"(+) BatchNormalization variance data generated in params/{layer.name}_variance.h file")
