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
