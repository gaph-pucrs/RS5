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
//    top (inner) linear layer for AES
module riscv_crypto_sbox_aes_top (
    input   [ 7:0] x,
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
