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
//    The shared non-linear middle part for AES, AES^-1, and SM4.
module riscv_crypto_sbox_inv_mid (
    input   [20:0] x,
    output  [17:0] y
);

    wire    t0  = x[ 3] ^  x[12];
    wire    t1  = x[ 9] &  x[ 5];
    wire    t2  = x[17] &  x[ 6];
    wire    t3  = x[10] ^  t1   ;
    wire    t4  = x[14] &  x[ 0];
    wire    t5  = t4    ^  t1   ;
    wire    t6  = x[ 3] &  x[12];
    wire    t7  = x[16] &  x[ 7];
    wire    t8  = t0    ^  t6   ;
    wire    t9  = x[15] &  x[13];
    wire    t10 = t9    ^  t6   ;
    wire    t11 = x[ 1] &  x[11];
    wire    t12 = x[ 4] &  x[20];
    wire    t13 = t12   ^  t11  ;
    wire    t14 = x[ 2] &  x[ 8];
    wire    t15 = t14   ^  t11  ;
    wire    t16 = t3    ^  t2   ;
    wire    t17 = t5    ^  x[18];
    wire    t18 = t8    ^  t7   ;
    wire    t19 = t10   ^  t15  ;
    wire    t20 = t16   ^  t13  ;
    wire    t21 = t17   ^  t15  ;
    wire    t22 = t18   ^  t13  ;
    wire    t23 = t19   ^  x[19];
    wire    t24 = t22   ^  t23  ;
    wire    t25 = t22   &  t20  ;
    wire    t26 = t21   ^  t25  ;
    wire    t27 = t20   ^  t21  ;
    wire    t28 = t23   ^  t25  ;
    wire    t29 = t28   &  t27  ;
    wire    t30 = t26   &  t24  ;
    wire    t31 = t20   &  t23  ;
    wire    t32 = t27   &  t31  ;
    wire    t33 = t27   ^  t25  ;
    wire    t34 = t21   &  t22  ;
    wire    t35 = t24   &  t34  ;
    wire    t36 = t24   ^  t25  ;
    wire    t37 = t21   ^  t29  ;
    wire    t38 = t32   ^  t33  ;
    wire    t39 = t23   ^  t30  ;
    wire    t40 = t35   ^  t36  ;
    wire    t41 = t38   ^  t40  ;
    wire    t42 = t37   ^  t39  ;
    wire    t43 = t37   ^  t38  ;
    wire    t44 = t39   ^  t40  ;
    wire    t45 = t42   ^  t41  ;
    assign  y[ 0] = t38  &  x[ 7];
    assign  y[ 1] = t37  &  x[13];
    assign  y[ 2] = t42  &  x[11];
    assign  y[ 3] = t45  &  x[20];
    assign  y[ 4] = t41  &  x[ 8];
    assign  y[ 5] = t44  &  x[ 9];
    assign  y[ 6] = t40  &  x[17];
    assign  y[ 7] = t39  &  x[14];
    assign  y[ 8] = t43  &  x[ 3];
    assign  y[ 9] = t38  &  x[16];
    assign  y[10] = t37  &  x[15];
    assign  y[11] = t42  &  x[ 1];
    assign  y[12] = t45  &  x[ 4];
    assign  y[13] = t41  &  x[ 2];
    assign  y[14] = t44  &  x[ 5];
    assign  y[15] = t40  &  x[ 6];
    assign  y[16] = t39  &  x[ 0];
    assign  y[17] = t43  &  x[12];

endmodule
