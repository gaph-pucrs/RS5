/* test_aes.c - TinyCrypt AES-128 tests (including NIST tests) */

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

/*
 * DESCRIPTION
 * This module tests the following AES routines:
 *
 * Scenarios tested include:
 * - AES128 NIST key schedule test
 * - AES128 NIST encryption test
 * - AES128 NIST fixed-key and variable-text
 * - AES128 NIST variable-key and fixed-text
 */

#include "tinycrypt/include/aes.h"
#include "tinycrypt/include/constants.h"
#include "tinycrypt/include/test_utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdint.h>
#include <stddef.h>

#define NUM_OF_NIST_KEYS 16
#define NUM_OF_FIXED_KEYS 128


struct kat_table {
	uint8_t in[NUM_OF_NIST_KEYS];
	uint8_t out[NUM_OF_NIST_KEYS];
};

/*
 * NIST test key schedule.
 */
int test_1(void)
{
	int result = TC_PASS;
    int ret;
	const uint8_t nist_key[NUM_OF_NIST_KEYS] = {
		0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
		0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
	};
	const struct tc_aes_key_sched_struct expected = {
		{
			0x2b7e1516, 0x28aed2a6, 0xabf71588, 0x09cf4f3c,
			0xa0fafe17, 0x88542cb1, 0x23a33939, 0x2a6c7605,
			0xf2c295f2, 0x7a96b943, 0x5935807a, 0x7359f67f,
			0x3d80477d, 0x4716fe3e, 0x1e237e44, 0x6d7a883b,
			0xef44a541, 0xa8525b7f, 0xb671253b, 0xdb0bad00,
			0xd4d1c6f8, 0x7c839d87, 0xcaf2b8bc, 0x11f915bc,
			0x6d88a37a, 0x110b3efd, 0xdbf98641, 0xca0093fd,
			0x4e54f70e, 0x5f5fc9f3, 0x84a64fb2, 0x4ea6dc4f,
			0xead27321, 0xb58dbad2, 0x312bf560, 0x7f8d292f,
			0xac7766f3, 0x19fadc21, 0x28d12941, 0x575c006e,
			0xd014f9a8, 0xc9ee2589, 0xe13f0cc8, 0xb6630ca6
		}
	};
	struct tc_aes_key_sched_struct s;

	printf("AES128 (NIST key schedule test):\n");

    ret = tc_aes128_set_encrypt_key(&s, nist_key);

	if (ret== 0) {
		printf("AES128 test (NIST key schedule test) failed.\n");
		result = TC_FAIL;
		goto exitTest1;
	}

	result = check_result(1, expected.words, sizeof(expected.words), s.words,
			      sizeof(s.words));

exitTest1:
    if (result == TC_PASS)
        printf("PASS\n");
    else
        printf("FAIL\n");
	return result;
}

/*
 * NIST test vectors for encryption.
 */
int test_2(void)
{
	int result = TC_PASS;
    int ret;
	const uint8_t nist_key[NUM_OF_NIST_KEYS] = {
		0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
		0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
	};
	const uint8_t nist_input[NUM_OF_NIST_KEYS] = {
		0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d,
		0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34
	};
	const uint8_t expected[NUM_OF_NIST_KEYS] = {
		0x39, 0x25, 0x84, 0x1d, 0x02, 0xdc, 0x09, 0xfb,
		0xdc, 0x11, 0x85, 0x97, 0x19, 0x6a, 0x0b, 0x32
	};
	struct tc_aes_key_sched_struct s;
	uint8_t ciphertext[NUM_OF_NIST_KEYS];

	printf("AES128 (NIST encryption test):\n");

	(void)tc_aes128_set_encrypt_key(&s, nist_key);
    ret = tc_aes_encrypt(ciphertext, nist_input, &s);

	if (ret == 0) {
		printf("AES128 %s (NIST encryption test) failed.\n");
		result = TC_FAIL;
		goto exitTest2;
	}

	result = check_result(2, expected, sizeof(expected), ciphertext,
			      sizeof(ciphertext));

exitTest2:
    if (result == TC_PASS)
        printf("PASS\n");
    else
        printf("FAIL\n");

	return result;
}

int kmain(void)
{
	int result = TC_PASS;

    // data_ind_timing_enable(1);

	result = test_2();
	if (result == TC_FAIL) { /* terminate test */
		printf("AES128 test #2 (NIST encryption test) failed.\n");
		goto exitTest;
	}
 exitTest:
	return result;
}
