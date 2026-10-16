# AlexNet setup

Bare-metal AlexNet (torchvision's pretrained model) for RS5, written after `app/lmfrnet`. Activations are CHW, conv weights OIHW and FC weights (out, in), the same order as PyTorch.

The **setup.sh** script does every step below. Run it with:

```sh
sh ./setup.sh
```

or, to reuse an existing venv that already has the dependencies instead of creating `.env`:

```sh
VENV=~/lmfrnet sh ./setup.sh
```

## Creating the virtual environment

```sh
python -m venv .env
```

## Installing dependencies

The weights and the dataset are generated with **alexnet-utils**' scripts, and they depend on **PyTorch** and **Numpy**. If those are already installed somewhere, this section is optional.

```sh
mkdir -p tmp
export TMPDIR=tmp
export PIP_CACHE_DIR=tmp
source .env/bin/activate
pip install torch torchvision numpy pillow
```

## Generating weights and dataset

**NOTE**: The **download_dataset.py** script downloads the ImageNetV2 dataset (about 1.3 GB) and it is expected to take a while. The first run of **gen_dataset.py** or **gen_weights.py** also downloads the pretrained AlexNet weights (about 233 MB) into `~/.cache/torch`.

**NOTE**: At least **1** image must be generated with **gen_dataset.py** because of the include list in **src/images.h**.

```sh
cd alexnet-utils
python download_dataset.py
python gen_dataset.py --num-images 10 --output-dir ../dataset
python gen_weights.py --output-dir ../params
cd ..
```

Images and biases are quantized ×256 and weights ×8192, so the C code shifts every conv/fc result right by `QUANT_SHIFT` = 13 (**src/cnn_std.h**). If the scales in **alexnet-utils** change, `QUANT_SHIFT` must change with them. **alexnet-utils**' `validate.py` checks the quantized model against the float one on ImageNetV2.

## Running natively (NO_RISCV)

```sh
make run-native
```

Builds **src/alexnet.c** with the host gcc and the scalar kernels, runs image1, and prints the predicted class and a checksum per layer. Every layer output is also dumped to `dump/<layer>.bin` (raw int32).

## Running on RS5

```sh
make                              # scalar
make VEn=1 VLEN=128               # vector (-DVECTOR, zve32x_zvl128b)
```

or from `sim/`: `make run-alexnet-refactor VEn=1 VLEN=128`.

The program prints the predicted class, the cycles per layer, and a checksum per layer. The checksums and the predicted class must match the native run.

**NOTE**: `MEM_SIZE` is 256 MiB, the whole testbench RAM (`MEM_ADDR_BITS = 28`). The image plus bss is about 247 MB.

**NOTE**: with `DEBUG = 1'b1` in `sim/testbench.sv`, every memory access is logged to `sim/debug/`, which is far too much for a full AlexNet run. Set it to `1'b0` first.
