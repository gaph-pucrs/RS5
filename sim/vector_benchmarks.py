import os
import subprocess
import shutil
import re
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# *********************************
# PARAMS
# *********************************
BUS_WIDTHs = [32, 64]
VLENs = [64, 128, 256]

print(f'\nBenchmark Executions will consider:')
print(f'\tBUS_WIDTHs = ', BUS_WIDTHs)
print(f'\tVLENs      = ', VLENs)
print()

# *********************************
# Benchmarks
# *********************************
script_dir = os.path.dirname(os.path.abspath(__file__))

benchmarks_dir = os.path.join(script_dir, "../app/vector-benchmarks/")

benchmarks_list = [entry for entry in os.listdir(benchmarks_dir) if os.path.isdir(os.path.join(benchmarks_dir, entry)) and entry != "results"]
benchmarks_list = sorted(benchmarks_list)

print('Benchmarks that will be executed:')
for i, benchmark in enumerate(benchmarks_list):
    print(f'\t{i+1:2d})', benchmark)
print()
# *********************************
# Execution
# *********************************
for benchmark in benchmarks_list:
    print("\n*********************************")
    print(f'Starting execution of {benchmark}.')
    print("*********************************")
    benchmark_path = os.path.join(benchmarks_dir, benchmark)
    results_dir = os.path.join(benchmarks_dir, 'results', benchmark)
    if os.path.exists(results_dir):
        shutil.rmtree(results_dir)
    os.makedirs(results_dir)

    ###############
    # Generate Data
    ###############
    script_dir = os.path.join(benchmark_path, 'script')
    if os.path.exists(script_dir) and os.path.isdir(script_dir):
        command = ["python3", os.path.join(script_dir, 'gen_data.py')]
        result_path = os.path.join(results_dir, "gen_result.txt")
        try:
            with open(result_path, "w") as result_file:
                result = subprocess.run(command, check=True, stdout=result_file, stderr=subprocess.STDOUT, universal_newlines=True)
                print(f"✅ Succesful Data Generation for {benchmark} !!!\n")
        except subprocess.CalledProcessError as e:
            print(f"❌ Failed Data Generation for {benchmark}:\n")
            continue

    ###############
    # Compile Code
    ###############
    command = ['make', '-C', benchmark_path, 'clean', 'all']
    result_path = os.path.join(results_dir, "make_result.txt")
    try:
        with open(result_path, "w") as result_file:
            result = subprocess.run(command, check=True, stdout=result_file, stderr=subprocess.STDOUT, universal_newlines=True)
            shutil.move(os.path.join(benchmark_path, f'{benchmark}.bin'), os.path.join(benchmarks_dir, f'benchmark.bin'))
            print(f"✅ Succesful Compilation for {benchmark} !!!\n")
    except subprocess.CalledProcessError as e:
        print(f"❌ Failed Compilation for {benchmark}:\n", e.stderr)
        continue

    ###############
    # Run BenchMark
    ###############
    for bus_width in BUS_WIDTHs:
        for vlen in VLENs:
            LANES = [2**i for i in range((vlen//32).bit_length()) if 2**i <= (vlen//32)]
            for lanes in LANES:
                llen = lanes*32
                print(f'Executing: BUS_WIDTH ={bus_width:3d}, VLEN ={vlen:3d}, LANES ={vlen//llen:2d}.')

                xcelium = ['xrun', '-f', 'sim.xrun', '-timescale 1ns/1ps']
                defines = [f'+define+BUS_WIDTH_P={bus_width}', f'+define+VLEN_P={vlen}', f'+define+LLEN_P={llen}']
                command = xcelium + defines

                result_path = os.path.join(results_dir, f"bus{bus_width}_vlen{vlen}_lanes{vlen//llen}.txt")
                with open(result_path, "w") as result_file:
                    try:
                        result = subprocess.run(command, check=True, stdout=result_file, stderr=result_file, universal_newlines=True)
                    except subprocess.CalledProcessError as e:
                        print(f"❌ Failed Execution for {benchmark} - bus={bus_width} vlen={vlen} llen={llen}:\n", e.stderr)
                        continue
                with open(result_path, "r") as result_file:
                    content = result_file.read()
                    if "fail" in content.lower():
                        os.rename(result_path, os.path.join(results_dir, f"[fail]bus{bus_width}_vlen{vlen}_lanes{vlen//llen}.txt"))

# *********************************
# Result extraction
# *********************************

print("\n*********************************")
print(f'!!! Extracting Data !!!')
print("*********************************\n")

# Regex to parse bus, vlen, lanes from the filename
filename_pattern = re.compile(r"bus(\d+)_vlen(\d+)_lanes(\d+)\.txt")

# Regex to find the cycle count line inside the file
cycle_pattern = re.compile(r"\[VECTOR\] The execution took (\d+) cycles\.")
scalar_pattern = re.compile(r"\[SCALAR\] The execution took (\d+) cycles\.")
scalar_loadstores_pattern = re.compile(r"Scalar LOAD-STORES\s*=\s*(\d+)")
vector_instructions_pattern = re.compile(r"Vector Instructions\s*=\s*(\d+)")
vector_loadstores_pattern = re.compile(r"Vector LOAD-STORES\s*=\s*(\d+)")
inst_retired_pattern = re.compile(r"Cycles\[\s*2\] - Inst Retired:\s*(\d+)")

for benchmark in benchmarks_list:
    data = []
    scalar_data = {}
    results_dir = os.path.join(benchmarks_dir, 'results', benchmark)

    for filename in os.listdir(results_dir):
        match = filename_pattern.match(filename)
        if not match:
            continue

        bus, vlen, lanes = map(int, match.groups())

        file_path = os.path.join(results_dir, filename)
        with open(file_path, "r") as f:
            content = f.read()

            # Extract vector cycles
            cycle_match = cycle_pattern.search(content)
            vector_cycles = int(cycle_match.group(1)) if cycle_match else 0

            scalar_match = scalar_pattern.search(content)
            scalar_data['cycles'] = int(scalar_match.group(1)) if scalar_match else 0

            # Split content into SCALAR and VECTOR sections for more precise extraction
            sections = content.split("VECTOR:")
            if len(sections) >= 2:
                scalar_section = sections[0]
                vector_section = sections[1]
            else:
                # Fallback: use entire content
                scalar_section = content
                vector_section = content

            scalar_ls_match = scalar_loadstores_pattern.search(scalar_section)
            scalar_data['loadstores'] = int(scalar_ls_match.group(1)) if scalar_ls_match else 0

            scalar_inst_match = inst_retired_pattern.search(scalar_section)
            scalar_data['inst_retired'] = int(scalar_inst_match.group(1)) if scalar_inst_match else 0

            # Vector section
            vector_inst_match = vector_instructions_pattern.search(vector_section)
            vector_instructions = int(vector_inst_match.group(1)) if vector_inst_match else 0

            vector_ls_match = vector_loadstores_pattern.search(vector_section)
            vector_loadstores = int(vector_ls_match.group(1)) if vector_ls_match else 0

            vector_inst_match = inst_retired_pattern.search(vector_section)
            vector_inst_retired = int(vector_inst_match.group(1)) if vector_inst_match else 0

            # Also extract scalar load-stores from vector section (the last occurrence)
            scalar_ls_vector_match = scalar_loadstores_pattern.search(vector_section)
            vector_scalar_loadstores = int(scalar_ls_vector_match.group(1)) if scalar_ls_vector_match else 0

            data.append((vlen, bus, lanes, vector_cycles, vector_inst_retired, vector_scalar_loadstores, vector_instructions, vector_loadstores))

    df = pd.DataFrame(data, columns=["VLEN", "BUS_WIDTH", "LANES", "CYCLES", "INST_RETIRED", "LOADSTORES", "VECTOR_INSTRUCTIONS", "VECTOR_LOADSTORES"])
    df = df.sort_values(by=["VLEN", "BUS_WIDTH", "LANES"])
    scalar_row = pd.DataFrame({
        "VLEN": [0],
        "BUS_WIDTH": [32],
        "LANES": [0],
        "CYCLES": [scalar_data.get('cycles', 0)],
        "INST_RETIRED": [scalar_data.get('inst_retired', 0)],
        "LOADSTORES": [scalar_data.get('loadstores', 0)],
        "VECTOR_INSTRUCTIONS": [0],  # Scalar has 0 vector instructions
        "VECTOR_LOADSTORES": [0],    # Scalar has 0 vector load-stores
    })
    df = pd.concat([scalar_row, df]).reset_index(drop=True)
    df.to_csv(os.path.join(benchmarks_dir, 'results', 'charts', f'{benchmark}.csv'), index=False)

    print(f"✅ Succesful Data Extraction for {benchmark}!!!\n")

command = ["python3", os.path.join(benchmarks_dir, 'gen_charts.py')]
result = subprocess.run(command, check=True)
