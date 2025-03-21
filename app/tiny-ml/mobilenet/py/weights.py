from tensorflow.keras.applications import MobileNet

model = MobileNet()

def create_c_array(layer):
    filename = "params/" + layer.name + ".h"
    weights = layer.get_weights()[0]
    c_weights = [w*1000 for w in weights.flatten()]

    with open(filename, "w") as f:
        f.write(f"#ifndef   __{layer.name}.h__\n")
        f.write(f"#define   __{layer.name}.h__\n\n")
        f.write(f"//{layer.name}: {weights.shape}\n")
        f.write(f"const int {layer.name}[{len(c_weights)}] = {{\n")
        f.write(f",\n".join(map(str, c_weights)))
        f.write(f"\n}};")
        f.write(f"\n\n#endif")

for layer in model.layers:
    if "conv1" in layer.name:
        weights = layer.get_weights()[0]
        #print(f"Layer Name: {layer.name}")
        print(f"//Kernel Shape:   {weights.shape}")
        #print(f"Kernel Weights:\n   {weights}")

        c_weights = [w * 1000 for w in weights.flatten()]
        print(f"const int conv_dw_1[{len(c_weights)}] = {{")
        print(",\n".join(map(str, c_weights)))
        print("};")
        break

for layer in model.layers:
    if layer.weights:
        create_c_array(layer)
        print(f"(+) Weights generated in params/{layer.name} file")
