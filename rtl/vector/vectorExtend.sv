/*!\file vectorExtend.sv
 *
 * Willian Nunes    <willian.nunes@edu.pucrs.br>
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * Marcos Sartori   <marcos.sartori@acad.pucrs.br>
 * Ney Calazans     <ney.calazans@ufsc.br>
 * Fernando Moraes  <fernando.moraes@pucrs.br>
 * GAPH - Hardware Design Support Group
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul <https://pucrs.br/>
 *
 * \brief
 * Integer extension of a vector register to SEW.
 *
 * \detailed
 * Takes the part of the register selected by slice_i and extends each of its
 * elements to SEW, with zeros or with the sign: half of the register for vf2
 * (SEW/2 to SEW) and a quarter for vf4 (SEW/4 to SEW). With EXT_NONE the
 * register passes unchanged. With ExtendByFour = 0 there is no extension by
 * 4 and EXT_VF4 also passes the register unchanged.
 */

`include "../RS5_pkg.sv"

module vectorExtend
    import RS5_pkg::*;
#(
    parameter int VLEN         = 64,
    /* The extension by 4 (vf4); the vs1 extender only extends by 2 */
    parameter bit ExtendByFour = 1'b1
) (
    input  logic [VLEN-1:0] data_i,
    input  vext_sel_e       ext_sel_i,
    input  logic            ext_signed_i,
    /* The half (bit 0, vf2) or the quarter (bits 1:0, vf4) of data_i taken */
    input  logic [1:0]      slice_i,
    /* SEW of the result */
    input  vew_e            vsew_i,

    output logic [VLEN-1:0] data_o
);

    localparam VLENB = VLEN/8;

    logic [(VLEN/2)-1:0] half;
    logic [(VLEN/4)-1:0] quarter;

    always_comb begin
        if (slice_i[0])
            half = data_i[VLEN-1:VLEN/2];
        else
            half = data_i[(VLEN/2)-1:0];
    end

    always_comb begin
        if (!ExtendByFour)
            quarter = '0;
        else begin
            unique case (slice_i)
                2'd0:    quarter = data_i[(VLEN/4)-1:0];
                2'd1:    quarter = data_i[(VLEN/2)-1:VLEN/4];
                2'd2:    quarter = data_i[(3*VLEN/4)-1:VLEN/2];
                default: quarter = data_i[VLEN-1:3*VLEN/4];
            endcase
        end
    end

    always_comb begin
        data_o = data_i;
        unique case (ext_sel_i)
            /* SEW = 16 extends bytes, SEW = 32 extends halfwords */
            EXT_VF2: begin
                if (vsew_i == EW16) begin
                    for (int i = 0; i < VLENB/2; i++)
                        data_o[(16*i)+:16] = {{8{ext_signed_i && half[(8*i)+7]}}, half[(8*i)+:8]};
                end
                else begin
                    for (int i = 0; i < VLENB/4; i++)
                        data_o[(32*i)+:32] = {{16{ext_signed_i && half[(16*i)+15]}}, half[(16*i)+:16]};
                end
            end
            /* SEW = 32 extends bytes */
            EXT_VF4: begin
                if (ExtendByFour) begin
                    for (int i = 0; i < VLENB/4; i++)
                        data_o[(32*i)+:32] = {{24{ext_signed_i && quarter[(8*i)+7]}}, quarter[(8*i)+:8]};
                end
            end
            default: ;
        endcase
    end

endmodule
