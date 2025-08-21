import os
import re
import subprocess
import pandas as pd

#-----------------
#     PARAMS
#-----------------
VLENs = [64, 128, 256]
LMULs = [1, 2, 4, 8]

#VLENs = [256]
#LMULs = [8]

def abort():
    print("\n**************************************")
    print("*   Aborting execution of LMFRNet.   *")
    print("**************************************")
    exit()


print(f"\n[LMFRNet executions will consider:]")
print(f"\tVLENs = ", VLENs)
print(f"\tLMULs = ", LMULs)
print()

script_dir = os.path.dirname(os.path.abspath(__file__))
lmfrnet_dir = os.path.join(script_dir, "../app/lmfrnet/")

#---------------------
#     EXECUTION
#---------------------
print("\n**************************************")
print("*   Starting execution of LMFRNet.   *")
print("**************************************")
print()

#--------------------------
#      GENERATE DATA
#--------------------------
dataset_path = os.path.join(lmfrnet_dir, "data-cifar10/")
if not os.path.exists(dataset_path):
    if not os.path.exists(os.path.join(lmfrnet_dir, "autodl-tmp/data-cifar10/")):
        print("[!] Neither cifar10 dataset nor trained weights found.")
        #print(f"    Please, run 'python3 main.py' in {lmfrnet_dir} directory to train the model.")
        print(f"    Please, check https://github.com/wgqhandsome/LMFRNet/tree/main and train the model.")
        abort()

results_dir = os.path.join(lmfrnet_dir, "results/")
#if not os.path.exists(results_dir):
#    os.makedirs(results_dir)

for lmul in LMULs:
    for vlen in VLENs:
        benchmark_dir = os.path.join(results_dir, f"vlen{vlen}_m{lmul}/")
        #if not os.path.exists(benchmark_dir):
        #    os.makedirs(benchmark_dir)

benchmarks_list = [entry for entry in os.listdir(results_dir) if os.path.isdir(os.path.join(results_dir, entry))]
benchmarks_list = sorted(benchmarks_list)

print("LMFRNet will be executed with:")
for i, benchmark in enumerate(benchmarks_list):
    print(f"\t{i+1:2d})", benchmark)
print()

scripts_dir = os.path.join(lmfrnet_dir, "scripts/")
if os.path.exists(scripts_dir) and os.path.isdir(scripts_dir):
     scripts_list = [entry for entry in os.listdir(scripts_dir)]
     for i, s in enumerate(scripts_list):
         cmd = ["python3", os.path.join(scripts_dir, s)]
         result_file = os.path.join(results_dir, os.path.splitext(s)[0]+'.txt') 
         try:
             #with open(result_file, "w") as f:
             #    subprocess.run(cmd, check=True, stdout=f, stderr=subprocess.STDOUT, universal_newlines=True)
             print("Oi")
         except subprocess.CalledProcessError as e:
             print(f"\n[!] Failed to run script {s}.")
             abort()
     print(f"Successfully generated data for the model.")
else:
    print("[!] Scripts for data and weights generation not found.")
    abort()

#------------------------
#    COMPILE AND RUN
#------------------------
for lmul in LMULs:
    for vlen in VLENs:
        makefile = ['make', '-C', lmfrnet_dir, 'clean', 'all', 'VLEN='+str(vlen), 'LMUL=m'+str(lmul)]
        benchmark_dir = os.path.join(results_dir, f"vlen{vlen}_m{lmul}/")
        result_file = os.path.join(benchmark_dir, f"make_vlen{vlen}_m{lmul}.txt")
        try:
            #with open(result_file, "w") as f:
            #    subprocess.run(makefile, check=True, stdout=f, stderr=subprocess.STDOUT, universal_newlines=True)
            print(f"Successfully compiled the model for VLEN={vlen}, LMUL=m{lmul}.")
        except subprocess.CalledProcessError as e:
            print(f"[!] Failed to compile the model for VLEN={vlen}, LMUL={lmul}.")
            abort()

        verilator = ['make', 'VLEN='+str(vlen)]
        result_file = os.path.join(benchmark_dir, f"verilator_vlen{vlen}_m{lmul}.txt")
        try:
            print(f"Simulating the model...")
            #with open(result_file, "w") as f:
            #    subprocess.run(verilator, check=True, stdout=f, stderr=subprocess.STDOUT, universal_newlines=True)
            print(f"Successfully simulated the model.")
        except subprocess.CalledProcessError as e:
            print(f"[!] Failed to simulate the model for VLEN={vlen}, LMUL={lmul}.")
            abort()

#-----------------------
#    EXTRACTING DATA
#-----------------------
print("\n**************************************")
print("*           EXTRACTING DATA          *")
print("**************************************")
print()

cycle_pattern = re.compile(r"\[VECTOR\] The execution took (\d+) cycles\.")
filename_pattern = re.compile(r"verilator_vlen(\d+)_m(\d+)\.txt")

for benchmark in benchmarks_list:
    data = []
    scalar = 0
    benchmark_dir = os.path.join(results_dir, benchmark+'/')
    #benchmark_dir = os.path.join(results_dir, "../backup/" + benchmark + '/')
    filename = "verilator_" + benchmark + ".txt"
    match = filename_pattern.match(filename)

    vlen, lmul = map(int, match.groups())
    filepath = os.path.join(benchmark_dir, filename)
    with open(filepath, "r") as f:
        content = f.read()
        cycle_match = cycle_pattern.search(content)
        if cycle_match:
            cycles = int(cycle_match.group(1))
            data.append((vlen, lmul, cycles))

    df = pd.DataFrame(data, columns=["VLEN", "LMUL", "CYCLES"])
    df = df.sort_values(by=["VLEN", "LMUL"])
    df.to_csv(os.path.join(benchmark_dir, benchmark + ".csv"), index=False)

    print(f"Successfully extracted data for {benchmark}.")

print()

cmd = ["python3", "lmfrnet_charts.py"]
#subprocess.run(cmd, check=True)
