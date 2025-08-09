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

#include "data.h"

// Run also the scalar benchmark
#define SCALAR 1

// Check the vector results against golden vectors
#define CHECK 1

int8_t dotp_v8b(int8_t *a, int8_t *b, uint32_t avl) {
  size_t orig_avl = avl;
  size_t vl;
  __asm__ volatile("vsetvli %0, %1, e8, m8, ta, ma" : "=r"(vl) : "r"(avl));

  int8_t red;

  int8_t *a_ = (int8_t *)a;
  int8_t *b_ = (int8_t *)b;

  // Clean the accumulator
  __asm__ volatile("vmv.s.x v0, zero");
  // Stripmine and accumulate a partial reduced vector
  for (; avl > 0; avl -= vl) {
    __asm__ volatile("vsetvli %0, %1, e8, m8, ta, ma" : "=r"(vl) : "r"(avl));
    // Load chunk a and b
    __asm__ volatile("vle8.v v8,  (%0)" ::"r"(a_));
    __asm__ volatile("vle8.v v16, (%0)" ::"r"(b_));
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

int8_t dotp_s8b(int8_t *a, int8_t *b, uint32_t avl) {
  int8_t acc0, acc1, acc2, acc3, acc4, acc5, acc6, acc7;

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

int8_t res8_v, res8_s;

extern const unsigned int N;

int main() {
  printf("\n");
  printf("======================================\n");
  printf("=                  DOTP              =\n");
  printf("======================================\n");

  printf("VSIZE = %d\n", N);

  uint32_t cycles_v8;
  uint32_t cycles_s8;

  printf("\n");
  printf("==========\n");
  printf("=   8b   =\n");
  printf("==========\n");
  printf("Calulating 8b dotp with vectors with length = %u\n", N);
  cycles_start = csr_read_mcycle();
  res8_v = dotp_v8b(v8a, v8b, N);
  cycles_end = csr_read_mcycle();
  cycles_v8 = cycles_end - cycles_start;

  printf("\nThe execution took %d cycles.\n\n", (int)cycles_v8);
  printf("VECTOR 8b - AVL = %u, cycles = %d\n", N, (int)cycles_v8);

  if (SCALAR) {
    cycles_start = csr_read_mcycle();
    res8_s = dotp_s8b(v8a, v8b, N);
    cycles_end = csr_read_mcycle();
    cycles_s8 = cycles_end - cycles_start;
    printf("SCALAR 8b - AVL = %u, cycles = %d\n\n", N, (int)cycles_s8);

    if (CHECK) {
      if (res8_v != res8_s) {
        printf("Fail - Error: v = %d, g = %d\n", res8_v, res8_s);
        return -1;
      }
    }
  }

  printf("\nSUCCESS.\n\n");

  return 0;
}
