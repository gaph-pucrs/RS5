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
//
// Author: Matteo Perotti

#include <stdint.h>
#include <stdio.h>
#include <riscv-csr.h>

#include "data.h"

// Scalar dropout
void dropout_gold(const unsigned int n, const int *i, const int scale,
                  const uint8_t *sel_ptr, int *o) {
  uint8_t buf_sel, sel;
  for (unsigned int k = 0; k < n; ++k) {
    if (!(k % 8))
      buf_sel = sel_ptr[k >> 3];
    sel = buf_sel & 0x01;
    o[k] = sel ? (i[k] * scale) : 0;
    buf_sel >>= 1;
  }
}

void dropout_vec(const unsigned int n, const int *i, const int scale,
                 const uint8_t *sel_ptr, int *o) {
  unsigned int vl;

  __asm__ volatile("vsetvli %[vl], %[n], e32, m8, ta, ma"
               : [vl] "=r"(vl)
               : [n] "r"(n));

  for (unsigned int avl = n; avl > 0; avl -= vl) {
    // Find next vl
    __asm__ volatile("vsetvli %[vl], %[avl], e32, m8, ta, ma"
                 : [vl] "=r"(vl)
                 : [avl] "r"(avl));
    // Load the mask vector (1 = keep, 0 = drop)
    __asm__ volatile("vlm.v v0, (%[sel_ptr])" ::[sel_ptr] "r"(sel_ptr));
    // Initialize output vector with zeroes
    __asm__ volatile("vmv.v.i v24, 0");
    // Load input vector
    __asm__ volatile("vle32.v v8, (%[i])" ::[i] "r"(i));
    // Calculate output vector
    __asm__ volatile("vmul.vx v24, v8, %[scale], v0.t" ::[scale] "r"(scale));
    __asm__ volatile("vse32.v v24, (%[o])" ::[o] "r"(o));
    // Bump pointers
    i += vl;
    sel_ptr += vl >> 3;
    o += vl;
  }
}

extern const unsigned int N;
extern const int SCALE;
extern const int I[] __attribute__((aligned(4)));
extern const uint8_t SEL[] __attribute__((aligned(4)));
extern int o[] __attribute__((aligned(4)));
extern int o_gold[] __attribute__((aligned(4)));

int NR_LANES = 1;

uint64_t cycles_start;
uint64_t cycles_end;

int main() {
  printf("\n");
  printf("=============\n");
  printf("=  DROPOUT  =\n");
  printf("=============\n");
  printf("\n");
  printf("\n");

  printf("Running Dropout with %d elements.\n\n", N);

  // Call the main kernel, and measure cycles
  cycles_start = csr_read_mcycle();
  dropout_vec(N, I, SCALE, SEL, o);
  cycles_end = csr_read_mcycle();
  // Performance metrics
  int64_t runtime = cycles_end - cycles_start;

  // Only count effective SPOP/cycle
  //int performance = N / runtime;
  printf("The execution took %d cycles.\n\n", (int)runtime);
  //printf("Max performance - %d\n", (int)runtime);
  //printf("Performance.    - %d\n", performance);
/*
  int arith_intensity = 1 / (8 + 1 / 8);
  int bw = 4 * NR_LANES;
  int max_perf = bw * arith_intensity;
  int utilization = 100 * performance / NR_LANES;
  printf("The performance is %d SPOP/cycle. Max achievable is %d "
         "SPOP/cycle. (%d%% on max). With %d%% FPU utilization.\n",
         performance, max_perf, 100 * performance / max_perf, utilization);
*/

  // Verify correctness
  dropout_gold(N, I, SCALE, SEL, o_gold);

  for (unsigned int k = 0; k < N; ++k) {
    if (o[k] != o_gold[k]) {
      printf("Fail - Error: o[%d] = %d != %d\n", k, o[k], o_gold[k]);
      return k ? k : -1;
    }
  }
  printf("Passed.\n\n");

  return 0;
}