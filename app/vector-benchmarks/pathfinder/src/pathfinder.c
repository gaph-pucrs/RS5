// Modified version of pathfinder from RODINIA and then RiVEC, adapted to Ara
// environment. Author: Matteo Perotti <mperotti@iis.ee.ethz.ch> Check LICENSE_0
// and LICENCE_1 for additional information

/*************************************************************************
 * RISC-V Vectorized Version
 * Author: Cristóbal Ramírez Lazo
 * email: cristobal.ramirez@bsc.es
 * Barcelona Supercomputing Center (2020)
 *************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <riscv-csr.h>

#include "data.h"

#define MIN(a, b) ((a) <= (b) ? (a) : (b))

int *run(int *wall, int *result_s, int *src, uint32_t cols, uint32_t rows,
         uint32_t num_runs) {
  int min;
  int *temp;
  int *dst;

  for (uint32_t j = 0; j < num_runs; j++) {
    for (uint32_t x = 0; x < cols; x++) {
      result_s[x] = wall[x];
    }

    dst = result_s;

    for (uint32_t t = 0; t < rows - 1; t++) {
      temp = src;
      src = dst;
      dst = temp;
      for (uint32_t n = 0; n < cols; n++) {
        min = src[n];
        if (n > 0)
          min = MIN(min, src[n - 1]);
        if (n < cols - 1)
          min = MIN(min, src[n + 1]);
        dst[n] = wall[(t + 1) * cols + n] + min;
      }
    }
    // Reset the pointer not to lose it
    src = temp;
  }
  return dst;
}

void run_vector(int *wall, int *result_v, uint32_t cols, uint32_t rows, uint32_t num_runs) {
    size_t gvl;
    int aux, aux2;
    int *dst;

    for (uint32_t j = 0; j < num_runs; j++) {
        // First loop: Copy wall to result_v
        for (uint32_t n = 0; n < cols; n += gvl) {
            // Set vector length (replaces __riscv_vsetvl_e32m1(cols))
            __asm__ volatile(
                "vsetvli %0, %1, e32, m1, ta, ma"
                : "=r"(gvl)
                : "r"(cols)
                : "memory"
            );

            // Load from wall[n] (replaces __riscv_vle32_v_i32m1(&wall[n], gvl))
            __asm__ volatile(
                "vle32.v v16, (%0)"
                :
                : "r"(&wall[n])
                : "v16", "memory"
            );

            // Store to result_v[n] (replaces __riscv_vse32_v_i32m1(&result_v[n], temp, gvl))
            __asm__ volatile(
                "vse32.v v16, (%0)"
                :
                : "r"(&result_v[n])
                : "v16", "memory"
            );
        }

        dst = result_v;

        // Set initial vector length for inner loop
        __asm__ volatile(
            "vsetvli %0, %1, e32, m1, ta, ma"
            : "=r"(gvl)
            : "r"(cols)
            : "memory"
        );

        for (uint32_t t = 0; t < rows - 1; t++) {
            aux = dst[0]; // Scalar load for slide-up

            for (uint32_t n = 0; n < cols; n += gvl) {
                // Update vector length for remaining elements (replaces __riscv_vsetvl_e32m1(cols - n))
                __asm__ volatile(
                    "vsetvli %0, %1, e32, m1, ta, ma"
                    : "=r"(gvl)
                    : "r"(cols - n)
                    : "memory"
                );

                // Load xNextrow from dst[n] (replaces __riscv_vle32_v_i32m1(&dst[n], gvl))
                __asm__ volatile(
                    "vle32.v v16, (%0)"
                    :
                    : "r"(&dst[n])
                    : "v16", "memory"
                );

                // xSrc = xNextrow (v16 holds xSrc)
                // Compute aux2 for slide-down
                aux2 = (n + gvl >= cols) ? dst[n + gvl - 1] : dst[n + gvl];

                // Slide-up: xSrc_slideup = __riscv_vslide1up_vx_i32m1(xSrc, aux, gvl)
                // First, load aux into a vector register (v0 as temporary)
                __asm__ volatile(
                    "vmv.v.x v0, %0" // Move scalar aux to vector register
                    :
                    : "r"(aux)
                    : "v0"
                );
                __asm__ volatile(
                    "vslide1up.vx v17, v16, %0"
                    :
                    : "r"(aux)
                    : "v17"
                );

                // Slide-down: xSrc_slidedown = __riscv_vslide1down_vx_i32m1(xSrc, aux2, gvl)
                __asm__ volatile(
                    "vmv.v.x v0, %0" // Move scalar aux2 to vector register
                    :
                    : "r"(aux2)
                    : "v0"
                );
                __asm__ volatile(
                    "vslide1down.vx v18, v16, %0"
                    :
                    : "r"(aux2)
                    : "v18"
                );

                // xSrc = vmin(xSrc, xSrc_slideup) (replaces __riscv_vmin_vv_i32m1(xSrc, xSrc_slideup, gvl))
                __asm__ volatile(
                    "vmin.vv v16, v16, v17"
                    :
                    :
                    : "v16"
                );

                // xSrc = vmin(xSrc, xSrc_slidedown) (replaces __riscv_vmin_vv_i32m1(xSrc, xSrc_slidedown, gvl))
                __asm__ volatile(
                    "vmin.vv v16, v16, v18"
                    :
                    :
                    : "v16"
                );

                // Load xNextrow from wall[(t + 1) * cols + n] (replaces __riscv_vle32_v_i32m1(&wall[(t + 1) * cols + n], gvl))
                __asm__ volatile(
                    "vle32.v v19, (%0)"
                    :
                    : "r"(&wall[(t + 1) * cols + n])
                    : "v19", "memory"
                );

                // xNextrow = vadd(xNextrow, xSrc) (replaces __riscv_vadd_vv_i32m1(xNextrow, xSrc, gvl))
                __asm__ volatile(
                    "vadd.vv v19, v19, v16"
                    :
                    :
                    : "v19"
                );

                // Update aux for next iteration
                aux = dst[n + gvl - 1];

                // Store xNextrow to dst[n] (replaces __riscv_vse32_v_i32m1(&dst[n], xNextrow, gvl))
                __asm__ volatile(
                    "vse32.v v19, (%0)"
                    :
                    : "r"(&dst[n])
                    : "v19", "memory"
                );
            }
        }
    }
}














int NR_LANES = 1;

#define CHECK

extern int32_t num_runs;
extern int32_t rows;
extern int32_t cols;
extern int src[] __attribute__((aligned(4)));
extern int wall[] __attribute__((aligned(4)));
extern int result_v[] __attribute__((aligned(4)));
extern int result_s[] __attribute__((aligned(4)));

int verify_result(int *result_s, int *result_v, uint32_t cols) {
  // Check vector with scalar result
  for (uint32_t i = 0; i < cols; i++) {
    if (result_v[i] != result_s[i]) {
      printf("Fail.\n");
      printf("Error. result_v[%d]=%d != result_s[%d]=%d \n", (int)i, result_v[i], (int)i,
             result_s[i]);
      return 1;
    }
  }

  printf("Passed.\n\n");

  return 0;
}

uint64_t cycles_start;
uint64_t cycles_end;

int main() {
  printf("\n");
  printf("================\n");
  printf("=  PATHFINDER  =\n");
  printf("================\n");
  printf("\n");
  printf("\n");

  int error;
  int *s_ptr;

  printf("Number of runs: %d\n\n", (int)num_runs);

#ifdef CHECK
  cycles_start = csr_read_mcycle();
  s_ptr = run(wall, result_s, src, cols, rows, num_runs);
  cycles_end = csr_read_mcycle();
  printf("[SCALAR] The execution took %d cycles.\n\n", (int)(cycles_end - cycles_start));
#endif

  cycles_start = csr_read_mcycle();
  run_vector(wall, result_v, cols, rows, num_runs);
  cycles_end = csr_read_mcycle();
  printf("[VECTOR] The execution took %d cycles.\n\n", (int)(cycles_end - cycles_start));

#ifdef CHECK
  error = verify_result(s_ptr, result_v, cols);
#else
  error = 0;
#endif

  return error;
}

