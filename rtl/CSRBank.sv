/*!\file CSRBank.sv
 * RS5 VERSION - 1.1.0 - Pipeline Simplified and Core Renamed
 *
 * Distribution:  July 2023
 *
 * Willian Nunes   <willian.nunes@edu.pucrs.br>
 * Marcos Sartori  <marcos.sartori@acad.pucrs.br>
 * Ney calazans    <ney.calazans@pucrs.br>
 *
 * Research group: GAPH-PUCRS  <>
 *
 * \brief
 * The CSR Bank contains all the Control and Status register.
 *
 * \detailed
 * The CSR Bank contains all the Control and Status register,
 * Each CSR has a associated mask that is used to implement
 * the CSR behaviors. There are three posible operations in CSRs,
 * 1) Write - Writes the given data in the given CRS.
 * 2) Set - Uses the given data as a mask to set bits in the CSR,
 * 3) Clear - Uses the given data as a mask to clear bits in CSR.
 * Each operation applies the CSR mask alongside with the CSR
 * current content in a determined way to generate the new CSR content.
 */

`include "RS5_pkg.sv"

module CSRBank
    import RS5_pkg::*;
#(
`ifndef SYNTH
    parameter bit       PROFILING      = 1'b0,
    parameter string    PROFILING_FILE = "./debug/Report.txt",
`endif
    parameter bit       XOSVMEnable    = 1'b0,
    parameter bit       ZIHPMEnable    = 1'b0,
    parameter bit       COMPRESSED     = 1'b0,
    parameter mul_e     MULEXT         = MUL_M,
    parameter atomic_e  AMOEXT         = AMO_A,
    parameter bit       VEnable        = 1'b0,
    parameter int       VLEN           = 64
)
(
    input   logic               clk,
    input   logic               reset_n,
    input   logic               sys_reset,

    input   logic               read_enable_i,
    input   logic               write_enable_i,
    input   csrOperation_e      operation_i,
    input   CSRs                address_i,
    input   logic [31:0]        data_i,
    output  logic [31:0]        out,

    /* Signals enabled with ZIHPM */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic               instruction_compressed_i,
    input   iType_e             instruction_operation_i,
    input   iTypeVector_e       vector_operation_i,

    input   logic               hazard,
    input   logic               stall,
    input   logic               hold,
    input   logic               killed,

    input   logic [31:0]        vtype_i,
    input   logic [31:0]        vlen_i,
    /* verilator lint_on UNUSEDSIGNAL */

    input   logic               raise_exception_i,
    input   logic               machine_return_i,
    input   exceptionCode_e     exception_code_i,
    input   logic [31:0]        pc_i,
    input   logic [31:0]        next_pc_i,
    input   logic [31:0]        instruction_i,

    input   logic               jump_i,
    input   logic [31:0]        jump_target_i,

    /* Not used without compressed */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic               jump_misaligned_i,
    /* verilator lint_on UNUSEDSIGNAL */

    input   logic [63:0]        mtime_i,

    input   logic               tip_i,
    input   logic               eip_i,
    input   logic               interrupt_ack_i,
    output  logic               interrupt_pending_o,

    output  privilegeLevel_e    privilege_o,

    output  logic [31:0]        mepc_o,
    output  logic [31:0]        mtvec_o,

    output  logic               mvmctl_o,
    output  logic [31:0]        mvmdo_o,
    output  logic [31:0]        mvmio_o,
    output  logic [31:0]        mvmds_o,
    output  logic [31:0]        mvmis_o,
    output  logic [31:0]        mvmim_o,
    output  logic [31:0]        mvmdm_o
);

    privilegeLevel_e privilege;

////////////////////////////////////////////////////////////////////////////////
// misa
////////////////////////////////////////////////////////////////////////////////

    logic [31:0] misa;
    assign misa = {
        2'b1,           // MXL
        4'b0,           // 0
        2'b0,           // YZ - Reserved
        XOSVMEnable,    // X - Non-standard extensions present
        1'b0,           // W - Reserved
        VEnable,        // V - Vector extension
        1'b1,           // U - User mode implemented
        1'b0,           // T - Reserved
        1'b0,           // S - Supervisor mode implemented
        1'b0,           // R - Reserved
        1'b0,           // Q - Quad-precision floating-point extension
        1'b0,           // P - Packed-SIMD extension
        1'b0,           // O - Reserved
        1'b0,           // N - User level interrupts supported
        (MULEXT==MUL_M),// M - Integer Multiply/Divide extension
        3'b0,           // JKL - Reserved
        1'b1,           // I - RV32I/64I/128I base ISA
        1'b0,           // H - Hypervisor extension
        1'b0,           // G - Reserved
        1'b0,           // F - Single precision floating-point extension
        1'b0,           // E - RV32E base ISA
        1'b0,           // D - Double precision floating-point extension
        (COMPRESSED),   // C - Compressed extension
        1'b0,           // B - Bit-Manipulation extension
        (AMOEXT==AMO_A) // A - Atomic Extension
    };

////////////////////////////////////////////////////////////////////////////////
// mstatus
////////////////////////////////////////////////////////////////////////////////

    /* @todo What if an interrupt occurs during mstatus write? */

    logic mstatus_mie;
    logic mstatus_mpie;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mstatus_mpie <= 1'b0;
        else if (sys_reset)
            mstatus_mpie <= 1'b0;
        else begin 
            if (raise_exception_i || interrupt_ack_i)
                mstatus_mpie <= mstatus_mie;
            else if (write_enable_i && address_i == MSTATUS)
                mstatus_mpie <= wr_data[7];
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mstatus_mie <= 1'b0;
        else if (sys_reset)
            mstatus_mie <= 1'b0;
        else begin 
            if (machine_return_i)
                mstatus_mie <= mstatus_mpie;
            else if (raise_exception_i || interrupt_ack_i)
                mstatus_mie <= 1'b0;
            else if (write_enable_i && address_i == MSTATUS)
                mstatus_mie <= wr_data[3];
        end
    end

    logic [1:0] mstatus_mpp;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mstatus_mpp <= 2'b11;
        else if (sys_reset)
            mstatus_mpp <= 2'b11;
        else begin 
            if (raise_exception_i || interrupt_ack_i)
                mstatus_mpp <= privilege;
            else if (write_enable_i && address_i == MSTATUS)
                mstatus_mpp <= wr_data[12:11];
        end
    end

    logic [31:0] mstatus;
    assign mstatus = {
        1'b0,        // SD
        8'b0,        // WPRI
        1'b0,        // TSR
        1'b0,        // TW
        1'b0,        // TVM
        1'b0,        // MXR
        1'b0,        // SUM
        1'b0,        // MPRV
        2'b0,        // XS
        2'b0,        // FS
        mstatus_mpp, // MPP
        2'b0,        // VS
        1'b0,        // SPP
        mstatus_mpie,// MPIE
        1'b0,        // UBE
        1'b0,        // SPIE
        1'b0,        // WPRI
        mstatus_mie, // MIE
        1'b0,        // WPRI
        1'b0,        // SIE
        1'b0         // WPRI
    };

////////////////////////////////////////////////////////////////////////////////
// mtvec
////////////////////////////////////////////////////////////////////////////////

    logic [31:2] mtvec_base;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mtvec_base <= '0;
        else begin 
            if (write_enable_i && address_i == MTVEC)
                mtvec_base <= wr_data[31:2];
        end
    end

    logic [31:0] mtvec;
    assign mtvec = {
        mtvec_base, // BASE
        2'b0        // MODE
    };

    assign mtvec_o = mtvec;

////////////////////////////////////////////////////////////////////////////////
// mip and mie
////////////////////////////////////////////////////////////////////////////////

    logic mip_msip;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mip_msip <= 1'b0;
        else if (sys_reset)
            mip_msip <= 1'b0;
        else begin
            if (write_enable_i && address_i == MIP)
                mip_msip <= wr_data[3];
        end
    end

    logic mip_mtip;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mip_mtip <= 1'b0;
        else if (sys_reset)
            mip_mtip <= 1'b0;
        else begin
            mip_mtip <= tip_i;
            if (write_enable_i && address_i == MIP)
                mip_mtip <= wr_data[7];
        end
    end

    logic mip_meip;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mip_meip <= 1'b0;
        else if (sys_reset)
            mip_meip <= 1'b0;
        else begin
            mip_meip <= eip_i;
            if (write_enable_i && address_i == MIP)
                mip_meip <= wr_data[11];
        end
    end

    logic [31:0] mip;
    assign mip = {
        16'b0,    // Designated for platform use
        2'b0,     // 0
        1'b0,     // LCOFIP
        1'b0,     // 0
        mip_meip, // MEIP
        1'b0,     // 0
        1'b0,     // SEIP
        1'b0,     // 0
        mip_mtip, // MTIP
        1'b0,     // 0
        1'b0,     // STIP
        1'b0,     // 0
        mip_msip, // MSIP
        1'b0,     // 0
        1'b0,     // SSIP
        1'b0      // 0
    };

    logic mie_msie;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mie_msie <= 1'b0;
        else if (sys_reset)
            mie_msie <= 1'b0;
        else begin 
            if (write_enable_i && address_i == MIE)
                mie_msie <= wr_data[3];
        end
    end

    logic mie_mtie;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mie_mtie <= 1'b0;
        else if (sys_reset)
            mie_mtie <= 1'b0;
        else begin 
            if (write_enable_i && address_i == MIE)
                mie_mtie <= wr_data[7];
        end
    end

    logic mie_meie;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mie_meie <= 1'b0;
        else if (sys_reset)
            mie_meie <= 1'b0;
        else begin 
            if (write_enable_i && address_i == MIE)
                mie_meie <= wr_data[11];
        end
    end

    logic [31:0] mie;
    assign mie = {
        16'b0,    // Designated for platform use
        2'b0,     // 0
        1'b0,     // LCOFIE
        1'b0,     // 0
        mie_meie, // MEIE
        1'b0,     // 0
        1'b0,     // SEIE
        1'b0,     // 0
        mie_mtie, // MTIE
        1'b0,     // 0
        1'b0,     // STIE
        1'b0,     // 0
        mie_msie, // MSIE
        1'b0,     // 0
        1'b0,     // SSIE
        1'b0      // 0
    };

////////////////////////////////////////////////////////////////////////////////
// mcounteren
////////////////////////////////////////////////////////////////////////////////

    logic [31:0] mcounteren;

    /* Allows all reads to shadow performance registers */
    /* @todo Cause illegal instruction on Zicntr/Zihpm when a bit is 0 */
    assign mcounteren = '1;

////////////////////////////////////////////////////////////////////////////////
// mcountinhibit
////////////////////////////////////////////////////////////////////////////////

    logic [31:0] mcountinhibit;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mcountinhibit <= '0;
        else if (sys_reset)
            mcountinhibit <= '0;
        else begin
            if (write_enable_i && address_i == MCOUNTINHIBIT) begin
                mcountinhibit[30:2] <= wr_data[30:2];
                mcountinhibit[0]    <= wr_data[0];
            end
        end
    end

////////////////////////////////////////////////////////////////////////////////
// mcycle and minstret
////////////////////////////////////////////////////////////////////////////////

    logic [63:0] mcycle;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mcycle <= '0;
        else if (sys_reset)
            mcycle <= '0;
        else begin
            if (!mcountinhibit[0])
                mcycle <= mcycle + 1'b1;

            if (write_enable_i) begin
                unique case(address_i)
                    MCYCLE:  mcycle[31:0] <= wr_data;
                    MCYCLEH: mcycle[63:32] <= wr_data;
                    default: ;
                endcase
            end
        end
    end

    logic [63:0] minstret;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            minstret <= '0;
        else if (sys_reset)
            minstret <= '0;
        else begin
            if (!mcountinhibit[2] && !(hold || instruction_operation_i == NOP))
                minstret <= minstret + 1'b1;

            if (write_enable_i) begin
                unique case(address_i)
                    MINSTRET:  minstret[31:0] <= wr_data;
                    MINSTRETH: minstret[63:32] <= wr_data;
                    default: ;
                endcase
            end
        end
    end

////////////////////////////////////////////////////////////////////////////////
// Performance counters
////////////////////////////////////////////////////////////////////////////////

    /* @todo Add (A)tomic, Zkne, and Zicond */

    logic [31:0] cntr_killed;     // mhpmcounter3
    logic [31:0] cntr_context;    // mhpmcounter4
    logic [31:0] cntr_exception;  // mhpmcounter5
    logic [31:0] cntr_irq;        // mhpmcounter6
    logic [31:0] cntr_hazard;     // mhpmcounter7
    logic [31:0] cntr_stall;      // mhpmcounter8
    logic [31:0] cntr_nop;        // mhpmcounter9
    logic [31:0] cntr_logic;      // mhpmcounter10
    logic [31:0] cntr_addsub;     // mhpmcounter11
    logic [31:0] cntr_shift;      // mhpmcounter12
    logic [31:0] cntr_branch;     // mhpmcounter13
    logic [31:0] cntr_jump;       // mhpmcounter14
    logic [31:0] cntr_load;       // mhpmcounter15
    logic [31:0] cntr_store;      // mhpmcounter16
    logic [31:0] cntr_sys;        // mhpmcounter17
    logic [31:0] cntr_csr;        // mhpmcounter18
    logic [31:0] cntr_luislt;     // mhpmcounter19
    logic [31:0] cntr_compressed; // mhpmcounter20
    logic [31:0] cntr_misaligned; // mhpmcounter21
    logic [31:0] cntr_mul;        // mhpmcounter22
    logic [31:0] cntr_div;        // mhpmcounter23
    logic [31:0] cntr_vaddsub;    // mhpmcounter24
    logic [31:0] cntr_vmul;       // mhpmcounter25
    logic [31:0] cntr_vdiv;       // mhpmcounter26
    logic [31:0] cntr_vmac;       // mhpmcounter27
    logic [31:0] cntr_vred;       // mhpmcounter28
    logic [31:0] cntr_vloadstore; // mhpmcounter29
    logic [31:0] cntr_vothers;    // mhpmcounter30

    if (ZIHPMEnable) begin : gen_hpmcounter_on
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                cntr_killed <= '0;
            else if (sys_reset)
                cntr_killed <= '0;
            else begin
                if (!mcountinhibit[3] && killed)
                    cntr_killed <= cntr_killed + 1'b1;

                if (write_enable_i && address_i == MHPMCOUNTER3)
                    cntr_killed <= wr_data;
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                cntr_context <= '0;
            else if (sys_reset)
                cntr_context <= '0;
            else begin
                if (!mcountinhibit[4] && (jump_i || raise_exception_i || machine_return_i || interrupt_ack_i))
                    cntr_context <= cntr_context + 1'b1;

                if (write_enable_i && address_i == MHPMCOUNTER4)
                    cntr_context <= wr_data;
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                cntr_exception <= '0;
            else if (sys_reset)
                cntr_exception <= '0;
            else begin
                if (!mcountinhibit[5] && raise_exception_i)
                    cntr_exception <= cntr_exception + 1'b1;

                if (write_enable_i && address_i == MHPMCOUNTER5)
                    cntr_exception <= wr_data;
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                cntr_irq <= '0;
            else if (sys_reset)
                cntr_irq <= '0;
            else begin
                if (!mcountinhibit[6] && interrupt_ack_i)
                    cntr_irq <= cntr_irq + 1'b1;

                if (write_enable_i && address_i == MHPMCOUNTER6)
                    cntr_irq <= wr_data;
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                cntr_hazard <= '0;
            else if (sys_reset)
                cntr_hazard <= '0;
            else begin
                if (!mcountinhibit[7] && hazard && !hold)
                    cntr_hazard <= cntr_hazard + 1'b1;

                if (write_enable_i && address_i == MHPMCOUNTER7)
                    cntr_hazard <= wr_data;
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                cntr_stall <= '0;
            else if (sys_reset)
                cntr_stall <= '0;
            else begin
                if (!mcountinhibit[8] && stall)
                    cntr_stall <= cntr_stall + 1'b1;

                if (write_enable_i && address_i == MHPMCOUNTER8)
                    cntr_stall <= wr_data;
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                cntr_nop <= '0;
            else if (sys_reset)
                cntr_nop <= '0;
            else begin
                if (!mcountinhibit[9] && (!hold && instruction_operation_i inside {NOP}))
                    cntr_nop <= cntr_nop + 1'b1;

                if (write_enable_i && address_i == MHPMCOUNTER9)
                    cntr_nop <= wr_data;
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                cntr_logic <= '0;
            else if (sys_reset)
                cntr_logic <= '0;
            else begin
                if (!mcountinhibit[10] && (!hold && instruction_operation_i inside {XOR, OR, AND}))
                    cntr_logic <= cntr_logic + 1'b1;

                if (write_enable_i && address_i == MHPMCOUNTER10)
                    cntr_logic <= wr_data;
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                cntr_addsub <= '0;
            else if (sys_reset)
                cntr_addsub <= '0;
            else begin
                if (!mcountinhibit[11] && (!hold && instruction_operation_i inside {ADD, SUB}))
                    cntr_addsub <= cntr_addsub + 1'b1;

                if (write_enable_i && address_i == MHPMCOUNTER11)
                    cntr_addsub <= wr_data;
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                cntr_shift <= '0;
            else if (sys_reset)
                cntr_shift <= '0;
            else begin
                if (!mcountinhibit[12] && (!hold && instruction_operation_i inside {SLL, SRL, SRA}))
                    cntr_shift <= cntr_shift + 1'b1;

                if (write_enable_i && address_i == MHPMCOUNTER12)
                    cntr_shift <= wr_data;
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                cntr_branch <= '0;
            else if (sys_reset)
                cntr_branch <= '0;
            else begin
                if (!mcountinhibit[13] && (!hold && instruction_operation_i inside {BEQ, BNE, BLT, BLTU, BGE, BGEU}))
                    cntr_branch <= cntr_branch + 1'b1;

                if (write_enable_i && address_i == MHPMCOUNTER13)
                    cntr_branch <= wr_data;
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                cntr_jump <= '0;
            else if (sys_reset)
                cntr_jump <= '0;
            else begin
                if (!mcountinhibit[14] && (!hold && instruction_operation_i inside {JAL, JALR}))
                    cntr_jump <= cntr_jump + 1'b1;

                if (write_enable_i && address_i == MHPMCOUNTER14)
                    cntr_jump <= wr_data;
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                cntr_load <= '0;
            else if (sys_reset)
                cntr_load <= '0;
            else begin
                if (!mcountinhibit[15] && (!hold && instruction_operation_i inside {LB, LBU, LH, LHU, LW}))
                    cntr_load <= cntr_load + 1'b1;

                if (write_enable_i && address_i == MHPMCOUNTER15)
                    cntr_load <= wr_data;
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                cntr_store <= '0;
            else if (sys_reset)
                cntr_store <= '0;
            else begin
                if (!mcountinhibit[16] && (!hold && instruction_operation_i inside {SB, SH, SW}))
                    cntr_store <= cntr_store + 1'b1;

                if (write_enable_i && address_i == MHPMCOUNTER16)
                    cntr_store <= wr_data;
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                cntr_sys <= '0;
            else if (sys_reset)
                cntr_sys <= '0;
            else begin
                if (!mcountinhibit[17] && (!hold && instruction_operation_i inside {MRET, WFI, ECALL, EBREAK}))
                    cntr_sys <= cntr_sys + 1'b1;

                if (write_enable_i && address_i == MHPMCOUNTER17)
                    cntr_sys <= wr_data;
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                cntr_csr <= '0;
            else if (sys_reset)
                cntr_csr <= '0;
            else begin
                if (
                        !mcountinhibit[18] && 
                        (
                            !hold && instruction_operation_i inside {CSRRW, CSRRWI, CSRRS, CSRRSI, CSRRC, CSRRCI}
                        )
                    )
                    cntr_csr <= cntr_csr + 1'b1;

                if (write_enable_i && address_i == MHPMCOUNTER18)
                    cntr_csr <= wr_data;
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                cntr_luislt <= '0;
            else if (sys_reset)
                cntr_luislt <= '0;
            else begin
                if (!mcountinhibit[19] && (!hold && instruction_operation_i inside {SLTU, SLT, LUI}))
                    cntr_luislt <= cntr_luislt + 1'b1;

                if (write_enable_i && address_i == MHPMCOUNTER19)
                    cntr_luislt <= wr_data;
            end
        end

        if (COMPRESSED) begin :gen_hpmcounter_compressed_on
            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    cntr_compressed <= '0;
                else if (sys_reset)
                    cntr_compressed <= '0;
                else begin
                    if (!mcountinhibit[20] && (!hold && instruction_compressed_i))
                        cntr_compressed <= cntr_compressed + 1'b1;

                    if (write_enable_i && address_i == MHPMCOUNTER20)
                        cntr_compressed <= wr_data;
                end
            end
            
            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    cntr_misaligned <= '0;
                else if (sys_reset)
                    cntr_misaligned <= '0;
                else begin
                    if (!mcountinhibit[21] && (!stall && !hold && !hazard && jump_misaligned_i))
                        cntr_misaligned <= cntr_misaligned + 1'b1;

                    if (write_enable_i && address_i == MHPMCOUNTER21)
                        cntr_misaligned <= wr_data;
                end
            end
        end
        else begin : gen_hpmcounter_compressed_off
            assign cntr_compressed = '0;
            assign cntr_misaligned = '0;
        end

        if (MULEXT inside {MUL_ZMMUL, MUL_M}) begin : gen_hpmcounter_mul_on
            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    cntr_mul <= '0;
                else if (sys_reset)
                    cntr_mul <= '0;
                else begin
                    if (!mcountinhibit[22] && (!hold && instruction_operation_i inside {MUL, MULH, MULHU, MULHSU}))
                        cntr_mul <= cntr_mul + 1'b1;

                    if (write_enable_i && address_i == MHPMCOUNTER22)
                        cntr_mul <= wr_data;
                end
            end
        end
        else begin : gen_hpmcounter_mul_off
            assign cntr_mul = '0;
        end

        if (MULEXT inside {MUL_M}) begin : gen_hpmcounter_div_on
            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    cntr_div <= '0;
                else if (sys_reset)
                    cntr_div <= '0;
                else begin
                    if (!mcountinhibit[23] && (!hold && instruction_operation_i inside {DIV, DIVU, REM, REMU}))
                        cntr_div <= cntr_div + 1'b1;

                    if (write_enable_i && address_i == MHPMCOUNTER23)
                        cntr_div <= wr_data;
                end
            end
        end
        else begin : gen_hpmcounter_div_off
            assign cntr_div = '0;
        end

        if (VEnable) begin : gen_hpmcounter_v_on
            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    cntr_vaddsub <= '0;
                else if (sys_reset)
                    cntr_vaddsub <= '0;
                else begin
                    if (
                            !mcountinhibit[24] && 
                            (
                                !hold && 
                                instruction_operation_i inside {VECTOR} && 
                                vector_operation_i inside {VADD, VSUB, VRSUB}
                            )
                        )
                        cntr_vaddsub <= cntr_vaddsub + 1'b1;

                    if (write_enable_i && address_i == MHPMCOUNTER24)
                        cntr_vaddsub <= wr_data;
                end
            end

            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    cntr_vmul <= '0;
                else if (sys_reset)
                    cntr_vmul <= '0;
                else begin
                    if (
                            !mcountinhibit[25] && 
                            (
                                !hold && 
                                instruction_operation_i inside {VECTOR} && 
                                vector_operation_i inside {VMUL, VMULH, VMULHU, VMULHSU, VWMUL, VWMULU, VWMULSU}
                            )
                        )
                        cntr_vmul <= cntr_vmul + 1'b1;

                    if (write_enable_i && address_i == MHPMCOUNTER25)
                        cntr_vmul <= wr_data;
                end
            end

            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    cntr_vdiv <= '0;
                else if (sys_reset)
                    cntr_vdiv <= '0;
                else begin
                    if (
                            !mcountinhibit[26] && 
                            (
                                !hold && 
                                instruction_operation_i inside {VECTOR} && 
                                vector_operation_i inside {VDIV, VDIVU, VREM, VREMU}
                            )
                        )
                        cntr_vdiv <= cntr_vdiv + 1'b1;

                    if (write_enable_i && address_i == MHPMCOUNTER26)
                        cntr_vdiv <= wr_data;
                end
            end

            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    cntr_vmac <= '0;
                else if (sys_reset)
                    cntr_vmac <= '0;
                else begin
                    if (
                            !mcountinhibit[27] && 
                            (
                                !hold && 
                                instruction_operation_i inside {VECTOR} && 
                                vector_operation_i inside {VMACC, VNMSAC, VMADD, VNMSUB}
                            )
                        )
                        cntr_vmac <= cntr_vmac + 1'b1;

                    if (write_enable_i && address_i == MHPMCOUNTER27)
                        cntr_vmac <= wr_data;
                end
            end

            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    cntr_vred <= '0;
                else if (sys_reset)
                    cntr_vred <= '0;
                else begin
                    if (
                            !mcountinhibit[28] && 
                            (
                                !hold && 
                                instruction_operation_i inside {VECTOR} && 
                                vector_operation_i inside {VREDMIN, VREDMINU, VREDMAX, VREDMAXU}
                            )
                        )
                        cntr_vred <= cntr_vred + 1'b1;

                    if (write_enable_i && address_i == MHPMCOUNTER28)
                        cntr_vred <= wr_data;
                end
            end

            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    cntr_vloadstore <= '0;
                else if (sys_reset)
                    cntr_vloadstore <= '0;
                else begin
                    if (!mcountinhibit[29] && (!hold && instruction_operation_i inside {VLOAD, VSTORE}))
                        cntr_vloadstore <= cntr_vloadstore + 1'b1;

                    if (write_enable_i && address_i == MHPMCOUNTER29)
                        cntr_vloadstore <= wr_data;
                end
            end

            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    cntr_vothers <= '0;
                else if (sys_reset)
                    cntr_vothers <= '0;
                else begin
                    if (
                            !mcountinhibit[30] && 
                            (
                                !hold && 
                                instruction_operation_i inside {VECTOR} && 
                                vector_operation_i inside {
                                    VMSEQ, VMSNE, VMSLTU, VMSLT, VMSLEU, VMSLE, VMSGTU, VMSGT,  // mask compares
                                    VREDAND, VREDOR, VREDXOR,                                   // logic reduction
                                    VMV, VMVR, VMVSX, VMVXS,                                    // register moves
                                    VSLL, VSRL, VSRA,                                           // shifts
                                    VAND, VOR, VXOR,                                            // logic
                                    VMERGE
                                }
                            )
                        )
                        cntr_vothers <= cntr_vothers + 1'b1;

                    if (write_enable_i && address_i == MHPMCOUNTER30)
                        cntr_vothers <= wr_data;
                end
            end
        end
        else begin : gen_hpmcounter_v_off
            assign cntr_vaddsub    = '0;
            assign cntr_vmul       = '0;
            assign cntr_vdiv       = '0;
            assign cntr_vmac       = '0;
            assign cntr_vred       = '0;
            assign cntr_vloadstore = '0;
            assign cntr_vothers    = '0;
        end
    end
    else begin : gen_hpmcounter_off
        assign cntr_killed     = '0;
        assign cntr_context    = '0;
        assign cntr_exception  = '0;
        assign cntr_irq        = '0;
        assign cntr_hazard     = '0;
        assign cntr_stall      = '0;
        assign cntr_nop        = '0;
        assign cntr_logic      = '0;
        assign cntr_addsub     = '0;
        assign cntr_shift      = '0;
        assign cntr_branch     = '0;
        assign cntr_jump       = '0;
        assign cntr_load       = '0;
        assign cntr_store      = '0;
        assign cntr_sys        = '0;
        assign cntr_csr        = '0;
        assign cntr_luislt     = '0;
        assign cntr_compressed = '0;
        assign cntr_misaligned = '0;
        assign cntr_mul        = '0;
        assign cntr_div        = '0;
        assign cntr_vaddsub    = '0;
        assign cntr_vmul       = '0;
        assign cntr_vdiv       = '0;
        assign cntr_vmac       = '0;
        assign cntr_vred       = '0;
        assign cntr_vloadstore = '0;
        assign cntr_vothers    = '0;
    end

////////////////////////////////////////////////////////////////////////////////
// mhpmcounter and mhpmevent
////////////////////////////////////////////////////////////////////////////////

    logic [63:0] mhpmcounter [3:31];
    assign mhpmcounter = {
        {32'h0, cntr_killed    }, // mhpmcounter3
        {32'h0, cntr_context   }, // mhpmcounter4
        {32'h0, cntr_exception }, // mhpmcounter5
        {32'h0, cntr_irq       }, // mhpmcounter6
        {32'h0, cntr_hazard    }, // mhpmcounter7
        {32'h0, cntr_stall     }, // mhpmcounter8
        {32'h0, cntr_nop       }, // mhpmcounter9
        {32'h0, cntr_logic     }, // mhpmcounter10
        {32'h0, cntr_addsub    }, // mhpmcounter11
        {32'h0, cntr_shift     }, // mhpmcounter12
        {32'h0, cntr_branch    }, // mhpmcounter13
        {32'h0, cntr_jump      }, // mhpmcounter14
        {32'h0, cntr_load      }, // mhpmcounter15
        {32'h0, cntr_store     }, // mhpmcounter16
        {32'h0, cntr_sys       }, // mhpmcounter17
        {32'h0, cntr_csr       }, // mhpmcounter18
        {32'h0, cntr_luislt    }, // mhpmcounter19
        {32'h0, cntr_compressed}, // mhpmcounter20
        {32'h0, cntr_misaligned}, // mhpmcounter21
        {32'h0, cntr_mul       }, // mhpmcounter22
        {32'h0, cntr_div       }, // mhpmcounter23
        {32'h0, cntr_vaddsub   }, // mhpmcounter24
        {32'h0, cntr_vmul      }, // mhpmcounter25
        {32'h0, cntr_vdiv      }, // mhpmcounter26
        {32'h0, cntr_vmac      }, // mhpmcounter27
        {32'h0, cntr_vred      }, // mhpmcounter28
        {32'h0, cntr_vloadstore}, // mhpmcounter29
        {32'h0, cntr_vothers   }, // mhpmcounter30
        {64'h0                 }  // mhpmcounter31
    };

    logic [63:0] mhpmevent [3:31];
    if (ZIHPMEnable) begin : gen_hpmevent_on
        always_comb begin
            for (int i = 3; i < 31; i++)
                mhpmevent[i] = 64'(i);   /* Non-zero event to indicate counter is present */
            
            mhpmevent[31] = '0; /* Currently disabled */
        end
    end
    else begin : gen_hpmevent_off
        always_comb begin
            for (int i = 3; i < 32; i++)
                mhpmevent[i] = '0;
        end
    end

////////////////////////////////////////////////////////////////////////////////
// mscratch
////////////////////////////////////////////////////////////////////////////////

    logic [31:0] mscratch;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mscratch <= '0;
        else begin
            if (write_enable_i && address_i == MSCRATCH)
                mscratch <= wr_data;
        end
    end

////////////////////////////////////////////////////////////////////////////////
// mepc
////////////////////////////////////////////////////////////////////////////////

    logic [31:0] mepc;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mepc <= '0;
        else begin
            if (raise_exception_i)
                mepc <= pc_i;
            else if (interrupt_ack_i)
                mepc <= jump_i ? jump_target_i : next_pc_i;
            else if (write_enable_i && address_i == MEPC)
                mepc <= wr_data;

            mepc[0] <= 1'b0;
            if (!COMPRESSED)
                mepc[1] <= 1'b0;
        end
    end

    assign mepc_o = mepc;

////////////////////////////////////////////////////////////////////////////////
// mcause
////////////////////////////////////////////////////////////////////////////////

    logic mcause_interrupt;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mcause_interrupt <= 1'b0;
        else begin
            if (raise_exception_i)
                mcause_interrupt <= 1'b0;
            else if (interrupt_ack_i)
                mcause_interrupt <= 1'b1;
            else if (write_enable_i && address_i == MCAUSE)
                mcause_interrupt <= wr_data[31];
        end
    end

    logic [30:0] mcause_exception_code;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mcause_exception_code <= '0;
        else begin
            if (raise_exception_i)
                mcause_exception_code <= {26'b0, exception_code_i};
            else if (interrupt_ack_i)
                mcause_exception_code <= {26'b0, Interruption_Code};
            else if (write_enable_i && address_i == MCAUSE)
                mcause_exception_code <= wr_data[30:0];
        end
    end

    logic [31:0] mcause;
    assign mcause = {
        mcause_interrupt,
        mcause_exception_code
    };

////////////////////////////////////////////////////////////////////////////////
// mtval
////////////////////////////////////////////////////////////////////////////////

    logic [31:0] mtval;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mtval <= '0;
        else begin
            if (raise_exception_i) begin
                unique case (exception_code_i)
                    BREAKPOINT, 
                    LOAD_PAGE_FAULT,
                    LOAD_ACCESS_FAULT,
                    STORE_AMO_PAGE_FAULT,
                    STORE_AMO_ACCESS_FAULT,
                    INSTRUCTION_PAGE_FAULT,
                    LOAD_ADDRESS_MISALIGNED,
                    INSTRUCTION_ACCESS_FAULT,
                    STORE_AMO_ADDRESS_MISALIGNED,
                    INSTRUCTION_ADDRESS_MISALIGNED: mtval <= pc_i;
                    ILLEGAL_INSTRUCTION:            mtval <= instruction_i;
                    default:                        mtval <= '0;
                endcase
            end
            else if (interrupt_ack_i)
                mtval <= '0;
            else if (write_enable_i && address_i == MTVAL)
                mtval <= wr_data;
        end
    end

////////////////////////////////////////////////////////////////////////////////
// menvcfg
////////////////////////////////////////////////////////////////////////////////

    logic [63:0] menvcfg;
    assign menvcfg = {
         1'b0, // STCE
         1'b0, // PBMTE
         1'b0, // ADUE
         1'b0, // CDE
        26'b0, // WPRI
         2'b0, // PMM
        24'b0, // WPRI
         1'b0, // CBZE
         1'b0, // CBCFE
         2'b0, // CBIE
         3'b0, // WPRI
         1'b0  // FIOM
    };

////////////////////////////////////////////////////////////////////////////////
// Privilege control
////////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            privilege <= privilegeLevel_e'(2'b11);
        else if(sys_reset)
            privilege <= privilegeLevel_e'(2'b11);
        else begin
            if (machine_return_i) 
                privilege <= privilegeLevel_e'(mstatus_mpp);
            else if (raise_exception_i || interrupt_ack_i)
                privilege <= privilegeLevel_e'(2'b11);
        end
    end

    assign privilege_o = privilege;

//////////////////////////////////////////////////////////////////////////////
// CSRs definition
//////////////////////////////////////////////////////////////////////////////

    /* Signals enabled with XOSVM */
    /* verilator lint_off UNUSEDSIGNAL */
    logic [31:0] mvmdo, mvmio, mvmds, mvmis, mvmdm, mvmim;
    logic        mvmctl;
    /* verilator lint_on UNUSEDSIGNAL */

    logic [31:0] wr_data, wmask, current_val;

    interruptionCode_e Interruption_Code;

//////////////////////////////////////////////////////////////////////////////
// Masks and Current Value
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        wmask = '1;
        case (address_i)
            MSTATUS:       begin current_val = mstatus;         wmask = 32'h00001888; end
            MTVEC:         begin current_val = mtvec;           wmask = 32'hFFFFFFFC; end
            MIP:           begin current_val = mip;             wmask = 32'h00000888; end
            MIE:           begin current_val = mie;             wmask = 32'h00000888; end
            /* @todo mcounteren as RW */
            MCOUNTINHIBIT: begin current_val = mcountinhibit;   wmask = 32'h7FFFFFFD; end
            MCYCLE:        begin current_val = mcycle[31:0];    wmask = 32'hFFFFFFFF; end
            MCYCLEH:       begin current_val = mcycle[63:32];   wmask = 32'hFFFFFFFF; end
            MINSTRET:      begin current_val = minstret[31:0];  wmask = 32'hFFFFFFFF; end
            MINSTRETH:     begin current_val = minstret[63:32]; wmask = 32'hFFFFFFFF; end
            /* @todo All mphmpcounter as RW */
            MSCRATCH:      begin current_val = mscratch;        wmask = 32'hFFFFFFFF; end
            MEPC:          begin current_val = mepc;            wmask = COMPRESSED ? 32'hFFFFFFFE : 32'hFFFFFFFC; end
            MCAUSE:        begin current_val = mcause;          wmask = 32'hFFFFFFFF; end
            MTVAL:         begin current_val = mtval;           wmask = 32'hFFFFFFFF; end

            MVMDO:         begin current_val = mvmdo;           wmask = 32'hFFFFFFFC; end
            MVMDS:         begin current_val = mvmds;           wmask = 32'hFFFFFFFC; end
            MVMDM:         begin current_val = mvmdm;           wmask = 32'hFFFFFFFC; end
            MVMIO:         begin current_val = mvmio;           wmask = 32'hFFFFFFFC; end
            MVMIS:         begin current_val = mvmis;           wmask = 32'hFFFFFFFC; end
            MVMIM:         begin current_val = mvmim;           wmask = 32'hFFFFFFFC; end
            MVMCTL:        begin current_val = {31'b0, mvmctl}; wmask = 32'h00000001; end

            default:       begin current_val = '0;              wmask = 32'h00000000; end
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Operation
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        case (operation_i)
            SET:     wr_data = (current_val | (data_i & wmask));
            CLEAR:   wr_data = (current_val & ~(data_i & wmask));
            default: wr_data = (current_val & ~wmask) | (data_i & wmask); // WRITE
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// CSR Reading
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (read_enable_i) begin
            case(address_i)
                /* Machine-Level CSRs */
                MISA:           out = misa;
                MVENDORID:      out = '0;
                MARCHID:        out = '0;
                MIMPID:         out = '0;
                MHARTID:        out = '0;
                MSTATUS:        out = mstatus;
                MTVEC:          out = mtvec;
                MIP:            out = mip;
                MIE:            out = mie;
                MCOUNTEREN:     out = mcounteren;
                MCOUNTINHIBIT:  out = mcountinhibit;
                MCYCLE:         out = mcycle[31:0];
                MCYCLEH:        out = mcycle[63:32];
                MINSTRET:       out = minstret[31:0];
                MINSTRETH:      out = minstret[63:32];
                MHPMCOUNTER3:   out = mhpmcounter[ 3][31: 0];
                MHPMCOUNTER4:   out = mhpmcounter[ 4][31: 0];
                MHPMCOUNTER5:   out = mhpmcounter[ 5][31: 0];
                MHPMCOUNTER6:   out = mhpmcounter[ 6][31: 0];
                MHPMCOUNTER7:   out = mhpmcounter[ 7][31: 0];
                MHPMCOUNTER8:   out = mhpmcounter[ 8][31: 0];
                MHPMCOUNTER9:   out = mhpmcounter[ 9][31: 0];
                MHPMCOUNTER10:  out = mhpmcounter[10][31: 0];
                MHPMCOUNTER11:  out = mhpmcounter[11][31: 0];
                MHPMCOUNTER12:  out = mhpmcounter[12][31: 0];
                MHPMCOUNTER13:  out = mhpmcounter[13][31: 0];
                MHPMCOUNTER14:  out = mhpmcounter[14][31: 0];
                MHPMCOUNTER15:  out = mhpmcounter[15][31: 0];
                MHPMCOUNTER16:  out = mhpmcounter[16][31: 0];
                MHPMCOUNTER17:  out = mhpmcounter[17][31: 0];
                MHPMCOUNTER18:  out = mhpmcounter[18][31: 0];
                MHPMCOUNTER19:  out = mhpmcounter[19][31: 0];
                MHPMCOUNTER20:  out = mhpmcounter[20][31: 0];
                MHPMCOUNTER21:  out = mhpmcounter[21][31: 0];
                MHPMCOUNTER22:  out = mhpmcounter[22][31: 0];
                MHPMCOUNTER23:  out = mhpmcounter[23][31: 0];
                MHPMCOUNTER24:  out = mhpmcounter[24][31: 0];
                MHPMCOUNTER25:  out = mhpmcounter[25][31: 0];
                MHPMCOUNTER26:  out = mhpmcounter[26][31: 0];
                MHPMCOUNTER27:  out = mhpmcounter[27][31: 0];
                MHPMCOUNTER28:  out = mhpmcounter[28][31: 0];
                MHPMCOUNTER29:  out = mhpmcounter[29][31: 0];
                MHPMCOUNTER30:  out = mhpmcounter[30][31: 0];
                MHPMCOUNTER31:  out = mhpmcounter[31][31: 0];
                MHPMCOUNTER3H:  out = mhpmcounter[ 3][63:32];
                MHPMCOUNTER4H:  out = mhpmcounter[ 4][63:32];
                MHPMCOUNTER5H:  out = mhpmcounter[ 5][63:32];
                MHPMCOUNTER6H:  out = mhpmcounter[ 6][63:32];
                MHPMCOUNTER7H:  out = mhpmcounter[ 7][63:32];
                MHPMCOUNTER8H:  out = mhpmcounter[ 8][63:32];
                MHPMCOUNTER9H:  out = mhpmcounter[ 9][63:32];
                MHPMCOUNTER10H: out = mhpmcounter[10][63:32];
                MHPMCOUNTER11H: out = mhpmcounter[11][63:32];
                MHPMCOUNTER12H: out = mhpmcounter[12][63:32];
                MHPMCOUNTER13H: out = mhpmcounter[13][63:32];
                MHPMCOUNTER14H: out = mhpmcounter[14][63:32];
                MHPMCOUNTER15H: out = mhpmcounter[15][63:32];
                MHPMCOUNTER16H: out = mhpmcounter[16][63:32];
                MHPMCOUNTER17H: out = mhpmcounter[17][63:32];
                MHPMCOUNTER18H: out = mhpmcounter[18][63:32];
                MHPMCOUNTER19H: out = mhpmcounter[19][63:32];
                MHPMCOUNTER20H: out = mhpmcounter[20][63:32];
                MHPMCOUNTER21H: out = mhpmcounter[21][63:32];
                MHPMCOUNTER22H: out = mhpmcounter[22][63:32];
                MHPMCOUNTER23H: out = mhpmcounter[23][63:32];
                MHPMCOUNTER24H: out = mhpmcounter[24][63:32];
                MHPMCOUNTER25H: out = mhpmcounter[25][63:32];
                MHPMCOUNTER26H: out = mhpmcounter[26][63:32];
                MHPMCOUNTER27H: out = mhpmcounter[27][63:32];
                MHPMCOUNTER28H: out = mhpmcounter[28][63:32];
                MHPMCOUNTER29H: out = mhpmcounter[29][63:32];
                MHPMCOUNTER30H: out = mhpmcounter[30][63:32];
                MHPMCOUNTER31H: out = mhpmcounter[31][63:32];
                MHPMEVENT3:     out = mhpmevent  [ 3][31: 0];
                MHPMEVENT4:     out = mhpmevent  [ 4][31: 0];
                MHPMEVENT5:     out = mhpmevent  [ 5][31: 0];
                MHPMEVENT6:     out = mhpmevent  [ 6][31: 0];
                MHPMEVENT7:     out = mhpmevent  [ 7][31: 0];
                MHPMEVENT8:     out = mhpmevent  [ 8][31: 0];
                MHPMEVENT9:     out = mhpmevent  [ 9][31: 0];
                MHPMEVENT10:    out = mhpmevent  [10][31: 0];
                MHPMEVENT11:    out = mhpmevent  [11][31: 0];
                MHPMEVENT12:    out = mhpmevent  [12][31: 0];
                MHPMEVENT13:    out = mhpmevent  [13][31: 0];
                MHPMEVENT14:    out = mhpmevent  [14][31: 0];
                MHPMEVENT15:    out = mhpmevent  [15][31: 0];
                MHPMEVENT16:    out = mhpmevent  [16][31: 0];
                MHPMEVENT17:    out = mhpmevent  [17][31: 0];
                MHPMEVENT18:    out = mhpmevent  [18][31: 0];
                MHPMEVENT19:    out = mhpmevent  [19][31: 0];
                MHPMEVENT20:    out = mhpmevent  [20][31: 0];
                MHPMEVENT21:    out = mhpmevent  [21][31: 0];
                MHPMEVENT22:    out = mhpmevent  [22][31: 0];
                MHPMEVENT23:    out = mhpmevent  [23][31: 0];
                MHPMEVENT24:    out = mhpmevent  [24][31: 0];
                MHPMEVENT25:    out = mhpmevent  [25][31: 0];
                MHPMEVENT26:    out = mhpmevent  [26][31: 0];
                MHPMEVENT27:    out = mhpmevent  [27][31: 0];
                MHPMEVENT28:    out = mhpmevent  [28][31: 0];
                MHPMEVENT29:    out = mhpmevent  [29][31: 0];
                MHPMEVENT30:    out = mhpmevent  [30][31: 0];
                MHPMEVENT31:    out = mhpmevent  [31][31: 0];
                MHPMEVENT3H:    out = mhpmevent  [ 3][63:32];
                MHPMEVENT4H:    out = mhpmevent  [ 4][63:32];
                MHPMEVENT5H:    out = mhpmevent  [ 5][63:32];
                MHPMEVENT6H:    out = mhpmevent  [ 6][63:32];
                MHPMEVENT7H:    out = mhpmevent  [ 7][63:32];
                MHPMEVENT8H:    out = mhpmevent  [ 8][63:32];
                MHPMEVENT9H:    out = mhpmevent  [ 9][63:32];
                MHPMEVENT10H:   out = mhpmevent  [10][63:32];
                MHPMEVENT11H:   out = mhpmevent  [11][63:32];
                MHPMEVENT12H:   out = mhpmevent  [12][63:32];
                MHPMEVENT13H:   out = mhpmevent  [13][63:32];
                MHPMEVENT14H:   out = mhpmevent  [14][63:32];
                MHPMEVENT15H:   out = mhpmevent  [15][63:32];
                MHPMEVENT16H:   out = mhpmevent  [16][63:32];
                MHPMEVENT17H:   out = mhpmevent  [17][63:32];
                MHPMEVENT18H:   out = mhpmevent  [18][63:32];
                MHPMEVENT19H:   out = mhpmevent  [19][63:32];
                MHPMEVENT20H:   out = mhpmevent  [20][63:32];
                MHPMEVENT21H:   out = mhpmevent  [21][63:32];
                MHPMEVENT22H:   out = mhpmevent  [22][63:32];
                MHPMEVENT23H:   out = mhpmevent  [23][63:32];
                MHPMEVENT24H:   out = mhpmevent  [24][63:32];
                MHPMEVENT25H:   out = mhpmevent  [25][63:32];
                MHPMEVENT26H:   out = mhpmevent  [26][63:32];
                MHPMEVENT27H:   out = mhpmevent  [27][63:32];
                MHPMEVENT28H:   out = mhpmevent  [28][63:32];
                MHPMEVENT29H:   out = mhpmevent  [29][63:32];
                MHPMEVENT30H:   out = mhpmevent  [30][63:32];
                MHPMEVENT31H:   out = mhpmevent  [31][63:32];
                MSCRATCH:       out = mscratch;
                MEPC:           out = mepc;
                MCAUSE:         out = mcause;
                MTVAL:          out = mtval;
                MCONFIGPTR:     out = '0;
                MENVCFG:        out = menvcfg[31:0];
                MENVCFGH:       out = menvcfg[63:32];

                /* V CSRs */
                VSTART:         out = '0;
                VLENBYTES:      out = VLEN/8;
                VTYPE:          out = vtype_i;
                VL:             out = vlen_i;
                
                /* Zicntr */
                CYCLE:          out = mcycle[31:0];
                TIME:           out = mtime_i[31:0];
                INSTRET:        out = minstret[31:0];
                CYCLEH:         out = mcycle[63:32];
                TIMEH:          out = mtime_i[63:32];
                INSTRETH:       out = minstret[63:32];

                /* Zihpm */
                /* @todo */

                /* Xosvm */
                MVMCTL:         out = {31'b0,mvmctl};
                MVMDO:          out = mvmdo[31:0];
                MVMDS:          out = mvmds[31:0];
                MVMDM:          out = mvmdm[31:0];
                MVMIO:          out = mvmio[31:0];
                MVMIS:          out = mvmis[31:0];
                MVMIM:          out = mvmim[31:0];

                default:        out = '0;
            endcase
        end
        else begin
            out = '0;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// XOSVM Extension
//////////////////////////////////////////////////////////////////////////////

    if (XOSVMEnable == 1'b1) begin : gen_xosvm_csr_on
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n) begin
                mvmctl      <= '0;
                mvmdo       <= '0;
                mvmds       <= '0;
                mvmdm       <= '0;
                mvmio       <= '0;
                mvmis       <= '0;
                mvmim       <= '0;
            end
            else if (sys_reset) begin
                mvmctl      <= '0;
                mvmdo       <= '0;
                mvmds       <= '0;
                mvmdm       <= '0;
                mvmio       <= '0;
                mvmis       <= '0;
                mvmim       <= '0;
            end
            else if (write_enable_i) begin
                case (address_i)
                    MVMCTL:     mvmctl  <= wr_data[0];
                    MVMDO:      mvmdo   <= wr_data;
                    MVMDS:      mvmds   <= wr_data;
                    MVMDM:      mvmdm   <= wr_data;
                    MVMIO:      mvmio   <= wr_data;
                    MVMIS:      mvmis   <= wr_data;
                    MVMIM:      mvmim   <= wr_data;
                    default: ;
                endcase
            end
        end
    end
    else begin : gen_xosvm_csr_off
        assign mvmctl   = '0;
        assign mvmdo    = '0;
        assign mvmds    = '0;
        assign mvmdm    = '0;
        assign mvmio    = '0;
        assign mvmis    = '0;
        assign mvmim    = '0;
    end

    assign mvmctl_o = mvmctl;
    assign mvmdo_o  = mvmdo;
    assign mvmds_o  = mvmds;
    assign mvmdm_o  = mvmdm;
    assign mvmio_o  = mvmio;
    assign mvmis_o  = mvmis;
    assign mvmim_o  = mvmim;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Interrupt Control
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    logic MEIP, MTIP, MSIP;
    assign  MEIP = mip[11],
            MTIP = mip[ 7],
            MSIP = mip[ 3];

    logic MEIE, MTIE, MSIE;
    assign  MEIE = mie[11],
            MTIE = mie[ 7],
            MSIE = mie[ 3];

    always_ff @(posedge clk or negedge reset_n) begin
        if(!reset_n) begin
            Interruption_Code   <= NO_INT;
            interrupt_pending_o <= 1'b0;
        end
        else begin
            if (mstatus_mie && (mie & mip) != '0 && !interrupt_ack_i) begin
                interrupt_pending_o <= 1;
                if ((MEIP & MEIE) == 1'b1)          // Machine External
                    Interruption_Code <= M_EXT_INT;
                else if ((MSIP & MSIE) == 1'b1)     // Machine Software
                    Interruption_Code <= M_SW_INT;
                else if ((MTIP & MTIE) == 1'b1)     // Machine Timer
                    Interruption_Code <= M_TIM_INT;
            end
            else begin
                interrupt_pending_o <= 0;
            end
        end
    end

////////////////////////////////////////////////////////////////////////////////
// Profiling
////////////////////////////////////////////////////////////////////////////////

`ifndef SYNTH
    if (PROFILING) begin : gen_profiling
        int fd;

        initial begin
            fd = $fopen(PROFILING_FILE, "w");
            if (fd == 0) begin
                $display("Error\ opening profiling file");
            end
        end

        final begin
            $fwrite(fd,"Clock Cycles:            %0d\n", mcycle);
            $fwrite(fd,"Instructions Retired:    %0d\n", minstret);
            if (COMPRESSED == 1'b1) begin
                $fwrite(fd,"Instructions Compressed: %0d\n", cntr_compressed);
            end
            $fwrite(fd,"Instructions Killed:     %0d\n", cntr_killed);
            $fwrite(fd,"Context Switches:        %0d\n", cntr_context);
            $fwrite(fd,"Exceptions Raised:       %0d\n", cntr_exception);
            $fwrite(fd,"Interrupts Acked:        %0d\n", cntr_irq);
            if (COMPRESSED == 1'b1) begin
                $fwrite(fd,"Misaligned Jumps:        %0d\n", cntr_misaligned);
            end

            $fwrite(fd,"\nCYCLES WITH::\n");
            $fwrite(fd,"HAZARDS:                 %0d\n", cntr_hazard);
            $fwrite(fd,"STALL:                   %0d\n", cntr_stall);
            $fwrite(fd,"BUBBLES (INC. HAZARDS):  %0d\n", cntr_nop);

            $fwrite(fd,"\nINSTRUCTION COUNTERS:\n");
            $fwrite(fd,"LUI_SLT:                 %0d\n", cntr_luislt);
            $fwrite(fd,"LOGIC:                   %0d\n", cntr_logic);
            $fwrite(fd,"ADDSUB:                  %0d\n", cntr_addsub);
            $fwrite(fd,"SHIFT:                   %0d\n", cntr_shift);
            $fwrite(fd,"BRANCH:                  %0d\n", cntr_branch);
            $fwrite(fd,"JUMP:                    %0d\n", cntr_jump);
            $fwrite(fd,"LOAD:                    %0d\n", cntr_load);
            $fwrite(fd,"STORE:                   %0d\n", cntr_store);
            $fwrite(fd,"SYS:                     %0d\n", cntr_sys);
            $fwrite(fd,"CSR:                     %0d\n", cntr_csr);
            $fwrite(fd,"MUL:                     %0d\n", cntr_mul);
            $fwrite(fd,"DIV:                     %0d\n", cntr_div);
        
            if(VEnable) begin
                $fwrite(fd, "\nVECTOR EXTENSION:\n");
                $fwrite(fd, "VADDSUB:                 %0d\n", cntr_vaddsub);
                $fwrite(fd, "VMUL:                    %0d\n", cntr_vmul);
                $fwrite(fd, "VDIV:                    %0d\n", cntr_vdiv);
                $fwrite(fd, "VMAC:                    %0d\n", cntr_vmac);
                $fwrite(fd, "VRED:                    %0d\n", cntr_vred);
                $fwrite(fd, "VLOAD/VSTORE:            %0d\n", cntr_vloadstore);
                $fwrite(fd, "VOTHERS:                 %0d\n", cntr_vothers);
            end
        end
    end
`endif

endmodule
