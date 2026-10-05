/*  test_sha512.c - TinyCrypt implementation of some SHA-512 tests */

/*
 *  Copyright (C) 2020 by Intel Corporation, All Rights Reserved.
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
  This module tests the following SHA512 routines:
  Scenarios tested include:
  - NIST SHA512 test vectors
*/

#include <tinycrypt/sha512.h>
#include <tinycrypt/constants.h>
#include <test_utils.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
 * NIST SHA512 test vector 1.
 */
unsigned int test_1(void)
{
        unsigned int result = TC_PASS;

        puts("SHA512 test #1:\n");
        const uint8_t expected[TC_SHA512_DIGEST_SIZE] = {
            0xdd, 0xaf, 0x35, 0xa1, 0x93, 0x61, 0x7a, 0xba,
            0xcc, 0x41, 0x73, 0x49, 0xae, 0x20, 0x41, 0x31,
            0x12, 0xe6, 0xfa, 0x4e, 0x89, 0xa9, 0x7e, 0xa2,
            0x0a, 0x9e, 0xee, 0xe6, 0x4b, 0x55, 0xd3, 0x9a,
            0x21, 0x92, 0x99, 0x2a, 0x27, 0x4f, 0xc1, 0xa8,
            0x36, 0xba, 0x3c, 0x23, 0xa3, 0xfe, 0xeb, 0xbd,
            0x45, 0x4d, 0x44, 0x23, 0x64, 0x3c, 0xe8, 0x0e,
            0x2a, 0x9a, 0xc9, 0x4f, 0xa5, 0x4c, 0xa4, 0x9f,
        };
        const char *m = "abc";
        uint8_t digest[TC_SHA512_DIGEST_SIZE];
        struct tc_sha512_state_struct s;

        //pcount_reset();
        //pcount_enable(1);
        (void)tc_sha512_init(&s);
        tc_sha512_update(&s, (const uint8_t *) m, strlen(m));
        (void)tc_sha512_final(digest, &s);
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

int main(void)
{
        unsigned int result = TC_PASS;
        puts("Performing SHA512 tests (NIST tests vectors):");

        data_ind_timing_enable(1);

        result = test_1();
        if (result == TC_FAIL) {
                /* terminate test */
                puts("SHA512 test #1 failed.\n");
                goto exitTest;
        }

exitTest:
        // TC_END_RESULT(result);
        if (result == TC_PASS)
            puts("PASS\n");
        else
            puts("FAIL\n");
        return result;
}
