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

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "data.h"
#include <riscv-csr.h>

int NR_LANES = 1;

typedef int16_t _DTYPE;
#define _KERNEL hp_iconv3d_CHx7x7
#define _VERIFY hp_iconv3d_verify
#include "hp-iconv3d.h"

// Define Matrix dimensions:
// o = i ° f, with i=[(M+F-1)x(N+f-1)xCH], f=[FxFxCH], o=[MxN]
// The filter is a square matrix, and F is odd

// Matrices defined in data.S
extern _DTYPE i[] __attribute__((aligned(4))); // [ (M+floor(F/2)) * (N+floor(F/2)) * CH ]
extern _DTYPE f[] __attribute__((aligned(4)));        // [ F*F*CH ]
extern _DTYPE o[] __attribute__((aligned(4)));        // [ M*N ]
extern _DTYPE golden_o[] __attribute__((aligned(4))); // [ M*N ]
// M, N, F defined in data.S
extern int32_t M;
extern int32_t N;
extern int32_t CH;
extern int32_t F;

int main() {
  printf("\n");
  printf("============\n");
  printf("=  CONV3D  =\n");
  printf("============\n");
  printf("\n");
  printf("\n");

  printf("Input Mtx size: %dx%d\n", (int)(M + F - 1), (int)(N + F - 1));
  printf("Output Mtx size: %dx%d\n", (int)M, (int)N);
  printf("Filter size: %dx%d\n", (int)F, (int)F);
  printf("Channels: %d\n", (int)CH);
  printf("Data width: %s\n\n", DATA_WIDTH);

  uint64_t cycles_start;
  uint64_t cycles_end;

  // Call the main kernel, and measure cycles
  cycles_start = csr_read_mcycle();
  if (F == 7)
    _KERNEL(o, i, f, M, N, CH, F);
  else
    printf("Error: the filter size is different from 7.\n");
  cycles_end = csr_read_mcycle();

  // Performance metrics
  int runtime = (int)(cycles_end - cycles_start);
  //float performance = 2.0 * CH * F * F * M * N / runtime;
  //float utilization = 100 * performance / (2.0 * NR_LANES * DTYPE_FACTOR);

  printf("The execution took %d cycles.\n\n", runtime);
  //printf("The performance is %f %s-OP/cycle (%f%% utilization).\n", performance,
  //       DTYPE_PREFIX, utilization);

  // Verify correctness
  printf("Verifying result...\n");
  int error = _VERIFY(o, golden_o, M, N, THRESHOLD);
  if (error != 0) {
    printf("Fail.\n\n");
  } else {
    printf("Passed.\n\n");
  }

  return error;
}