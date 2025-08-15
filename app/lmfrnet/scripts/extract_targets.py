import os
import torch
import pickle

path = '../autodl-tmp/data-cifar10/cifar-10-batches-py/'
filename = 'test_batch'
out_file = '../targets.txt'

def unpickle(file):
    with open(file, 'rb') as fo:
        dict = pickle.load(fo, encoding='bytes')
    return dict

test_dict = unpickle(path+filename)

# b'batch_label'
# b'labels'
# b'data'
# b'filenames'

with open(out_file, "w") as f:
    f.write(f"\n".join(map(str, test_dict[b'labels'])))
    print(f"[+] Target labels generated in {out_file} file!")