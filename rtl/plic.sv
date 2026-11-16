/*!\file plic.sv
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
 * Platform-Level Interrupt Controller, with one context for each hart.
 *
 * \detailed
 * OBI subordinate, with the register map of the RISC-V PLIC:
 *   0x001000:              pending sources (bit s for source s)
 *   0x002000 + 0x80*hart:  enabled sources of the hart
 *   0x200004 + 0x1000*hart: claim (read) and complete (write) of the hart
 * A source is pending while it requests and is not in service. Reading claim
 * returns the lowest pending source enabled for the hart, or 0, and puts it
 * in service, so that another hart cannot claim it too. Writing the source to
 * complete acknowledges the peripheral (iack_o), which takes it out of
 * service. There are no priorities or thresholds.
 */

`include "RS5_pkg.sv"

module plic
    import RS5_pkg::*;
#(
    parameter int i_cnt     = 1,
    parameter int NUM_HARTS = 1
)
(
    input   logic                   clk,
    input   logic                   reset_n,

    /* OBI subordinate: always granted, answers in the next cycle */
    input   logic                   req_i,
    output  logic                   gnt_o,
    input   logic [23:0]            addr_i,
    input   logic                   we_i,
    input   logic  [3:0]            be_i,
    /* Only a reduced number of bits is used depending on the number of interrupts */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic [31:0]            wdata_i,
    /* verilator lint_on UNUSEDSIGNAL */
    output  logic                   rvalid_o,
    output  logic [31:0]            rdata_o,

    input   logic [i_cnt:1]         irq_i,
    output  logic [i_cnt:1]         iack_o,

    output  logic [NUM_HARTS-1:0]   irq_o
);
    typedef logic [$clog2(i_cnt):0] intr_t;

    logic [i_cnt:1]                 ip;
    logic [i_cnt:1]                 in_service;
    logic [NUM_HARTS-1:0][i_cnt:1]  ie;
    intr_t [NUM_HARTS-1:0]          id;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Memory Mapped Regs
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    assign gnt_o = 1'b1;

    logic read;
    logic write;
    assign read  = req_i && !we_i;
    assign write = req_i &&  we_i;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            rvalid_o <= 1'b0;
        else
            rvalid_o <= req_i;
    end

    logic [NUM_HARTS-1:0] sel_ie;
    logic [NUM_HARTS-1:0] sel_claim;

    /* Register mux */
    logic [31:0] reg_val;
    always_comb begin
        reg_val = '0;
        if (addr_i == 24'h001000)
            reg_val = {{31-i_cnt{1'b0}}, ip, 1'b0};
        for (int c = 0; c < NUM_HARTS; c++) begin
            if (sel_ie[c])
                reg_val = {{31-i_cnt{1'b0}}, ie[c], 1'b0};
            if (sel_claim[c])
                reg_val = {{31-$clog2(i_cnt){1'b0}}, id[c]};
        end
    end

    /* Byte access */
    /* The number of bits used depends on i_cnt */
    /* verilator lint_off UNUSEDSIGNAL */
    logic [31:0] write_val;
    /* verilator lint_on UNUSEDSIGNAL */
    assign write_val[31:24] = be_i[3] ? wdata_i[31:24] : reg_val[31:24];
    assign write_val[23:16] = be_i[2] ? wdata_i[23:16] : reg_val[23:16];
    assign write_val[15: 8] = be_i[1] ? wdata_i[15: 8] : reg_val[15: 8];
    assign write_val[ 7: 0] = be_i[0] ? wdata_i[ 7: 0] : reg_val[ 7: 0];

    /* Read */
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            rdata_o <= '0;
        end
        else if (read) begin
            rdata_o <= reg_val;
        end
    end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Contexts
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for (genvar c = 0; c < NUM_HARTS; c++) begin : gen_context
        assign sel_ie[c]    = (addr_i == 24'(32'h002000 + c * 32'h80));
        assign sel_claim[c] = (addr_i == 24'(32'h200004 + c * 32'h1000));

        logic write_ie;
        assign write_ie = write && sel_ie[c];

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                ie[c] <= '0;
            else if (write_ie)
                ie[c] <= write_val[i_cnt:1];
        end

        logic [i_cnt:1] interrupt;
        assign interrupt = ip & ie[c];
        assign irq_o[c]  = (|interrupt);

        /* The lowest source has the highest priority, 0 = NO IRQ */
        always_comb begin
            id[c] = '0;
            for (int i = i_cnt; i >= 1; i--) begin
                if (interrupt[i])
                    id[c] = intr_t'(i);
            end
        end
    end

    /* One access at a time: at most one hart claims or completes in a cycle */
    intr_t claim_id;
    always_comb begin
        claim_id = '0;
        for (int c = 0; c < NUM_HARTS; c++) begin
            if (read && sel_claim[c])
                claim_id = id[c];
        end
    end

    logic  complete;
    intr_t complete_id;
    assign complete    = write && (|sel_claim);
    assign complete_id = write_val[$clog2(i_cnt):0];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sources
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for (genvar s = 1; s <= i_cnt; s++) begin : gen_source
        logic claimed;
        logic completed;
        assign claimed   = (claim_id == intr_t'(s));
        assign completed = complete && (complete_id == intr_t'(s));

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                ip[s] <= 1'b0;
            else
                ip[s] <= irq_i[s] && !in_service[s] && !claimed;
        end

        /* The peripheral drops its request after the acknowledge */
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                in_service[s] <= 1'b0;
            else if (claimed)
                in_service[s] <= 1'b1;
            else if (iack_o[s])
                in_service[s] <= 1'b0;
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                iack_o[s] <= 1'b0;
            else
                iack_o[s] <= completed;
        end
    end

endmodule
