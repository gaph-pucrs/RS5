`include "RS5_pkg.sv"

module vectorRegbank
    import RS5_pkg::*;
#(
    parameter environment_e Environment = ASIC,
    parameter int           VLEN        = 64,
    parameter int           VLENB       = 8
) (
    input   logic             clk,
    input   logic             reset_n,

    input   logic [4:0]       vs1_addr,
    input   logic [4:0]       vs2_addr,

    input   logic [VLENB-1:0] enable,
    input   logic [4:0]       vd_addr,
    input   logic [VLEN-1:0]  result,

    output  logic [VLEN-1:0]  v0_mask,
    output  logic [VLEN-1:0]  vs1_data,
    output  logic [VLEN-1:0]  vs2_data
);

    //////////////////////////////////////////////////////////////////////////////
    // RegBank
    //////////////////////////////////////////////////////////////////////////////

    if (Environment == FPGA) begin : gen_vector_regbank_fpga

        logic [VLEN-1:0] v0;

        always_ff @(posedge clk  or negedge reset_n) begin
            if (!reset_n) begin
                v0 <= '0;
            end
            else if (vd_addr == 0) begin
                for (int i = 0; i < VLENB; i++) begin
                    if (enable[i]) begin
                        v0[(8*i)+:8]  <= result[(8*i)+:8];
                    end
                end
            end
        end

        assign v0_mask = v0;

        DRAM_Vector_RegBank VectorRegBankA (
            .clk        (clk),
            .we         (enable),
            .a          (vd_addr),
            .d          (result),
            .dpra       (vs1_addr),
            .dpo        (vs1_data)
        );

        DRAM_Vector_RegBank VectorRegBankB (
            .clk        (clk),
            .we         (enable),
            .a          (vd_addr),
            .d          (result),
            .dpra       (vs2_addr),
            .dpo        (vs2_data)
        );

    end
    else begin : gen_vector_regbank_asic
        logic [31:0][VLEN-1:0] regfile;

        //////////////////////////////////////////////////////////////////////////////
        // Reads
        //////////////////////////////////////////////////////////////////////////////

        assign vs1_data = regfile[vs1_addr];
        assign vs2_data = regfile[vs2_addr];
        assign v0_mask  = regfile[0];

        //////////////////////////////////////////////////////////////////////////////
        // Reset and Write control
        //////////////////////////////////////////////////////////////////////////////

        for (genvar j = 0; j < 32 ; j++) begin : gen_vectorRegfile
            always_ff @(posedge clk  or negedge reset_n) begin
                if (!reset_n) begin
                    regfile[j] <= '0;
                end
                else if (vd_addr == j) begin
                    for (int i = 0; i < VLENB; i++) begin
                        if (enable[i]) begin
                            regfile[j][(8*i)+:8]  <= result[(8*i)+:8];
                        end
                    end
                end
            end
        end
    end

endmodule
