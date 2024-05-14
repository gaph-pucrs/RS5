//
// Copyright (C) 2020
//    SCARV Project  <info@scarv.org>
//    Ben Marshall   <ben.marshall@bristol.ac.uk>
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
// SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
// IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//

module aes_unit #(
    parameter LOGIC_GATING = 0  // Gate sub-module inputs to save toggling
)(
    input wire[31:0] rs1_in,    // Source register 1
    input wire[31:0] rs2_in,    // Source register 2
    input wire[ 1:0] bs_in,     // Byte select immediate

    output wire[31:0] rd_out,   // Output destination register value

    input wire mix_in,          // SubBytes + MixColumn or just SubBytes
    input wire valid_in         // Are the inputs valid?

);

    `define GATE_INPUTS(LEN,SEL,SIG) (LOGIC_GATING ? ({LEN{SEL}} & SIG[LEN-1:0]) : SIG[LEN-1:0])

    wire[31:0] rs1_gated = `GATE_INPUTS(32, valid_in, rs1_in);
    wire[31:0] rs2_gated = `GATE_INPUTS(32, valid_in, rs2_in);

    `undef GATE_INPUTS

    wire[7:0] bytes_in[3:0];

    assign bytes_in[0] = rs2_gated[ 7: 0];
    assign bytes_in[1] = rs2_gated[15: 8];
    assign bytes_in[2] = rs2_gated[23:16];
    assign bytes_in[3] = rs2_gated[31:24];

    wire[7:0] sel_byte = bytes_in[bs_in];
    wire[7:0] sbox_out;

    // Multiply by 2 in GF(2^8) modulo 8'h1b
    function[7:0] xtime2;
        input[7:0] a;

        xtime2 = {a[6:0], 1'b0} ^ (a[7] ? 8'h1b : 8'b0);

    endfunction

    // Paired down multiply by X in GF(2^8)
    function[7:0] xtimeN;
        input[7:0] a;
        input[3:0] b;

        xtimeN =
            (b[0] ?                         a   : 0) ^
            (b[1] ? xtime2(                 a)  : 0) ^
            (b[2] ? xtime2(xtime2(          a)) : 0) ^
            (b[3] ? xtime2(xtime2(xtime2(   a))): 0) ;

    endfunction

    wire[7:0] mix_b3 = xtimeN(sbox_out, 3);
    wire[7:0] mix_b2 = sbox_out;
    wire[7:0] mix_b1 = sbox_out;
    wire[7:0] mix_b0 = xtimeN(sbox_out, 2);

    wire[31:0] result_mix = {mix_b3, mix_b2, mix_b1, mix_b0};

    wire[31:0] result = mix_in ? result_mix : {24'b0, sbox_out};

    wire[31:0] rotated =
        {32{bs_in == 2'b00}} & {result                      } |
        {32{bs_in == 2'b01}} & {result[23:0], result[31:24] } |
        {32{bs_in == 2'b10}} & {result[15:0], result[31:16] } |
        {32{bs_in == 2'b11}} & {result[ 7:0], result[31: 8] } ;

    assign rd_out = rotated ^ rs1_gated;

    riscv_crypto_aes_fwd_sbox i_aes_sbox_fwd (
        .in(sel_byte),
        .fx(sbox_out)
    );

endmodule
