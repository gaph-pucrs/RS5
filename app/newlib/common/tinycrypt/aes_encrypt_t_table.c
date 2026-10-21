/* aes_encrypt.c - TinyCrypt implementation of AES encryption procedure */

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

#include <aes.h>
#include <utils.h>
#include <constants.h>

#include "riscv_crypto.h"

#include <test_utils.h>

#ifdef AES_RISCV_ASM
#include "aes_encrypt_tc.inc"
#else

static const uint32_t Te2[256] = {
	0x63c6a563, 0x7cf8847c, 0x77ee9977, 0x7bf68d7b,
	0xf2ff0df2, 0x6bd6bd6b, 0x6fdeb16f, 0xc59154c5,
	0x30605030, 0x01020301, 0x67cea967, 0x2b567d2b,
	0xfee719fe, 0xd7b562d7, 0xab4de6ab, 0x76ec9a76,
	0xca8f45ca, 0x821f9d82, 0xc98940c9, 0x7dfa877d,
	0xfaef15fa, 0x59b2eb59, 0x478ec947, 0xf0fb0bf0,
	0xad41ecad, 0xd4b367d4, 0xa25ffda2, 0xaf45eaaf,
	0x9c23bf9c, 0xa453f7a4, 0x72e49672, 0xc09b5bc0,
	0xb775c2b7, 0xfde11cfd, 0x933dae93, 0x264c6a26,
	0x366c5a36, 0x3f7e413f, 0xf7f502f7, 0xcc834fcc,
	0x34685c34, 0xa551f4a5, 0xe5d134e5, 0xf1f908f1,
	0x71e29371, 0xd8ab73d8, 0x31625331, 0x152a3f15,
	0x04080c04, 0xc79552c7, 0x23466523, 0xc39d5ec3,
	0x18302818, 0x9637a196, 0x050a0f05, 0x9a2fb59a,
	0x070e0907, 0x12243612, 0x801b9b80, 0xe2df3de2,
	0xebcd26eb, 0x274e6927, 0xb27fcdb2, 0x75ea9f75,
	0x09121b09, 0x831d9e83, 0x2c58742c, 0x1a342e1a,
	0x1b362d1b, 0x6edcb26e, 0x5ab4ee5a, 0xa05bfba0,
	0x52a4f652, 0x3b764d3b, 0xd6b761d6, 0xb37dceb3,
	0x29527b29, 0xe3dd3ee3, 0x2f5e712f, 0x84139784,
	0x53a6f553, 0xd1b968d1, 0x00000000, 0xedc12ced,
	0x20406020, 0xfce31ffc, 0xb179c8b1, 0x5bb6ed5b,
	0x6ad4be6a, 0xcb8d46cb, 0xbe67d9be, 0x39724b39,
	0x4a94de4a, 0x4c98d44c, 0x58b0e858, 0xcf854acf,
	0xd0bb6bd0, 0xefc52aef, 0xaa4fe5aa, 0xfbed16fb,
	0x4386c543, 0x4d9ad74d, 0x33665533, 0x85119485,
	0x458acf45, 0xf9e910f9, 0x02040602, 0x7ffe817f,
	0x50a0f050, 0x3c78443c, 0x9f25ba9f, 0xa84be3a8,
	0x51a2f351, 0xa35dfea3, 0x4080c040, 0x8f058a8f,
	0x923fad92, 0x9d21bc9d, 0x38704838, 0xf5f104f5,
	0xbc63dfbc, 0xb677c1b6, 0xdaaf75da, 0x21426321,
	0x10203010, 0xffe51aff, 0xf3fd0ef3, 0xd2bf6dd2,
	0xcd814ccd, 0x0c18140c, 0x13263513, 0xecc32fec,
	0x5fbee15f, 0x9735a297, 0x4488cc44, 0x172e3917,
	0xc49357c4, 0xa755f2a7, 0x7efc827e, 0x3d7a473d,
	0x64c8ac64, 0x5dbae75d, 0x19322b19, 0x73e69573,
	0x60c0a060, 0x81199881, 0x4f9ed14f, 0xdca37fdc,
	0x22446622, 0x2a547e2a, 0x903bab90, 0x880b8388,
	0x468cca46, 0xeec729ee, 0xb86bd3b8, 0x14283c14,
	0xdea779de, 0x5ebce25e, 0x0b161d0b, 0xdbad76db,
	0xe0db3be0, 0x32645632, 0x3a744e3a, 0x0a141e0a,
	0x4992db49, 0x060c0a06, 0x24486c24, 0x5cb8e45c,
	0xc29f5dc2, 0xd3bd6ed3, 0xac43efac, 0x62c4a662,
	0x9139a891, 0x9531a495, 0xe4d337e4, 0x79f28b79,
	0xe7d532e7, 0xc88b43c8, 0x376e5937, 0x6ddab76d,
	0x8d018c8d, 0xd5b164d5, 0x4e9cd24e, 0xa949e0a9,
	0x6cd8b46c, 0x56acfa56, 0xf4f307f4, 0xeacf25ea,
	0x65caaf65, 0x7af48e7a, 0xae47e9ae, 0x08101808,
	0xba6fd5ba, 0x78f08878, 0x254a6f25, 0x2e5c722e,
	0x1c38241c, 0xa657f1a6, 0xb473c7b4, 0xc69751c6,
	0xe8cb23e8, 0xdda17cdd, 0x74e89c74, 0x1f3e211f,
	0x4b96dd4b, 0xbd61dcbd, 0x8b0d868b, 0x8a0f858a,
	0x70e09070, 0x3e7c423e, 0xb571c4b5, 0x66ccaa66,
	0x4890d848, 0x03060503, 0xf6f701f6, 0x0e1c120e,
	0x61c2a361, 0x356a5f35, 0x57aef957, 0xb969d0b9,
	0x86179186, 0xc19958c1, 0x1d3a271d, 0x9e27b99e,
	0xe1d938e1, 0xf8eb13f8, 0x982bb398, 0x11223311,
	0x69d2bb69, 0xd9a970d9, 0x8e07898e, 0x9433a794,
	0x9b2db69b, 0x1e3c221e, 0x87159287, 0xe9c920e9,
	0xce8749ce, 0x55aaff55, 0x28507828, 0xdfa57adf,
	0x8c038f8c, 0xa159f8a1, 0x89098089, 0x0d1a170d,
	0xbf65dabf, 0xe6d731e6, 0x4284c642, 0x68d0b868,
	0x4182c341, 0x9929b099, 0x2d5a772d, 0x0f1e110f,
	0xb07bcbb0, 0x54a8fc54, 0xbb6dd6bb, 0x162c3a16
};

#ifdef TC_AES_128
int tc_aes128_set_encrypt_key(TCAesKeySched_t s, const uint8_t *k) {
#endif

#ifdef TC_AES_192
int tc_aes192_set_encrypt_key(TCAesKeySched_t s, const uint8_t *k) {
#endif

#ifdef TC_AES_256
int tc_aes256_set_encrypt_key(TCAesKeySched_t s, const uint8_t *k) {
#endif

	//const unsigned int rconst[Nr+1] = RCON;  // Defined in aes.h
	// unsigned int i;
	// unsigned int t;

	if (s == (TCAesKeySched_t) 0)
		return TC_CRYPTO_FAIL;
	else if (k == (const uint8_t *) 0)
		return TC_CRYPTO_FAIL;

	// for (i = 0; i < Nk; ++i)
	// 	s->words[i] = (k[Nb*i] << 24) | (k[Nb*i+1] << 16) | (k[Nb*i+2] << 8) | (k[Nb*i+3]);

	// for (; i < (Nb * (Nr + 1)); ++i) {

	// 	t = s->words[i-1];

	// 	if ((i % Nk) == 0)
	// 		t = subword(rotword(t)) ^ rconst[i/Nk];

    //     #ifdef TC_AES_256
	// 	if ((i % Nk) == 4)
	// 		t = subword(t);
    //     #endif

	// 	s->words[i] = s->words[i-Nk] ^ t;
	// }

	#if defined(TC_AES_128)
		uint32_t w0, w1, w2, w3;
		const uint8_t rconst[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};
	#elif defined(TC_AES_192)
		uint32_t w0, w1, w2, w3, w4, w5;
		const uint8_t rconst[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
	#elif defined(TC_AES_256)
		uint32_t w0, w1, w2, w3, w4, w5, w6, w7;
		const uint8_t rconst[7] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40};
	#endif

	// Copy first Nk words from user key
	w0 = ((uint32_t *) k)[0];
	w1 = ((uint32_t *) k)[1];
	w2 = ((uint32_t *) k)[2];
	w3 = ((uint32_t *) k)[3];
	s->words[0] = w0;
	s->words[1] = w1;
	s->words[2] = w2;
	s->words[3] = w3;
	#if defined(TC_AES_192)
	w4 = ((uint32_t *) k)[4];
	w5 = ((uint32_t *) k)[5];
	s->words[4] = w4;
	s->words[5] = w5;
	#elif defined(TC_AES_256)
	w4 = ((uint32_t *) k)[4];
	w5 = ((uint32_t *) k)[5];
	w6 = ((uint32_t *) k)[6];
	w7 = ((uint32_t *) k)[7];
	s->words[4] = w4;
	s->words[5] = w5;
	s->words[6] = w6;
	s->words[7] = w7;
	#endif

	// Compute Nk key schedule words per loop iteration
	for (int i = 0; i < Nb*Nr/Nk; i++) {

   		uint32_t a2, a3, a4, a5;  // Temps for SubWord()

		#if defined(TC_AES_128)
			#define W_i_minus_1 w3
		#elif defined(TC_AES_192)
			#define W_i_minus_1 w5
		#elif defined(TC_AES_256)
			#define W_i_minus_1 w7
		#endif

		// a5 = (*t3 << 4) & 0xff0;
		a5 = ((uint8_t *) Te2)[(W_i_minus_1 << 2) & 0x3fc];
		a2 = ((uint8_t *) Te2)[(W_i_minus_1 >> 6) & 0x3fc];
		a3 = ((uint8_t *) Te2)[(W_i_minus_1 >> 14) & 0x3fc];
		a4 = ((uint8_t *) Te2)[(W_i_minus_1 >> 22) & 0x3fc];

		w0 ^= ((uint32_t) rconst[i]);
		w0 ^= a2;
		w0 ^= (a3 << 8);
		w0 ^= (a4 << 16);
		w0 ^= (a5 << 24);

		w1 ^= w0;
		w2 ^= w1;
		w3 ^= w2;
		#if defined(TC_AES_192)
		w4 ^= w3;
		w5 ^= w4;
		#elif defined(TC_AES_256)
		a5 = ((uint8_t *) Te2)[(w3 << 2) & 0x3fc];
		a2 = ((uint8_t *) Te2)[(w3 >> 6) & 0x3fc];
		a3 = ((uint8_t *) Te2)[(w3 >> 14) & 0x3fc];
		a4 = ((uint8_t *) Te2)[(w3 >> 22) & 0x3fc];
		w4 ^= a5 ^ (a2 << 8) ^ (a3 << 16) ^ (a4 << 24);
		w5 ^= w4;
		w6 ^= w5;
		w7 ^= w6;
		#endif

		s->words[Nk*i + Nk] = w0;
		s->words[Nk*i+1 + Nk] = w1;
		s->words[Nk*i+2 + Nk] = w2;
		s->words[Nk*i+3 + Nk] = w3;
		#if defined(TC_AES_192)
		s->words[Nk*i+4 + Nk] = w4;
		s->words[Nk*i+5 + Nk] = w5;
		#elif defined(TC_AES_256)
		if (i == Nb*Nr/Nk - 1)
			break;
		s->words[Nk*i+4 + Nk] = w4;
		s->words[Nk*i+5 + Nk] = w5;
		s->words[Nk*i+6 + Nk] = w6;
		s->words[Nk*i+7 + Nk] = w7;
		#endif

		// puts("Iteration ");
		// puthex(i+1);
		// puts(": \n");
		// puts("w0 = ");
		// puthex(w0);
		// puts("\n");
		// puts("w1 = ");
		// puthex(w1);
		// puts("\n");
		// puts("w2 = ");
		// puthex(w2);
		// puts("\n");
		// puts("w3 = ");
		// puthex(w3);
		// puts("\n");
		// puts("w4 = ");
		// puthex(w4);
		// puts("\n");
		// puts("w5 = ");
		// puthex(w5);
		// puts("\n");
		// puts("w6 = ");
		// puthex(w6);
		// puts("\n");
		// puts("w7 = ");
		// puthex(w7);
		// puts("\n");

		// puts("Iteration ");
		// puthex(i+1);
		// puts(" (from mem): \n");
		// puts("w0 = ");
		// puthex(s->words[Nk*i + Nk]);
		// puts("\n");
		// puts("w1 = ");
		// puthex(s->words[Nk*i + Nk + 1]);
		// puts("\n");
		// puts("w2 = ");
		// puthex(s->words[Nk*i + Nk + 2]);
		// puts("\n");
		// puts("w3 = ");
		// puthex(s->words[Nk*i + Nk + 3]);
		// puts("\n");
		// puts("w4 = ");
		// puthex(s->words[Nk*i + Nk + 4]);
		// puts("\n");
		// puts("w5 = ");
		// puthex(s->words[Nk*i + Nk + 5]);
		// puts("\n");
		// puts("w6 = ");
		// puthex(s->words[Nk*i + Nk + 6]);
		// puts("\n");
		// puts("w7 = ");
		// puthex(s->words[Nk*i + Nk + 7]);
		// puts("\n");

	}

	return TC_CRYPTO_SUCCESS;
}

int tc_aes_encrypt(uint8_t *out, const uint8_t *in, const TCAesKeySched_t s) {

	if (out == (uint8_t *) 0) {
		return TC_CRYPTO_FAIL;
	} else if (in == (const uint8_t *) 0) {
		return TC_CRYPTO_FAIL;
	} else if (s == (TCAesKeySched_t) 0) {
		return TC_CRYPTO_FAIL;
	}

    uint32_t i0, i1, i2, i3;
    uint32_t k0, k1, k2, k3;
    uint32_t T0, T1, T2, T3;  // Temporaries for each column

    uint32_t* rk = (uint32_t *) s->words;

    // load table address once
    const uint32_t* Te2_ptr = Te2;
    // const uint8_t* Te2_byte_ptr = (uint8_t *) Te2;
    // const uint8_t *lut1 = lut0 + 4;   // Equivalent to Te0
    // const uint8_t *lut2 = lut0 + 8;   // Equivalent to Te3
    // const uint8_t *lut3 = lut0 + 12;  // Equivalent to Te1
    uint32_t mask = 0xff;

    // load input                                [31:24] [23:16] [15:8] [7:0]
    i0 = *((uint32_t *)in);         // Column 0 ( a3,0  | a2,0  | a1,0 | a0,0)
    i1 = *((uint32_t *)(in + 4));   // Column 1 ( a3,1  | a2,1  | a1,1 | a0,1)
    i2 = *((uint32_t *)(in + 8));   // Column 2 ( a3,2  | a2,2  | a1,2 | a0,2)
    i3 = *((uint32_t *)(in + 12));  // Column 3 ( a3,3  | a2,3  | a1,3 | a0,3)

    // load key
    k0 = rk[0];
    k1 = rk[1];
    k2 = rk[2];
    k3 = rk[3];
    // rk += 16;
    rk += 4;

    // first AddRoundKey
    i0 ^= k0;
    i1 ^= k1;
    i2 ^= k2;
    i3 ^= k3;

    for (int i = 0; i < Nr - 1; i++, rk += 4) {
    // for (int i = 0; i < Nr - 1; i++, rk += 16) {

        // round_C(&i0, &i1, &i2, &i3, ((uint32_t *)rk) + 4,  lut0, lut1, lut2, lut3, mask);

        // while LUT0, LUT1, LUT2, LUT3 are actually uint32_t, we consider them as
        // uint8_t to avoid processing of index values multiple times

		// puts("Round ");
		// puthex(i+1);
		// puts(": (input state)\n");
		// puts("i0 = ");
		// puthex(i0);
		// puts("\n");
		// puts("i1 = ");
		// puthex(i1);
		// puts("\n");
		// puts("i2 = ");
		// puthex(i2);
		// puts("\n");
		// puts("i3 = ");
		// puthex(i3);
		// puts("\n");

		// From AES original NIST submission, Subsection 5.2.1:
		// (https://csrc.nist.gov/csrc/media/projects/cryptographic-standards-and-guidelines/documents/aes-development/rijndael-ammended.pdf)
		// e0 = T0[a0,0] ^ T1[a1,3] ^ T2[a2,3] ^ T3[a3,3] ^ k0
		// e1 = T0[a0,1] ^ T1[a1,0] ^ T2[a2,3] ^ T3[a3,2] ^ k1
		// e2 = T0[a0,2] ^ T1[a1,1] ^ T2[a2,0] ^ T3[a3,3] ^ k2
		// e3 = T0[a0,3] ^ T1[a1,2] ^ T2[a2,1] ^ T3[a3,0] ^ k3

		// T0[a] == ROTL(T2[a], 16)
		// T1[a] == ROTL(T2[a], 24)
		// T3[a] == ROTL(T2[a], 8)

		// aw,z = Row W, Column Z
		// Compute column 0 (d0 = T0[a0,0] ^ T1[a1,1] ^ T2[a2,2] ^ T3[a3,3])
		T0 = _rv32_rol(Te2_ptr[i0 & mask], 16);          // T0[a0,0]
		T0 ^= _rv32_rol(Te2_ptr[(i1 >> 8) & mask], 24);  // T1[a1,1]
		T0 ^= Te2_ptr[(i2 >> 16) & mask];                  // T2[a2,2]
		T0 ^= _rv32_rol(Te2_ptr[(i3 >> 24) & mask], 8);  // T3[a3,3]

		// Compute column 1 (d1 = T0[a0,1] ^ T1[a1,2] ^ T2[a2,3] ^ T3[a3,0])
		T1 = _rv32_rol(Te2_ptr[i1 & mask], 16);          // T0[a0,1]
		T1 ^= _rv32_rol(Te2_ptr[(i2 >> 8) & mask], 24);  // T1[a1,2]
		T1 ^= Te2_ptr[(i3 >> 16) & mask];                  // T2[a2,3]
		T1 ^= _rv32_rol(Te2_ptr[(i0 >> 24) & mask], 8);  // T3[a3,0]

		// Compute column 2 (d2 = T0[a0,2] ^ T1[a1,3] ^ T2[a2,0] ^ T3[a3,1])
		T2 = _rv32_rol(Te2_ptr[i2 & mask], 16);          // T0[a0,2]
		T2 ^= _rv32_rol(Te2_ptr[(i3 >> 8) & mask], 24);  // T1[a1,3]
		T2 ^= Te2_ptr[(i0 >> 16) & mask];                  // T2[a2,0]
		T2 ^= _rv32_rol(Te2_ptr[(i1 >> 24) & mask], 8);  // T3[a3,1]

		// Compute column 3 (d3 = T0[a0,3] ^ T1[a1,0] ^ T2[a2,1] ^ T3[a3,2])
		T3 = _rv32_rol(Te2_ptr[i3 & mask], 16);          // T0[a0,3]
		T3 ^= _rv32_rol(Te2_ptr[(i0 >> 8) & mask], 24);  // T1[a1,0]
		T3 ^= Te2_ptr[(i1 >> 16) & mask];                  // T2[a2,1]
		T3 ^= _rv32_rol(Te2_ptr[(i2 >> 24) & mask], 8);  // T3[a3,3]

		// puts("T0[ ");
		// puthex(i0 & mask);
		// puts("] = ");
		// puthex(_rv32_rol(Te2_ptr[i0 & mask], 16));
		// puts("\n");
		// puts("T1[ ");
		// puthex((i1 >> 8) & mask);
		// puts("] = ");
		// puthex(_rv32_rol(Te2_ptr[(i1 >> 8) & mask], 24));
		// puts("\n");
		// puts("T2[ ");
		// puthex((i2 >> 16) & mask);
		// puts("] = ");
		// puthex(Te2_ptr[(i2 >> 16) & mask]);
		// puts("\n");
		// puts("T3[ ");
		// puthex((i3 >> 24) & mask);
		// puts("] = ");
		// puthex(Te2_ptr[(i3 >> 24) & mask]);
		// puts("\n");

		// puts("Round ");
		// puthex(i+1);
		// puts(": (after MixColumns)\n");
		// puts("T0 = ");
		// puthex(T0);
		// puts("\n");
		// puts("T1 = ");
		// puthex(T1);
		// puts("\n");
		// puts("T2 = ");
		// puthex(T2);
		// puts("\n");
		// puts("T3 = ");
		// puthex(T3);
		// puts("\n");

		// puts("Round ");
		// puthex(i+1);
		// puts(": (round key)\n");
		// puts("rk[0] = ");
		// puthex(rk[0]);
		// puts("\n");
		// puts("rk[1] = ");
		// puthex(rk[1]);
		// puts("\n");
		// puts("rk[2] = ");
		// puthex(rk[2]);
		// puts("\n");
		// puts("rk[3] = ");
		// puthex(rk[3]);
		// puts("\n");

		i0 = T0 ^ rk[0];
		i1 = T1 ^ rk[1];
		i2 = T2 ^ rk[2];
		i3 = T3 ^ rk[3];

		// puts("Round ");
		// puthex(i+1);
		// puts(": (final state)\n");
		// puts("i0 = ");
		// puthex(i0);
		// puts("\n");
		// puts("i1 = ");
		// puthex(i1);
		// puts("\n");
		// puts("i2 = ");
		// puthex(i2);
		// puts("\n");
		// puts("i3 = ");
		// puthex(i3);
		// puts("\n");

    }

	mask = 0x3fc;

    // final round (no MixColumns(), must be outside the loop)
    // T0 = Te2_byte_ptr[i0 & 0xff];
    // T1 = Te2_byte_ptr[(i1 << 4) & 0xff];
    // T2 = Te2_byte_ptr[(i2 << 4) & 0xff];
    // T3 = Te2_byte_ptr[(i3 << 4) & 0xff];

	// SubBytes and ShiftRows for first byte in all columns
    T0 = ((uint8_t*) Te2_ptr)[(i0 << 2) & mask];
    T1 = ((uint8_t*) Te2_ptr)[(i1 << 2) & mask];
    T2 = ((uint8_t*) Te2_ptr)[(i2 << 2) & mask];
    T3 = ((uint8_t*) Te2_ptr)[(i3 << 2) & mask];

	// SubBytes and ShiftRows for second byte in all columns
    T0 ^= ((uint8_t*) Te2_ptr)[(i1 >> 6) & mask] << 8;
    T1 ^= ((uint8_t*) Te2_ptr)[(i2 >> 6) & mask] << 8;
    T2 ^= ((uint8_t*) Te2_ptr)[(i3 >> 6) & mask] << 8;
    T3 ^= ((uint8_t*) Te2_ptr)[(i0 >> 6) & mask] << 8;

	// SubBytes and ShiftRows for third byte in all columns
    T0 ^= ((uint8_t*) Te2_ptr)[(i2 >> 14) & mask] << 16;
    T1 ^= ((uint8_t*) Te2_ptr)[(i3 >> 14) & mask] << 16;
    T2 ^= ((uint8_t*) Te2_ptr)[(i0 >> 14) & mask] << 16;
    T3 ^= ((uint8_t*) Te2_ptr)[(i1 >> 14) & mask] << 16;

	// SubBytes and ShiftRows for fourth byte in all columns
    T0 ^= ((uint8_t*) Te2_ptr)[(i3 >> 22) & mask] << 24;
    T1 ^= ((uint8_t*) Te2_ptr)[(i0 >> 22) & mask] << 24;
    T2 ^= ((uint8_t*) Te2_ptr)[(i1 >> 22) & mask] << 24;
    T3 ^= ((uint8_t*) Te2_ptr)[(i2 >> 22) & mask] << 24;

    // i0 = ((uint32_t *)rk)[40];
    // i1 = ((uint32_t *)rk)[41];
    // i2 = ((uint32_t *)rk)[42];
    // i3 = ((uint32_t *)rk)[43];

    // i0 = T0 ^ ((uint32_t *)rk)[0];
    // i1 = T1 ^ ((uint32_t *)rk)[1];
    // i2 = T2 ^ ((uint32_t *)rk)[2];
    // i3 = T3 ^ ((uint32_t *)rk)[3];

    // final AddRoundKey and store output
    ((uint32_t *) out)[0] = T0 ^ ((uint32_t *)rk)[0];
    ((uint32_t *) out)[1] = T1 ^ ((uint32_t *)rk)[1];
    ((uint32_t *) out)[2] = T2 ^ ((uint32_t *)rk)[2];
    ((uint32_t *) out)[3] = T3 ^ ((uint32_t *)rk)[3];

	return TC_CRYPTO_SUCCESS;
}

#endif
