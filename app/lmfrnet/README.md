# LMFRNet setup

The **setup.sh** script does every step below. To run it with:

```sh
sh ./setup.sh
```

## Creating the virtual environment

```sh
python -m venv .env
```

## Installing dependencies 

The weights and the dataset are generated with **lmfrnet-utils**' scripts, and they depend on **PyTorch** and **Numpy**. If those are already installed somewhere, this section is optional.

```sh
mkdir -p tmp
export TMPDIR=tmp
export PIP_CACHE_DIR=tmp
source .env/bin/activate
pip install torch torchvision numpy
```

## Generating weights and dataset

**NOTE**: The **download_dataset.py** script downloads the CIFAR-10 dataset and it is expected to take a while. 

**NOTE**: At least **20** images must be generated with **gen_dataset.py** because of the include list in **src/images.h**.

```sh
cd lmfrnet-utils
python download_dataset.py
python gen_dataset.py --num-images 20 --output-dir ../dataset
python fused_weights.py --output-dir ../params
cd ..

```

##