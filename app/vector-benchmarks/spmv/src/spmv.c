// Copyright 2022 ETH Zurich and University of Bologna.
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

// Author: Chi Zhang, ETH Zurich <chizhang@iis.ee.ethz.ch>

#include <stdint.h>
#include <stdio.h>
#include <riscv-csr.h>

#include "data.h"

#define DATA_BYTE 4 // int type has 4 bytes

void spmv_csr_idx32(int32_t N_ROW, int32_t *CSR_PROW, int32_t *CSR_INDEX,
                    int *CSR_DATA, int *IN_VEC, int *OUT_VEC) {
  for (int i = 0; i < N_ROW; ++i) {
    size_t vl;
    int32_t len = CSR_PROW[i + 1] - CSR_PROW[i];
    int *data = CSR_DATA + CSR_PROW[i];
    int32_t *index = CSR_INDEX + CSR_PROW[i];
    int *_dst_ = OUT_VEC + i - 1;

    if (i % 2 == 0) {
      // clear register file
      __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(1));
      __asm__ volatile("vmv.v.i v16,  0");

      // SpVV
      while (len > 0) {
        __asm__ volatile("vsetvli %0, %1, e32, m2, ta, ma"
                         : "=r"(vl)
                         : "r"(len));
        __asm__ volatile("vmv.v.i v12, 0");
        __asm__ volatile("vle32.v v4, (%0)" ::"r"(data));          // fetch entries
        __asm__ volatile("vle32.v v8, (%0)" ::"r"(index));         // fetch indices
        __asm__ volatile("vloxei32.v v0, (%0), v8" ::"r"(IN_VEC)); // load data
        __asm__ volatile("vmul.vv v12, v4, v0");      // vector multiply
        __asm__ volatile("vredsum.vs v16, v12, v16"); // reduction
        len -= vl;
        data += vl;
        index += vl;
      }
      // store previous data
      if (i != 0) {
        int tmp;
        __asm__ volatile("vmv.x.s %0, v24" : "=r"(tmp));
        *_dst_ = tmp;
      }

    } else {
      // clear register file
      __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(1));
      __asm__ volatile("vmv.v.i v24, 0");

      // SpVV
      while (len > 0) {
        __asm__ volatile("vsetvli %0, %1, e32, m2, ta, ma"
                         : "=r"(vl)
                         : "r"(len));
        __asm__ volatile("vmv.v.i v12, 0");
        __asm__ volatile("vle32.v v4, (%0)" ::"r"(data));          // fetch entries
        __asm__ volatile("vle32.v v8, (%0)" ::"r"(index));         // fetch indices
        __asm__ volatile("vloxei32.v v0, (%0), v8" ::"r"(IN_VEC)); // load data
        __asm__ volatile("vmul.vv v12, v4, v0");      // vector multiply
        __asm__ volatile("vredsum.vs v24, v12, v24"); // reduction
        len -= vl;
        data += vl;
        index += vl;
      }

      // store previous data
      int tmp;
      __asm__ volatile("vmv.x.s %0, v16" : "=r"(tmp));
      *_dst_ = tmp;
    }
  }

  // store the last value
  int *_dst_ = OUT_VEC + N_ROW - 1;
  if (N_ROW % 2 == 0) // even
  {
    int tmp;
    __asm__ volatile("vmv.x.s %0, v24" : "=r"(tmp));
    *_dst_ = tmp;
  } else { // odd
    int tmp;
    __asm__ volatile("vmv.x.s %0, v16" : "=r"(tmp));
    *_dst_ = tmp;
  }
}

int spmv_verify(int32_t N_ROW) {
  for (int32_t i = 0; i < N_ROW; ++i) {
    if ((int)CSR_OUT_GOLDEN[i] != (int)CSR_OUT_VECTOR[i]) {
      printf("Fail\n");
      printf("Sorry, wrong value! at index %d, result = %d, golden = %d \n", (int)i,
             CSR_OUT_VECTOR[i], CSR_OUT_GOLDEN[i]);
      return i;
    }
  }
}

void spmv_scalar(int32_t N_ROW, int32_t *CSR_PROW, int32_t *CSR_INDEX,
                int *CSR_DATA, int *IN_VEC, int *OUT_GOLDEN) {

    for (int32_t i = 0; i < N_ROW; ++i) {
        int32_t len = CSR_PROW[i + 1] - CSR_PROW[i];
        int *data = CSR_DATA + CSR_PROW[i];
        int32_t *index = CSR_INDEX + CSR_PROW[i];

        int golden = 0;
        for (int32_t j = 0; j < len; ++j) {
            int32_t idx = index[j] / DATA_BYTE;
            golden = golden + data[j] * IN_VEC[idx];
            //printf("index:%d, data: %d, in_vec: %d, golden: %d\n", idx, data[j], IN_VEC[idx], golden);
        }
        OUT_GOLDEN[i] = golden;
    }
}


uint64_t cycles_start;
uint64_t cycles_end;

int NR_LANES = 1;

extern uint32_t R;
extern uint32_t C;
extern uint32_t NZ;

extern int32_t CSR_PROW[]
    __attribute__((aligned(4)));
extern int32_t CSR_INDEX[]
    __attribute__((aligned(4)));
extern int CSR_DATA[] __attribute__((aligned(4)));
extern int CSR_IN_VECTOR[]
    __attribute__((aligned(4)));
extern int CSR_OUT_VECTOR[]
    __attribute__((aligned(4)));

int main() {
  printf("\n");
  printf("==========\n");
  printf("=  SpMV  =\n");
  printf("==========\n");
  printf("\n");
  printf("\n");

  double density = ((double)NZ) / (R * C);
  double nz_per_row = ((double)NZ) / R;

  printf("\n");
  printf(
      "-------------------------------------------------------------------\n");
  printf(
      "Calculating a (%d x %d) x %d sparse matrix vector multiplication...\n",
      (int)R, (int)C, (int)C);
  printf("CSR format with %d nozeros: %f density, %f nonzeros per row \n", (int)NZ,
         density, nz_per_row);
  printf(
      "-------------------------------------------------------------------\n");
  printf("\n");

  printf("\ncalculating ... \n\n");
  cycles_start = csr_read_mcycle();
  spmv_csr_idx32(R, CSR_PROW, CSR_INDEX, CSR_DATA, CSR_IN_VECTOR,
                 CSR_OUT_VECTOR);
  cycles_end = csr_read_mcycle();


  // Metrics
  int64_t runtime = cycles_end - cycles_start;
  float performance = 2.0 * NZ / runtime;
  float utilization = 100 * performance / (2.0 * NR_LANES);

  printf("[VECTOR] The execution took %d cycles.\n", (int)runtime);
  //printf("The performance is %f FLOP/cycle (%f%% utilization) at %d lanes.\n",
  //       performance, utilization, NR_LANES);

  cycles_start = csr_read_mcycle();
  spmv_scalar(R, CSR_PROW, CSR_INDEX, CSR_DATA, CSR_IN_VECTOR,
                 CSR_OUT_GOLDEN);
  cycles_end = csr_read_mcycle();

  runtime = cycles_end - cycles_start;
  printf("[SCALAR] The execution took %d cycles.\n", (int)runtime);

  printf("\nVerifying ...\n");
  if (spmv_verify(R)) {
    return 1;
  } else {
    printf("\nPassed.\n\n");
  }
  return 0;
}