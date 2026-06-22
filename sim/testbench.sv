/*!\file testbench.sv
 * RS5 VERSION - 1.1.0 - Pipeline Simplified and Core Renamed
 *
 * Distribution:  October 2023
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
 * Testbench for RS5 simulation.
 *
 * \detailed
 * Testbench for RS5 simulation.
 */

`include "../rtl/RS5_pkg.sv"

//////////////////////////////////////////////////////////////////////////////
// CPU TESTBENCH
//////////////////////////////////////////////////////////////////////////////

module testbench
    import RS5_pkg::*;
(
);

  timeunit 1ns; timeprecision 1ns;

//////////////////////////////////////////////////////////////////////////////
// PARAMETERS FOR CORE INSTANTIATION
//////////////////////////////////////////////////////////////////////////////

    localparam mul_e         MULEXT          = MUL_M;
    localparam atomic_e      AMOEXT          = AMO_A;
    localparam bit           COMPRESSED      = 1'b1;
    localparam bit           USE_XOSVM       = 1'b0;
    localparam bit           USE_ZKNE        = 1'b1;
    localparam bit           USE_ZICOND      = 1'b1;
    localparam bit           USE_ZCB         = 1'b1;
    localparam bit           USE_HPMCOUNTER  = 1'b1;
    localparam bit           BRANCHPRED      = 1'b1;
    localparam bit           FORWARDING      = 1'b1;
    localparam int           IQUEUE_SIZE     = 2;
    localparam bit           DUALPORT_MEM    = 1'b0;
    localparam int           RAM_DELAY_CYCLES= 0;

    localparam bit           VEnable         = 1'b0;
    localparam int           VLEN            = 512;
    localparam int           LLEN            = 32;

`ifndef SYNTH
    localparam bit           PROFILING       = 1'b1;
    localparam bit           DEBUG           = 1'b1;
`endif
    localparam string        PROFILING_FILE  = "./results/Report.txt";
    localparam string        OUTPUT_FILE     = "./results/Output.txt";

    localparam int           BUS_WIDTH       = 32;
    localparam int           MEM_ADDR_BITS   = 28;
    localparam string        BIN_FILE        = "../app/riscv-tests/test.bin";

    localparam bit           ICACHE_EN       = 1'b1;
    localparam bit           DCACHE_EN       = 1'b1;

    /* Parameters used only when cache is on */
    /* verilator lint_off UNUSEDPARAM */
    localparam int           ICACHE_WIDTH    = 12;
    localparam int           ICACHE_OFF_W    = 6;
    localparam int           DCACHE_WIDTH    = 12;
    localparam int           DCACHE_OFF_W    = 6;
    /* verilator lint_on UNUSEDPARAM */

    localparam int           i_cnt = 1;

///////////////////////////////////////// Clock generator //////////////////////////////

    logic clk;
    initial begin
        clk = 0;
        forever #5.0 clk = ~clk;
    end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// RESET CPU ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    logic reset_n;

    initial begin
        reset_n = 0;                                          // RESET for CPU initialization

        #100 reset_n = 1;                                     // Hold state for 100 ns
    end

//////////////////////////////////////////////////////////////////////////////
// TB SIGNALS
//////////////////////////////////////////////////////////////////////////////

    /* Number of used bits is defined by the memory size */
    /* verilator lint_off UNUSEDSIGNAL */
    logic [31:0]            instruction_address;
    /* verilator lint_on UNUSEDSIGNAL */

    /* RTC is 64 bits but the bus is 32 bits */
    /* verilator lint_off UNUSEDSIGNAL */
    logic [63:0]            data_rtc;
    /* verilator lint_on UNUSEDSIGNAL */

    logic                   interrupt_ack;
    logic [63:0]            mtime;
    /* verilator lint_off UNUSEDSIGNAL */
    logic [BUS_WIDTH-1:0]   instruction;
    /* verilator lint_on UNUSEDSIGNAL */
    logic                   enable_ram, enable_rtc, enable_plic, enable_tb;
    logic                   mem_operation_enable;
    logic [31:0]            mem_address;
    logic [BUS_WIDTH  -1:0] mem_data_read, mem_data_write;
    logic [BUS_WIDTH/8-1:0] mem_write_enable;
    byte                    char;
    logic [BUS_WIDTH  -1:0] data_ram;
    logic [31:0]            data_plic;
    logic [BUS_WIDTH  -1:0] data_tb;
    logic                   enable_tb_r, enable_rtc_r, enable_plic_r;
    logic                   mti, mei;

//////////////////////////////////////////////////////////////////////////////
// Control
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] dmem_dataR;

    assign enable_ram  = mem_operation_enable && ((mem_address[31:28] == 4'b0000) || (mem_address[31:28] == 4'b0001));
    assign enable_rtc  = mem_operation_enable && (mem_address[31:28] == 4'b0010);
    assign enable_plic = mem_operation_enable && (mem_address[31:28] == 4'b0100);
    assign enable_tb   = mem_operation_enable && (mem_address[31:28] == 4'b1000);

    always_ff @(posedge clk) begin
        enable_tb_r     <= enable_tb;
        enable_rtc_r    <= enable_rtc;
        enable_plic_r   <= enable_plic;
    end

    always_comb begin
        unique case ({enable_tb_r, enable_plic_r, enable_rtc_r})
            3'b100:  mem_data_read = data_tb;
            3'b010:  mem_data_read = {{(BUS_WIDTH-32){1'b0}}, data_plic};
            3'b001:  mem_data_read = {{(BUS_WIDTH-32){1'b0}}, data_rtc[31:0]};
            default: mem_data_read = dmem_dataR;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// CPU
//////////////////////////////////////////////////////////////////////////////

    logic busy;
    logic enable_imem;
    logic stall;

    RS5 #(
    `ifndef SYNTH
	    .DEBUG          (DEBUG          ),
	    .PROFILING      (PROFILING      ),
        .PROFILING_FILE (PROFILING_FILE ),
    `endif
        .Environment     (ASIC          ),
        .MULEXT          (MULEXT        ),
        .AMOEXT          (AMOEXT        ),
        .COMPRESSED      (COMPRESSED    ),
        .BUS_WIDTH       (BUS_WIDTH     ),
        .VEnable         (VEnable       ),
        .VLEN            (VLEN          ),
        .LLEN            (LLEN          ),
        .XOSVMEnable     (USE_XOSVM     ),
        .ZKNEEnable      (USE_ZKNE      ),
        .ZICONDEnable    (USE_ZICOND    ),
        .ZCBEnable       (USE_ZCB       ),
        .HPMCOUNTEREnable(USE_HPMCOUNTER),
        .IQUEUE_SIZE     (IQUEUE_SIZE   ),
        .BRANCHPRED      (BRANCHPRED    ),
        .FORWARDING      (FORWARDING    )
    ) dut (
        .clk                    (clk),
        .reset_n                (reset_n),
        .sys_reset_i            (1'b0),
        .stall                  (stall),
        .busy_i                 (busy),
        .instruction_i          (instruction[31:0]),
        .mem_data_i             (mem_data_read),
        .mtime_i                (mtime),
        .tip_i                  (mti),
        .eip_i                  (mei),
        .imem_operation_enable_o(enable_imem),
        .instruction_address_o  (instruction_address),
        .dmem_operation_enable_o(mem_operation_enable),
        .mem_write_enable_o     (mem_write_enable),
        .mem_address_o          (mem_address),
        .mem_data_o             (mem_data_write),
        .interrupt_ack_o        (interrupt_ack)
    );

//////////////////////////////////////////////////////////////////////////////
// Cache
//////////////////////////////////////////////////////////////////////////////

    logic        imem_busy;
    logic        imem_ce;
    logic [31:0] imem_data;

    logic        dmem_busy;
    logic        dmem_ce;
    logic [3:0]  dmem_we;
    logic [31:0] dmem_dataW;

    /* Number of used bits is defined by the memory size */
    /* verilator lint_off UNUSEDSIGNAL */
    logic [31:0] imem_addr;
    logic [31:0] dmem_addr;
    /* verilator lint_on UNUSEDSIGNAL */

    if (ICACHE_EN) begin : gen_icache_on
        logic                    icache_ce;
        logic [3:0]              icache_we;
        logic [ICACHE_WIDTH-1:0] icache_addr;
        logic [31:0]             icache_dataR;
        logic [31:0]             icache_dataW;

        DMWTCtrl #(
            .ADDR_WIDTH  (MEM_ADDR_BITS),
            .CACHE_WIDTH (ICACHE_WIDTH ),
            .OFFSET_WIDTH(ICACHE_OFF_W )
        ) icache_ctrl (
            .clk         (clk                ),
            .rst_n       (reset_n            ),
            .ce_i        (enable_imem        ),
            .we_i        ('0                 ),
            .address_i   (instruction_address[MEM_ADDR_BITS-1:0]),
            .data_i      ('0                 ),
            .data_o      (instruction        ),
            .busy_o      (busy               ),
            .cache_ce_o  (icache_ce          ),
            .cache_we_o  (icache_we          ),
            .cache_addr_o(icache_addr        ),
            .cache_data_i(icache_dataR       ),
            .cache_data_o(icache_dataW       ),
            .mem_ce_o    (imem_ce            ),
            .mem_addr_o  (imem_addr[MEM_ADDR_BITS-1:0]),
            .mem_data_i  (imem_data          ),
            .mem_busy_i  (imem_busy          ),
            /* verilator lint_off PINCONNECTEMPTY */
            .mem_we_o    (/* Unconnected */  ),
            .mem_data_o  (/* Unconnected */  )
            /* verilator lint_on PINCONNECTEMPTY */
        );

        RAM_mem #(
            .MEM_WIDTH(1 << ICACHE_WIDTH),
            .BIN_FILE("")
        ) icache_sram (
            .clk    (clk),
            .enA_i  (icache_ce),
            .weA_i  (icache_we),
            .addrA_i(icache_addr),
            .dataA_i(icache_dataW),
            .dataA_o(icache_dataR),
            .enB_i  (1'b0),
            .weB_i  ('0),
            .addrB_i('0),
            .dataB_i('0),
            /* verilator lint_off PINCONNECTEMPTY */
            .dataB_o(/* Unconnected */)
            /* verilator lint_on PINCONNECTEMPTY */
        );
    end
    else begin : gen_icache_off
        assign imem_ce     = enable_imem;
        assign imem_addr   = instruction_address;
        assign instruction = imem_data;
        assign busy        = imem_busy;
    end

    if (DCACHE_EN) begin : gen_dcache_on
        logic                    dcache_ce;
        logic [3:0]              dcache_we;
        logic [ICACHE_WIDTH-1:0] dcache_addr;
        logic [31:0]             dcache_dataR;
        logic [31:0]             dcache_dataW;

        logic dcache_busy;
        assign stall = dcache_busy && enable_ram;

        DMWBCtrl #(
            .ADDR_WIDTH  (MEM_ADDR_BITS),
            .CACHE_WIDTH (DCACHE_WIDTH ),
            .OFFSET_WIDTH(DCACHE_OFF_W )
        ) dcache_ctrl (
            .clk         (clk                ),
            .rst_n       (reset_n            ),
            .ce_i        (enable_ram         ),
            .we_i        (mem_write_enable   ),
            .address_i   (mem_address[MEM_ADDR_BITS-1:0]),
            .data_i      (mem_data_write     ),
            .data_o      (dmem_dataR         ),
            .busy_o      (dcache_busy        ),
            .cache_ce_o  (dcache_ce          ),
            .cache_we_o  (dcache_we          ),
            .cache_addr_o(dcache_addr        ),
            .cache_data_i(dcache_dataR       ),
            .cache_data_o(dcache_dataW       ),
            .mem_ce_o    (dmem_ce            ),
            .mem_addr_o  (dmem_addr[MEM_ADDR_BITS-1:0]),
            .mem_data_i  (data_ram           ),
            .mem_busy_i  (dmem_busy          ),
            .mem_we_o    (dmem_we            ),
            .mem_data_o  (dmem_dataW         )
        );

        RAM_mem #(
            .MEM_WIDTH(1 << DCACHE_WIDTH),
            .BIN_FILE("")
        ) dcache_sram (
            .clk    (clk),
            .enA_i  (dcache_ce),
            .weA_i  (dcache_we),
            .addrA_i(dcache_addr),
            .dataA_i(dcache_dataW),
            .dataA_o(dcache_dataR),
            .enB_i  (1'b0),
            .weB_i  ('0),
            .addrB_i('0),
            .dataB_i('0),
            /* verilator lint_off PINCONNECTEMPTY */
            .dataB_o(/* Unconnected */)
            /* verilator lint_on PINCONNECTEMPTY */
        );
    end
    else begin : gen_dcache_off
        assign dmem_ce    = enable_ram;
        assign dmem_we    = mem_write_enable;
        assign dmem_addr  = mem_address;
        assign dmem_dataW = mem_data_write;
        assign dmem_dataR = data_ram;
        assign stall      = dmem_busy;
    end

//////////////////////////////////////////////////////////////////////////////
// RAM
//////////////////////////////////////////////////////////////////////////////

    localparam int MEM_WIDTH = 1 << MEM_ADDR_BITS;

    logic                             enA;
    logic [BUS_WIDTH/8-1:0]           weA;
    logic [($clog2(MEM_WIDTH) - 1):0] addrA;
    logic [BUS_WIDTH-1:0]             dataAi;
    logic [BUS_WIDTH-1:0]             dataAo;

    logic                             enB;
    logic [BUS_WIDTH/8-1:0]           weB;
    logic [($clog2(MEM_WIDTH) - 1):0] addrB;
    logic [BUS_WIDTH-1:0]             dataBi;
    /* verilator lint_off UNUSEDSIGNAL */
    logic [BUS_WIDTH-1:0]             dataBo;
    /* verilator lint_on UNUSEDSIGNAL */

    RAM_mem #(
    `ifndef SYNTH
        .DEBUG     (DEBUG     ),
        .DEBUG_PATH("./debug/"),
    `endif
        .BUS_WIDTH(BUS_WIDTH  ),
        .MEM_WIDTH(MEM_WIDTH  ),
        .BIN_FILE (BIN_FILE   )
    ) RAM_MEM (
        .clk        (clk),

        .enA_i      (enA),
        .weA_i      (weA),
        .addrA_i    (addrA),
        .dataA_i    (dataAi),
        .dataA_o    (dataAo),

        .enB_i      (enB),
        .weB_i      (weB),
        .addrB_i    (addrB),
        .dataB_i    (dataBi),
        .dataB_o    (dataBo)
    );

    logic enable_ram_delayed;
    initial begin
        dmem_busy = 1'b0;
        enable_ram_delayed = 1'b0;

        forever begin
            // 1. Wait for enable_ram to go high
            @(negedge clk iff dmem_ce);

            // 2. Assert stall
            dmem_busy = 1'b1;

            // 3. Wait for some cycles (to simulate delay)
            repeat (RAM_DELAY_CYCLES) @(negedge clk);

            // 4. Deassert stall, assert delayed signal
            dmem_busy = 1'b0;
            enable_ram_delayed = 1'b1;

            // 5. Wait for enable_ram to go low to finish
            @(negedge clk iff !dmem_ce);
            enable_ram_delayed = 1'b0;
        end
    end

    if (DUALPORT_MEM) begin : dual_port
        assign enA         = imem_ce;
        assign weA         = '0;
        assign addrA       = imem_addr[($clog2(MEM_WIDTH) - 1):0];
        assign dataAi      = '0;
        assign imem_data   = dataAo;

        assign enB         = enable_ram_delayed;
        assign weB         = dmem_we;
        assign addrB       = dmem_addr[($clog2(MEM_WIDTH) - 1):0];
        assign dataBi      = dmem_dataW;
        assign data_ram    = dataBo;

        assign imem_busy   = 1'b0;
    end
    else begin : single_port
        assign enA         = imem_ce || enable_ram_delayed;
        assign weA         = enable_ram_delayed ? dmem_we : '0;
        assign addrA       = enable_ram_delayed ? dmem_addr[($clog2(MEM_WIDTH) - 1):0] : imem_addr[($clog2(MEM_WIDTH) - 1):0];
        assign dataAi      = dmem_dataW;
        assign imem_data   = dataAo;
        assign data_ram    = dataAo;

        assign enB         = '0;
        assign weB         = '0;
        assign addrB       = '0;
        assign dataBi      = '0;

        assign imem_busy   = dmem_ce;
    end

//////////////////////////////////////////////////////////////////////////////
// PLIC
//////////////////////////////////////////////////////////////////////////////

    /* Bits depending on connected peripherals */
    /* verilator lint_off UNUSED */
    logic [i_cnt:1] iack_periph;
    /* verilator lint_on UNUSED */

    plic #(
        .i_cnt(i_cnt)
    ) plic1 (
        .clk     (clk),
        .reset_n (reset_n),
        .en_i    (enable_plic),
        .we_i    (mem_write_enable[3:0]),
        .addr_i  (mem_address[23:0]),
        .data_i  (mem_data_write[31:0]),
        .data_o  (data_plic),
        .irq_i   ('0),
        .iack_i  (interrupt_ack),
        .iack_o  (iack_periph),
        .irq_o   (mei)
    );

//////////////////////////////////////////////////////////////////////////////
// RTC
//////////////////////////////////////////////////////////////////////////////

    rtc rtc(
        .clk        (clk),
        .reset_n    (reset_n),
        .en_i       (enable_rtc),
        .addr_i     (mem_address[3:0]),
        .we_i       ({4'h0, mem_write_enable[3:0]}),
        .data_i     ({32'h0, mem_data_write[31:0]}),
        .data_o     (data_rtc),
        .mti_o      (mti),
        .mtime_o    (mtime)
    );

//////////////////////////////////////////////////////////////////////////////
// Memory Mapped regs
//////////////////////////////////////////////////////////////////////////////
    int fd;
    initial begin
        fd = $fopen(OUTPUT_FILE,"w");
    end

    always_ff @(posedge clk) begin
        if (enable_tb) begin
            // OUTPUT REG
            if ((mem_address == 32'h80004000 || mem_address == 32'h80001000) && mem_write_enable != '0) begin
                char <= mem_data_write[7:0];
                $write("%c",char);
                if (char != 8'h00)
                    $fwrite(fd,"%c",char);
                $fflush();
            end
            else if (mem_address == 32'h80002000 && mem_write_enable != '0) begin
                $write(    "%0d\n",mem_data_write);
                $fwrite(fd,"%0d\n",mem_data_write);
                $fflush();
            end
            // END REG
            if (mem_address == 32'h80000000 && mem_write_enable != '0) begin
                $display(    "\n# %0t END OF SIMULATION",$time);
                $finish;
            end
        end
        else begin
            data_tb <= '0;
        end
    end

endmodule
