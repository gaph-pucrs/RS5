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

# arg1: image size, arg2: filter size

import numpy as np
import sys
import os

def convolve2D(kernel, image, padding):
    # Default stride
    strides = 1

    # Gather Shapes of Kernel + Image + Padding
    xKernShape = kernel.shape[0]
    yKernShape = kernel.shape[1]
    xImgShape  = image.shape[0]
    yImgShape  = image.shape[1]

    # Shape of Output Convolution
    xOutput = xImgShape - xKernShape + 1
    yOutput = yImgShape - yKernShape + 1
    output = np.zeros((xOutput, yOutput))

    # Iterate through image
    for y in range(image.shape[1]):
        # Exit Convolution
        if y > image.shape[1] - yKernShape:
            break
        # Only Convolve if y has gone down by the specified Strides
        if y % strides == 0:
            for x in range(image.shape[0]):
                # Go to next row once kernel is out of bounds
                if x > image.shape[0] - xKernShape:
                    break
                try:
                    # Only Convolve if x has moved by the specified Strides
                    if x % strides == 0:
                        output[x, y] = (kernel * image[x: x + xKernShape, y: y + yKernShape]).sum()
                except:
                    break

    return output

# Define the filter size and the matrix dimension (max, for now, is 128 64-bit elements)
if len(sys.argv) > 1:
	matrix_width = int(sys.argv[1])
#	assert(matrix_width <= 128), "The width of the image cannot be greater than 128 64-bit \
#	                                  elements. If this is not enough, modify the algorithm."
	# Filter size must be odd
	# Data type
	CH = sys.argv[2]
else:
	matrix_width = 64
	CH = 3

dtype = 'int16'
F = 7

# Input image. Take a square image
M = matrix_width
N = matrix_width
padding = int(F/2)
M_pad = M + 2*padding
N_pad = N + 2*padding
assert(M % 4 == 0), "Output image dimension must be divisible by 4, pad the input image accordingly"
assert(N % 4 == 0), "Output image dimension must be divisible by 4, pad the input image accordingly"

image = list()
# Generate a random int32 input padded image
for ch in range(CH):
    image += [np.random.randint(0, 256, (M_pad, N_pad)).astype(dtype)]

gen_filter = list()
# Generate a random int32 filter
for ch in range(CH):
    gen_filter += [np.random.randint(0, 256, (F, F)).astype(dtype)]

# Create the empty o matrix
empty_o = np.zeros((M, N)).astype(dtype)

# Calculate the output matrix
result = np.zeros((M, N)).astype(dtype)
for ch in range(CH):
    result += convolve2D(gen_filter[ch], image[ch], padding).astype(dtype)


script_dir = os.path.dirname(os.path.abspath(__file__))
header_file_path = os.path.join(script_dir, "../src/data.h")
with open(header_file_path, 'w') as file:
    file.write("// data.h\n")
    file.write("// Generated file containing random test data\n\n")
    file.write("#ifndef DATA_H\n")
    file.write("#define DATA_H\n\n")

    file.write(f"int32_t M  = {np.array(M,  dtype=np.uint32)};\n\n")
    file.write(f"int32_t N  = {np.array(N,  dtype=np.uint32)};\n\n")
    file.write(f"int32_t CH = {np.array(CH, dtype=np.uint32)};\n\n")
    file.write(f"int32_t F  = {np.array(F,  dtype=np.uint32)};\n\n")

    file.write(f"{dtype}_t i[{len(np.concatenate(image).flatten())}] = {{\n")
    file.write(",\n".join(f"    {num}" for num in np.concatenate(image).flatten()))
    file.write("\n};\n\n")

    file.write(f"{dtype}_t f[{len(np.concatenate(gen_filter).flatten())}] = {{\n")
    file.write(",\n".join(f"    {num}" for num in np.concatenate(gen_filter).flatten()))
    file.write("\n};\n\n")

    file.write(f"{dtype}_t o[{len(empty_o.flatten())}] = {{\n")
    file.write(",\n".join(f"    {num}" for num in empty_o.flatten()))
    file.write("\n};\n\n")

    file.write(f"{dtype}_t o_g[{len(empty_o.flatten())}] = {{\n")
    file.write(",\n".join(f"    {num}" for num in empty_o.flatten()))
    file.write("\n};\n\n")

    file.write(f"{dtype}_t golden_o[{len(result.flatten())}] = {{\n")
    file.write(",\n".join(f"    {num}" for num in result.flatten()))
    file.write("\n};\n\n")

    file.write("#endif\n")