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

// Author: Matteo Perotti <mperotti@iis.ee.ethz.ch>

#include <stdint.h>
#include <stdio.h>
#include <riscv-csr.h>
#include <riscv-csr-hpm.h>

#include "data.h"

// Run also the scalar benchmark
#define SCALAR 1

// Check the vector results against golden vectors
#define CHECK 1

uint32_t hpm_0_s[32];
uint32_t hpm_1_s[32];
uint32_t hpm_0_v[32];
uint32_t hpm_1_v[32];

int16_t dotp_v16b(int16_t *a, int16_t *b, uint32_t avl) {

  size_t orig_avl = avl;
  size_t vl;
  __asm__ volatile("vsetvli %0, %1, e16, m8, ta, ma" : "=r"(vl) : "r"(avl));

  int16_t red;

  int16_t *a_ = (int16_t *)a;
  int16_t *b_ = (int16_t *)b;

  // Clean the accumulator
  __asm__ volatile("vmv.s.x v0, zero");
  // Stripmine and accumulate a partial reduced vector
  for (; avl > 0; avl -= vl) {
    __asm__ volatile("vsetvli %0, %1, e16, m8, ta, ma" : "=r"(vl) : "r"(avl));
    // Load chunk a and b
    __asm__ volatile("vle16.v v8,  (%0)" ::"r"(a_));
    __asm__ volatile("vle16.v v16, (%0)" ::"r"(b_));
    // Multiply and accumulate
    if (avl == orig_avl) {
      __asm__ volatile("vmul.vv v24, v8, v16");
    } else {
      __asm__ volatile("vmacc.vv v24, v8, v16");
    }
    // Bump pointers
    a_ += vl;
    b_ += vl;
  }

  // Reduce and return
  __asm__ volatile("vredsum.vs v0, v24, v0");
  __asm__ volatile("vmv.x.s %0, v0" : "=r"(red));

  return red;
}

int16_t dotp_s16b(int16_t *a, int16_t *b, uint32_t avl) {
  int16_t acc0, acc1, acc2, acc3, acc4, acc5, acc6, acc7;

  acc0 = 0;
  acc1 = 0;
  acc2 = 0;
  acc3 = 0;
  acc4 = 0;
  acc5 = 0;
  acc6 = 0;
  acc7 = 0;

  for (uint32_t i = 0; i < avl; i += 8) {
    acc0 += a[i + 0] * b[i + 0];
    acc1 += a[i + 1] * b[i + 1];
    acc2 += a[i + 2] * b[i + 2];
    acc3 += a[i + 3] * b[i + 3];
    acc4 += a[i + 4] * b[i + 4];
    acc5 += a[i + 5] * b[i + 5];
    acc6 += a[i + 6] * b[i + 6];
    acc7 += a[i + 7] * b[i + 7];
  }

  acc0 += acc1;
  acc2 += acc3;
  acc4 += acc5;
  acc6 += acc7;

  acc0 += acc2;
  acc4 += acc6;

  acc0 += acc4;

  return acc0;
}

uint64_t cycles_start;
uint64_t cycles_end;

int16_t res16_v, res16_s;

extern const unsigned int N;

int main() {
  csr_write_mcountinhibit(-1);
  printf("\n");
  printf("======================================\n");
  printf("=                  DOTP              =\n");
  printf("======================================\n");

  printf("VSIZE = %d\n", N);

  uint32_t cycles_v16;
  uint32_t cycles_s16;

  printf("\n");
  printf("==========\n");
  printf("=  16b   =\n");
  printf("==========\n");
  printf("Calulating 16b dotp with vectors with length = %u\n\n", N);

// ********************************
//       !!!    VECTOR    !!!
// ********************************
  read_hpms(hpm_0_v);
  cycles_start = csr_read_mcycle();
  csr_write_mcountinhibit(0);
  res16_v = dotp_v16b(v16a, v16b, N);
  csr_write_mcountinhibit(-1);
  cycles_end = csr_read_mcycle();
  read_hpms(hpm_1_v);
  cycles_v16 = cycles_end - cycles_start;

  printf("[VECTOR] The execution took %d cycles.\n\n", (int)cycles_v16);
  //printf("VECTOR 16b - AVL = %u, cycles = %d\n", N, (int)cycles_v16);

// ********************************
//       !!!    SCALAR    !!!
// ********************************
  if (SCALAR) {
    read_hpms(hpm_0_s);
    cycles_start = csr_read_mcycle();
    csr_write_mcountinhibit(0);
    res16_s = dotp_s16b(v16a, v16b, N);
    csr_write_mcountinhibit(-1);
    cycles_end = csr_read_mcycle();
    read_hpms(hpm_1_s);
    cycles_s16 = cycles_end - cycles_start;
    //printf("SCALAR 16b - AVL = %u, cycles = %d\n", N, (int)cycles_s16);
    printf("[SCALAR] The execution took %d cycles.\n\n", (int)cycles_s16);

    if (CHECK) {
      if (res16_v != res16_s) {
        printf("Fail - Error: v = %d, g = %d\n", res16_v, res16_s);
        return -1;
      }
    }
  }

  printf("\nSUCCESS.\n\n");

  printf("SCALAR:\n");
  evaluate_hpms(hpm_0_s, hpm_1_s);

  printf("VECTOR:\n");
  evaluate_hpms(hpm_0_v, hpm_1_v);

  return 0;
}
