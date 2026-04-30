#!/usr/bin/env python3
# Copyright 2021 ETH Zurich and University of Bologna.
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

# arg1: vector size, arg2: filter size

import numpy as np
import sys
import os

############
## SCRIPT ##
############

if len(sys.argv) == 3:
  R = int(sys.argv[1])
  C = int(sys.argv[2])
else:
  print("Usage: python gen_data.py <R> <C>")
  R = 128
  C = 128

dtype = np.int32
TSTEPS = 3

# Fill in the extra data to align the matrices to 4*NrLanes in SW
maxNrLanes   = 1
maxAlignment = 4*maxNrLanes              # [B]
sizeOfDType  = np.dtype(dtype).itemsize  # [B]
R_ext = int(R + (maxAlignment / sizeOfDType))
C_ext = int(C + (maxAlignment / sizeOfDType))

# Vector of samples (padding is random since it does not impact performance)
A = np.random.randint(0, 256, (R_ext, C_ext)).astype(dtype)
B = np.zeros([R_ext, C_ext], dtype=dtype)

script_dir = os.path.dirname(os.path.abspath(__file__))
header_file_path = os.path.join(script_dir, "../src/data.h")
with open(header_file_path, 'w') as file:
    file.write("// data.h\n")
    file.write("// Generated file containing random test data\n\n")
    file.write("#ifndef DATA_H\n")
    file.write("#define DATA_H\n\n")

    file.write(f"uint32_t R = {np.array(R, dtype=np.uint32)};\n\n")

    file.write(f"uint32_t C = {np.array(R, dtype=np.uint32)};\n\n")

    file.write(f"uint32_t TSTEPS = {np.array(TSTEPS, dtype=np.uint32)};\n\n")

    file.write(f"int A_v[{len(A.flatten())}] = {{\n")
    file.write(",\n".join(f"    {num}" for num in A.flatten()))
    file.write("\n};\n\n")

    file.write(f"int B_v[{len(B.flatten())}] = {{\n")
    file.write(",\n".join(f"    {num}" for num in B.flatten()))
    file.write("\n};\n\n")

    file.write(f"int A_s[{len(A.flatten())}] = {{\n")
    file.write(",\n".join(f"    {num}" for num in A.flatten()))
    file.write("\n};\n\n")

    file.write(f"int B_s[{len(B.flatten())}] = {{\n")
    file.write(",\n".join(f"    {num}" for num in B.flatten()))
    file.write("\n};\n\n")

    file.write("#endif\n")