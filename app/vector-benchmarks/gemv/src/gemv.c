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
#include <riscv-csr-hpm.h>

uint32_t hpm_0_s[32];
uint32_t hpm_1_s[32];
uint32_t hpm_0_v[32];
uint32_t hpm_1_v[32];

void init_gemv_data(const unsigned long int m_row,
                    const unsigned long int VECTOR_LENGTH, int *matrix,
                    int *vector, int a, int b, int c) {
  // initialize matrix
  for (uint32_t i = 0; i < m_row; ++i) {
    for (uint32_t j = 0; j < VECTOR_LENGTH; ++j) {
      matrix[i * VECTOR_LENGTH + j] = a * (int)i + b * (int)j + c;
    }
  }

  // initialize vector
  for (uint32_t i = 0; i < VECTOR_LENGTH; ++i) {
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
                                   const unsigned long int VECTOR_LENGTH,
                                   int *matrix, int *vector,
                                   int *dest) {
  // setup
  __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(1));
  __asm__ volatile("vmv.v.i v24,  0");
  __asm__ volatile("vmv.v.i v16,  0");
  // load vector
  __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(VECTOR_LENGTH));
  __asm__ volatile("vle32.v v0, (%0);" ::"r"(vector));
  for (uint32_t i = 0; i < m_row; ++i) {
    int *_mat_ = matrix + i * VECTOR_LENGTH;
    int *_dst_ = dest + i - 1; // delayed store
    __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(VECTOR_LENGTH));

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

void gemv_rowwise_kernel_slice(const unsigned long int VECTOR_LENGTH,
                               const unsigned long int slice_width,
                               const unsigned long int slice_height,
                               int *matrix, int *vector) {
  __asm__ volatile("vsetvli zero, %0, e32, m2, ta, ma" ::"r"(slice_width));
  // load vector
  __asm__ volatile("vle32.v v0, (%0);" ::"r"(vector));

  // for each row in slice
  for (uint32_t i = 0; i < slice_height; ++i) {
    int *_mat_ = matrix + i * VECTOR_LENGTH;
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

void gemv_rowwise(const unsigned long int m_row, const unsigned long int VECTOR_LENGTH,
                  int *matrix, int *vector, int *dest) {
  // when matrix is samller than a slice
  __asm__ volatile("vsetvli %0, %1, e32, m2, ta, ma" : "=r"(vl) :"r"(VECTOR_LENGTH));

  if (VECTOR_LENGTH <= vl) {
    gemv_rowwise_small_than_slice(m_row, VECTOR_LENGTH, matrix, vector, dest);
    return;
  }

  uint32_t num_slice_row = m_row / vl;
  uint32_t rest_row = m_row % vl;
  uint32_t num_slice_col = VECTOR_LENGTH / vl;
  uint32_t rest_col = VECTOR_LENGTH % vl;

  // each slice row
  for (uint32_t i = 0; i < num_slice_row; ++i) {
    // clear reduction sum register file
    clear_reduction_register();
    // each full slice
    for (uint32_t j = 0; j < num_slice_col; ++j) {
      int *_mat_ = matrix + i * vl * VECTOR_LENGTH + j * vl;
      int *_vec_ = vector + j * vl;
      gemv_rowwise_kernel_slice(VECTOR_LENGTH, vl, vl, _mat_, _vec_);
    }
    // margin slice
    if (rest_col > 0) {
      int *_mat_ =
          matrix + i * vl * VECTOR_LENGTH + num_slice_col * vl;
      int *_vec_ = vector + num_slice_col * vl;
      gemv_rowwise_kernel_slice(VECTOR_LENGTH, rest_col, vl, _mat_, _vec_);
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
          matrix + num_slice_row * vl * VECTOR_LENGTH + j * vl;
      int *_vec_ = vector + j * vl;
      gemv_rowwise_kernel_slice(VECTOR_LENGTH, vl, rest_row, _mat_, _vec_);
    }
    // margin slice
    if (rest_col > 0) {
      int *_mat_ = matrix + num_slice_row * vl * VECTOR_LENGTH +
                      num_slice_col * vl;
      int *_vec_ = vector + num_slice_col * vl;
      gemv_rowwise_kernel_slice(VECTOR_LENGTH, rest_col, rest_row, _mat_, _vec_);
    }
    // store dest vector value
    int *_dst_ = dest + num_slice_row * vl;
    store_slice_results(_dst_, rest_row);
  }
}

void gemv_gold(const unsigned long int m_row, const unsigned long int VECTOR_LENGTH,
                int *matrix, int *vector, int *dest) {
  for (uint32_t i = 0; i < m_row; ++i) {
    int golden = 0;
    for (uint32_t j = 0; j < VECTOR_LENGTH; ++j) {
      golden = golden + matrix[i * VECTOR_LENGTH + j] * vector[j];
    }
    dest[i] = golden;
  }
}

int gemv_verify(const unsigned long int m_row, int *res_vector, int *res_golden) {
  for (uint32_t i = 0; i < m_row; ++i) {
    if (res_golden[i] != res_vector[i]) {
      printf("Fail, wrong value! at index %d, result = %d, golden = %d\n", (int)i, res_vector[i], res_golden[i]);
      return i;
    }
  }
  return 0;
}



#define MAX_ONLY 1

#define VERIFY 1
#define VECTOR_LENGTH 128
#define NR_LANES 1


int GEMV_MATRIX[VECTOR_LENGTH * VECTOR_LENGTH] __attribute__((aligned(4)));
int GEMV_VECTOR[VECTOR_LENGTH] __attribute__((aligned(4)));
int GEMV_RES_V [VECTOR_LENGTH] __attribute__((aligned(4)));
int GEMV_RES_S [VECTOR_LENGTH] __attribute__((aligned(4)));

uint64_t cycles_start;
uint64_t cycles_end;

int main() {
  csr_write_mcountinhibit(-1);
  printf("\n");
  printf("==========\n");
  printf("=  GEMV  =\n");
  printf("==========\n");
  printf("\n");
  printf("\n");

  int64_t runtime;

  #ifdef MAX_ONLY
    int init_value = VECTOR_LENGTH;
  #else
    int init_value = 4;
  #endif

  for (int size = init_value; size <= VECTOR_LENGTH; size *= 2) {
    printf("\n");
    printf("------------------------------------------------------------\n");
    printf("Calculating a (%d x %d) x %d matrix vector multiplication...\n", size,
           size, size);
    printf("------------------------------------------------------------\n");

    // Initialize Matrices
    printf("Initializing matrix and vector...\n");
    init_gemv_data(size, size, GEMV_MATRIX, GEMV_VECTOR, 1, 2, 3);

    // Start GEMV calculating
    printf("calculating...\n\n");

// ********************************
//       !!!    SCALAR    !!!
// ********************************
    read_hpms(hpm_0_s);
    cycles_start = csr_read_mcycle();
    csr_write_mcountinhibit(0);
    gemv_gold(size, size, GEMV_MATRIX, GEMV_VECTOR, GEMV_RES_S);
    csr_write_mcountinhibit(-1);
    cycles_end = csr_read_mcycle();
    read_hpms(hpm_1_s);

    runtime = cycles_end - cycles_start;
    printf("[SCALAR] The execution took %d cycles.\n\n", (int)runtime);

// ********************************
//       !!!    VECTOR    !!!
// ********************************
    read_hpms(hpm_0_v);
    cycles_start = csr_read_mcycle();
    csr_write_mcountinhibit(0);
    gemv_rowwise(size, size, GEMV_MATRIX, GEMV_VECTOR, GEMV_RES_V);
    csr_write_mcountinhibit(-1);
    cycles_end = csr_read_mcycle();
    read_hpms(hpm_1_v);

    // Metrics
    runtime = cycles_end - cycles_start;
    // float performance = 2.0 * size * size / runtime;
    // float utilization = 100 * performance / (2.0 * NR_LANES);

    printf("[VECTOR] The execution took %d cycles.\n\n", (int)runtime);
    //printf("The performance is %f FLOP/cycle (%f%% utilization) at %d lanes.\n",
    //       performance, utilization, NR_LANES);

    // Verify the result
    if (VERIFY) {
      printf("Verifying ...\n");
      if (gemv_verify(size, GEMV_RES_V, GEMV_RES_S)) {
        return 1;
      } else {
        printf("Passed.\n\n");
      }
    }
  }

  printf("Done!\n\n");

  printf("SCALAR:\n");
  evaluate_hpms(hpm_0_s, hpm_1_s);

  printf("VECTOR:\n");
  evaluate_hpms(hpm_0_v, hpm_1_v);

  return 0;
}