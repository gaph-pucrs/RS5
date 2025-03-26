import tensorflow as tf
from tensorflow.keras.applications import MobileNet
import numpy as np

model = MobileNet(weights="imagenet")

def create_avg_array(layer):
    filename = "params/" + layer.name + "_avg.h"
    x = layer.moving_mean.numpy()
    avg = [m*1 for m in x]

    with open(filename, "w") as f:
        f.write(f"#ifndef   __{layer.name}_avg_h\n")
        f.write(f"#define   __{layer.name}_avg_h\n\n")
        f.write(f"const double {layer.name}_avg[{len(avg)}] = {{\n")
        f.write(f",\n".join(map(str, avg)))
        f.write(f"\n}};")
        f.write(f"\n\n#endif")
    print(f"(+) BatchNormalization mean data generated in {filename} file") 

def create_var_array(layer):
    filename = "params/" + layer.name + "_var.h"
    x = layer.moving_variance.numpy()
    var = [v*1 for v in x]

    with open(filename, "w") as f:
        f.write(f"#ifndef   __{layer.name}_var_h\n")
        f.write(f"#define   __{layer.name}_var_h\n\n")
        f.write(f"const double {layer.name}_var[{len(var)}] = {{\n")
        f.write(f",\n".join(map(str, var)))
        f.write(f"\n}};")
        f.write(f"\n\n#endif")
    print(f"(+) BatchNormalization variance data generated in {filename} file")

def create_gamma_array(layer):
    filename = "params/" + layer.name + "_gamma.h"
    x = layer.gamma.numpy()
    var = [v*1 for v in x]

    with open(filename, "w") as f:
        f.write(f"#ifndef   __{layer.name}_gamma_h\n")
        f.write(f"#define   __{layer.name}_gamma_h\n\n")
        f.write(f"const double {layer.name}_gamma[{len(var)}] = {{\n")
        f.write(f",\n".join(map(str, var)))
        f.write(f"\n}};")
        f.write(f"\n\n#endif")
    print(f"(+) BatchNormalization gamma data generated in {filename} file")

def create_beta_array(layer):
    filename = "params/" + layer.name + "_beta.h"
    x = layer.beta.numpy()
    var = [v*1 for v in x]

    with open(filename, "w") as f:
        f.write(f"#ifndef   __{layer.name}_beta_h\n")
        f.write(f"#define   __{layer.name}_beta_h\n\n")
        f.write(f"const double {layer.name}_beta[{len(var)}] = {{\n")
        f.write(f",\n".join(map(str, var)))
        f.write(f"\n}};")
        f.write(f"\n\n#endif")
    print(f"(+) BatchNormalization beta data generated in {filename} file")

def create_eps(layer):
    filename = "params/" + layer.name + "_eps.h"
    x = layer.epsilon

    with open(filename, "w") as f:
        f.write(f"#ifndef   __{layer.name}_eps_h\n")
        f.write(f"#define   __{layer.name}_eps_h\n\n")
        f.write(f"const double {layer.name}_eps = {x};\n")
        f.write("\n\n#endif")
    print(f"(+) BatchNormalization epsilon data generated in {filename} file")

for layer in model.layers:
    if isinstance(layer, tf.keras.layers.BatchNormalization):
        create_avg_array(layer)
        create_var_array(layer)
        create_gamma_array(layer)
        create_beta_array(layer)
        create_eps(layer)
