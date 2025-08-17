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

// Author: Matheus Cavalcante, ETH Zurich
//         Samuel Riedel, ETH Zurich

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <riscv-csr.h>
#include "data.h"

#define MIN(a, b) ((a) <= (b) ? (a) : (b))

typedef int8_t _DTYPE;
#define _KERNEL bp_imatmul
#define _VERIFY bp_imatmul_verify
#include "bp-imatmul.h"

void matmul(_DTYPE *C, _DTYPE *A, _DTYPE *B,
            size_t m, size_t n, size_t p) {
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < p; j++) {
            _DTYPE sum = 0;
            for (size_t k = 0; k < n; k++) {
                sum += A[i*n + k] * B[k*p + j];
            }
            C[i*p + j] = sum;
        }
    }
}

// Define Matrix dimensions:
// C = AB with A=[MxN], B=[NxP], C=[MxP]
extern uint32_t M;
extern uint32_t N;
extern uint32_t P;

extern _DTYPE a[] __attribute__((aligned(4)));
extern _DTYPE b[] __attribute__((aligned(4)));
extern _DTYPE c[] __attribute__((aligned(4)));
extern _DTYPE g[] __attribute__((aligned(4)));

uint64_t cycles_start;
uint64_t cycles_end;

int main() {
  printf("\n");
  printf("============\n");
  printf("=  MATMUL  =\n");
  printf("============\n");
  printf("\n");
  printf("\n");

  printf("\n");
  printf("------------------------------------------------------------\n");
  printf("Calculating a (%d x %d) x (%d x %d) matrix multiplication...\n", (int)M, (int)N,
         (int)N, (int)P);
  printf("------------------------------------------------------------\n");
  printf("\n");

  // Matrices are initialized --> Start calculating
  printf("Calculating matmul...\n");
  //int unsigned loop_cont = 1;
  //do {
  //  _KERNEL(c, a, b, M, N, P);
  //} while (--loop_cont != 0);

  cycles_start = csr_read_mcycle();
  _KERNEL(c, a, b, M, N, P);
  cycles_end = csr_read_mcycle();

  // Metrics
  int runtime = (int)(cycles_end - cycles_start);
  //float performance = 2.0 * M * N * P / runtime;
  //float utilization = 100 * performance / (2.0 * NR_LANES * DTYPE_FACTOR);

  printf("[VECTOR] The execution took %d cycles.\n\n", runtime);
  //printf("The performance is %f FLOP/cycle (%f%% utilization).\n", performance,
  //       utilization);

  cycles_start = csr_read_mcycle();
  matmul(g, a, b, M, N, P);
  cycles_end = csr_read_mcycle();

  runtime = (int)(cycles_end - cycles_start);
  printf("[SCALAR] The execution took %d cycles.\n\n", runtime);

  // Verify the result
  printf("Verifying result...\n");
  int error = _VERIFY(c, g, M, P);
  if (error != 0) {
    unsigned int idx = error == -1 ? 0 : error;
    printf("Fail.\n");
    printf("Error code %d\n", error);
    printf("c[%d]=%d\n", idx, (int)c[idx]);
    return 1;
  } else {
    printf("Passed.\n\n");
  }

  return 0;
}