import os
import subprocess
import shutil
import re

# *********************************
# PARAMS
# *********************************
BUS_WIDTHs = [32, 64, 128, 256]
VLENs = [64, 128, 256]

script_dir = os.path.dirname(os.path.abspath(__file__))

results_dir = os.path.join(script_dir, "results")
output_dir = os.path.join(script_dir, "vectorUnit")

# *********************************
# Synthesis
# *********************************
for bus_width in BUS_WIDTHs:
    for vlen in VLENs:
        if bus_width > vlen:
            continue

        LANES = [2**i for i in range((vlen//32).bit_length()) if 2**i <= (vlen//32)]
        for lanes in LANES:
            llen = lanes*32
            print(f'Executing: BUS_WIDTH ={bus_width:3d}, VLEN ={vlen:3d}, LANES ={vlen//llen:2d}.')

            command = f'genus -f run_logical_synthesis.tcl -execute "set TOP_MODULE vectorUnit" -execute "set VLEN {vlen}" -execute "set LLEN {llen}" -execute "set BUS_WIDTH {bus_width}"'

            os.makedirs(results_dir, exist_ok=True)
            result_path = os.path.join(results_dir, "genus_log.txt")
            with open(result_path, "w") as result_file:
                try:
                    result = subprocess.run(command, shell=True, check=True, stdout=result_file, stderr=result_file, universal_newlines=True)
                except subprocess.CalledProcessError as e:
                    print(f"❌ Failed Execution for bus={bus_width} vlen={vlen} llen={llen}:\n", e.stderr)
                    continue

            shutil.move(results_dir, os.path.join(script_dir, "vectorUnit", f"bus{bus_width}_vlen{vlen}_lanes{vlen//llen}"))