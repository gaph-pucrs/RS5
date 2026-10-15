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
#include <riscv-csr-hpm.h>
#include "data.h"

#define MIN(a, b) ((a) <= (b) ? (a) : (b))

typedef int16_t _DTYPE;
#define _KERNEL hp_imatmul
#define _VERIFY hp_imatmul_verify
#include "hp-imatmul.h"

uint32_t hpm_0_s[64];
uint32_t hpm_1_s[64];
uint32_t hpm_0_v[64];
uint32_t hpm_1_v[64];

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
  csr_write_mcountinhibit(-1);
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

  int runtime;

  // Matrices are initialized --> Start calculating
  printf("Calculating matmul...\n");
  //int unsigned loop_cont = 1;
  //do {
  //  _KERNEL(c, a, b, M, N, P);
  //} while (--loop_cont != 0);

// ********************************
//       !!!    VECTOR    !!!
// ********************************
  read_hpms(hpm_0_v);
  cycles_start = csr_read_mcycle();
  csr_write_mcountinhibit(0);
  _KERNEL(c, a, b, M, N, P);
  csr_write_mcountinhibit(-1);
  cycles_end = csr_read_mcycle();
  read_hpms(hpm_1_v);

  // Metrics
  runtime = (int)(cycles_end - cycles_start);
  printf("[VECTOR] The execution took %d cycles.\n\n", runtime);

  //float performance = 2.0 * M * N * P / runtime;
  //float utilization = 100 * performance / (2.0 * NR_LANES * DTYPE_FACTOR);
  //printf("The performance is %f FLOP/cycle (%f%% utilization).\n", performance,
  //       utilization);

// ********************************
//       !!!    SCALAR    !!!
// ********************************
  read_hpms(hpm_0_s);
  cycles_start = csr_read_mcycle();
  csr_write_mcountinhibit(0);
  matmul(g, a, b, M, N, P);
  csr_write_mcountinhibit(-1);
  cycles_end = csr_read_mcycle();
  read_hpms(hpm_1_s);

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

  printf("SCALAR:\n");
  evaluate_hpms(hpm_0_s, hpm_1_s);

  printf("VECTOR:\n");
  evaluate_hpms(hpm_0_v, hpm_1_v);

  return 0;
}