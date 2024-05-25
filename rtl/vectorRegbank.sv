module vectorRegbank
    import RS5_pkg::*;
#(
    parameter int VLEN  = 64,
    parameter int VLENB = 8
) (
    input   logic             clk,
    input   logic             reset_n,

    input   logic [4:0]       vs1_addr,
    input   logic [4:0]       vs2_addr,
    input   logic [4:0]       vs3_addr,

    input   logic [VLENB-1:0] enable,
    input   logic [4:0]       vd_addr,
    input   logic [VLEN-1:0]  result,

    output  logic [VLEN-1:0]  v0_mask,
    output  logic [VLEN-1:0]  vs1_data,
    output  logic [VLEN-1:0]  vs2_data,
    output  logic [VLEN-1:0]  vs3_data
);

    logic [31:0][VLEN-1:0] regfile;

//////////////////////////////////////////////////////////////////////////////
// Reads
//////////////////////////////////////////////////////////////////////////////

    assign v0_mask  = regfile[0];
    assign vs1_data = regfile[vs1_addr];
    assign vs2_data = regfile[vs2_addr];
    assign vs3_data = regfile[vs3_addr];

//////////////////////////////////////////////////////////////////////////////
// Reset and Write control
//////////////////////////////////////////////////////////////////////////////
/*
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            regfile <= '{VLEN{'0}};
        else begin
            // Don't write to v0 (reserved for vector mask)
            if ((enable != '0) && (vd_addr != '0)) begin
                for (int i = 0; i < VLENB; i++) begin
                    if (enable[i])
                        regfile[vd_addr][(8*(i+1))-1-:8]  <= result[(8*(i+1))-1-:8];
                end
            end
        end
    end
*/
    for (genvar j = 0; j < 32 ; j++) begin : gen_vectorRegfile
        always_ff @(posedge clk  or negedge reset_n) begin
            if (!reset_n) begin
                regfile[j] <= '0;
            end
            else if (vd_addr == j && enable != '0) begin
                for (int i = 0; i < VLENB; i++) begin
                    if (enable[i]) begin
                        regfile[j][(8*(i+1))-1-:8]  <= result[(8*(i+1))-1-:8];
                    end
                end
            end
        end
    end

endmodule