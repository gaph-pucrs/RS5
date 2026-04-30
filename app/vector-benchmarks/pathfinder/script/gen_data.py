import random as rand
import numpy as np
import sys
import os

def rand_matrix(N, dtype):
  return np.random.rand(N).astype(dtype)


def write_header_file(filepath,
                      num_runs,
                      rows,
                      cols,
                      wall,
                      result_s,
                      result_v,
                      src):
    """Writes the generated arrays to a header file."""
    with open(filepath, 'w') as file:
        file.write("// data.h\n")
        file.write("// Generated file containing random test data\n\n")
        file.write("#ifndef DATA_H\n")
        file.write("#define DATA_H\n\n")

        file.write(f"int32_t num_runs = {num_runs};\n\n")
        file.write(f"int32_t rows = {rows};\n\n")
        file.write(f"int32_t cols = {cols};\n\n")

        file.write(f"int src[{len(src)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in src))
        file.write("\n};\n\n")

        file.write(f"int wall[{len(wall)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in wall))
        file.write("\n};\n\n")

        file.write(f"int result_v[{len(result_v)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in result_v))
        file.write("\n};\n\n")

        file.write(f"int result_s[{len(result_s)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in result_s))
        file.write("\n};\n\n")

        file.write("#endif\n")

############
## SCRIPT ##
############

if len(sys.argv) == 4:
  num_runs = int(sys.argv[1])
  cols = int(sys.argv[2])
  rows = int(sys.argv[3])
else:
  print("Usage: python gen_data.py <RUNS> <COLUMNS> <ROWS>")
  num_runs = 16
  cols = 32
  rows = 32

dtype = np.int32
dmax  = np.iinfo(dtype).max

# Vector of samples
wall = np.random.randint(10, size=rows * cols, dtype=dtype)

# Buffers
result_s = np.zeros(cols, dtype=dtype)
result_v = np.zeros(cols, dtype=dtype)
src      = np.zeros(cols, dtype=dtype)

# Write the data to a header file
script_dir = os.path.dirname(os.path.abspath(__file__))
header_file_path = os.path.join(script_dir, "../src/data.h")
write_header_file(  header_file_path,
                    num_runs    = np.array(num_runs, dtype=np.uint32),
                    rows        = np.array(rows, dtype=np.uint32),
                    cols        = np.array(cols, dtype=np.uint32),
                    wall        = wall,
                    result_s    = result_s,
                    result_v    = result_v,
                    src         = src)

print(f"Generated data.h.")