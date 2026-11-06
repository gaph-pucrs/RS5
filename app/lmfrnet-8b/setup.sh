#!/bin/bash
# Sets up the LMFRNet W8A8 application: generates the weights, dataset, shifts and
# golden checksums with lmfrnet-utils/quantize.py. Uses the venv and the CIFAR-10
# download of ../lmfrnet (run ../lmfrnet/setup.sh first).
#     ./setup.sh [w8a8|w16a16]

set -e

APP_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PRECISION="${1:-w8a8}"

source "$APP_DIR/../lmfrnet/.env/bin/activate"
cd "$APP_DIR/../lmfrnet/lmfrnet-utils"
python quantize.py --precision "$PRECISION" --output-dir "$APP_DIR"
