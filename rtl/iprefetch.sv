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
    input  logic        jumped_i,
    input  logic  [2:0] tag_i,
    input  logic [31:0] pc_i,
    input  logic [31:0] instruction_i,
    input  logic        jump_misaligned_i,

    output logic        prefetched_o,
    output logic        compressed_o,
    output logic [2:0]  tag_o,
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

    logic jumped_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            jumped_r <= 1'b0;
        end
        else if (enable_i) begin
            jumped_r <= jumped_i;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Compression control
//////////////////////////////////////////////////////////////////////////////

    logic compressed;

    assign compressed   = (instruction[1:0] != '1);

//////////////////////////////////////////////////////////////////////////////
// PC control
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] pc_add;
    logic [31:0] next_pc;
    logic [31:0] pc;
    logic [31:0] pc_r;

    assign pc = jumped_i || (jumped_r && hazard_r) ? pc_i : pc_r;
    assign pc_add = compressed || jump_misaligned_i ? 32'd2 : 32'd4;
    assign next_pc = pc + pc_add;

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
    logic        prefetched;

    assign instruction_aligned    = instruction_i;
    assign instruction_misaligned = {instruction_i[15:0], instruction_r[31:16]};
    assign instruction_prefetched = instruction_r;

    assign prefetched  = misaligned & compressed;

    logic prefetched_r;

    always_ff @(posedge clk or negedge reset_n) begin
        if (reset_n == 1'b0)
            prefetched_r <= 1'b0;
        else if (enable_i == 1'b1 && hazard_i == 1'b0)
            prefetched_r <= prefetched;
    end

    always_comb begin
        if (misaligned)
            instruction = instruction_misaligned;
        else if (misaligned_r && !jumped_i)
            instruction = instruction_prefetched;
        else
            instruction = instruction_aligned;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (reset_n == 1'b0) begin
            instruction_r <= '0;
        end
        else if (enable_i == 1'b1 && !hazard_i && !(prefetched_r && compressed)) begin
            instruction_r <= instruction_i;
        end
    end

    assign prefetched_o = prefetched;

    always_ff @(posedge clk or negedge reset_n) begin
        if (reset_n == 1'b0) begin
            pc_o          <= '0;
            compressed_o  <= 1'b0;
            instruction_o <= '0;
        end
        else if (enable_i == 1'b1 && !hazard_i) begin
            pc_o          <= pc;
            compressed_o  <= compressed;
            instruction_o <= instruction;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (reset_n == 1'b0) begin
            tag_o <= '0;
        end
        else if (enable_i == 1'b1 && !hazard_i && !jump_misaligned_i) begin
            tag_o <= tag_i;
        end
    end

endmodule
