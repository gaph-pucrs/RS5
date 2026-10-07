#!/bin/bash
# Sets up the LMFRNet application: creates the venv, installs the dependencies
# and generates the dataset and weights headers with lmfrnet-utils.

set -e

APP_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$APP_DIR"

python -m venv .env

mkdir -p tmp
export TMPDIR="$APP_DIR/tmp"
export PIP_CACHE_DIR="$APP_DIR/tmp"
source .env/bin/activate
pip install torch torchvision numpy

cd lmfrnet-utils
python download_dataset.py
python gen_dataset.py --num-images 20 --output-dir ../dataset
python fused_weights.py --output-dir ../params
cd ..
