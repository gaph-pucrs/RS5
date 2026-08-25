#!/bin/bash
# Simulates the lmfrnet application on RS5 in scalar and vector (VLEN 64/128/256)
# configurations, collecting Output.txt and Report.txt of each run into lmfrnet/<config>.

set -e

SIM_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SIM_DIR"

APP=lmfrnet

# "<config name> <VEn> <VLEN>"
CONFIGS=(
    "scalar 0 64"
    "v64    1 64"
    "v128   1 128"
    "v256   1 256"
)

for config in "${CONFIGS[@]}"; do
    read -r name ven vlen <<< "$config"

    echo
    echo "############################################################"
    echo "## $APP - $name (VEn=$ven, VLEN=$vlen)"
    echo "############################################################"

    make "compile-$APP" VEn="$ven" VLEN="$vlen"
    make "run-$APP"     VEn="$ven" VLEN="$vlen"

    dest="$SIM_DIR/$APP/$name"
    mkdir -p "$dest"
    cp results/Output.txt results/Report.txt "$dest/"
    echo "-- RESULTS COPIED TO $dest --"
done

echo
echo "All $APP simulations finished."
