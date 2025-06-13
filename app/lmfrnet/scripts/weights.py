import os
import torch
import numpy as np

OUTPUT_DIRECTORY = '../params'
type = 'float'

def load_checkpoint(ckpt_path):
    checkpoint = torch.load(ckpt_path, map_location='cpu')
    state_dict = checkpoint['net'] if 'net' in checkpoint else checkpoint
    return state_dict

def classifier_mapper(state_dict):
    classifier_map = {}
    keys = list(state_dict.keys())

    for idx, key in enumerate(keys):
        if key.endswith('weight') and ('.classifier' in key or '.fc' in key):
            class_name_base = key.rsplit('.weight', 1)[0]
            class_bias = class_name_base + 'bias'
            classifier_map[class_name_base] = {
                'weight': state_dict[key].cpu().numpy(),
                'bias': state_dict.get(class_bias, None).cpu().numpy() if class_bias in state_dict else None
            }
    
    return classifier_map

def stemblock_mapper(state_dict):
    stemblock_map = {}
    key = 'module.features.stemBlock.stemConv.0.weight'
    layer_name = key.rsplit('.0.', 1)[0]

    conv_name_base = layer_name + '.0'
    bn_name_base = layer_name + '.1'

    conv_bias = conv_name_base + '.bias'

    gamma_key = bn_name_base + '.weight'
    beta_key = bn_name_base + '.bias'
    mean_key = bn_name_base + '.running_mean'
    var_key = bn_name_base + '.running_var'

    stemblock_map[layer_name] = {
        'conv_weight': state_dict[key].cpu().numpy(),
        'conv_bias': state_dict.get(conv_bias, None).cpu().numpy() if conv_bias in state_dict else None,
        'bn_gamma': state_dict[gamma_key].cpu().numpy(),
        'bn_beta': state_dict[beta_key].cpu().numpy(),
        'bn_running_mean': state_dict[mean_key].cpu().numpy(),
        'bn_running_var': state_dict[var_key].cpu().numpy()
    }

    return stemblock_map

def conv_bn_mapper(state_dict):
    conv_bn_map = {}
    keys = list(state_dict.keys())

    for idx, key in enumerate(keys):
        if key.endswith('weight') and ('.conv.' in key or '.stemConv212' in key):
            conv_name = key.rsplit('.weight', 1)[0]
            bn_name_base = conv_name.replace('.conv', '.norm')

            gamma_key = bn_name_base + '.weight'
            beta_key = bn_name_base + '.bias'
            mean_key = bn_name_base + '.running_mean'
            var_key = bn_name_base + '.running_var'

            has_bn = all(k in state_dict for k in [gamma_key, beta_key, mean_key, var_key])

            conv_bn_map[conv_name] = {
                'conv_weight': state_dict[key].cpu().numpy(),
                'conv_bias': state_dict.get(conv_name + '.bias', None)
                .cpu().numpy() if conv_name + '.bias' in state_dict else None
                # 'has_bn': has_bn
            }

            if has_bn:
                conv_bn_map[conv_name].update({
                    'bn_gamma': state_dict[gamma_key].cpu().numpy(),
                    'bn_beta': state_dict[beta_key].cpu().numpy(),
                    'bn_running_mean': state_dict[mean_key].cpu().numpy(),
                    'bn_running_var': state_dict[var_key].cpu().numpy()
                })
        # else:
            # print(f"Skipped: {key}")

    return conv_bn_map

def create_c_header(name, value):
    index = -1
    layer_types = {'stemBlock', 'MMCBlock', 'tran_ConvNormRelu', 'classifier', 'fc'}

    for t in layer_types:
        index = name.find(t)
        if index != -1:
            break

    if index == -1:
        print(f"[!] Layer type invalid for {name}!")
        exit()

    real_name = name[index:]    

    filename = OUTPUT_DIRECTORY + '/' + real_name + '.h'

    x = value.flatten()

    with open(filename, "w") as f:
        f.write(f"#ifndef __{real_name}___h\n")
        f.write(f"#define __{real_name}___h\n\n")
        f.write(f"const {type} {real_name}[{x.size}] = {{\n")
        f.write(f",\n".join(map(str, x)))
        f.write(f"\n}};")
        f.write(f"\n\n#endif")

    print(f"[+] parameters generated in {filename} file!")

def save_to_numpy(out_dir, layers):
    os.makedirs(out_dir)

    for l in layers:
        for layer_name, params in l.items():
            safe_name = layer_name.replace('.', '_')
            for param_name, value in params.items():
                if value is not None:
                    name = f"{safe_name}_{param_name}"
                    create_c_header(name, value)

    print(f"[!] Done generating data in {out_dir} directory!")

if __name__ == "__main__":
    ckpt_path = '../checkpoint/ckpt.pth'
    state_dict = load_checkpoint(ckpt_path)
    stemblock_map = stemblock_mapper(state_dict)
    conv_bn_map = conv_bn_mapper(state_dict)
    classifier_map = classifier_mapper(state_dict)

    layers = [stemblock_map, conv_bn_map, classifier_map]

    # for l in layers:
    #     for layer, params in l.items():
    #         print(f"\nLayer: {layer}")
    #         for p, v in params.items():
    #             shape = v.shape if v is not None else None
    #             print(f"  {p}: {shape}")

    save_to_numpy(OUTPUT_DIRECTORY, layers)
    