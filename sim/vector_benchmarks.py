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
BUS_WIDTHs = [32, 64, 128, 256]
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

exclude_substrings = []
include_substrings = []

benchmarks_list = [
    entry for entry in os.listdir(benchmarks_dir)
    if (
        os.path.isdir(os.path.join(benchmarks_dir, entry))
        and entry not in ["results", "charts"]
        and (not exclude_substrings or not any(ex in entry for ex in exclude_substrings))
        and (not include_substrings or any(inc in entry for inc in include_substrings))
    )
]

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
            if bus_width > vlen:
                continue

            LANES = [2**i for i in range((vlen//32).bit_length()) if 2**i <= (vlen//32)]
            for lanes in LANES:
                llen = lanes*32
                print(f'Executing: BUS_WIDTH ={bus_width:3d}, VLEN ={vlen:3d}, LANES ={vlen//llen:2d}.')

                xcelium = ['xrun', '-f', 'sim.xrun']
                defines = [f"-defparam testbench.BUS_WIDTH={bus_width}", f"-defparam testbench.VLEN={vlen}", f"-defparam testbench.LLEN={llen}"]
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
# *********************************
# Result extraction
# *********************************

print("\n*********************************")
print(f'!!! Extracting Data !!!')
print("*********************************\n")

filename_pattern = re.compile(r"bus(\d+)_vlen(\d+)_lanes(\d+)\.txt")

# Regex patterns for extraction
cycle_pattern = re.compile(r"\[VECTOR\] The execution took (\d+) cycles\.")
scalar_pattern = re.compile(r"\[SCALAR\] The execution took (\d+) cycles\.")
scalar_loadstores_pattern = re.compile(r"Scalar LOAD-STORES\s*=\s*(\d+)")
vector_instructions_pattern = re.compile(r"Cycles\[\s*\d+\]\s*-\s*V-Inst\s*:\s*(\d+)")
vector_loadstores_pattern = re.compile(r"Vector LOAD-STORES\s*=\s*(\d+)")
inst_retired_pattern = re.compile(r"Cycles\[\s*\d+\]\s*-\s*Inst Retired:\s*(\d+)")

# New patterns for additional vector metrics
cycles_scalar_pattern = re.compile(r"Cycles\[\s*\d+\]\s*-\s*CyclesScalar:\s*(\d+)")
v_cycles_tot_pattern = re.compile(r"V-Cycles-Tot:\s*(\d+)")
v_cycles_pattern = re.compile(r"Cycles\[\s*\d+\]\s*-\s*V-Cycles:\s*(\d+)")
v_cycles_ls_pattern = re.compile(r"Cycles\[\s*\d+\]\s*-\s*V-Cycles-LS:\s*(\d+)")

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

            # Extract CyclesScalar from scalar section for scalar row
            cycles_scalar_scalar_match = cycles_scalar_pattern.search(scalar_section)
            scalar_data['cycles_scalar'] = int(cycles_scalar_scalar_match.group(1)) if cycles_scalar_scalar_match else 0

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

            # Extract new vector metrics
            v_cycles_tot_match = v_cycles_tot_pattern.search(vector_section)
            v_cycles_tot = int(v_cycles_tot_match.group(1)) if v_cycles_tot_match else 0

            v_cycles_match = v_cycles_pattern.search(vector_section)
            v_cycles = int(v_cycles_match.group(1)) if v_cycles_match else 0

            v_cycles_ls_match = v_cycles_ls_pattern.search(vector_section)
            v_cycles_ls = int(v_cycles_ls_match.group(1)) if v_cycles_ls_match else 0

            # Extract CyclesScalar
            cycles_scalar_match = cycles_scalar_pattern.search(vector_section)
            cycles_scalar = int(cycles_scalar_match.group(1)) if cycles_scalar_match else 0

            data.append((vlen, bus, lanes, vector_cycles, vector_inst_retired, 
                        vector_scalar_loadstores, vector_instructions, vector_loadstores,
                        v_cycles_tot, v_cycles, v_cycles_ls, cycles_scalar))

    df = pd.DataFrame(data, columns=["VLEN", "BUS_WIDTH", "LANES", "CYCLES", "INST_RETIRED", 
                                      "LOADSTORES", "VECTOR_INSTRUCTIONS", "VECTOR_LOADSTORES",
                                      "V_CYCLES_TOT", "V_CYCLES", "V_CYCLES_LS", "CYCLES_SCALAR"])
    df = df.sort_values(by=["VLEN", "BUS_WIDTH", "LANES"])

    # Create scalar row with all columns properly filled
    scalar_inst = scalar_data.get('inst_retired', 0) - 0  # No vector instructions in scalar
    scalar_row = pd.DataFrame({
        "VLEN": [0],
        "BUS_WIDTH": [32],
        "LANES": [0],
        "CYCLES": [scalar_data.get('cycles', 0)],
        "INST_RETIRED": [scalar_data.get('inst_retired', 0)],
        "SCALAR_INST": [scalar_inst],
        "LOADSTORES": [scalar_data.get('loadstores', 0)],
        "VECTOR_INSTRUCTIONS": [0],
        "VECTOR_LOADSTORES": [0],
        "V_CYCLES_TOT": [0],
        "V_CYCLES": [0],
        "V_CYCLES_LS": [0],
        "CYCLES_SCALAR": [scalar_data.get('cycles_scalar', 0)],
        "RATIO_V_SC_INST": [0.0],  # No vector instructions
        "RATIO_V_SC_CYCLES": [0.0],  # No vector cycles
        "RATIO_V_CYCLESTOT": [0.0],  # No vector cycles
        "RATIO_LS_INSTRET": [scalar_data.get('loadstores', 0) / scalar_data.get('inst_retired', 1) if scalar_data.get('inst_retired', 0) > 0 else 0.0],
        "RATIO_VLS_INSTRET": [0.0],  # No vector load-stores
        "RATIO_LS": [scalar_data.get('loadstores', 0) / scalar_data.get('inst_retired', 1) if scalar_data.get('inst_retired', 0) > 0 else 0.0],
        "RATIO_VLSCYCLES_CYCLES": [0.0],  # No vector LS cycles
        "RATIO_VLSCYCLE_VCYCLES": [0.0],  # No vector cycles
    })

    # Calculate derived columns for vector rows
    df['SCALAR_INST'] = df['INST_RETIRED'] - df['VECTOR_INSTRUCTIONS']
    df['RATIO_V_SC_INST'] = df['VECTOR_INSTRUCTIONS'] / df['SCALAR_INST'].replace(0, float('nan'))
    df['RATIO_V_SC_CYCLES'] = df['V_CYCLES_TOT'] / df['CYCLES_SCALAR'].replace(0, float('nan'))
    df['RATIO_V_CYCLESTOT'] = df['V_CYCLES_TOT'] / df['CYCLES'].replace(0, float('nan'))
    df['RATIO_LS_INSTRET'] = df['LOADSTORES'] / df['INST_RETIRED'].replace(0, float('nan'))
    df['RATIO_VLS_INSTRET'] = df['VECTOR_LOADSTORES'] / df['INST_RETIRED'].replace(0, float('nan'))
    df['RATIO_LS'] = df['RATIO_LS_INSTRET'] + df['RATIO_VLS_INSTRET']
    df['RATIO_VLSCYCLES_CYCLES'] = df['V_CYCLES_LS'] / df['CYCLES'].replace(0, float('nan'))
    df['RATIO_VLSCYCLE_VCYCLES'] = df['V_CYCLES_LS'] / df['V_CYCLES_TOT'].replace(0, float('nan'))

    # Reorder columns
    cols = ['VLEN', 'BUS_WIDTH', 'LANES', 'CYCLES', 'INST_RETIRED', 'SCALAR_INST', 
            'LOADSTORES', 'VECTOR_INSTRUCTIONS', 'VECTOR_LOADSTORES',
            'V_CYCLES_TOT', 'V_CYCLES', 'V_CYCLES_LS', 'CYCLES_SCALAR',
            'RATIO_V_SC_INST', 'RATIO_V_SC_CYCLES', 'RATIO_V_CYCLESTOT', 'RATIO_LS_INSTRET', 
            'RATIO_VLS_INSTRET', 'RATIO_LS', 'RATIO_VLSCYCLES_CYCLES', 'RATIO_VLSCYCLE_VCYCLES']
    df = df[cols]

    # Concatenate scalar row and vector rows
    df = pd.concat([scalar_row, df]).reset_index(drop=True)

    # Round all ratio columns to 3 decimal places
    ratio_cols = ['RATIO_V_SC_INST', 'RATIO_V_SC_CYCLES', 'RATIO_V_CYCLESTOT', 'RATIO_LS_INSTRET', 
                  'RATIO_VLS_INSTRET', 'RATIO_LS', 'RATIO_VLSCYCLES_CYCLES', 'RATIO_VLSCYCLE_VCYCLES']
    df[ratio_cols] = df[ratio_cols].round(3)

    # Export to CSV
    os.makedirs(os.path.join(benchmarks_dir, 'results', 'charts'), exist_ok=True)
    df.to_csv(os.path.join(benchmarks_dir, 'results', 'charts', f'{benchmark}.csv'), index=False, float_format='%.3f')

    print(f"✅ Succesful Data Extraction for {benchmark}!!!\n")

command = ["python3", os.path.join(benchmarks_dir, 'gen_charts.py')]
result = subprocess.run(command, check=True)
