import os
import torch
import numpy as np

OUTPUT_DIRECTORY = '../params-quant'
type = 'int'
MULTIP = 1024*8

if not os.path.exists(OUTPUT_DIRECTORY):
        os.makedirs(OUTPUT_DIRECTORY)

def load_checkpoint(ckpt_path):
    checkpoint = torch.load(ckpt_path, map_location='cpu')
    state_dict = checkpoint['net'] if 'net' in checkpoint else checkpoint
    return state_dict

def classifier_mapper(state_dict):
    classifier_map = {}
    keys = list(state_dict.keys())

    for idx, key in enumerate(keys):
        if key.endswith('weight') and ('.fc' in key or 'classifier' in key):
            class_name_base = key.rsplit('.weight', 1)[0]
            class_bias = class_name_base + '.bias'
            #print(f"{state_dict[key].shape}")
            classifier_map[class_name_base] = {
                'weight': np.array([x*MULTIP for x in state_dict[key].cpu().permute(1, 0).numpy()]),
                'bias'  : np.array([x*MULTIP for x in state_dict.get(class_bias, None).cpu().numpy()]) if class_bias in state_dict else None
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

    # x = (img.permute(0, 2, 3, 1).numpy().flatten()*MULTIP).astype(np.float32)

    stemblock_map[layer_name] = {
        'conv_weight': np.array([x*MULTIP for x in state_dict[key].cpu().permute(2, 3, 1, 0).numpy()]),
        'conv_bias'  : np.array([x*MULTIP for x in state_dict.get(conv_bias, None).cpu().numpy()]) if conv_bias in state_dict else None,
        'bn_gamma'   : np.array([x*316 for x in state_dict[gamma_key].cpu().numpy()]),
        'bn_beta'    : np.array([x*MULTIP for x in state_dict[beta_key].cpu().numpy()]),
        'bn_running_mean': np.array([x*MULTIP for x in state_dict[mean_key].cpu().numpy()]),
        'bn_deviation': np.sqrt(1e5*state_dict[var_key].cpu().numpy()+1)
    }

    return stemblock_map

# MMCBlock
def conv_bn_mapper(state_dict):
    conv_bn_map = {}
    keys = list(state_dict.keys())

    for idx, key in enumerate(keys):
        if key.endswith('weight') and ('.conv.' in key):
            conv_name = key.rsplit('.weight', 1)[0]
            bn_name_base = conv_name.replace('.conv', '.norm')

            gamma_key = bn_name_base + '.weight'
            beta_key = bn_name_base + '.bias'
            mean_key = bn_name_base + '.running_mean'
            var_key = bn_name_base + '.running_var'

            has_bn = all(k in state_dict for k in [gamma_key, beta_key, mean_key, var_key])

            conv_bn_map[conv_name] = {
                'conv_weight': np.array([x*MULTIP for x in state_dict[key].cpu().permute(2, 3, 1, 0).numpy()]),
                'conv_bias'  : state_dict.get(conv_name + '.bias', None).cpu().numpy() if conv_name + '.bias' in state_dict else None
            }

            if has_bn:
                conv_bn_map[conv_name].update({
                    'bn_gamma': np.array([x*316 for x in state_dict[gamma_key].cpu().numpy()]),
                    'bn_beta' : np.array([x*MULTIP for x in state_dict[beta_key].cpu().numpy() ]),
                    'bn_running_mean': np.array([x*MULTIP for x in state_dict[mean_key].cpu().numpy()]),
                    'bn_deviation': np.sqrt(1e5*state_dict[var_key].cpu().numpy()+1)
                })

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

    x = value.flatten().astype(np.int32)

    with open(filename, "w") as f:
        f.write(f"#ifndef __{real_name}___h\n")
        f.write(f"#define __{real_name}___h\n\n")
        f.write(f"// {value.shape}\n")
        f.write(f"const {type} {real_name}[{x.size}] = {{\n")
        f.write(f",\n".join(map(str, x)))
        f.write(f"\n}};")
        f.write(f"\n\n#endif")

    print(f"[+] parameters generated in {filename} file!")

def save_to_numpy(out_dir, layers):
    if not os.path.exists(out_dir):
        os.makedirs(out_dir)

    for l in layers:
        for layer_name, params in l.items():
            safe_name = layer_name.replace('.', '_')
            for param_name, value in params.items():
                if value is not None:
                    name = safe_name.rsplit('_conv', 1)[0]
                    name = f"{name}_{param_name}"
                    create_c_header(name, value)

    print(f"[!] Done generating data in {out_dir} directory!")

if __name__ == "__main__":
    ckpt_path = '../checkpoint/ckpt.pth'
    state_dict = load_checkpoint(ckpt_path)
    stemblock_map = stemblock_mapper(state_dict)
    conv_bn_map = conv_bn_mapper(state_dict)
    classifier_map = classifier_mapper(state_dict)

    layers = [stemblock_map, conv_bn_map, classifier_map]

    save_to_numpy(OUTPUT_DIRECTORY, layers)
    
