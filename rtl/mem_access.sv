`include "RS5_pkg.sv"

module mem_access
    import RS5_pkg::*;
#(
    parameter int BUS_WIDTH = 32
)
(
    input  logic                     clk,
    input  logic                     reset_n,

    /* Stalls the pipeline while the data interface is busy */
    output logic                     stall_o,

    /* Registered input from execute */
    input  wb_ctrl_t                 ctrl_i,
    input  logic [31:0]              result_i,
    input  logic  [4:0]              rd_i,

    /* MMU interface */
    input  logic                     load_access_fault_i,

    /* Data request of this instruction, from execute through the MMU */
    input  logic                     req_i,
    input  logic [31:0]              addr_i,
    input  logic                     we_i,
    input  logic [BUS_WIDTH/8-1:0]   be_i,
    input  logic [BUS_WIDTH-1:0]     wdata_i,
    input  logic [5:0]               atop_i,

    /* OBI data interface */
    output logic                     data_req_o,
    input  logic                     data_gnt_i,
    output logic [31:0]              data_addr_o,
    output logic                     data_we_o,
    output logic [BUS_WIDTH/8-1:0]   data_be_o,
    output logic [BUS_WIDTH-1:0]     data_wdata_o,
    output logic [5:0]               data_atop_o,
    input  logic                     data_rvalid_i,

    /* The instruction in retire has its read data, or awaits no response */
    output logic                     rsp_ok_o,

    /* Registered outputs to retire */
    output wb_ctrl_t                 ctrl_o,
    output logic [31:0]              result_o,
    output logic  [4:0]              rd_o
);

//////////////////////////////////////////////////////////////////////////////
// Request
//////////////////////////////////////////////////////////////////////////////

    /* The request leaves execute registered and is handed to the bus here:   */
    /* sent in the same cycle when granted, or kept in a one-entry skid       */
    /* buffer that holds it on the bus until gnt. A handed request lets the   */
    /* instruction move on, so gnt never reaches the stall: the bus hold is   */
    /* separated from the pipeline. The response is awaited when the          */
    /* instruction reaches retire.                                            */
    logic handed;
    logic rsp_pending;
    logic rsp_atomic;

    /* OBI R-12: an atomic transaction is never outstanding with another one */
    logic atomic_wait;
    assign atomic_wait = rsp_pending && (rsp_atomic || atop_i[5]);

    logic hand_req;
    logic skid_free;
    assign hand_req = req_i && !handed && !atomic_wait;

    localparam int SKID_SIZE = 32 + 1 + BUS_WIDTH/8 + BUS_WIDTH + 6;

    /* Unused: the skid buffer only reports room */
    /* verilator lint_off UNUSEDSIGNAL */
    logic skid_count;
    logic skid_almost_full;
    logic skid_almost_empty;
    /* verilator lint_on UNUSEDSIGNAL */

    RingBuffer #(
        .DATA_SIZE              (SKID_SIZE),
        .BUFFER_SIZE            (1        ),
        .FIRST_WORD_FALL_THROUGH(1        ),
        .ALMOST_FULL_THRESHOLD  (0        ),
        .ALMOST_EMPTY_THRESHOLD (0        )
    ) data_skid (
        .clk_i         (clk                                                           ),
        .rst_ni        (reset_n                                                       ),
        .buf_rst_i     (1'b0                                                          ),
        .rx_i          (hand_req                                                      ),
        .rx_ack_o      (skid_free                                                     ),
        .data_i        ({addr_i, we_i, be_i, wdata_i, atop_i}                         ),
        .tx_o          (data_req_o                                                    ),
        .tx_ack_i      (data_gnt_i                                                    ),
        .data_o        ({data_addr_o, data_we_o, data_be_o, data_wdata_o, data_atop_o}),
        .count_o       (skid_count                                                    ),
        .almost_full_o (skid_almost_full                                              ),
        .almost_empty_o(skid_almost_empty                                             )
    );

    logic hand;
    assign hand = hand_req && skid_free;

    assign stall_o  = (req_i && !handed && !hand) || (rsp_pending && !data_rvalid_i);
    assign rsp_ok_o = !rsp_pending || data_rvalid_i;

    /* While the pipeline is stalled, a handed request is not handed again */
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            handed <= 1'b0;
        else if (!stall_o)
            handed <= 1'b0;
        else if (hand)
            handed <= 1'b1;
    end

//////////////////////////////////////////////////////////////////////////////
// Response
//////////////////////////////////////////////////////////////////////////////

    /* Without a stall, the request was handed and moves to retire */
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            rsp_pending <= 1'b0;
        else if (!stall_o)
            rsp_pending <= req_i;
        else if (data_rvalid_i)
            rsp_pending <= 1'b0;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            rsp_atomic <= 1'b0;
        else if (!stall_o)
            rsp_atomic <= req_i && atop_i[5];
        else if (data_rvalid_i)
            rsp_atomic <= 1'b0;
    end

//////////////////////////////////////////////////////////////////////////////
// To retire
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            ctrl_o <= '0;
        else if (!stall_o) begin
            ctrl_o        <= ctrl_i;
            ctrl_o.rd_we  <= ctrl_i.rd_we && !load_access_fault_i;
        end
        else begin
            /* once rd is written, don't rewrite it with stale bus data while stalled */
            ctrl_o.rd_we  <= ctrl_o.rd_we && !rsp_ok_o;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            rd_o <= '0;
        end
        else if (!stall_o) begin
            rd_o <= rd_i;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            result_o <= '0;
        end
        else if (!stall_o) begin
            result_o <= result_i;
        end
    end

endmodule
