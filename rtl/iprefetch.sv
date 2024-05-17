/*!
 * RS5
 * \file iprefetch.sv
 *
 * \author Angelo Elias Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * GAPH - Hardware Design Support Group (https://corfu.pucrs.br/)
 *
 * \date April 2024
 *
 * \brief Instruction prefetcher for compressed extension unaligned fetch
 */

module iprefetch
(
    input  logic        clk,
    input  logic        reset_n,

    input  logic        enable_i,
    input  logic        hazard_i,
    input  logic  [2:0] tag_i,
    input  logic [31:0] pc_i,
    input  logic [31:0] instruction_i,

    output logic        prefetched_o,
    output logic        compressed_o,
    output logic [31:0] pc_o,
    output logic [31:0] instruction_o
);

    logic [31:0] instruction;

    logic hazard_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            hazard_r <= 1'b0;
        end
        else if (enable_i) begin
            hazard_r <= hazard_i;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Tag control 
//////////////////////////////////////////////////////////////////////////////

    logic       valid_tag;
    logic       valid_tag_r;
    logic [2:0] tag_r;

    assign valid_tag = (tag_i == tag_r);

    always_ff @(posedge clk or negedge reset_n) begin
        if (reset_n == 1'b0) begin
            tag_r <= '0;
            valid_tag_r <= '0;
        end
        else if (enable_i == 1'b1) begin
            tag_r <= tag_i;
            valid_tag_r <= valid_tag;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Compression control
//////////////////////////////////////////////////////////////////////////////

    logic compressed;

    assign compressed   = (instruction[1:0] != '1);
    assign compressed_o = compressed;

//////////////////////////////////////////////////////////////////////////////
// PC control
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] pc_add;
    logic [31:0] next_pc;
    logic [31:0] pc;
    logic [31:0] pc_r;

    assign pc_add = compressed ? 32'd2 : 32'd4;

    always_comb begin
        if (valid_tag && !(!valid_tag_r && hazard_r)) begin
            pc = pc_r;
        end
        else begin
            pc = pc_i;
        end
    end

    //assign pc     = valid_tag && !(!valid_tag_r && hazard_r)  ? pc_r  : pc_i;
    assign pc_o   = pc;
    
    always_comb begin
        if (valid_tag && !(!valid_tag_r && hazard_r)) begin
            next_pc = pc_r + pc_add;
        end
        else begin
            next_pc = pc_i + pc_add;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (reset_n == 1'b0) begin
            pc_r <= '0;
        end
        else if (enable_i == 1'b1 && hazard_i == 1'b0) begin
            pc_r <= next_pc;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Alignment control
//////////////////////////////////////////////////////////////////////////////

    logic misaligned;
    logic misaligned_r;

    assign misaligned = pc[1];

    always_ff @(posedge clk or negedge reset_n) begin
        if (reset_n == 1'b0) begin
            misaligned_r <= '0;
        end
        else if (enable_i == 1'b1 && hazard_i == 1'b0) begin
            misaligned_r <= misaligned;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Prefetch control
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] instruction_r;
    logic [31:0] instruction_aligned;
    logic [31:0] instruction_misaligned;
    logic [31:0] instruction_prefetched;

    assign instruction_aligned    = instruction_i;
    assign instruction_misaligned = {instruction_i[15:0], instruction_r[31:16]};
    assign instruction_prefetched = instruction_r;

    assign instruction_o = instruction;
    assign prefetched_o  = misaligned & compressed;

    logic prefetched_r;

    always_ff @(posedge clk or negedge reset_n) begin
        if (reset_n == 1'b0)
            prefetched_r <= 1'b0;
        else if (enable_i == 1'b1)
            prefetched_r <= prefetched_o;
    end

    always_comb begin
        if (misaligned)
            instruction = instruction_misaligned;
        else if (misaligned_r && valid_tag)
            instruction = instruction_prefetched;
        else
            instruction = instruction_aligned;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (reset_n == 1'b0) begin
            instruction_r <= '0;
        end
        else if (enable_i == 1'b1 && prefetched_r == 1'b0 && !(!compressed && misaligned && hazard_i) && !(hazard_r && compressed) 
                 && !(hazard_i && prefetched_o) || (prefetched_o && prefetched_r)) begin
            instruction_r <= instruction_i;
        end
    end

endmodule
