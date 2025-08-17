/*
OHIO STATE UNIVERSITY SOFTWARE DISTRIBUTION LICENSE

PolyBench/C, a collection of benchmarks containing static control
parts (the "Software")
Copyright (c) 2010-2016, Ohio State University. All rights reserved.

The Software is available for download and use subject to the terms
and conditions of this License.  Access or use of the Software
constitutes acceptance and agreement to the terms and conditions of
this License.  Redistribution and use of the Software in source and
binary forms, with or without modification, are permitted provided
that the following conditions are met:

1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the capitalized paragraph below.

2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the capitalized paragraph below in
the documentation and/or other materials provided with the
distribution.

3. The name of Ohio State University, or its faculty, staff or
students may not be used to endorse or promote products derived from
the Software without specific prior written permission.

This software was produced with support from the U.S. Defense Advanced
Research Projects Agency (DARPA), the U.S. Department of Energy (DoE)
and the U.S. National Science Foundation. Nothing in this work should
be construed as reflecting the official policy or position of the
Defense Department, the United States government or Ohio State
University.

THIS SOFTWARE HAS BEEN APPROVED FOR PUBLIC RELEASE, UNLIMITED
DISTRIBUTION.  THE SOFTWARE IS PROVIDED ?AS IS? AND WITHOUT ANY
EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, WARRANTIES OF ACCURACY, COMPLETENESS, NONINFRINGEMENT,
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
ACCESS OR USE OF THE SOFTWARE IS ENTIRELY AT THE USER?S RISK.  IN NO
EVENT SHALL OHIO STATE UNIVERSITY OR ITS FACULTY, STAFF OR STUDENTS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  THE SOFTWARE USER SHALL
INDEMNIFY, DEFEND AND HOLD HARMLESS OHIO STATE UNIVERSITY AND ITS
FACULTY, STAFF AND STUDENTS FROM ANY AND ALL CLAIMS, ACTIONS, DAMAGES,
LOSSES, LIABILITIES, COSTS AND EXPENSES, INCLUDING ATTORNEYS? FEES AND
COURT COSTS, DIRECTLY OR INDIRECTLY ARISING OUT OF OR IN CONNECTION
WITH ACCESS OR USE OF THE SOFTWARE.
*/

/**
 * This version is stamped on May 10, 2016
 *
 * Contact:
 *   Louis-Noel Pouchet <pouchet.ohio-state.edu>
 *   Tomofumi Yuki <tomofumi.yuki.fr>
 *
 * Web address: http://polybench.sourceforge.net
 */
/* jacobi-2d.c: this file is part of PolyBench/C */

/*************************************************************************
 * RISC-V Vectorized Version
 * Author: Cristóbal Ramírez Lazo
 * email: cristobal.ramirez@bsc.es
 * Barcelona Supercomputing Center (2020)
 *************************************************************************/

// Porting to Ara SW environment and Optimization
// Author: Matteo Perotti, ETH Zurich, <mperotti@iis.ee.ethz.ch>

#include <stdint.h>
#include <stdio.h>
#include <riscv-csr.h>

#include "data.h"

#define DATA_TYPE int

// DOUBLE_BUFFERING WITH PROBLEMS -- 09/08/25
//#define DOUBLE_BUFFERING

void j2d_s(uint32_t r, uint32_t c, DATA_TYPE *A, DATA_TYPE *B,
           uint32_t tsteps) {
  for (uint32_t t = 0; t < tsteps; t++) {
    for (uint32_t i = 1; i < r - 1; i++)
      for (uint32_t j = 1; j < c - 1; j++)
        B[i * c + j] =
            (A[i * c + j] + A[i * c + j - 1] + A[i * c + j + 1] +
             A[(i + 1) * c + j] + A[(i - 1) * c + j]) / 5;
#ifdef DOUBLE_BUFFERING
    for (uint32_t i = 1; i < r - 1; i++)
      for (uint32_t j = 1; j < c - 1; j++)
        A[i * c + j] =
            (B[i * c + j] + B[i * c + j - 1] + B[i * c + j + 1] +
             B[(i + 1) * c + j] + B[(i - 1) * c + j]) / 5;
#endif
  }
}

void j2d_v(uint32_t r, uint32_t c, DATA_TYPE *A, DATA_TYPE *B,
           uint32_t tsteps) {
  for (uint32_t t = 0; t < tsteps; t++) {
    j2d_kernel_asm_v(r, c, A, B);
#ifdef DOUBLE_BUFFERING
    j2d_kernel_asm_v(r, c, B, A);
#endif
  }
}

// Optimized version of the jacobi2d kernel
// 1) Preload the coefficients, before each vstore
// 2) Eliminate WAW and WAR hazards
// 3) Unroll the loop and use multiple buffers
// 4) Optimize pointers
void j2d_kernel_asm_v(uint32_t r, uint32_t c, DATA_TYPE *A, DATA_TYPE *B) {
  DATA_TYPE izq_0, izq_1, izq_2;
  DATA_TYPE der_0, der_1, der_2;
  uint32_t size_x = c - 2;
  uint32_t size_y = r - 2;
  // Simplify pointer calc
  uint32_t sc_ptr_0, sc_ptr_1;
  uint32_t mtx_ptr_0, mtx_ptr_1;

  int five = 5;

  size_t gvl;

  __asm__ volatile("vsetvli %0, %1, e32, m4, ta, ma" : "=r"(gvl) : "r"(size_x));

  for (uint32_t j = 1; j <= size_x; j = j + gvl) {
    __asm__ volatile("vsetvli %0, %1, e32, m4, ta, ma"
                 : "=r"(gvl)
                 : "r"(size_x - j + 1));
    mtx_ptr_0 = j;                                         // 0 * c + j
    __asm__ volatile("vle32.v v0, (%0)" ::"r"(&A[mtx_ptr_0])); // v0 top
    mtx_ptr_1 = j + c;                                     // 1 * c + j
    __asm__ volatile("vle32.v v4, (%0)" ::"r"(&A[mtx_ptr_1])); // v4 middle
    mtx_ptr_0 = mtx_ptr_1 + c;                             // 2 * c + j
    __asm__ volatile("vle32.v v8, (%0)" ::"r"(&A[mtx_ptr_0])); // v8 bottom

    // Look ahead and load the next coefficients
    // Do it before vector stores
    sc_ptr_0 = mtx_ptr_1 - 1; // 1 * c + j - 1
    izq_0 = A[sc_ptr_0];
    sc_ptr_1 = mtx_ptr_1 + gvl; // 1 * c + j + gvl
    der_0 = A[sc_ptr_1];

    // mtx_ptr_0 = 2 * c + j
    // mtx_ptr_1 = 1 * c + j
    // sc_ptr_0  = 1 * c + j - 1
    // sc_ptr_1  = 1 * c + j + gvl

    for (uint32_t i = 1; i <= size_y; i += 3) {
      // mtx_ptr_0 = (i + 1) * c + j
      // mtx_ptr_1 = i * c + j
      // sc_ptr_0  = i * c + j - 1
      // sc_ptr_1  = i * c + j + gvl

      __asm__ volatile("vslide1up.vx v24, v4, %0" ::"r"(izq_0));
      __asm__ volatile("vslide1down.vx v28, v4, %0" ::"r"(der_0));
      __asm__ volatile("vadd.vv v12, v4, v0");   // middle - top
      mtx_ptr_0 += c;                        // (i + 2) * c + j
      __asm__ volatile("vadd.vv v12, v12, v8");  // bottom
      sc_ptr_0 += c;                         // (i + 1) * c + j - 1
      __asm__ volatile("vadd.vv v12, v12, v24"); // left
      if ((i + 1) <= size_y) {
        __asm__ volatile("vle32.v v0, (%0)" ::"r"(&A[mtx_ptr_0])); // v0 top
      }
      __asm__ volatile("vadd.vv v12, v12, v28"); // right
      sc_ptr_1 += c;                          // (i + 1) * c + j + gvl
      __asm__ volatile("vdiv.vx v12, v12, %0" ::"r"(five));
      if ((i + 1) <= size_y) {
        izq_1 = A[sc_ptr_0];
        der_1 = A[sc_ptr_1];
      }
      __asm__ volatile("vse32.v v12, (%0)" ::"r"(&B[mtx_ptr_1]));
      mtx_ptr_1 += c; // (i + 1) * c + j

      // mtx_ptr_0 = (i + 2) * c + j
      // mtx_ptr_1 = (i + 1) * c + j
      // sc_ptr_0  = (i + 1) * c + j - 1
      // sc_ptr_1  = (i + 1) * c + j + gvl

      if ((i + 1) <= size_y) {
        __asm__ volatile("vslide1up.vx v24, v8, %0" ::"r"(izq_1));
        __asm__ volatile("vslide1down.vx v28, v8, %0" ::"r"(der_1));
        __asm__ volatile("vadd.vv v16, v4, v8");   // middle - top
        mtx_ptr_0 += c;                         // (i + 3) * c + j
        __asm__ volatile("vadd.vv v16, v16, v0");  // bottom
        sc_ptr_0 += c;                          // (i + 2) * c + j - 1
        __asm__ volatile("vadd.vv v16, v16, v24"); // left
        if ((i + 2) <= size_y) {
          __asm__ volatile("vle32.v v4, (%0)" ::"r"(&A[mtx_ptr_0])); // v4 middle
        }
        __asm__ volatile("vadd.vv v16, v16, v28"); // right
        sc_ptr_1 += c;                          // (i + 2) * c + j + gvl
        __asm__ volatile("vdiv.vx v16, v16, %0" ::"r"(five));
        if ((i + 2) <= size_y) {
          izq_2 = A[sc_ptr_0];
          der_2 = A[sc_ptr_1];
        }
        __asm__ volatile("vse32.v v16, (%0)" ::"r"(&B[mtx_ptr_1]));
        mtx_ptr_1 += c; // (i + 2) * c + j

        // mtx_ptr_0 = (i + 3) * c + j
        // mtx_ptr_1 = (i + 2) * c + j
        // sc_ptr_0  = (i + 2) * c + j - 1
        // sc_ptr_1  = (i + 2) * c + j + gvl

        if ((i + 2) <= size_y) {
          __asm__ volatile("vslide1up.vx v24, v0, %0" ::"r"(izq_2));
          __asm__ volatile("vslide1down.vx v28, v0, %0" ::"r"(der_2));
          __asm__ volatile("vadd.vv v20, v0, v8");   // middle - top
          mtx_ptr_0 += c;                         // (i + 4) * c + j
          __asm__ volatile("vadd.vv v20, v20, v4");  // bottom
          sc_ptr_0 += c;                          // (i + 3) * c + j - 1
          __asm__ volatile("vadd.vv v20, v20, v24"); // left
          if ((i + 3) <= size_y) {
            __asm__ volatile("vle32.v v8, (%0)" ::"r"(&A[mtx_ptr_0])); // v8 bottom
          }
          __asm__ volatile("vadd.vv v20, v20, v28"); // right
          sc_ptr_1 += c;                          // (i + 3) * c + j + gvl
          __asm__ volatile("vdiv.vx v20, v20, %0" ::"r"(five));
          if ((i + 3) <= size_y) {
            izq_0 = A[sc_ptr_0];
            der_0 = A[sc_ptr_1];
          }
          __asm__ volatile("vse32.v v20, (%0)" ::"r"(&B[mtx_ptr_1]));
          mtx_ptr_1 += c; // (i + 3) * c + j

          // mtx_ptr_0 = (i + 4) * c + j
          // mtx_ptr_1 = (i + 3) * c + j
          // sc_ptr_0  = (i + 3) * c + j - 1
          // sc_ptr_1  = (i + 3) * c + j + gvl
        }
      }
    }
  }
}

// Debug
void output_printfile(uint32_t r, uint32_t c, DATA_TYPE *A) {
  for (uint32_t i = 0; i < r; i++)
    for (uint32_t j = 0; j < c; j++) {
      printf("A[%d][%d] = %d, ", (int)i, (int)j, A[i * c + j]);
      if (j == c - 1)
        printf("A[%d][%d] = %d\n", (int)i, (int)j, A[i * c + j]);
    }
}



//#define RESULT_PRINT
#define NR_LANES 1

// The padded matrices should be aligned in SW not on the padding,
// but on the actual data.
// R and C contain the padding as well.
extern uint32_t R;
extern uint32_t C;

extern uint32_t TSTEPS;

extern DATA_TYPE A_s[] __attribute__((aligned(4)));
extern DATA_TYPE B_s[] __attribute__((aligned(4)));
extern DATA_TYPE A_v[] __attribute__((aligned(4)));
extern DATA_TYPE B_v[] __attribute__((aligned(4)));

uint64_t cycles_start;
uint64_t cycles_end;

int main() {
  printf("\n");
  printf("==============\n");
  printf("=  JACOBI2D  =\n");
  printf("==============\n");
  printf("\n");

  int error = 0;

  // Align the matrices so that the vector store will also be aligned
  size_t mtx_offset = ((4 * NR_LANES) / sizeof(DATA_TYPE)) - 1;
  DATA_TYPE *A_fixed_s = A_s + mtx_offset;
  DATA_TYPE *A_fixed_v = A_v + mtx_offset;
  DATA_TYPE *B_fixed_s = B_s + mtx_offset;
  DATA_TYPE *B_fixed_v = B_v + mtx_offset;

  // Check that the matrices are aligned on the actual output data
  // NR_LANES can be maximum 16 here
  if (((uint32_t)(B_fixed_v + 1) & (0x3f / (16 / NR_LANES))) != 0) {
    printf("Fatal warning: the matrices are not correctly aligned.\n");
    return -1;
  } else {
    printf("The store address 0x%lx is correctly aligned.\n\n",
           (uint32_t)(B_fixed_v + 1));
  }

  // Measure scalar kernel execution
  printf("Processing the scalar benchmark\n");
  cycles_start = csr_read_mcycle();
  j2d_s(R, C, A_fixed_s, B_fixed_s, TSTEPS);
  cycles_end = csr_read_mcycle();
  //printf("Scalar jacobi2d cycle count: %d\n\n", (int)(cycles_end - cycles_start));
  printf("[SCALAR] The execution took %d cycles.\n\n", (int)(cycles_end - cycles_start));

  // Measure vector kernel execution
  printf("Processing the vector benchmark\n");
  cycles_start = csr_read_mcycle();
  j2d_v(R, C, A_fixed_v, B_fixed_v, TSTEPS);
  cycles_end = csr_read_mcycle();
  int runtime = (int)(cycles_end - cycles_start);
  // 2* since we have 2 jacobi kernels, one on A_fixed_v, one on B_fixed_v
  // TSTEPS*5*N*N is the number of DPFLOP to compute
  //float performance = (2.0 * TSTEPS * 5.0 * (R - 1) * (C - 1) / runtime);
  //float utilization = 100.0 * performance / NR_LANES;
  //printf("Vector jacobi2d cycle count: %d\n", runtime);
  printf("[VECTOR] The execution took %d cycles.\n\n", runtime);

  //printf("The performance is %f DPFLOP/cycle (%f%% utilization).\n",
  //       performance, utilization);

#ifdef RESULT_PRINT
  printf("Scalar A mtx:\n");
  output_printfile(R, C, A_fixed_s);
  printf("Vector A mtx:\n");
  output_printfile(R, C, A_fixed_v);
  printf("Scalar B mtx:\n");
  output_printfile(R, C, B_fixed_s);
  printf("Vector B mtx:\n");
  output_printfile(R, C, B_fixed_v);
#endif

  printf("Checking the results:\n");
  for (uint32_t i = 0; i < R; i++)
    for (uint32_t j = 0; j < C; j++)
      if (A_fixed_s[i * C + j] != A_fixed_v[i * C + j]) {
        printf("Fail.\n");
        printf("Error: [%d, %d], %d, %d\n", (int)i, (int)j, A_fixed_s[i * C + j],
               A_fixed_v[i * C + j]);
        error = 1;
      }
  if (!error)
    printf("Passed.\n\n");

  return error;
}
