#include <stdint.h>
#include "params.h"
#include "cbd.h"

/*************************************************
* Name:        load32_littleendian
*
* Description: load 4 bytes into a 32-bit integer
*              in little-endian order
*
* Arguments:   - const uint8_t *x: pointer to input byte array
*
* Returns 32-bit unsigned integer loaded from x
**************************************************/
static uint32_t load32_littleendian(const uint8_t x[4])
{
  uint32_t r;
  r  = (uint32_t)x[0];
  r |= (uint32_t)x[1] << 8;
  r |= (uint32_t)x[2] << 16;
  r |= (uint32_t)x[3] << 24;
  return r;
}

/*************************************************
* Name:        load24_littleendian
*
* Description: load 3 bytes into a 32-bit integer
*              in little-endian order
*              This function is only needed for Kyber-512
*
* Arguments:   - const uint8_t *x: pointer to input byte array
*
* Returns 32-bit unsigned integer loaded from x (most significant byte is zero)
**************************************************/
#if KYBER_ETA1 == 3
static uint32_t load24_littleendian(const uint8_t x[3])
{
  uint32_t r;
  r  = (uint32_t)x[0];
  r |= (uint32_t)x[1] << 8;
  r |= (uint32_t)x[2] << 16;
  return r;
}
#endif


/*************************************************
* Name:        cbd2
*
* Description: Given an array of uniformly random bytes, compute
*              polynomial with coefficients distributed according to
*              a centered binomial distribution with parameter eta=2
*
* Arguments:   - poly *r:            pointer to output polynomial
*              - const uint8_t *buf: pointer to input byte array
**************************************************/
static void cbd2(poly *r, const uint8_t buf[2*KYBER_N/4])
{
  unsigned int i,j;
  uint32_t t,d;
  int16_t a,b;

  for (i=0;i<KYBER_N/8;i++) {

    t  = load32_littleendian(buf+4*i);

    #ifdef KYBER_ISE

    uint32_t* r_ptr = ((uint32_t *) r->coeffs);
    uint32_t asm_val;

    for (j = 0; j < 4; j++, t = t >> 8) {

      __asm__("kybercbd2 %0, %1" :  "=r"(asm_val) : "r"(t));

      #ifdef KYBER_ISE_DEBUG

      int32_t ref_val, a_high, b_high, a_low, b_low, sample_high, sample_low;

      b_high = (t >> 6) & 0x3;
      a_high = (t >> 4) & 0x3;
      b_low = (t >> 2) & 0x3;
      a_low = (t >> 0) & 0x3;

      b_high = (b_high & 1) + ((b_high >> 1) & 1);
      a_high = (a_high & 1) + ((a_high >> 1) & 1);
      b_low = (b_low & 1) + ((b_low >> 1) & 1);
      a_low = (a_low & 1) + ((a_low >> 1) & 1);

      sample_high = (a_high - b_high) < 0 ? a_high - b_high + KYBER_Q : a_high - b_high;
      sample_low = (a_low - b_low) < 0 ? a_low - b_low + KYBER_Q : a_low - b_low;

      ref_val = (sample_high << 16) | sample_low;

      if (rvkat_chku32("kybercbd2", ref_val, asm_val))
        __asm__ volatile ("ebreak");

      #endif

      r_ptr[4*i + j] = asm_val;

    }

    #else

    d  = t & 0x55555555;
    d += (t>>1) & 0x55555555;

    for(j=0;j<8;j++) {
      a = (d >> (4*j+0)) & 0x3;
      b = (d >> (4*j+2)) & 0x3;
      r->coeffs[8*i+j] = a - b;
    }

    #endif

  }
}

/*************************************************
* Name:        cbd3
*
* Description: Given an array of uniformly random bytes, compute
*              polynomial with coefficients distributed according to
*              a centered binomial distribution with parameter eta=3
*              This function is only needed for Kyber-512
*
* Arguments:   - poly *r:            pointer to output polynomial
*              - const uint8_t *buf: pointer to input byte array
**************************************************/
#if KYBER_ETA1 == 3
static void cbd3(poly *r, const uint8_t buf[3*KYBER_N/4])
{
  unsigned int i,j;
  uint32_t t,d;
  int16_t a,b;

  for(i=0;i<KYBER_N/4;i++) {
    t  = load24_littleendian(buf+3*i);

  #ifdef KYBER_ISE

    uint32_t* r_ptr = ((uint32_t *) r->coeffs);
    uint32_t asm_val;

    for (j = 0; j < 2; j++, t = t >> 12) {

      __asm__("kybercbd3 %0, %1" :  "=r"(asm_val) : "r"(t));

      #ifdef KYBER_ISE_DEBUG

      int32_t ref_val, a_high, b_high, a_low, b_low, sample_high, sample_low;

      b_high = (t >> 9) & 0x7;
      a_high = (t >> 6) & 0x7;
      b_low = (t >> 3) & 0x7;
      a_low = (t >> 0) & 0x7;

      b_high = (b_high & 1) + ((b_high >> 1) & 1) + ((b_high >> 2) & 1);
      a_high = (a_high & 1) + ((a_high >> 1) & 1) + ((a_high >> 2) & 1);
      b_low = (b_low & 1) + ((b_low >> 1) & 1) + ((b_low >> 2) & 1);
      a_low = (a_low & 1) + ((a_low >> 1) & 1) + ((a_low >> 2) & 1);

      //sample_high = ((a_high - b_high) < 0) ? a_high - b_high + KYBER_Q : a_high - b_high;
      sample_high = a_high - b_high;
      sample_high = (sample_high < 0) ? sample_high + KYBER_Q : sample_high;
      //sample_low = ((a_low - b_low) < 0) ? a_low - b_low + KYBER_Q : a_low - b_low;
      sample_low = a_low - b_low;
      sample_low = (sample_low < 0) ? sample_low + KYBER_Q : sample_low;

      ref_val = (sample_high << 16) | (sample_low & 0x0000FFFF);

      if (rvkat_chku32("kybercbd3", ref_val, asm_val))
        __asm__ volatile ("ebreak");

      #endif

      r_ptr[2*i + j] = asm_val;

    }

  #else

    d  = t & 0x00249249;
    d += (t>>1) & 0x00249249;
    d += (t>>2) & 0x00249249;

    for(j=0;j<4;j++) {
      a = (d >> (6*j+0)) & 0x7;
      b = (d >> (6*j+3)) & 0x7;
      r->coeffs[4*i+j] = a - b;
    }

  #endif

  }

}
#endif

void cbd_eta1(poly *r, const uint8_t buf[KYBER_ETA1*KYBER_N/4])
{
#if KYBER_ETA1 == 2
  cbd2(r, buf);
#elif KYBER_ETA1 == 3
  cbd3(r, buf);
#else
#error "This implementation requires eta1 in {2,3}"
#endif
}

void cbd_eta2(poly *r, const uint8_t buf[KYBER_ETA1*KYBER_N/4])
{
#if KYBER_ETA2 != 2
#error "This implementation requires eta2 = 2"
#else
  cbd2(r, buf);
#endif
}
