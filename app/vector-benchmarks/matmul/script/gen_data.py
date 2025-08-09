#!/usr/bin/env python3
# Copyright 2022 ETH Zurich and University of Bologna.
#
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Author: Matteo Perotti

# C = AB with A=[MxN], B=[NxP], C=[MxP]
# arg1, arg2, arg3: M, N, P

import random as rand
import numpy as np
import sys
import os

############
## SCRIPT ##
############

if len(sys.argv) == 5:
  dtype = str(sys.argv[1])
  M = int(sys.argv[2])
  N = int(sys.argv[3])
  P = int(sys.argv[4])
else:
  print("Usage: python gen_data.py <dtype>, <M>, <N>, <P>")
  print("dtype in [float64, float32, float16, int64, int32, int16, int8]")
  dtype = 'int32'
  M = 32
  N = 32
  P = 32
print("C = AB with A=[MxP], B=[PxN], C=[MxN]")

# Matrices and results
A = np.random.randint(0, 256, (M, N)).astype(dtype)
B = np.random.randint(0, 256, (N, P)).astype(dtype)
C = np.zeros([M, P], dtype=dtype)
# Golden result matrix
G = np.matmul(A, B).astype(dtype)

script_dir = os.path.dirname(os.path.abspath(__file__))
header_file_path = os.path.join(script_dir, "../src/data.h")
with open(header_file_path, 'w') as file:
    file.write("// data.h\n")
    file.write("// Generated file containing random test data\n\n")
    file.write("#ifndef DATA_H\n")
    file.write("#define DATA_H\n\n")

    file.write(f"uint32_t M = {np.array(M, dtype=np.uint32)};\n\n")
    file.write(f"uint32_t N = {np.array(N, dtype=np.uint32)};\n\n")
    file.write(f"uint32_t P = {np.array(P, dtype=np.uint32)};\n\n")

    file.write(f"{dtype}_t a[{len(A.flatten())}] = {{\n")
    file.write(",\n".join(f"    {num}" for num in A.flatten()))
    file.write("\n};\n\n")

    file.write(f"{dtype}_t b[{len(B.flatten())}] = {{\n")
    file.write(",\n".join(f"    {num}" for num in B.flatten()))
    file.write("\n};\n\n")

    file.write(f"{dtype}_t c[{len(C.flatten())}] = {{\n")
    file.write(",\n".join(f"    {num}" for num in C.flatten()))
    file.write("\n};\n\n")

    file.write(f"{dtype}_t g[{len(G.flatten())}] = {{\n")
    file.write(",\n".join(f"    {num}" for num in G.flatten()))
    file.write("\n};\n\n")

    file.write("#endif\n")