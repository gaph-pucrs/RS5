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
    localparam bit           USE_ZKNE        = 1'b0;
    localparam bit           USE_ZICOND      = 1'b0;
    localparam bit           USE_ZCB         = 1'b0;
    localparam bit           USE_ZBKB        = 1'b1;
    localparam bit           USE_ZKNH        = 1'b0;
    localparam bit           USE_XKYBER      = 1'b0;
    localparam bit           USE_HPMCOUNTER  = 1'b1;
    localparam bit           BRANCHPRED      = 1'b1;
    localparam bit           FORWARDING      = 1'b1;
    localparam int           IQUEUE_SIZE     = 2;
    localparam bit           DUALPORT_MEM    = 1'b1;
    localparam int           RAM_DELAY_CYCLES= 0;
    localparam int           STALL_INJECT    = 0;    // > 0: also stall ~1 in STALL_INJECT cycles, see below

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
            default: mem_data_read = data_ram;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// CPU
//////////////////////////////////////////////////////////////////////////////

    logic busy;
    logic enable_imem;
    logic stall;
    logic [BUS_WIDTH-1:0] mem_data_cpu;

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
        .ZBKBEnable      (USE_ZBKB      ),
        .ZKNHEnable      (USE_ZKNH      ),
        .XKYBEREnable    (USE_XKYBER    ),
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
        .mem_data_i             (mem_data_cpu ),
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

    /* Every RAM request stalls the core for RAM_DELAY_CYCLES, like a slow
     * device behind the SoC bus (soc axil2axi4):
     *   IDLE/RESP  new request: stall (combinational)
     *   WAIT       stall
     *   DONE       no stall, RAM accessed; the request still on the bus is
     *              the same one
     *   RESP       read data valid; a request here is a new one
     * RAM_DELAY_CYCLES = 0 never stalls.
     *
     * STALL_INJECT > 0 also stalls the core for 1-4 cycles, starting on about
     * 1 in STALL_INJECT cycles chosen independently of the core's requests,
     * like another bus master holding the bus. The RAM waits while it lasts.
     * RAM stalls only ever hit an instruction's first cycle (the request
     * comes from the previous one); injected stalls also hit multi-cycle
     * operations mid-way. STALL_INJECT = 0 never injects. */
    typedef enum logic [1:0] {RAM_IDLE, RAM_WAIT, RAM_DONE, RAM_RESP} ram_state_e;

    ram_state_e ram_state;
    int         ram_delay_cnt;
    logic       ram_new_request;
    logic       enable_ram_delayed;
    logic       ram_stall;
    int         inject_cnt;
    logic       inject_stall;

    assign ram_new_request    = (ram_state inside {RAM_IDLE, RAM_RESP}) && enable_ram;
    assign ram_stall          = (RAM_DELAY_CYCLES > 0) && (ram_new_request || ram_state == RAM_WAIT);
    assign enable_ram_delayed = (RAM_DELAY_CYCLES > 0) ? (ram_state == RAM_DONE) : enable_ram;
    assign inject_stall       = (inject_cnt != 0);
    assign stall              = ram_stall || inject_stall;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            inject_cnt <= 0;
        else if (inject_cnt != 0)
            inject_cnt <= inject_cnt - 1;
        else if (STALL_INJECT > 0 && $urandom_range(STALL_INJECT - 1) == 0)
            inject_cnt <= $urandom_range(4, 1);
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            ram_state     <= RAM_IDLE;
            ram_delay_cnt <= 0;
        end
        else if (inject_stall) begin
            /* the bus is held: the RAM request in progress waits */
        end
        else begin
            unique case (ram_state)
                RAM_IDLE, RAM_RESP: begin
                    if (ram_new_request && RAM_DELAY_CYCLES > 0) begin
                        ram_delay_cnt <= RAM_DELAY_CYCLES - 1;
                        ram_state     <= (RAM_DELAY_CYCLES > 1) ? RAM_WAIT : RAM_DONE;
                    end
                    else begin
                        ram_state     <= RAM_IDLE;
                    end
                end
                RAM_WAIT: begin
                    ram_delay_cnt <= ram_delay_cnt - 1;
                    if (ram_delay_cnt <= 1)
                        ram_state <= RAM_DONE;
                end
                RAM_DONE: ram_state <= RAM_RESP;
                default:  ram_state <= RAM_IDLE;
            endcase
        end
    end

    /* The core's regbank write is not gated by stall: hold the read data seen
     * on the first stall cycle until the stall ends (soc dig_top) */
    logic                 stall_r;
    logic [BUS_WIDTH-1:0] mem_data_read_r;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            stall_r         <= 1'b0;
            mem_data_read_r <= '0;
        end
        else begin
            stall_r <= stall;
            if (!stall_r)
                mem_data_read_r <= mem_data_read;
        end
    end

    assign mem_data_cpu = stall_r ? mem_data_read_r : mem_data_read;

    if (DUALPORT_MEM) begin : dual_port
        assign enA         = enable_imem;
        assign weA         = '0;
        assign addrA       = instruction_address[($clog2(MEM_WIDTH) - 1):0];
        assign dataAi      = '0;
        assign instruction = dataAo;

        assign enB         = enable_ram_delayed;
        assign weB         = mem_write_enable;
        assign addrB       = mem_address[($clog2(MEM_WIDTH) - 1):0];
        assign dataBi      = mem_data_write;
        assign data_ram    = dataBo;

        assign busy        = 1'b0;
    end
    else begin : single_port
        assign enA         = enable_imem || enable_ram_delayed;
        assign weA         = enable_ram_delayed ? mem_write_enable : '0;
        assign addrA       = enable_ram_delayed ? mem_address[($clog2(MEM_WIDTH) - 1):0] : instruction_address[($clog2(MEM_WIDTH) - 1):0];
        assign dataAi      = mem_data_write;
        assign instruction = dataAo;
        assign data_ram    = dataAo;

        assign enB         = '0;
        assign weB         = '0;
        assign addrB       = '0;
        assign dataBi      = '0;

        assign busy        = enable_ram;
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
        /* A store stalled on the bus is still there on the first cycle after
         * the stall: act on it only then, once */
        if (enable_tb && stall) begin
        end
        else if (enable_tb) begin
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
