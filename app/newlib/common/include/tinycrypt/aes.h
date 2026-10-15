/* aes.h - TinyCrypt interface to an AES-128 implementation */

/*
 *  Copyright (C) 2017 by Intel Corporation, All Rights Reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *    - Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *    - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    - Neither the name of Intel Corporation nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief -- Interface to an AES-128 implementation.
 *
 *  Overview:   AES-128 is a NIST approved block cipher specified in
 *              FIPS 197. Block ciphers are deterministic algorithms that
 *              perform a transformation specified by a symmetric key in fixed-
 *              length data sets, also called blocks.
 *
 *  Security:   AES-128 provides approximately 128 bits of security.
 *
 *  Usage:      1) call tc_aes128_set_encrypt/decrypt_key to set the key.
 *
 *              2) call tc_aes_encrypt/decrypt to process the data.
 */

#ifndef __TC_AES_H__
#define __TC_AES_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef TC_AES_128
    #define Nk (4)  /* number of 32-bit words comprising the key */
    #define Nr (10) /* number of rounds */
    #define	RCON {0x00000000, 0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000}
    #define	RCON_ASM {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36}
    #define RCON_DIM 10
#elif TC_AES_192
    #define Nk (6)  /* number of 32-bit words comprising the key */
    #define Nr (12) /* number of rounds */
    #define	RCON {0x00000000, 0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000}
    #define	RCON_ASM {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80}
    #define RCON_DIM 8
#elif TC_AES_256
    #define Nk (8)  /* number of 32-bit words comprising the key */
    #define Nr (14) /* number of rounds */
    #define	RCON {0x00000000, 0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000}
    #define	RCON_ASM {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40}
    #define RCON_DIM 7
#endif

#define Nb (4)  /* number of columns (32-bit words) comprising the state */

#define TC_AES_BLOCK_SIZE (4*Nb)
#define TC_AES_KEY_SIZE (Nb*Nk)

typedef struct tc_aes_key_sched_struct {
	unsigned int words[Nb*(Nr+1)];
} *TCAesKeySched_t;

/**
 *  @brief Set AES-128 encryption key
 *  Uses key k to initialize s
 *  @return  returns TC_CRYPTO_SUCCESS (1)
 *           returns TC_CRYPTO_FAIL (0) if: s == NULL or k == NULL
 *  @note       This implementation skips the additional steps required for keys
 *              larger than 128 bits, and must not be used for AES-192 or
 *              AES-256 key schedule -- see FIPS 197 for details
 *  @param      s IN/OUT -- initialized struct tc_aes_key_sched_struct
 *  @param      k IN -- points to the AES key
 */
#ifdef TC_AES_128
int tc_aes128_set_encrypt_key(TCAesKeySched_t s, const uint8_t *k);
#elifdef TC_AES_192
int tc_aes192_set_encrypt_key(TCAesKeySched_t s, const uint8_t *k);
#elifdef TC_AES_256
int tc_aes256_set_encrypt_key(TCAesKeySched_t s, const uint8_t *k);
#endif

/**
 *  @brief AES-128 Encryption procedure
 *  Encrypts contents of in buffer into out buffer under key;
 *              schedule s
 *  @note Assumes s was initialized by aes_set_encrypt_key;
 *              out and in point to 16 byte buffers
 *  @return  returns TC_CRYPTO_SUCCESS (1)
 *           returns TC_CRYPTO_FAIL (0) if: out == NULL or in == NULL or s == NULL
 *  @param out IN/OUT -- buffer to receive ciphertext block
 *  @param in IN -- a plaintext block to encrypt
 *  @param s IN -- initialized AES key schedule
 */

int tc_aes_encrypt(uint8_t *out, const uint8_t *in, 
		   const TCAesKeySched_t s);

#ifdef __cplusplus
}
#endif

#endif /* __TC_AES_H__ */
