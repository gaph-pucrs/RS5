#!/usr/bin/env python3
import numpy as np
import sys

# default: 
# python3 gen_data.py 128 128 128

# Function to write arrays in C format
def write_array(f, name, array):
    f.write(f"int32_t {name}[] = {{\n")
    rows, cols = array.shape
    for i in range(rows):
        f.write("    " + ", ".join(f"{x}" for x in array[i]) + (",\n" if i < rows - 1 else "\n"))
    f.write("};\n\n")

# Function to write a single integer in C format
def write_variable(f, name, value):
    f.write(f"int32_t {name} = {value};\n")

############
## SCRIPT ##
############

if len(sys.argv) == 4:
    M = int(sys.argv[1])
    N = int(sys.argv[2])
    P = int(sys.argv[3])
else:
    print("Error. Provide three arguments: M, N, P.")
    print("C = AB with A=[MxN], B=[NxP], C=[MxP]")
    sys.exit()

# Set matrix limits and dtype
UPPER_LIMIT = 100
LOWER_LIMIT = -100
dtype = np.int32

# Generate matrices
A = np.random.randint(LOWER_LIMIT, UPPER_LIMIT, size=(M, N)).astype(dtype)
B = np.random.randint(LOWER_LIMIT, UPPER_LIMIT, size=(N, P)).astype(dtype)
C = np.zeros((M, P), dtype=dtype)  # Placeholder for results
G = np.matmul(A, B).astype(dtype)  # Golden result

# Write to data.h
with open("src/data.h", "w") as f:
    f.write("// Automatically generated data.h file\n")
    f.write("// Matrices for C = AB, with A=[MxN], B=[NxP], C=[MxP]\n")
    f.write("// Dimensions: M = {}, N = {}, P = {}\n\n".format(M, N, P))
    f.write("#ifndef DATA_H\n#define DATA_H\n\n#include <stdint.h>\n\n")

    # Write dimensions
    write_variable(f, "M", M)
    write_variable(f, "N", N)
    write_variable(f, "P", P)
    f.write("\n")

    # Write arrays
    write_array(f, "a", A)
    write_array(f, "b", B)
    write_array(f, "c", C)
    write_array(f, "g", G)

    f.write("#endif // DATA_H\n")

