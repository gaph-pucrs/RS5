#!/bin/bash
# Sets up the AlexNet application: activates $VENV (an existing venv with torch,
# torchvision, numpy and pillow) or creates .env and installs them, then
# generates the weights and image headers with alexnet-utils.

set -e

APP_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$APP_DIR"

if [ -n "$VENV" ]; then
    source "$VENV/bin/activate"
else
    python -m venv .env

    mkdir -p tmp
    export TMPDIR="$APP_DIR/tmp"
    export PIP_CACHE_DIR="$APP_DIR/tmp"
    source .env/bin/activate
    pip install torch torchvision numpy pillow
fi

cd alexnet-utils
python download_dataset.py
python gen_dataset.py --num-images 10 --output-dir ../dataset
python gen_weights.py --output-dir ../params
cd ..
