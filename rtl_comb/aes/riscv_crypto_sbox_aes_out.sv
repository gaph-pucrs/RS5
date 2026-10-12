//    sboxes.v
//    2020-01-29    Markku-Juhani O. Saarinen <mjos@pqshield.com>
//    Copyright (c) 2020, PQShield Ltd. All rights reserved.

/*

    Non-hardened combinatorial logic for AES, inverse AES, and SM4 S-Boxes.

    Each S-Box has a nonlinear middle layer sandwitched between linear
    top and bottom layers. In this version the top ("inner") layer expands
    8 bits to 21 bits while the bottom layer compresses 18 bits back to 8.

    Overall structure and AES and AES^-1 slightly modified from [BoPe12].
    SM4 top and bottom layers by Markku-Juhani O. Saarinen, January 2020.

    The middle layer is common between all; the beneficiality of muxing it
    depends on target. Currently we are not doing it.

    How? Because all of these are "Nyberg S-boxes" [Ny93]; built from a
    multiplicative inverse in GF(256) and are therefore affine isomorphic.

    [BoPe12] Boyar J., Peralta R. "A Small Depth-16 Circuit for the AES
    S-Box." Proc.SEC 2012. IFIP AICT 376. Springer, pp. 287-298 (2012)
    DOI: https://doi.org/10.1007/978-3-642-30436-1_24
    Preprint: https://eprint.iacr.org/2011/332.pdf

    [Ny93] Nyberg K., "Differentially Uniform Mappings for Cryptography",
    Proc. EUROCRYPT '93, LNCS 765, Springer, pp. 55-64 (1993)
    DOI: https://doi.org/10.1007/3-540-48285-7_6

*/

//
//    bottom (outer) linear layer for AES
module riscv_crypto_sbox_aes_out (
    input   [17:0] x,
    output  [ 7:0] y
);

    wire    t0   = x[11] ^  x[12];
    wire    t1   = x[0]  ^  x[6];
    wire    t2   = x[14] ^  x[16];
    wire    t3   = x[15] ^  x[5];
    wire    t4   = x[4]  ^  x[8];
    wire    t5   = x[17] ^  x[11];
    wire    t6   = x[12] ^  t5;
    wire    t7   = x[14] ^  t3;
    wire    t8   = x[1]  ^  x[9];
    wire    t9   = x[2]  ^  x[3];
    wire    t10  = x[3]  ^  t4;
    wire    t11  = x[10] ^  t2;
    wire    t12  = x[16] ^  x[1];
    wire    t13  = x[0]  ^  t0;
    wire    t14  = x[2]  ^  x[11];
    wire    t15  = x[5]  ^  t1;
    wire    t16  = x[6]  ^  t0;
    wire    t17  = x[7]  ^  t1;
    wire    t18  = x[8]  ^  t8;
    wire    t19  = x[13] ^  t4;
    wire    t20  = t0    ^  t1;
    wire    t21  = t1    ^  t7;
    wire    t22  = t3    ^  t12;
    wire    t23  = t18   ^  t2;
    wire    t24  = t15   ^  t9;
    wire    t25  = t6    ^  t10;
    wire    t26  = t7    ^  t9;
    wire    t27  = t8    ^  t10;
    wire    t28  = t11   ^  t14;
    wire    t29  = t11   ^  t17;
    assign  y[0] = t6    ^~ t23;
    assign  y[1] = t13   ^~ t27;
    assign  y[2] = t25   ^  t29;
    assign  y[3] = t20   ^  t22;
    assign  y[4] = t6    ^  t21;
    assign  y[5] = t19   ^~ t28;
    assign  y[6] = t16   ^~ t26;
    assign  y[7] = t6    ^  t24;

endmodule
