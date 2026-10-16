#include <stdint.h>
#include "params.h"
#include "ntt.h"
#include "reduce.h"

/* Code to generate zetas and zetas_inv used in the number-theoretic transform:

#define KYBER_ROOT_OF_UNITY 17

static const uint16_t tree[128] = {
  0, 64, 32, 96, 16, 80, 48, 112, 8, 72, 40, 104, 24, 88, 56, 120,
  4, 68, 36, 100, 20, 84, 52, 116, 12, 76, 44, 108, 28, 92, 60, 124,
  2, 66, 34, 98, 18, 82, 50, 114, 10, 74, 42, 106, 26, 90, 58, 122,
  6, 70, 38, 102, 22, 86, 54, 118, 14, 78, 46, 110, 30, 94, 62, 126,
  1, 65, 33, 97, 17, 81, 49, 113, 9, 73, 41, 105, 25, 89, 57, 121,
  5, 69, 37, 101, 21, 85, 53, 117, 13, 77, 45, 109, 29, 93, 61, 125,
  3, 67, 35, 99, 19, 83, 51, 115, 11, 75, 43, 107, 27, 91, 59, 123,
  7, 71, 39, 103, 23, 87, 55, 119, 15, 79, 47, 111, 31, 95, 63, 127
};

void init_ntt() {
  unsigned int i, j, k;
  int16_t tmp[128];

  tmp[0] = MONT;
  for(i = 1; i < 128; ++i)
    tmp[i] = fqmul(tmp[i-1], KYBER_ROOT_OF_UNITY*MONT % KYBER_Q);

  for(i = 0; i < 128; ++i)
    zetas[i] = tmp[tree[i]];

  k = 0;
  for(i = 64; i >= 1; i >>= 1)
    for(j = i; j < 2*i; ++j)
      zetas_inv[k++] = -tmp[128 - tree[j]];

  zetas_inv[127] = MONT * (MONT * (KYBER_Q - 1) * ((KYBER_Q - 1)/128) % KYBER_Q) % KYBER_Q;
}

*/

// Without Montgomery constant (for Kyber ISE)
#ifdef KYBER_ISE
const int16_t zetas[128] = {
  1, 1729, 2580, 3289, 2642, 630, 1897, 848, 1062, 1919, 193, 797,
  2786, 3260, 569, 1746, 296, 2447, 1339, 1476, 3046, 56, 2240, 1333,
  1426, 2094, 535, 2882, 2393, 2879, 1974, 821, 289, 331, 3253, 1756,
  1197, 2304, 2277, 2055, 650, 1977, 2513, 632, 2865, 33, 1320, 1915,
  2319, 1435, 807, 452, 1438, 2868, 1534, 2402, 2647, 2617, 1481, 648,
  2474, 3110, 1227, 910, 17, 2761, 583, 2649, 1637, 723, 2288, 1100,
  1409, 2662, 3281, 233, 756, 2156, 3015, 3050, 1703, 1651, 2789, 1789,
  1847, 952, 1461, 2687, 939, 2308, 2437, 2388, 733, 2337, 268, 641,
  1584, 2298, 2037, 3220, 375, 2549, 2090, 1645, 1063, 319, 2773, 757,
  2099, 561, 2466, 2594, 2804, 1092, 403, 1026, 1143, 2150, 2775, 886,
  1722, 1212, 1874, 1029, 2110, 2935, 885, 2154
};

#else
const int16_t zetas[128] = {
  2285, 2571, 2970, 1812, 1493, 1422, 287, 202, 3158, 622, 1577, 182, 962,
  2127, 1855, 1468, 573, 2004, 264, 383, 2500, 1458, 1727, 3199, 2648, 1017,
  732, 608, 1787, 411, 3124, 1758, 1223, 652, 2777, 1015, 2036, 1491, 3047,
  1785, 516, 3321, 3009, 2663, 1711, 2167, 126, 1469, 2476, 3239, 3058, 830,
  107, 1908, 3082, 2378, 2931, 961, 1821, 2604, 448, 2264, 677, 2054, 2226,
  430, 555, 843, 2078, 871, 1550, 105, 422, 587, 177, 3094, 3038, 2869, 1574,
  1653, 3083, 778, 1159, 3182, 2552, 1483, 2727, 1119, 1739, 644, 2457, 349,
  418, 329, 3173, 3254, 817, 1097, 603, 610, 1322, 2044, 1864, 384, 2114, 3193,
  1218, 1994, 2455, 220, 2142, 1670, 2144, 1799, 2051, 794, 1819, 2475, 2459,
  478, 3221, 3021, 996, 991, 958, 1869, 1522, 1628
};

#endif

// Not needed anymore, new INTT from pq-crystals github repo reuses same zetas as forward NTT
// const int16_t zetas_inv[128] = {
//   1701, 1807, 1460, 2371, 2338, 2333, 308, 108, 2851, 870, 854, 1510, 2535,
//   1278, 1530, 1185, 1659, 1187, 3109, 874, 1335, 2111, 136, 1215, 2945, 1465,
//   1285, 2007, 2719, 2726, 2232, 2512, 75, 156, 3000, 2911, 2980, 872, 2685,
//   1590, 2210, 602, 1846, 777, 147, 2170, 2551, 246, 1676, 1755, 460, 291, 235,
//   3152, 2742, 2907, 3224, 1779, 2458, 1251, 2486, 2774, 2899, 1103, 1275, 2652,
//   1065, 2881, 725, 1508, 2368, 398, 951, 247, 1421, 3222, 2499, 271, 90, 853,
//   1860, 3203, 1162, 1618, 666, 320, 8, 2813, 1544, 282, 1838, 1293, 2314, 552,
//   2677, 2106, 1571, 205, 2918, 1542, 2721, 2597, 2312, 681, 130, 1602, 1871,
//   829, 2946, 3065, 1325, 2756, 1861, 1474, 1202, 2367, 3147, 1752, 2707, 171,
//   3127, 3042, 1907, 1836, 1517, 359, 758, 1441
// };

/*************************************************
* Name:        fqmul
*
* Description: Multiplication followed by Montgomery reduction
*
* Arguments:   - int16_t a: first factor
*              - int16_t b: second factor
*
* Returns 16-bit integer congruent to a*b*R^{-1} mod q
**************************************************/
static int16_t fqmul(int16_t a, int16_t b) {

  #ifdef KYBER_ISE
  int16_t asm_val;
  __asm__("kybermul %0, %1, %2" :  "=r"(asm_val) : "r"(a), "r"(b));

  #ifdef KYBER_ISE_DEBUG

  puts("kybermul a = ");
  puthex(a);
  puts(" | ");
  puts("kybermul b = ");
  puthex(b);
  puts("\n");

  int ref_val = (a * b) % KYBER_Q;

  if (rvkat_chku32("kybermul", ref_val, asm_val))
    __asm__("ebreak");
  #endif

  return asm_val;

  #else
  return montgomery_reduce((int32_t)a*b);
  #endif

}

/*************************************************
* Name:        ntt
*
* Description: Inplace number-theoretic transform (NTT) in Rq
*              input is in standard order, output is in bitreversed order
*
* Arguments:   - int16_t r[256]: pointer to input/output vector of elements
*                                of Zq
**************************************************/
void ntt(int16_t r[256]) {
  unsigned int len, start, j, k;
  int16_t t, zeta;

  #ifdef KYBER_ISE
  uint32_t* r_word_ptr = (uint32_t*) r;
  #endif

  k = 1;
  for (len = 128; len >= 2; len >>= 1) {
    for (start = 0; start < 256; start = j + len) {

      zeta = zetas[k++];

      #ifdef KYBER_ISE
      for (j = start; j < start + len; j+=2) {
      #else
      for (j = start; j < start + len; ++j) {
      #endif

        #ifdef KYBER_ISE

        uint32_t op_a, op_b;
        uint32_t add_result, sub_result;
        uint32_t temp1, temp2;

        op_a = r_word_ptr[j/2];
        op_b = r_word_ptr[j/2 + len/2];

        __asm__ __volatile__ ("kybermul %0, %1, %2" :  "=r"(temp1) : "r"(zeta), "r"(op_b));
        op_b = op_b >> 16;
        __asm__ __volatile__ ("kybermul %0, %1, %2" :  "=r"(temp2) : "r"(zeta), "r"(op_b));
        temp2 = temp2 << 16;
        temp1 = temp1 | temp2;
        __asm__ __volatile__ ("kybersub %0, %1, %2" :  "=r"(sub_result) : "r"(op_a), "r"(temp1));
        __asm__ __volatile__ ("kyberadd %0, %1, %2" :  "=r"(add_result) : "r"(op_a), "r"(temp1));

        r_word_ptr[j/2 + len/2] = sub_result;
        r_word_ptr[j/2] = add_result;

        #else

        t = fqmul(zeta, r[j + len]);
        r[j + len] = r[j] - t;
        r[j] = r[j] + t;

        #endif
      }

    }
  }
}

/*************************************************
* Name:        invntt_tomont
*
* Description: Inplace inverse number-theoretic transform in Rq and
*              multiplication by Montgomery factor 2^16.
*              Input is in bitreversed order, output is in standard order
*
* Arguments:   - int16_t r[256]: pointer to input/output vector of elements
*                                of Zq
**************************************************/
// void invntt(int16_t r[256]) {
//   unsigned int start, len, j, k;
//   int16_t t, zeta;

//   k = 0;
//   for(len = 2; len <= 128; len <<= 1) {
//     for(start = 0; start < 256; start = j + len) {
//       zeta = zetas_inv[k++];

//       puts("k = ");
//       puthex(k);
//       puts("\n");

//       if (zeta == zetas_inv[127])
//         __asm__ volatile ("ebreak");

//       for(j = start; j < start + len; ++j) {
//         t = r[j];
//         r[j] = barrett_reduce(t + r[j + len]);
//         r[j + len] = t - r[j + len];
//         r[j + len] = fqmul(zeta, r[j + len]);
//       }
//     }
//   }

//   for(j = 0; j < 256; ++j)
//     r[j] = fqmul(r[j], zetas_inv[127]);
// }

void invntt(int16_t r[256]) {
  unsigned int start, len, j, k;
  int16_t t, zeta;

  #ifdef KYBER_ISE
  const int16_t f = 3303; // 1/128 scaling factor in Zq
  uint32_t* r_word_ptr = (uint32_t*) r;
  #else
  const int16_t f = 1441; // mont^2/128
  #endif

  k = 127;
  for(len = 2; len <= 128; len <<= 1) {

    for(start = 0; start < 256; start = j + len) {

      zeta = zetas[k--];

      #ifdef KYBER_ISE
      for(j = start; j < start + len; j+=2) {
      #else
      for(j = start; j < start + len; j++) {
      #endif

        #ifdef KYBER_ISE

        uint32_t op_a, op_b;  // SIMD add/sub mod q operands
        uint32_t add_result, sub_result;  // SIMD add/sub mod q result
        uint32_t temp1, temp2;

        op_a = r_word_ptr[j/2];
        op_b = r_word_ptr[j/2 + len/2];

        __asm__ __volatile__("kyberadd %0, %1, %2" :  "=r"(add_result) : "r"(op_b), "r"(op_a));
        __asm__ __volatile__("kybersub %0, %1, %2" :  "=r"(sub_result) : "r"(op_b), "r"(op_a));
        __asm__ __volatile__("kybermul %0, %1, %2" :  "=r"(temp1) : "r"(zeta), "r"(sub_result));
        sub_result = sub_result >> 16;
        __asm__ __volatile__("kybermul %0, %1, %2" :  "=r"(temp2) : "r"(zeta), "r"(sub_result));
        temp2 = temp2 << 16;
        temp1 = temp1 | temp2;

        r_word_ptr[j/2] = add_result;
        r_word_ptr[j/2 + len/2] = temp1;

        #else

        t = r[j];
        r[j] = barrett_reduce(t + r[j + len]);
        r[j + len] = r[j + len] - t;
        r[j + len] = fqmul(zeta, r[j + len]);

        #endif

      }

    }
  }

  for(j = 0; j < 256; j++)
    r[j] = fqmul(r[j], f);
}

/*************************************************
* Name:        basemul
*
* Description: Multiplication of polynomials in Zq[X]/(X^2-zeta)
*              used for multiplication of elements in Rq in NTT domain
*
* Arguments:   - int16_t r[2]:       pointer to the output polynomial
*              - const int16_t a[2]: pointer to the first factor
*              - const int16_t b[2]: pointer to the second factor
*              - int16_t zeta:       integer defining the reduction polynomial
**************************************************/
void basemul(int16_t r[2],
             const int16_t a[2],
             const int16_t b[2],
             int16_t zeta)
{
  r[0]  = fqmul(a[1], b[1]);
  r[0]  = fqmul(r[0], zeta);
  #ifdef KYBER_ISE
  __asm__("kyberadd %0, %1, %2" :  "=r"(r[0]) : "r"(r[0]), "r"(fqmul(a[0], b[0])));
  #else
  r[0] += fqmul(a[0], b[0]);
  #endif

  r[1]  = fqmul(a[0], b[1]);
  #ifdef KYBER_ISE
  __asm__("kyberadd %0, %1, %2" :  "=r"(r[1]) : "r"(r[1]), "r"(fqmul(a[1], b[0])));
  #else
  r[1] += fqmul(a[1], b[0]);
  #endif

}
