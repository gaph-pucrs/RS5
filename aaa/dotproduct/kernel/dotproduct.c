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

#include "dotproduct.h"

int32_t dotp_v32b(int32_t *a, int32_t *b, uint64_t avl) {
  size_t orig_avl = avl;
  size_t vl;
  asm volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

  int32_t red;

  int32_t *a_ = (int32_t *)a;
  int32_t *b_ = (int32_t *)b;

  // Clean the accumulator
  asm volatile("vmv.s.x v0, zero");
  // Stripmine and accumulate a partial reduced vector
  for (; avl > 0; avl -= vl) {
    asm volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
    // Load chunk a and b
    asm volatile("vle32.v v8,  (%0)" ::"r"(a_));
    asm volatile("vle32.v v16, (%0)" ::"r"(b_));
    // Multiply and accumulate
    if (avl == orig_avl) {
      asm volatile("vmul.vv v24, v8, v16");
    } else {
      asm volatile("vmacc.vv v24, v8, v16");
    }
    // Bump pointers
    a_ += vl;
    b_ += vl;
  }

  // Reduce and return
  asm volatile("vredsum.vs v0, v24, v0");
  asm volatile("vmv.x.s %0, v0" : "=r"(red));

  return red;
}

int32_t dotp_s32b(int32_t *a, int32_t *b, uint64_t avl) {
  int32_t acc0, acc1, acc2, acc3, acc4, acc5, acc6, acc7;

  acc0 = 0;
  acc1 = 0;
  acc2 = 0;
  acc3 = 0;
  acc4 = 0;
  acc5 = 0;
  acc6 = 0;
  acc7 = 0;

  for (uint64_t i = 0; i < avl; i += 8) {
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