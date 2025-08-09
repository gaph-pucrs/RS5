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
#LLENs = [2**i for i in range((vlen//32).bit_length()) if 2**i <= (vlen//32)]

print(f'\nBenchmark Executions will consider:')
print(f'\tBUS_WIDTHs = ', BUS_WIDTHs)
print(f'\tVLENs      = ', VLENs)
print()

# *********************************
# Benchmarks
# *********************************
script_dir = os.path.dirname(os.path.abspath(__file__))

benchmarks_dir = os.path.join(script_dir, "../app/vector-benchmarks/")

benchmarks_list =  [entry for entry in os.listdir(benchmarks_dir) if os.path.isdir(os.path.join(benchmarks_dir, entry)) and entry != "results"]
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

                xcelium = ['xrun', '-f', 'sim.xrun']
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
print(f'!!! Generating Charts !!!')
print("*********************************")

# Regex to find the cycle count line inside the file
cycle_pattern = re.compile(r"The execution took (\d+) cycles\.")
# Regex to parse bus, vlen, lanes from the filename
filename_pattern = re.compile(r"bus(\d+)_vlen(\d+)_lanes(\d+)\.txt")

for benchmark in benchmarks_list:
    data = []
    results_dir = os.path.join(benchmarks_dir, 'results', benchmark)
    for filename in os.listdir(results_dir):
        match = filename_pattern.match(filename)
        if not match:
            continue

        bus, vlen, lanes = map(int, match.groups())

        file_path = os.path.join(results_dir, filename)
        with open(file_path, "r") as f:
            content = f.read()
            cycle_match = cycle_pattern.search(content)
            if cycle_match:
                cycles = int(cycle_match.group(1))
                data.append((bus, vlen, lanes, cycles))

    df = pd.DataFrame(data, columns=["BUS_WIDTH", "VLEN", "LANES", "CYCLES"])
    df = df.sort_values(by=["BUS_WIDTH", "LANES", "VLEN"])
    df.to_csv(os.path.join(results_dir, f'{benchmark}.csv'), index=False)

    vlen_vals = sorted(df['VLEN'].unique())
    lanes_vals = sorted(df['LANES'].unique())
    bus_width_vals = sorted(df['BUS_WIDTH'].unique())

    bar_width = 0.08
    spacing = 0.02
    n_lanes = len(lanes_vals)
    n_bus = len(bus_width_vals)

    fig, ax = plt.subplots(figsize=(10, 5))
    x = np.arange(len(vlen_vals))

    offsets = np.linspace(
        -((n_lanes * n_bus - 1) / 2) * (bar_width + spacing),
        ((n_lanes * n_bus - 1) / 2) * (bar_width + spacing),
        n_lanes * n_bus
    )

    colors = {1: 'tab:blue', 2: 'tab:olive', 4: 'tab:orange', 8: 'tab:green'}
    patterns = {32: '', 64: '//'}

    for i, lanes in enumerate(lanes_vals):
        for j, bus in enumerate(bus_width_vals):
            subset = df[(df['LANES'] == lanes) & (df['BUS_WIDTH'] == bus)]
            # Map VLEN to CYCLES with NaN fill for missing
            cycles = [subset[subset['VLEN'] == v]['CYCLES'].values[0] if v in subset['VLEN'].values else np.nan for v in vlen_vals]
            bar_pos = x + offsets[i * n_bus + j]
            ax.bar(bar_pos, cycles, bar_width,
                label=f'LANES: {lanes} - BUS_WIDTH: {bus}',
                color=colors[lanes],
                hatch=patterns[bus],
                edgecolor='black')

    ax.set_xlabel('VLEN')
    ax.set_ylabel('Cycles')
    ax.set_title('Cycles vs VLEN grouped by LANES and BUS_WIDTH')
    ax.set_xticks(x)
    ax.set_xticklabels(vlen_vals)
    ax.legend(loc='upper right', bbox_to_anchor=(1.35, 1))

    plt.tight_layout()
    plt.savefig(os.path.join(results_dir, f'{benchmark}.png'), dpi=300)
    plt.close()

    print(f"✅ Succesful Chart Generation for {benchmark} !!!\n")
