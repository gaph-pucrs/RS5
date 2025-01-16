// #include <stdio.h>
#include "printf.h"

// extern uint64_t vsize;

// extern int32_t v32a[] __attribute__((aligned(32 * NR_LANES), section(".l2")));
// extern int32_t v32b[] __attribute__((aligned(32 * NR_LANES), section(".l2")));

// extern int32_t res32_v, res32_s;

int main() {
  printf("\n");
  printf("=============\n");
  printf("=  GENDATA  =\n");
  printf("=============\n");
  printf("\n");

  printf("NR_LANES: %d\n", NR_LANES);
  printf("VLEN: %d\n", VLEN);

//   for(uint64_t i=0; i<(vsize >> 2); i*=8) {
//     printf("%ld\n", *v32a);
//   }

  return 0;
}