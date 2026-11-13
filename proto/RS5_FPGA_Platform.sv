/*!
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
 * Atomic memory operations.
 */


`include "../rtl/RS5_pkg.sv"

module RS5_FPGA_Platform
    import RS5_pkg::*;
#(
    parameter int           i_cnt             = 2,
    parameter environment_e Environment       = FPGA,
    parameter mul_e         MULEXT            = MUL_M,
    parameter atomic_e      AMOEXT            = AMO_A,
    parameter bit           COMPRESSED        = 1'b1,
    parameter bit           XOSVMEnable       = 1'b0,
    parameter bit           HPMCOUNTEREnable  = 1'b0,
    parameter bit           ZKNEEnable        = 1'b1,
    parameter bit           ZICONDEnable      = 1'b0,
    parameter bit           ZCBEnable         = 1'b1,
    parameter bit           ZBKBEnable        = 1'b1,
    parameter bit           ZKNHEnable        = 1'b0,
    parameter bit           XKYBEREnable      = 1'b1,
    parameter bit           VEnable           = 1'b0,
    parameter bit           BRANCHPRED        = 1'b1,
    parameter bit           FORWARDING        = 1'b1,
    parameter int           IMEM_LATENCY      = 1,
    parameter int           VLEN              = 64,
    parameter int           CLKS_PER_BIT_UART = 868
)
(
    input  logic       clk,
    input  logic       reset_n,
    input  logic       BTND,
    input  logic       UART_RX,
    output logic       UART_TX
);
    logic [31:0]            cpu_instruction_address, cpu_instruction;
    logic [31:0]            cpu_data_address, cpu_data_in, cpu_data_out;
    logic                   cpu_instruction_enable, cpu_instruction_rvalid;
    logic                   cpu_data_req, cpu_data_gnt, cpu_data_we, cpu_data_rvalid;
    logic [3:0]             cpu_data_be;
    logic                   cpu_operation_enable, enable_ram, enable_peripherals, enable_rtc, enable_plic;
    logic                   enable_rtc_r, enable_plic_r, enable_peripherals_r;
    logic [63:0]            mtime;
    logic [31:0]            data_bram, data_plic, data_peripherals;
    logic [63:0]            data_rtc;
    logic [3:0]             cpu_write_enable;
    logic                   stall;
    logic                   mei, mti;
    logic                   interrupt_ack;
    logic [31:0]            irq;
    logic [i_cnt:1]         irq_peripherals, iack_peripherals;

    assign irq = {20'h0, mei, 3'h0, mti, 7'h0};

//////////////////////////////////////////////////////////////////////////////
// Control
//////////////////////////////////////////////////////////////////////////////

    /* OBI data interface: the peripherals stall a request by withholding gnt */
    /* Every target answers in the cycle after the access                    */
    assign cpu_data_gnt         = !stall;
    assign cpu_operation_enable = cpu_data_req && cpu_data_gnt;
    assign cpu_write_enable     = cpu_data_we ? cpu_data_be : 4'h0;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            cpu_data_rvalid <= 1'b0;
        else
            cpu_data_rvalid <= cpu_operation_enable;
    end

    /* The instruction memory is always ready */
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            cpu_instruction_rvalid <= 1'b0;
        else
            cpu_instruction_rvalid <= cpu_instruction_enable;
    end

    assign enable_ram         = cpu_data_req && (cpu_data_address[31:28] <  4'h2);
    assign enable_rtc         = cpu_data_req && (cpu_data_address[31:28] == 4'h2);
    assign enable_plic        = cpu_data_req && (cpu_data_address[31:28] >= 4'h3) && (cpu_data_address[31:28] < 4'h8);
    assign enable_peripherals = cpu_data_req && (cpu_data_address[31:28] >= 4'h8);

    /* A target is accessed once its request is granted */
    logic access_ram, access_rtc, access_plic, access_peripherals;
    assign access_ram         = enable_ram         && cpu_data_gnt;
    assign access_rtc         = enable_rtc         && cpu_data_gnt;
    assign access_plic        = enable_plic        && cpu_data_gnt;
    assign access_peripherals = enable_peripherals && cpu_data_gnt;

    always_ff @(posedge clk) begin
        enable_rtc_r            <= access_rtc;
        enable_plic_r           <= access_plic;
        enable_peripherals_r    <= access_peripherals;
    end

    always_comb begin
        if (enable_rtc_r) begin
            cpu_data_in = data_rtc[31:0];
        end
        else if (enable_plic_r) begin
            cpu_data_in = data_plic;
        end
        else if (enable_peripherals_r) begin
            cpu_data_in = data_peripherals;
        end
        else begin
            cpu_data_in = data_bram;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// CPU INSTANTIATION
//////////////////////////////////////////////////////////////////////////////

    RS5 #(
        .Environment     (Environment     ),
        .MULEXT          (MULEXT          ),
        .AMOEXT          (AMOEXT          ),
        .XOSVMEnable     (XOSVMEnable     ),
        .HPMCOUNTEREnable(HPMCOUNTEREnable),
        .ZKNEEnable      (ZKNEEnable      ),
        .ZICONDEnable    (ZICONDEnable    ),
        .ZCBEnable       (ZCBEnable       ),
        .ZBKBEnable      (ZBKBEnable      ),
        .ZKNHEnable      (ZKNHEnable      ),
        .XKYBEREnable    (XKYBEREnable    ),
        .COMPRESSED      (COMPRESSED      ),
        .VEnable         (VEnable         ),
        .VLEN            (VLEN            ),
        .IMEM_LATENCY    (IMEM_LATENCY    ),
        .BRANCHPRED      (BRANCHPRED      ),
        .FORWARDING      (FORWARDING      )
    ) dut (
        .clk                    (clk),
        .reset_n                (reset_n),
        .sys_reset_i            (1'b0),
        .mtime_i                (mtime),
        .tip_i                  (mti),
        .eip_i                  (mei),
        .interrupt_ack_o        (interrupt_ack),
        .instr_req_o            (cpu_instruction_enable),
        .instr_gnt_i            (1'b1),
        .instr_addr_o           (cpu_instruction_address),
        .instr_rvalid_i         (cpu_instruction_rvalid),
        .instr_rdata_i          (cpu_instruction),
        .data_req_o             (cpu_data_req),
        .data_gnt_i             (cpu_data_gnt),
        .data_addr_o            (cpu_data_address),
        .data_we_o              (cpu_data_we),
        .data_be_o              (cpu_data_be),
        .data_wdata_o           (cpu_data_out),
        .data_rvalid_i          (cpu_data_rvalid),
        .data_rdata_i           (cpu_data_in)
    );

//////////////////////////////////////////////////////////////////////////////
// BRAM INSTANTIATION
//////////////////////////////////////////////////////////////////////////////

    BRAM RAM (
        .clka   (clk),                      // input wire clka
        .ena    (cpu_instruction_enable),   // input wire ena
        .wea    (4'h0),                     // input wire [3 : 0] wea
        .addra  (cpu_instruction_address),  // input wire [31 : 0] addra
        .dina   (0),                        // input wire [31 : 0] dina
        .douta  (cpu_instruction),          // output wire [31 : 0] douta
        //////////////////////////////////////////////////////
        .clkb   (clk),                      // input wire clkb
        .enb    (access_ram),               // input wire enb
        .web    (cpu_write_enable),         // input wire [3 : 0] web
        .addrb  (cpu_data_address),         // input wire [31 : 0] addrb
        .dinb   (cpu_data_out),             // input wire [31 : 0] dinb
        .doutb  (data_bram)                 // output wire [31 : 0] doutb
    );

//////////////////////////////////////////////////////////////////////////////
// RTC INSTANTIATION
//////////////////////////////////////////////////////////////////////////////

    rtc rtc(
        .clk        (clk),
        .reset_n    (reset_n),
        .en_i       (access_rtc),
        .addr_i     (cpu_data_address[3:0]),
        .we_i       ({4'h0, cpu_write_enable}),
        .data_i     ({32'h0, cpu_data_out}),
        .data_o     (data_rtc),
        .mti_o      (mti),
        .mtime_o    (mtime)
    );

//////////////////////////////////////////////////////////////////////////////
// PLIC
//////////////////////////////////////////////////////////////////////////////

    plic #(
        .i_cnt(i_cnt)
    ) plic1 (
        .clk     (clk),
        .reset_n (reset_n),
        .en_i    (access_plic),
        .we_i    (cpu_write_enable),
        .addr_i  (cpu_data_address[23:0]),
        .data_i  (cpu_data_out),
        .data_o  (data_plic),
        .irq_i   (irq_peripherals),
        .iack_i  (interrupt_ack),
        .irq_o   (mei),
        .iack_o  (iack_peripherals)
    );

//////////////////////////////////////////////////////////////////////////////
// PERIPHERALS
//////////////////////////////////////////////////////////////////////////////

    Peripherals #(
        .i_cnt(i_cnt),
        .CLKS_PER_BIT_UART(CLKS_PER_BIT_UART)
    ) Peripherals1 (
        .clk            (clk),
        .reset_n        (reset_n),
        .stall_o        (stall),
        .enable_i       (enable_peripherals),
        .write_enable_i (cpu_write_enable),
        .data_address_i (cpu_data_address),
        .data_i         (cpu_data_out),
        .data_o         (data_peripherals),
        .BTND           (BTND),
        .UART_TX        (UART_TX),
        .UART_RX        (UART_RX),
        .interrupt_req_o(irq_peripherals),
        .interrupt_ack_i(iack_peripherals)
    );

endmodule
