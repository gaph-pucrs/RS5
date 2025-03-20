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

#define VSIZE 4096

int32_t dotp_v32b(int32_t *a, int32_t *b, uint32_t avl) {
  size_t orig_avl = avl;
  size_t vl;
  __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

  int32_t red;

  int32_t *a_ = (int32_t *)a;
  int32_t *b_ = (int32_t *)b;

  // Clean the accumulator
  __asm__ volatile("vmv.s.x v0, zero");
  // Stripmine and accumulate a partial reduced vector
  for (; avl > 0; avl -= vl) {
    __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
    // Load chunk a and b
    __asm__ volatile("vle32.v v8,  (%0)" ::"r"(a_));
    __asm__ volatile("vle32.v v16, (%0)" ::"r"(b_));
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

int32_t dotp_s32b(int32_t *a, int32_t *b, uint32_t avl) {
  int32_t acc0, acc1, acc2, acc3, acc4, acc5, acc6, acc7;

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

uint32_t index;
uint64_t cycles_start;
uint64_t cycles_end;

int32_t res32_v, res32_s;
int16_t res16_v, res16_s;
int8_t res8_v, res8_s;


int main() {
  printf("\n");
  printf("======================================\n");
  printf("=                  DOTP              =\n");
  printf("======================================\n");

  int num_iterations = 0;

  // Calculate the number of iterations
  for (uint32_t avl = 8; avl <= (VSIZE >> 0); avl *= 2) {
      num_iterations++;
  }
  printf("VSIZE = %d - Num of iterations = %d\n", VSIZE, num_iterations);

  uint32_t cycles_v32[num_iterations];
  uint32_t cycles_s32[num_iterations];
  uint32_t cycles_v16[num_iterations];
  uint32_t cycles_s16[num_iterations];
  uint32_t cycles_v8 [num_iterations];
  uint32_t cycles_s8 [num_iterations];

  printf("\n");
  printf("==========\n");
  printf("=   32b  =\n");
  printf("==========\n");
  index = 0;
  for (uint32_t avl = 8; avl <= (VSIZE >> 0); avl *= 2) {
    printf("Calulating 32b dotp with vectors with length = %u\n", avl);
    cycles_start = csr_read_mcycle();
    res32_v = dotp_v32b(v32a, v32b, avl);
    cycles_end = csr_read_mcycle();
    cycles_v32[index] = cycles_end - cycles_start;
    printf("VECTOR 32b - AVL = %lu, cycles = %ld\n", avl, cycles_v32[index]);

    if (SCALAR) {
      cycles_start = csr_read_mcycle();
      res32_s = dotp_s32b(v32a, v32b, avl);
      cycles_end = csr_read_mcycle();
      cycles_s32[index] = cycles_end - cycles_start;
      printf("SCALAR 32b - AVL = %lu, cycles = %ld\n\n", avl, cycles_s32[index]);

      if (CHECK) {
        if (res32_v != res32_s) {
          printf("Error: v = %ld, g = %ld\n", res32_v, res32_s);
          return -1;
        }
      }
    }
    index++;
 }

  printf("\n");
  printf("==========\n");
  printf("=   16b  =\n");
  printf("==========\n");
  index = 0;
  for (uint32_t avl = 8; avl <= (VSIZE >> 0); avl *= 2) {
    printf("Calulating 16b dotp with vectors with length = %u\n", avl);
    cycles_start = csr_read_mcycle();
    res16_v = dotp_v16b(v16a, v16b, avl);
    cycles_end = csr_read_mcycle();
    cycles_v16[index] = cycles_end - cycles_start;
    printf("VECTOR 16b - AVL = %lu, cycles = %ld\n", avl, cycles_v16[index]);

    if (SCALAR) {
      cycles_start = csr_read_mcycle();
      res16_s = dotp_s16b(v16a, v16b, avl);
      cycles_end = csr_read_mcycle();
      cycles_s16[index] = cycles_end - cycles_start;
      printf("SCALAR 16b - AVL = %lu, cycles = %ld\n\n", avl, cycles_s16[index]);

      if (CHECK) {
        if (res16_v != res16_s) {
          printf("Error: v = %ld, g = %ld\n", res16_v, res16_s);
          return -1;
        }
      }
    }
    index++;
  }

  printf("\n");
  printf("==========\n");
  printf("=   8b   =\n");
  printf("==========\n");
  index = 0;
  for (uint32_t avl = 8; avl <= (VSIZE >> 0); avl *= 2) {
    printf("Calulating 8b dotp with vectors with length = %u\n", avl);
    index = 0;
    cycles_start = csr_read_mcycle();
    res8_v = dotp_v32b(v32a, v32b, avl);
    cycles_end = csr_read_mcycle();
    cycles_v8[index] = cycles_end - cycles_start;
    printf("VECTOR 32b - AVL = %lu, cycles = %ld\n", avl, cycles_v8[index]);
    if (SCALAR) {
      cycles_start = csr_read_mcycle();
      res8_s = dotp_s8b(v8a, v8b, avl);
      cycles_end = csr_read_mcycle();
      cycles_s8[index] = cycles_end - cycles_start;
      printf("SCALAR 8b - AVL = %lu, cycles = %ld\n\n", avl, cycles_s8[index]);

      if (CHECK) {
        if (res8_v != res8_s) {
          printf("Error: v = %d, g = %d\n", res8_v, res8_s);
          return -1;
        }
      }
    }
    index++;
  }

  printf("\nAmount of Cycles:\n");
//  // 32 -----------------------------------------------
  printf("X = [");
  for (int i = 8; i <= (VSIZE >> 0); i *= 2) {
    if (i > 8) {
      printf(", ");
    }
    printf("%0d", i);
  }
  printf("]\n");

//  // 32 -----------------------------------------------
  printf("Vector_32b = [");
  for (int i = 0; i < num_iterations; i++) {
    if (i > 0) {
      printf(", ");
    }
    printf("%0d", cycles_v32[i]);
  }
  printf("]\n");

//  // 16 -----------------------------------------------
  printf("Vector_16b = [");
  for (int i = 0; i < num_iterations; i++) {
    if (i > 0) {
      printf(", ");
    }
    printf("%0d", cycles_v16[i]);
  }
  printf("]\n");

//  //  8 -----------------------------------------------
  printf("Vector_8b  = [");
  for (int i = 0; i < num_iterations; i++) {
    if (i > 0) {
      printf(", ");
    }
    printf("%0d", cycles_v8[i]);
  }
  printf("]\n");

  //   -----------------------------------------------
  //   Scalar
  //   -----------------------------------------------

  if (SCALAR) {
  //  32 -----------------------------------------------
    printf("Scalar_32b = [");
    for (int i = 0; i < num_iterations; i++) {
      if (i > 0) {
        printf(", ");
      }
      printf("%0d", cycles_s32[i]);
    }
    printf("]\n");
    //  16 -----------------------------------------------
    printf("Scalar_16b = [");
    for (int i = 0; i < num_iterations; i++) {
      if (i > 0) {
        printf(", ");
      }
      printf("%0d", cycles_s16[i]);
    }
    printf("]\n");
    //  8 -----------------------------------------------
    printf("Scalar_8b  = [");
    for (int i = 0; i < num_iterations; i++) {
      if (i > 0) {
        printf(", ");
      }
      printf("%0d", cycles_s8[i]);
    }
    printf("]\n");
  }

  //  -----------------------------------------------
  //  -----------------------------------------------
  //  -----------------------------------------------

  printf("\nSUCCESS.\n\n");

  return 0;
}
