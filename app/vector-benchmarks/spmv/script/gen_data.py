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

# // Author: Chi Zhang, ETH Zurich <chizhang@iis.ee.ethz.ch>


# arg1: row, arg2: column, arg3: density
# default configuration:
# # INT32 idx
# # INT32  data

import os
import sys
import numpy as np
import random

def randomCSR(num_row, num_col, density, element_byte):
  non_zero = int(num_row * num_col * density)
  # print("non_zero="+str(non_zero))
  # random insert
  insert_list = []
  pool = list(range(num_row*num_col))
  for x in range(non_zero):
    insert = random.choice(pool)
    pool.remove(insert)
    # print(insert)
    insert_list.append(insert)
    # print("inseting: "+str(x)+"/"+str(non_zero), end="\r")
    pass
  insert_list.sort()
  # print(insert_list)

  #Count for p_row
  p_row = []
  p_row.append(0)
  acc_bar = num_col
  acc_cnt = 0
  for x in range(non_zero):
    # print("generate p_row: "+str(x)+"/"+str(non_zero), end="\r")
    if insert_list[x] >= acc_bar:
      p_row.append(x)
      acc_bar = acc_bar + num_col
      acc_cnt = acc_cnt +1
      while insert_list[x] >= acc_bar:
        p_row.append(x)
        acc_bar = acc_bar + num_col
        acc_cnt = acc_cnt +1
        pass
      pass
    pass
  for x in range(num_row-acc_cnt):
    p_row.append(non_zero)
    pass
  # print(p_row)

  #generate indicies
  index_list = []
  for x in range(num_row):
    # print("generate index: "+str(x)+"/"+str(num_row), end="\r")
    length = p_row[x+1]- p_row[x]
    row_idx_list = []
    pool = list(range(0,num_col*element_byte,element_byte))
    for x in range(length):
      index = random.choice(pool)
      pool.remove(index)
      row_idx_list.append(index)
      pass
    row_idx_list.sort()
    index_list = index_list + row_idx_list
    pass

  #generate data
  # print("start generate data")
  data_list = []
  for x in range(non_zero):
    # data_list.append(random.random())
    data_list.append(x)
    pass

  #generate vector
  # print("start generate vector")
  vector_list = []
  for x in range(num_col):
    vector_list.append(random.random())
    # vector_list.append(x)
    pass

  return non_zero, p_row, index_list, data_list, vector_list

  pass

def write_header_file(filepath, R, C, NZ, CSR_PROW, CSR_INDEX, CSR_DATA, CSR_IN_VECTOR, CSR_OUT_VECTOR):
    """Writes the generated arrays to a header file."""
    with open(filepath, 'w') as file:
        file.write("// data.h\n")
        file.write("// Generated file containing random test data\n\n")
        file.write("#ifndef DATA_H\n")
        file.write("#define DATA_H\n\n")

        file.write(f"uint32_t R = {R};\n\n")

        file.write(f"uint32_t C = {C};\n\n")

        file.write(f"uint32_t NZ = {NZ};\n\n")

        file.write(f"int32_t CSR_PROW[{len(CSR_PROW)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in CSR_PROW))
        file.write("\n};\n\n")

        file.write(f"int32_t CSR_INDEX[{len(CSR_INDEX)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in CSR_INDEX))
        file.write("\n};\n\n")

        file.write(f"int CSR_DATA[{len(CSR_DATA)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in CSR_DATA))
        file.write("\n};\n\n")

        file.write(f"int CSR_IN_VECTOR[{len(CSR_IN_VECTOR)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in CSR_IN_VECTOR))
        file.write("\n};\n\n")

        file.write(f"int CSR_OUT_VECTOR[{len(CSR_OUT_VECTOR)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in CSR_OUT_VECTOR))
        file.write("\n};\n\n")

        file.write("#endif\n")

############
## SCRIPT ##
############

if len(sys.argv) == 4:
  R = int(sys.argv[1])
  C = int(sys.argv[2])
  D = float(sys.argv[3])
else:
  print("Usage: python gen_data.py <ROW> <COLUMN> <DENSITY>")
  R = 25
  C = 25
  D = 0.5

data_type = np.int32
idx_type = np.int32
element_byte = 8
idx_byte = 4

#generate sparse matrix
non_zero, p_row, index_list, data_list, vector_list = randomCSR(R, C, D, element_byte)

# Write the data to a header file
script_dir = os.path.dirname(os.path.abspath(__file__))
header_file_path = os.path.join(script_dir, "../src/data.h")
write_header_file(  header_file_path,
                    R               = np.array(R, dtype=np.uint32),
                    C               = np.array(C, dtype=np.uint32),
                    NZ              = np.array(non_zero, dtype=np.uint32),
                    CSR_PROW        = np.array(p_row, dtype=idx_type),
                    CSR_INDEX       = np.array(index_list, dtype=idx_type),
                    CSR_DATA        = np.array(data_list, dtype=data_type),
                    CSR_IN_VECTOR   = np.array(vector_list, dtype=data_type),
                    CSR_OUT_VECTOR  = np.zeros([C], dtype=data_type))

print(f"Generated data.h.")
