/*  test_sha256.c - TinyCrypt implementation of some SHA-256 tests */

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
  DESCRIPTION
  This module tests the following SHA256 routines:

  Scenarios tested include:
  - NIST SHA256 test vectors
*/

#include <tinycrypt/sha256.h>
#include <tinycrypt/constants.h>
#include <test_utils.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
 * NIST SHA256 test vector 1.
 */
unsigned int test_1(void)
{
        unsigned int result = TC_PASS;

        puts("SHA256 test #1: ");
        const uint8_t expected[32] = {
		0xba, 0x78, 0x16, 0xbf, 0x8f, 0x01, 0xcf, 0xea, 0x41, 0x41, 0x40, 0xde,
		0x5d, 0xae, 0x22, 0x23, 0xb0, 0x03, 0x61, 0xa3, 0x96, 0x17, 0x7a, 0x9c,
		0xb4, 0x10, 0xff, 0x61, 0xf2, 0x00, 0x15, 0xad
        };
        const char *m = "abc";
        uint8_t digest[32];
        struct tc_sha256_state_struct s;

        //pcount_reset();
        //pcount_enable(1);
        (void)tc_sha256_init(&s);
        tc_sha256_update(&s, (const uint8_t *) m, strlen(m));
        (void)tc_sha256_final(digest, &s);
        //pcount_reset();
        //pcount_enable(0);

        result = check_result(1, expected, sizeof(expected),
			      digest, sizeof(digest));
        
        // TC_END_RESULT(result);
        if (result == TC_PASS)
            puts("PASS\n");
        else
            puts("FAIL\n");

        return result;
}

int main(void) {
        unsigned int result = TC_PASS;

        //pcount_enable(0);
        //pcount_reset();
        //pcount_enable(1);
        //data_ind_timing_enable(1);

        puts("Performing SHA256 tests (NIST tests vectors):\n\n");
        result = test_1();
        if (result == TC_FAIL) {
		/* terminate test */
                puts("SHA256 test #1 failed.\n");
                goto exitTest;
        }

        puts("All SHA256 tests succeeded!\n");

exitTest:
        return 0;
}

