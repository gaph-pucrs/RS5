import os
import re
import subprocess
import time

script_dir = os.path.dirname(os.path.abspath(__file__))

#------------------------------------
#       vector-tests/operations
#------------------------------------
# out_file = os.path.join(script_dir, "vector-tests-operations.txt")

# benchmarks_dir = os.path.join(script_dir, "../app/vector-tests/")
# operations_dir = os.path.join(benchmarks_dir, "operations/")
# test_dir = os.path.join(benchmarks_dir, "test/")

# benchmarks_list = [entry for entry in os.listdir(operations_dir)]
# benchmarks_list = sorted(benchmarks_list)

# clean = ["make", "-C", benchmarks_dir, "clean"]
# make  = ["make", "-C", benchmarks_dir]
# riscv_size = ["riscv64-elf-size", "--format=SysV", os.path.join(benchmarks_dir, "test.axf")]

# subprocess.run(clean)    

# cnt = 0
# for benchmark in benchmarks_list:
#     test_prog = os.path.join(operations_dir, benchmark)
#     subprocess.run(["cp", test_prog, test_dir])
#     subprocess.run(make)
    
#     with open(out_file, "a") as f:
#         subprocess.run(riscv_size, stdout=f)

#     time.sleep(1)
#     subprocess.run(clean)    
#     subprocess.run(["rm", os.path.join(test_dir, benchmark)])

#     cnt = cnt + 1
#     # if (cnt == 1):
#     #     break

#------------------------------------
#        vector-benchmarks
#------------------------------------
out_file = os.path.join(script_dir, "vector-benchmarks.txt")
benchmarks_dir = os.path.join(script_dir, "../app/vector-benchmarks")
benchmarks_list = [entry for entry in os.listdir(benchmarks_dir) if os.path.isdir(os.path.join(benchmarks_dir, entry)) and entry != "results"]
benchmarks_list = sorted(benchmarks_list)

print('Benchmarks that will be executed:')
for i, benchmark in enumerate(benchmarks_list):
    print(f'\t{i+1:2d})', benchmark)
print()

for benchmark in benchmarks_list:
    benchmark_path = os.path.join(benchmarks_dir, benchmark)
    script_dir = os.path.join(benchmark_path, 'script')
    if os.path.exists(script_dir) and os.path.isdir(script_dir):
        cmd = ["python", os.path.join(script_dir, 'gen_data.py')]
        subprocess.run(cmd)
    
    make = ['make', '-C', benchmark_path, 'clean', 'all']
    clean = ["make", "-C", benchmark_path, "clean"]

    subprocess.run(make)
    riscv_size = ["riscv64-elf-size", "--format=SysV", os.path.join(benchmark_path, f"{benchmark}.elf")]

    with open(out_file, "a") as f:
        subprocess.run(riscv_size, stdout=f)

    subprocess.run(clean)
