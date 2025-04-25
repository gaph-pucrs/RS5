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
    input   logic [11:0]        address_i,
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

    output  logic [31:0]        mepc,
    output  logic [31:0]        mtvec_o,

    output  logic               mvmctl_o,
    output  logic [31:0]        mvmdo_o,
    output  logic [31:0]        mvmio_o,
    output  logic [31:0]        mvmds_o,
    output  logic [31:0]        mvmis_o,
    output  logic [31:0]        mvmim_o,
    output  logic [31:0]        mvmdm_o
);

    CSRs CSR;
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
            else if (write_enable_i && CSR == MSTATUS)
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
            else if (write_enable_i && CSR == MSTATUS)
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
            else if (write_enable_i && CSR == MSTATUS)
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
            if (write_enable_i && CSR == MTVEC)
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
            if (write_enable_i && CSR == MIP)
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
            if (write_enable_i && CSR == MIP)
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
            if (write_enable_i && CSR == MIP)
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
            if (write_enable_i && CSR == MIE)
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
            if (write_enable_i && CSR == MIE)
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
            if (write_enable_i && CSR == MIE)
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
// mcycle and minstret
////////////////////////////////////////////////////////////////////////////////

    logic [63:0] mcycle;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mcycle <= '0;
        else if (sys_reset)
            mcycle <= '0;
        else begin
            mcycle <= mcycle + 1'b1;
            if (write_enable_i) begin
                unique case(CSR)
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
            if (!(hold || instruction_operation_i == NOP))
                minstret <= minstret + 1'b1;

            if (write_enable_i) begin
                unique case(CSR)
                    MINSTRET:  minstret[31:0] <= wr_data;
                    MINSTRETH: minstret[63:32] <= wr_data;
                    default: ;
                endcase
            end
        end
    end

////////////////////////////////////////////////////////////////////////////////
// mhpmcounter and mhpmevent
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// CSRs definition
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] mscratch, mepc_r, mcause, mtval;

    /* Signals enabled with XOSVM */
    /* verilator lint_off UNUSEDSIGNAL */
    logic [31:0] mvmdo, mvmio, mvmds, mvmis, mvmdm, mvmim;
    logic        mvmctl;
    /* verilator lint_on UNUSEDSIGNAL */

    logic [31:0] wr_data, wmask, current_val;

    logic [31:0] instructions_killed_counter, hazard_counter, stall_counter, nop_counter;
    logic [31:0] interrupt_ack_counter, raise_exception_counter, context_switch_counter;
    logic [31:0] logic_counter, addsub_counter, lui_slt_counter, shift_counter;
    logic [31:0] branch_counter, jump_counter;
    logic [31:0] load_counter, store_counter;
    logic [31:0] sys_counter, csr_counter;
    logic [31:0] compressed_counter, jump_misaligned_counter;
    logic [31:0] mcountinhibit;
    interruptionCode_e Interruption_Code;

    /* Signals enabled with ZIHPM */
    /* verilator lint_off UNUSEDSIGNAL */
    logic [31:0] mul_counter, div_counter;
    /* verilator lint_on UNUSEDSIGNAL */

    /* vector extension profiling signals */
    logic [31:0] vaddsub_counter, vmul_counter, vdiv_counter, vmac_counter, vred_counter, 
                 vloadstore_counter, vothers_counter;

//////////////////////////////////////////////////////////////////////////////
// MCAUSE and MSTATUS CSRs
//////////////////////////////////////////////////////////////////////////////

    logic        mcause_interrupt;
    logic [30:0] mcause_exc_code;

    assign mcause = {mcause_interrupt, mcause_exc_code};

//////////////////////////////////////////////////////////////////////////////
// Assigns
//////////////////////////////////////////////////////////////////////////////

    assign privilege_o = privilege;
    
    assign mepc        = mepc_r;

    assign CSR = CSRs'(address_i);

//////////////////////////////////////////////////////////////////////////////
// Masks and Current Value
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        wmask = '1;
        case (CSR)
            MSTATUS:       begin current_val = mstatus;         wmask = 32'h00001888; end
            MTVEC:         begin current_val = mtvec;           wmask = 32'hFFFFFFFC; end
            MIP:           begin current_val = mip;             wmask = 32'h00000888; end
            MIE:           begin current_val = mie;             wmask = 32'h00000888; end
            MCYCLE:        begin current_val = mcycle[31:0];    wmask = 32'hFFFFFFFF; end
            MCYCLEH:       begin current_val = mcycle[63:32];   wmask = 32'hFFFFFFFF; end
            MINSTRET:      begin current_val = minstret[31:0];  wmask = 32'hFFFFFFFF; end
            MINSTRETH:     begin current_val = minstret[63:32]; wmask = 32'hFFFFFFFF; end

            // MCOUNTEREN: begin current_val = mcounteren;      wmask = '1; end
            MSCRATCH:      begin current_val = mscratch;        wmask = 32'hFFFFFFFF; end
            MEPC:          begin current_val = mepc_r;          wmask = COMPRESSED ? 32'hFFFFFFFE : 32'hFFFFFFFC; end
            MCAUSE:        begin current_val = mcause;          wmask = 32'hFFFFFFFF; end
            MTVAL:         begin current_val = mtval;           wmask = 32'hFFFFFFFF; end
            MCOUNTINHIBIT: begin current_val = mcountinhibit;   wmask = 32'hFFFFFFFF; end

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
// CSR Writing
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        //////////////////////////////////////////////////////////////////////////////
        // Reset
        //////////////////////////////////////////////////////////////////////////////
        if (!reset_n) begin
            mcountinhibit    <= '0;            
            //mcounteren     <= '0;
            mscratch         <= '0;
            mepc_r           <= '0;
            mcause_interrupt <= '0;
            mcause_exc_code  <= '0;
            mtval            <= '0;
            privilege        <= privilegeLevel_e'(2'b11);
        end
        else if(sys_reset) begin
            mcountinhibit    <= '0;
            //mcounteren     <= '0;
            mscratch         <= '0;
            mepc_r           <= '0;
            mcause_interrupt <= '0;
            mcause_exc_code  <= '0;
            mtval            <= '0;
            privilege        <= privilegeLevel_e'(2'b11);
        end
        //////////////////////////////////////////////////////////////////////////////
        // Cycle Updates
        //////////////////////////////////////////////////////////////////////////////
        else begin
        //////////////////////////////////////////////////////////////////////////////
        // Machine Return
        //////////////////////////////////////////////////////////////////////////////
            if (machine_return_i == 1'b1) begin
                privilege       <= privilegeLevel_e'(mstatus_mpp);
            end
        //////////////////////////////////////////////////////////////////////////////
        // Exception
        //////////////////////////////////////////////////////////////////////////////
            else if (raise_exception_i == 1'b1) begin
                mcause_interrupt<= '0;
                mcause_exc_code <= {26'b0, exception_code_i};
                privilege       <= privilegeLevel_e'(2'b11);
                mepc_r          <= pc_i;
                mtval           <= (exception_code_i == ILLEGAL_INSTRUCTION)
                                    ? instruction_i
                                    : pc_i;
            end
        //////////////////////////////////////////////////////////////////////////////
        // Interrupt
        //////////////////////////////////////////////////////////////////////////////
            else if (interrupt_ack_i == 1'b1) begin
                mcause_interrupt<= '1;
                mcause_exc_code <= {26'b0, Interruption_Code};
                privilege       <= privilegeLevel_e'(2'b11);

                /* Interrupted instruction is in fact the next instruction,
                 * because this one will be retired completely before taking
                 * the trap
                 */
                if (jump_i)
                    mepc_r      <= jump_target_i;
                else
                    mepc_r      <= next_pc_i;
            end
        //////////////////////////////////////////////////////////////////////////////
        // CSR Write
        //////////////////////////////////////////////////////////////////////////////
            else if (write_enable_i) begin
                case(CSR)
                    // MCOUNTEREN:  mcounteren          <= wr_data;
                    MSCRATCH:       mscratch            <= wr_data;
                    MEPC:           mepc_r              <= wr_data;
                    MTVAL:          mtval               <= wr_data;
                    MCOUNTINHIBIT:  mcountinhibit       <= wr_data;
                    MCAUSE: begin
                                    mcause_interrupt    <= wr_data[31];
                                    mcause_exc_code     <= wr_data[30:0];
                            end
                    default:    ; // no op
                endcase
            end
        end
    end

//////////////////////////////////////////////////////////////////////////////
// CSR Reading
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (read_enable_i) begin
            case(CSR)
                MISA:           out = misa;
                MSTATUS:        out = mstatus;
                MTVEC:          out = mtvec;
                MIP:            out = mip;
                MIE:            out = mie;
                MCYCLE:         out = mcycle[31:0];
                MCYCLEH:        out = mcycle[63:32];
                MINSTRET:       out = minstret[31:0];
                MINSTRETH:      out = minstret[63:32];

                //RO
                MCONFIGPTR:     out = '0;
                // MCOUNTEREN:  out = mcounteren;
                MSCRATCH:       out = mscratch;
                MEPC:           out = mepc_r;
                MCAUSE:         out = mcause;
                MTVAL:          out = mtval;

                //RO
                CYCLE:          out = mcycle[31:0];
                TIME:           out = mtime_i[31:0];
                INSTRET:        out = minstret[31:0];

                MHPMCOUNTER3:   out = instructions_killed_counter;
                MHPMCOUNTER4:   out = context_switch_counter;
                MHPMCOUNTER5:   out = raise_exception_counter;
                MHPMCOUNTER6:   out = interrupt_ack_counter;
                MHPMCOUNTER7:   out = hazard_counter;
                MHPMCOUNTER8:   out = stall_counter;
                MHPMCOUNTER9:   out = nop_counter;
                MHPMCOUNTER10:  out = logic_counter;
                MHPMCOUNTER11:  out = addsub_counter;
                MHPMCOUNTER12:  out = shift_counter;
                MHPMCOUNTER13:  out = branch_counter;
                MHPMCOUNTER14:  out = jump_counter;
                MHPMCOUNTER15:  out = load_counter;
                MHPMCOUNTER16:  out = store_counter;
                MHPMCOUNTER17:  out = sys_counter;
                MHPMCOUNTER18:  out = csr_counter;
                MHPMCOUNTER19:  out = lui_slt_counter;
                MHPMCOUNTER20:  out = compressed_counter;
                MHPMCOUNTER21:  out = jump_misaligned_counter;
                MHPMCOUNTER22:  out = mul_counter;
                MHPMCOUNTER23:  out = div_counter;

                // Vector Extension counters
                MHPMCOUNTER24:  out = vaddsub_counter;
                MHPMCOUNTER25:  out = vmul_counter;
                MHPMCOUNTER26:  out = vdiv_counter;
                MHPMCOUNTER27:  out = vmac_counter;
                MHPMCOUNTER28:  out = vred_counter;
                MHPMCOUNTER29:  out = vloadstore_counter;
                MHPMCOUNTER30:  out = vothers_counter;

                CYCLEH:         out = mcycle[63:32];
                TIMEH:          out = mtime_i[63:32];
                INSTRETH:       out = minstret[63:32];

                MCOUNTINHIBIT:  out = mcountinhibit;

                MVMCTL:         out = {31'b0,mvmctl};
                MVMDO:          out = mvmdo[31:0];
                MVMDS:          out = mvmds[31:0];
                MVMDM:          out = mvmdm[31:0];
                MVMIO:          out = mvmio[31:0];
                MVMIS:          out = mvmis[31:0];
                MVMIM:          out = mvmim[31:0];

                // Vector Extension CSRs
                VSTART:         out = '0;
                VLENBYTES:      out = VLEN/8;
                VTYPE:          out = vtype_i;
                VL:             out = vlen_i;

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
                case (CSR)
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZIHPM
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (ZIHPMEnable == 1'b1) begin : gen_zihpm_csr_on
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n) begin
                instructions_killed_counter <= '0;
                nop_counter                 <= '0;
                logic_counter               <= '0;
                addsub_counter              <= '0;
                shift_counter               <= '0;
                branch_counter              <= '0;
                jump_counter                <= '0;
                load_counter                <= '0;
                store_counter               <= '0;
                sys_counter                 <= '0;
                lui_slt_counter             <= '0;
                csr_counter                 <= '0;
                mul_counter                 <= '0;
                div_counter                 <= '0;

                vaddsub_counter             <= '0;
                vmul_counter                <= '0;
                vdiv_counter                <= '0;
                vmac_counter                <= '0;
                vred_counter                <= '0;
                vloadstore_counter          <= '0;
                vothers_counter             <= '0;

                if (COMPRESSED == 1'b1) begin
                    jump_misaligned_counter     <= '0;
                    compressed_counter          <= '0;
                end

                hazard_counter              <= '0;
                stall_counter               <= '0;
                interrupt_ack_counter       <= '0;
                raise_exception_counter     <= '0;
                context_switch_counter      <= '0;
            end
            else if (sys_reset) begin
                instructions_killed_counter <= '0;
                nop_counter                 <= '0;
                logic_counter               <= '0;
                addsub_counter              <= '0;
                shift_counter               <= '0;
                branch_counter              <= '0;
                jump_counter                <= '0;
                load_counter                <= '0;
                store_counter               <= '0;
                sys_counter                 <= '0;
                lui_slt_counter             <= '0;
                csr_counter                 <= '0;
                mul_counter                 <= '0;
                div_counter                 <= '0;

                vaddsub_counter             <= '0;
                vmul_counter                <= '0;
                vdiv_counter                <= '0;
                vmac_counter                <= '0;
                vred_counter                <= '0;
                vloadstore_counter          <= '0;
                vothers_counter             <= '0;

                if (COMPRESSED == 1'b1) begin
                    jump_misaligned_counter     <= '0;
                    compressed_counter          <= '0;
                end

                hazard_counter              <= '0;
                stall_counter               <= '0;
                interrupt_ack_counter       <= '0;
                raise_exception_counter     <= '0;
                context_switch_counter      <= '0;
            end
            else begin
                instructions_killed_counter <= (killed                                                               && !mcountinhibit[ 3]) ? instructions_killed_counter  + 1 : instructions_killed_counter;

                hazard_counter              <= (hazard && !hold                                                      && !mcountinhibit[ 7]) ? hazard_counter + 1 : hazard_counter;
                stall_counter               <= (stall                                                                && !mcountinhibit[ 8]) ? stall_counter  + 1 : stall_counter;

                interrupt_ack_counter       <= (interrupt_ack_i                                                      && !mcountinhibit[ 6]) ? interrupt_ack_counter   + 1 : interrupt_ack_counter;
                raise_exception_counter     <= (raise_exception_i                                                    && !mcountinhibit[ 5]) ? raise_exception_counter + 1 : raise_exception_counter;
                context_switch_counter      <= ((jump_i || raise_exception_i || machine_return_i || interrupt_ack_i) && !mcountinhibit[ 4]) ? context_switch_counter  + 1 : context_switch_counter;
                nop_counter                 <= (instruction_operation_i == NOP && !hold                              && !mcountinhibit[ 9]) ? nop_counter             + 1 : nop_counter;

                if (COMPRESSED == 1'b1) begin
                    jump_misaligned_counter <= jump_misaligned_counter + ((jump_misaligned_i && !hold && !mcountinhibit[21]) ? 1 : 0);
                end

                if (!hold) begin
                    logic_counter           <= (instruction_operation_i inside {XOR, OR, AND})                                && !mcountinhibit[10] ? logic_counter   + 1 : logic_counter;
                    addsub_counter          <= (instruction_operation_i inside {ADD, SUB})                                    && !mcountinhibit[11] ? addsub_counter  + 1 : addsub_counter;
                    lui_slt_counter         <= (instruction_operation_i inside {SLTU, SLT, LUI})                              && !mcountinhibit[19] ? lui_slt_counter + 1 : lui_slt_counter;
                    shift_counter           <= (instruction_operation_i inside {SLL, SRL, SRA})                               && !mcountinhibit[12] ? shift_counter   + 1 : shift_counter;
                    branch_counter          <= (instruction_operation_i inside {BEQ, BNE, BLT, BLTU, BGE, BGEU})              && !mcountinhibit[13] ? branch_counter  + 1 : branch_counter;
                    jump_counter            <= (instruction_operation_i inside {JAL, JALR})                                   && !mcountinhibit[14] ? jump_counter    + 1 : jump_counter;
                    load_counter            <= (instruction_operation_i inside {LB, LBU, LH, LHU, LW})                        && !mcountinhibit[15] ? load_counter    + 1 : load_counter;
                    store_counter           <= (instruction_operation_i inside {SB, SH, SW})                                  && !mcountinhibit[16] ? store_counter   + 1 : store_counter;
                    sys_counter             <= (instruction_operation_i inside {SRET, MRET, WFI, ECALL, EBREAK})              && !mcountinhibit[17] ? sys_counter     + 1 : sys_counter;
                    csr_counter             <= (instruction_operation_i inside {CSRRW, CSRRWI, CSRRS, CSRRSI, CSRRC, CSRRCI}) && !mcountinhibit[18] ? csr_counter     + 1 : csr_counter;
                    mul_counter             <= (instruction_operation_i inside {MUL, MULH, MULHU, MULHSU})                    && !mcountinhibit[22] ? mul_counter     + 1 : mul_counter;
                    div_counter             <= (instruction_operation_i inside {DIV, DIVU, REM, REMU})                        && !mcountinhibit[23] ? div_counter     + 1 : div_counter;

                if(VEnable) begin
                        vloadstore_counter      <= (instruction_operation_i inside {VLOAD, VSTORE})                           && !mcountinhibit[29] ? vloadstore_counter + 1 : vloadstore_counter;
        
                        if(instruction_operation_i == VECTOR) begin

                            vaddsub_counter     <= (vector_operation_i      inside {VADD, VSUB, VRSUB})                       && !mcountinhibit[24] ? vaddsub_counter    + 1 : vaddsub_counter;
                            
                            vmul_counter        <= (vector_operation_i      inside {
                                                                                    VMUL, VMULH, VMULHU, VMULHSU,                               // non-widening multiplication
                                                                                    VWMUL, VWMULU, VWMULSU                                      // widening multiplication
                                                                                   })   && !mcountinhibit[25] ?  vmul_counter    + 1 : vmul_counter;

                            vdiv_counter        <= (vector_operation_i      inside {VDIV, VDIVU, VREM, VREMU})                    && !mcountinhibit[26] ? vdiv_counter   + 1 : vdiv_counter;
                            vmac_counter        <= (vector_operation_i      inside {VMACC, VNMSAC, VMADD, VNMSUB})                && !mcountinhibit[27] ? vmac_counter   + 1 : vmac_counter;          
                            vred_counter        <= (vector_operation_i      inside {VREDMIN, VREDMINU, VREDMAX, VREDMAXU})        && !mcountinhibit[28] ? vred_counter   + 1 : vred_counter;

                            vothers_counter     <= (vector_operation_i      inside {
                                                                                    VMSEQ, VMSNE, VMSLTU, VMSLT, VMSLEU, VMSLE, VMSGTU, VMSGT,  // mask compares
                                                                                    VREDAND, VREDOR, VREDXOR,                                   // logic reduction
                                                                                    VMV, VMVR, VMVSX, VMVXS,                                    // register moves
                                                                                    VSLL, VSRL, VSRA,                                           // shifts
                                                                                    VAND, VOR, VXOR,                                            // logic
                                                                                    VMERGE                                                      // merge
                                                                                   })   && !mcountinhibit[30] ?  vothers_counter + 1 : vothers_counter;
                        end
                    end                    

                    if (COMPRESSED == 1'b1) begin
                        compressed_counter  <= compressed_counter + (instruction_compressed_i && !mcountinhibit[20] ? 1 : 0);
                    end
                end
            end
        end
        
    `ifndef SYNTH
        if (PROFILING) begin : gen_csr_dbg
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
                    $fwrite(fd,"Instructions Compressed: %0d\n", compressed_counter);
                end
                $fwrite(fd,"Instructions Killed:     %0d\n", instructions_killed_counter);
                $fwrite(fd,"Context Switches:        %0d\n", context_switch_counter);
                $fwrite(fd,"Exceptions Raised:       %0d\n", raise_exception_counter);
                $fwrite(fd,"Interrupts Acked:        %0d\n", interrupt_ack_counter);
                if (COMPRESSED == 1'b1) begin
                    $fwrite(fd,"Misaligned Jumps:        %0d\n", jump_misaligned_counter);
                end

                $fwrite(fd,"\nCYCLES WITH::\n");
                $fwrite(fd,"HAZARDS:                 %0d\n", hazard_counter);
                $fwrite(fd,"STALL:                   %0d\n", stall_counter);
                $fwrite(fd,"BUBBLES (INC. HAZARDS):  %0d\n", nop_counter);

                $fwrite(fd,"\nINSTRUCTION COUNTERS:\n");
                $fwrite(fd,"LUI_SLT:                 %0d\n", lui_slt_counter);
                $fwrite(fd,"LOGIC:                   %0d\n", logic_counter);
                $fwrite(fd,"ADDSUB:                  %0d\n", addsub_counter);
                $fwrite(fd,"SHIFT:                   %0d\n", shift_counter);
                $fwrite(fd,"BRANCH:                  %0d\n", branch_counter);
                $fwrite(fd,"JUMP:                    %0d\n", jump_counter);
                $fwrite(fd,"LOAD:                    %0d\n", load_counter);
                $fwrite(fd,"STORE:                   %0d\n", store_counter);
                $fwrite(fd,"SYS:                     %0d\n", sys_counter);
                $fwrite(fd,"CSR:                     %0d\n", csr_counter);
                $fwrite(fd,"MUL:                     %0d\n", mul_counter);
                $fwrite(fd,"DIV:                     %0d\n", div_counter);
            
            if(VEnable) begin
                    $fwrite(fd, "\nVECTOR EXTENSION:\n");
                    $fwrite(fd, "VADDSUB:                 %0d\n", vaddsub_counter);
                    $fwrite(fd, "VMUL:                    %0d\n", vmul_counter);
                    $fwrite(fd, "VDIV:                    %0d\n", vdiv_counter);
                    $fwrite(fd, "VMAC:                    %0d\n", vmac_counter);
                    $fwrite(fd, "VRED:                    %0d\n", vred_counter);
                    $fwrite(fd, "VLOAD/VSTORE:            %0d\n", vloadstore_counter);
                    $fwrite(fd, "VOTHERS:                 %0d\n", vothers_counter);
                end
            end
        end
    `endif
    end
    else begin : gen_zihpm_csr_off
        assign instructions_killed_counter = '0;
        assign nop_counter                 = '0;
        assign logic_counter               = '0;
        assign lui_slt_counter             = '0;
        assign addsub_counter              = '0;
        assign shift_counter               = '0;
        assign branch_counter              = '0;
        assign jump_counter                = '0;
        assign load_counter                = '0;
        assign store_counter               = '0;
        assign sys_counter                 = '0;
        assign csr_counter                 = '0;
        assign mul_counter                 = '0;
        assign div_counter                 = '0;
        assign hazard_counter              = '0;
        assign stall_counter               = '0;
        assign interrupt_ack_counter       = '0;
        assign raise_exception_counter     = '0;
        assign context_switch_counter      = '0;
        assign compressed_counter          = '0;
        assign jump_misaligned_counter     = '0;

        assign vaddsub_counter             = '0; 
        assign vmul_counter                = '0;
        assign vdiv_counter                = '0;
        assign vmac_counter                = '0;
        assign vred_counter                = '0;
        assign vloadstore_counter          = '0;
        assign vothers_counter             = '0;
    end

endmodule
