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

void init_gemv_data(const unsigned long int m_row,
                    const unsigned long int v_len, int *matrix,
                    int *vector, int a, int b, int c) {
  // initialize matrix
  for (uint32_t i = 0; i < m_row; ++i) {
    for (uint32_t j = 0; j < v_len; ++j) {
      matrix[i * v_len + j] = a * (int)i + b * (int)j + c;
    }
  }

  // initialize vector
  for (uint32_t i = 0; i < v_len; ++i) {
    vector[i] = a * (int)i + b;
  }
}

//=====================================//
//========= GEMV ROW WISE KERNEL ======//
//=====================================//

size_t vl;

void clear_reduction_register() {
  __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(vl));
  __asm__ volatile("vmv.v.i v16,  0");
  __asm__ volatile("vmv.v.i v24,  0");
}

void store_slice_results(int *dest, const unsigned long int slice_height) {
  int tmp;
  // round slide
  __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(slice_height));
  __asm__ volatile("vmv.x.s %0, v24" : "=r"(tmp));
  __asm__ volatile("vslide1down.vx  v16, v24, %0" ::"r"(tmp));
  // store
  __asm__ volatile("vse32.v v16, (%0);" ::"r"(dest));
}

void gemv_rowwise_small_than_slice(const unsigned long int m_row,
                                   const unsigned long int v_len,
                                   int *matrix, int *vector,
                                   int *dest) {
  // setup
  __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(1));
  __asm__ volatile("vmv.v.i v24,  0");
  __asm__ volatile("vmv.v.i v16,  0");
  // load vector
  __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(v_len));
  __asm__ volatile("vle32.v v0, (%0);" ::"r"(vector));
  for (uint32_t i = 0; i < m_row; ++i) {
    int *_mat_ = matrix + i * v_len;
    int *_dst_ = dest + i - 1; // delayed store
    __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(v_len));

    if (i % 2 == 0) {
      // load matrix slice row
      __asm__ volatile("vle32.v v4, (%0);" ::"r"(_mat_));
      // multiply with vector
      __asm__ volatile("vmul.vv v8, v4, v0");
      // reduction
      __asm__ volatile("vredsum.vs v16, v8, v16");
      // store previous data
      if (i != 0) {
        // __asm__ volatile("vse32.v v24, (%0);" ::"r"(_dst_));
        int tmp;
        __asm__ volatile("vmv.x.s %0, v24" : "=r"(tmp));
        *_dst_ = tmp;
        // clear reduction register
        __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(1));
        __asm__ volatile("vmv.v.i v24,  0");
      }

    } else {
      // load matrix slice row
      __asm__ volatile("vle32.v v2, (%0);" ::"r"(_mat_));
      // multiply with vector
      __asm__ volatile("vmul.vv v6, v2, v0");
      // reduction
      __asm__ volatile("vredsum.vs v24, v6, v24");
      // store previous data
      // __asm__ volatile("vse32.v v16, (%0);" ::"r"(_dst_));
      int tmp;
      __asm__ volatile("vmv.x.s %0, v16" : "=r"(tmp));
      *_dst_ = tmp;
      // clear reduction register
      __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(1));
      __asm__ volatile("vmv.v.i v16,  0");
    }
  }

  // store the last value
  int *_dst_ = dest + m_row - 1;
  if (m_row % 2 == 0) // even
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

void gemv_rowwise_kernel_slice(const unsigned long int v_len,
                               const unsigned long int slice_width,
                               const unsigned long int slice_height,
                               int *matrix, int *vector) {
  __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(slice_width));
  // load vector
  __asm__ volatile("vle32.v v0, (%0);" ::"r"(vector));

  // for each row in slice
  for (uint32_t i = 0; i < slice_height; ++i) {
    int *_mat_ = matrix + i * v_len;
    int tmp; // for round slice later
    __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(slice_width));
    // load matrix slice row
    __asm__ volatile("vle32.v v4, (%0);" ::"r"(_mat_));
    // multiply with vector
    __asm__ volatile("vmul.vv v8, v4, v0");
    if (i % 2 == 0) {
      // round slide
      __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(slice_height));
      __asm__ volatile("vmv.x.s %0, v24" : "=r"(tmp));
      __asm__ volatile("vslide1down.vx  v16, v24, %0" ::"r"(tmp));
      // reduction
      __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(slice_width));
      __asm__ volatile("vredsum.vs v16, v8, v16");
    } else {
      // round slide
      __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(slice_height));
      __asm__ volatile("vmv.x.s %0, v16" : "=r"(tmp));
      __asm__ volatile("vslide1down.vx  v24, v16, %0" ::"r"(tmp));
      // reduction
      __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(slice_width));
      __asm__ volatile("vredsum.vs v24, v8, v24");
    }
  }

  if (slice_height % 2) {
    __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(slice_height));
    __asm__ volatile("vmv.v.v v24, v16");
  }
}

void gemv_rowwise(const unsigned long int m_row, const unsigned long int v_len,
                  int *matrix, int *vector, int *dest) {
  // when matrix is samller than a slice
  __asm__ volatile("vsetvli %0, %1, e32, m2, ta, ma" : "=r"(vl) :"r"(v_len));

  if (v_len <= vl) {
    gemv_rowwise_small_than_slice(m_row, v_len, matrix, vector, dest);
    return;
  }

  uint32_t num_slice_row = m_row / vl;
  uint32_t rest_row = m_row % vl;
  uint32_t num_slice_col = v_len / vl;
  uint32_t rest_col = v_len % vl;

  // each slice row
  for (uint32_t i = 0; i < num_slice_row; ++i) {
    // clear reduction sum register file
    clear_reduction_register();
    // each full slice
    for (uint32_t j = 0; j < num_slice_col; ++j) {
      int *_mat_ = matrix + i * vl * v_len + j * vl;
      int *_vec_ = vector + j * vl;
      gemv_rowwise_kernel_slice(v_len, vl, vl, _mat_, _vec_);
    }
    // margin slice
    if (rest_col > 0) {
      int *_mat_ =
          matrix + i * vl * v_len + num_slice_col * vl;
      int *_vec_ = vector + num_slice_col * vl;
      gemv_rowwise_kernel_slice(v_len, rest_col, vl, _mat_, _vec_);
    }
    // store dest vector value
    int *_dst_ = dest + i * vl;
    store_slice_results(_dst_, vl);
  }

  // margin slice row
  if (rest_row > 0) {
    // clear reduction sum register file
    clear_reduction_register();
    // each bottom slice
    for (uint32_t j = 0; j < num_slice_col; ++j) {
      int *_mat_ =
          matrix + num_slice_row * vl * v_len + j * vl;
      int *_vec_ = vector + j * vl;
      gemv_rowwise_kernel_slice(v_len, vl, rest_row, _mat_, _vec_);
    }
    // margin slice
    if (rest_col > 0) {
      int *_mat_ = matrix + num_slice_row * vl * v_len +
                      num_slice_col * vl;
      int *_vec_ = vector + num_slice_col * vl;
      gemv_rowwise_kernel_slice(v_len, rest_col, rest_row, _mat_, _vec_);
    }
    // store dest vector value
    int *_dst_ = dest + num_slice_row * vl;
    store_slice_results(_dst_, rest_row);
  }
}

int gemv_verify(const unsigned long int m_row, const unsigned long int v_len,
                int *matrix, int *vector, int *dest) {
  for (uint32_t i = 0; i < m_row; ++i) {
    int res = dest[i];
    int golden = 0;
    for (uint32_t j = 0; j < v_len; ++j) {
      golden = golden + matrix[i * v_len + j] * vector[j];
    }
    if (golden != res) {
      printf("Fail, wrong value! at index %d, result = %d, golden = %d\n", (int)i,
             res, golden);
      return i;
    }
  }
  return 0;
}



#define MAX_ONLY 1

#define VERIFY 1
#define V_LEN 128
#define NR_LANES 1


int GEMV_M[V_LEN * V_LEN] __attribute__((aligned(4)));
int GEMV_D[V_LEN] __attribute__((aligned(4)));
int GEMV_V[V_LEN] __attribute__((aligned(4)));

uint64_t cycles_start;
uint64_t cycles_end;

int main() {
  printf("\n");
  printf("==========\n");
  printf("=  GEMV  =\n");
  printf("==========\n");
  printf("\n");
  printf("\n");

  #ifdef MAX_ONLY
    int init_value = V_LEN;
  #else
    int init_value = 4;
  #endif

  for (int s = init_value; s <= V_LEN; s *= 2) {
    printf("\n");
    printf("------------------------------------------------------------\n");
    printf("Calculating a (%d x %d) x %d matrix vector multiplication...\n", s,
           s, s);
    printf("------------------------------------------------------------\n");

    // Initialize Matrices
    printf("Initializing matrix and vector...\n");
    init_gemv_data(s, s, GEMV_M, GEMV_V, 1, 2, 3);

    // Start GEMV calculating
    printf("calculating...\n");
    cycles_start = csr_read_mcycle();
    gemv_rowwise(s, s, GEMV_M, GEMV_V, GEMV_D);
    cycles_end = csr_read_mcycle();

    // Metrics
    int64_t runtime = cycles_end - cycles_start;
    // float performance = 2.0 * s * s / runtime;
    // float utilization = 100 * performance / (2.0 * NR_LANES);

    printf("\nThe execution took %d cycles.\n\n", (int)runtime);
    //printf("The performance is %f FLOP/cycle (%f%% utilization) at %d lanes.\n",
    //       performance, utilization, NR_LANES);

    // Verify the result
    if (VERIFY) {
      printf("Verifying ...\n");
      if (gemv_verify(s, s, GEMV_M, GEMV_V, GEMV_D)) {
        return 1;
      } else {
        printf("Passed.\n\n");
      }
    }
  }

  printf("Done!\n");
  return 0;
}