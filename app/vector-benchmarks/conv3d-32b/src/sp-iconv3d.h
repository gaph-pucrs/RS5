// Copyright 2020 ETH Zurich and University of Bologna.
//
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Author: Matteo Perotti

#ifndef ICONV3D_H
#define ICONV3D_H

#include <stdint.h>
#include <stdio.h>

#define MIN(a, b) ((a) <= (b) ? (a) : (b))

// Threshold for FP numbers comparison during the final check
#define THRESHOLD 0

// Help calculate performance
// How many parallel elements in an ELEN-wide FPU data bus?
#define DTYPE_FACTOR 2
#define DTYPE_PREFIX "SP"
#define DATA_WIDTH "int32"

void sp_iconv3d_CHx7x7(int32_t *o, int32_t *i, int32_t *f, int32_t M, int32_t N,
                       int32_t C, int32_t F);

void sp_iconv3d_CHx7x7_block(int32_t *o, int32_t *i, int32_t *f, int32_t M,
                             int32_t N, int32_t n_, int32_t C, int32_t F);

// Verify the matrices
int sp_iconv3d_verify(int32_t *matrix, int32_t *golden_matrix, int32_t R,
                      int32_t C, int32_t threshold);

#endif