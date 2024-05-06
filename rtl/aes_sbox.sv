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
module riscv_crypto_sbox_inv_mid(
input   [20:0] x    ,
output  [17:0] y
);

    wire    t0  = x[ 3] ^     x[12];
    wire    t1  = x[ 9] &     x[ 5];
    wire    t2  = x[17] &     x[ 6];
    wire    t3  = x[10] ^     t1   ;
    wire    t4  = x[14] &     x[ 0];
    wire    t5  = t4    ^     t1   ;
    wire    t6  = x[ 3] &     x[12];
    wire    t7  = x[16] &     x[ 7];
    wire    t8  = t0    ^     t6   ;
    wire    t9  = x[15] &     x[13];
    wire    t10 = t9    ^     t6   ;
    wire    t11 = x[ 1] &     x[11];
    wire    t12 = x[ 4] &     x[20];
    wire    t13 = t12   ^     t11  ;
    wire    t14 = x[ 2] &     x[ 8];
    wire    t15 = t14   ^     t11  ;
    wire    t16 = t3    ^     t2   ;
    wire    t17 = t5    ^     x[18];
    wire    t18 = t8    ^     t7   ;
    wire    t19 = t10   ^     t15  ;
    wire    t20 = t16   ^     t13  ;
    wire    t21 = t17   ^     t15  ;
    wire    t22 = t18   ^     t13  ;
    wire    t23 = t19   ^     x[19];
    wire    t24 = t22   ^     t23  ;
    wire    t25 = t22   &     t20  ;
    wire    t26 = t21   ^     t25  ;
    wire    t27 = t20   ^     t21  ;
    wire    t28 = t23   ^     t25  ;
    wire    t29 = t28   &     t27  ;
    wire    t30 = t26   &     t24  ;
    wire    t31 = t20   &     t23  ;
    wire    t32 = t27   &     t31  ;
    wire    t33 = t27   ^     t25  ;
    wire    t34 = t21   &     t22  ;
    wire    t35 = t24   &     t34  ;
    wire    t36 = t24   ^     t25  ;
    wire    t37 = t21   ^     t29  ;
    wire    t38 = t32   ^     t33  ;
    wire    t39 = t23   ^     t30  ;
    wire    t40 = t35   ^     t36  ;
    wire    t41 = t38   ^     t40  ;
    wire    t42 = t37   ^     t39  ;
    wire    t43 = t37   ^     t38  ;
    wire    t44 = t39   ^     t40  ;
    wire    t45 = t42   ^     t41  ;
    assign    y[ 0] = t38 &     x[ 7];
    assign    y[ 1] = t37 &     x[13];
    assign    y[ 2] = t42 &     x[11];
    assign    y[ 3] = t45 &     x[20];
    assign    y[ 4] = t41 &     x[ 8];
    assign    y[ 5] = t44 &     x[ 9];
    assign    y[ 6] = t40 &     x[17];
    assign    y[ 7] = t39 &     x[14];
    assign    y[ 8] = t43 &     x[ 3];
    assign    y[ 9] = t38 &     x[16];
    assign    y[10] = t37 &     x[15];
    assign    y[11] = t42 &     x[ 1];
    assign    y[12] = t45 &     x[ 4];
    assign    y[13] = t41 &     x[ 2];
    assign    y[14] = t44 &     x[ 5];
    assign    y[15] = t40 &     x[ 6];
    assign    y[16] = t39 &     x[ 0];
    assign    y[17] = t43 &     x[12];

endmodule

//
//    top (inner) linear layer for AES
module riscv_crypto_sbox_aes_top(
input   [ 7:0] x    ,
output  [20:0] y
);

    wire    y0  = x[ 0] ;
    wire    y1  = x[ 7] ^     x[ 4];
    wire    y2  = x[ 7] ^     x[ 2];
    wire    y3  = x[ 7] ^     x[ 1];
    wire    y4  = x[ 4] ^     x[ 2];
    wire    t0  = x[ 3] ^     x[ 1];
    wire    y5  = y1    ^     t0   ;
    wire    t1  = x[ 6] ^     x[ 5];
    wire    y6  = x[ 0] ^     y5   ;
    wire    y7  = x[ 0] ^     t1   ;
    wire    y8  = y5    ^     t1   ;
    wire    t2  = x[ 6] ^     x[ 2];
    wire    t3  = x[ 5] ^     x[ 2];
    wire    y9  = y3    ^     y4   ;
    wire    y10 = y5    ^     t2   ;
    wire    y11 = t0    ^     t2   ;
    wire    y12 = t0    ^     t3   ;
    wire    y13 = y7    ^     y12  ;
    wire    t4  = x[ 4] ^     x[ 0];
    wire    y14 = t1    ^     t4   ;
    wire    y15 = y1    ^     y14  ;
    wire    t5  = x[ 1] ^     x[ 0];
    wire    y16 = t1    ^     t5   ;
    wire    y17 = y2    ^     y16  ;
    wire    y18 = y2    ^     y8   ;
    wire    y19 = y15   ^     y13  ;
    wire    y20 = y1    ^     t3   ;

    assign y[0 ]  = y0 ;
    assign y[1 ]  = y1 ;
    assign y[10]  = y10;
    assign y[11]  = y11;
    assign y[12]  = y12;
    assign y[13]  = y13;
    assign y[14]  = y14;
    assign y[15]  = y15;
    assign y[16]  = y16;
    assign y[17]  = y17;
    assign y[18]  = y18;
    assign y[19]  = y19;
    assign y[2 ]  = y2 ;
    assign y[20]  = y20;
    assign y[3 ]  = y3 ;
    assign y[4 ]  = y4 ;
    assign y[5 ]  = y5 ;
    assign y[6 ]  = y6 ;
    assign y[7 ]  = y7 ;
    assign y[8 ]  = y8 ;
    assign y[9 ]  = y9 ;

endmodule


//
//    bottom (outer) linear layer for AES
module riscv_crypto_sbox_aes_out(
input   [17:0] x    ,
output  [ 7:0] y
);

    wire    t0   = x[11] ^  x[12];
    wire    t1   = x[0] ^   x[6];
    wire    t2   = x[14] ^  x[16];
    wire    t3   = x[15] ^  x[5];
    wire    t4   = x[4] ^   x[8];
    wire    t5   = x[17] ^  x[11];
    wire    t6   = x[12] ^  t5;
    wire    t7   = x[14] ^  t3;
    wire    t8   = x[1] ^   x[9];
    wire    t9   = x[2] ^   x[3];
    wire    t10  = x[3] ^   t4;
    wire    t11  = x[10] ^  t2;
    wire    t12  = x[16] ^  x[1];
    wire    t13  = x[0] ^   t0;
    wire    t14  = x[2] ^   x[11];
    wire    t15  = x[5] ^   t1;
    wire    t16  = x[6] ^   t0;
    wire    t17  = x[7] ^   t1;
    wire    t18  = x[8] ^   t8;
    wire    t19  = x[13] ^  t4;
    wire    t20  = t0 ^     t1;
    wire    t21  = t1 ^     t7;
    wire    t22  = t3 ^     t12;
    wire    t23  = t18 ^    t2;
    wire    t24  = t15 ^    t9;
    wire    t25  = t6 ^     t10;
    wire    t26  = t7 ^     t9;
    wire    t27  = t8 ^     t10;
    wire    t28  = t11 ^    t14;
    wire    t29  = t11 ^    t17;
    assign    y[0] = t6 ^~  t23;
    assign    y[1] = t13 ^~ t27;
    assign    y[2] = t25 ^  t29;
    assign    y[3] = t20 ^  t22;
    assign    y[4] = t6 ^   t21;
    assign    y[5] = t19 ^~ t28;
    assign    y[6] = t16 ^~ t26;
    assign    y[7] = t6 ^   t24;

endmodule


//
// Forward AES SBox
module riscv_crypto_aes_fwd_sbox (
    output [7:0] fx,
    input  [7:0] in
);

    wire [20:0] t1;
    wire [17:0] t2;

    riscv_crypto_sbox_aes_top top ( .y(t1), .x(in) );
    riscv_crypto_sbox_inv_mid mid ( .y(t2), .x(t1) );
    riscv_crypto_sbox_aes_out out ( .y(fx), .x(t2) );

endmodule
