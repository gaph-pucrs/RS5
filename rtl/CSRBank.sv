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

module CSRBank 
    import RS5_pkg::*;
#( 
    parameter bit   XOSVMEnable = 1'b0
)
(
    input   logic               clk,
    input   logic               reset,

    input   logic               read_enable_i,
    input   logic               write_enable_i,
    input   csrOperation_e      operation_i,
    input   logic [11:0]        address_i,
    input   logic [31:0]        data_i,
    input   logic               killed,
    output  logic [31:0]        out,

`ifdef ZIHPM
    input   iType_e             instruction_operation_i,
    input   logic               hazard,
    input   logic               stall,
`endif

    input   logic               raise_exception_i,
    input   logic               machine_return_i,
    input   exceptionCode_e     exception_code_i,
    input   logic [31:0]        pc_i,
    input   logic [31:0]        instruction_i,

    input   logic               jump_i,
    input   logic [31:0]        jump_target_i,

    input   logic [63:0]        mtime_i,
    
    input   logic [31:0]        irq_i,
    input   logic               interrupt_ack_i,
    output  logic               interrupt_pending_o,

    output  privilegeLevel_e    privilege_o,

    output  logic [31:0]        mepc,
    output  logic [31:0]        mtvec,

    output  logic               mvmctl_o,
    output  logic [31:0]        mvmdo_o, 
    output  logic [31:0]        mvmio_o, 
    output  logic [31:0]        mvmds_o, 
    output  logic [31:0]        mvmis_o

);

    CSRs CSR;
    privilegeLevel_e privilege;

    logic [31:0] mstatus, misa, mie, mtvec_r, mscratch, mepc_r, mcause, mtval, mip;
    logic [31:0] mvmdo, mvmio, mvmds, mvmis;
    logic        mvmctl;
    logic [63:0] mcycle, minstret;
    
    logic [31:0] wr_data, wmask, current_val;

    logic read_allowed, write_allowed;

`ifdef ZIHPM
    logic [31:0] instructions_killed_counter, hazard_counter, stall_counter, nop_counter;
    logic [31:0] interrupt_ack_counter, raise_exception_counter, context_switch_counter;
    logic [31:0] logic_counter, arithmetic_counter, shift_counter, branch_counter, jump_counter;
    logic [31:0] load_counter, store_counter, sys_counter, csr_counter;
    logic [31:0] mul_counter, div_counter;
`endif
    //logic [31:0] medeleg, mideleg; // NOT IMPLEMENTED YET (REQUIRED ONLY WHEN SYSTEM HAVE S-MODE)
    interruptionCode_e Interruption_Code;

    assign privilege_o = privilege;
    assign mtvec       = mtvec_r;
    assign mepc        = mepc_r;

    assign CSR = CSRs'(address_i);

    assign write_allowed = (write_enable_i == 1'b1 & killed == 1'b0);

    assign read_allowed = (read_enable_i == 1'b1 & killed == 1'b0);

    always_comb begin
        wmask = '1;
        case (CSR)
            MSTATUS:    begin current_val = mstatus;         wmask = 32'h007E19AA; end
            MISA:       begin current_val = misa;            wmask = 32'h3C000000; end
            // MEDELEG:    begin current_val = medeleg;         wmask = '1; end
            // MIDELEG:    begin current_val = mideleg;         wmask = '1; end
            MIE:        begin current_val = mie;             wmask = 32'h00000888; end
            MTVEC:      begin current_val = mtvec_r;         wmask = 32'hFFFFFFFC; end
            // MCOUNTEREN: begin current_val = mcounteren;      wmask = '1; end
            // MSTATUSH:   begin current_val = mstatush;        wmask = '1; end
            MSCRATCH:   begin current_val = mscratch;        wmask = 32'hFFFFFFFF; end
            MEPC:       begin current_val = mepc_r;          wmask = 32'hFFFFFFFC; end
            MCAUSE:     begin current_val = mcause;          wmask = 32'hFFFFFFFF; end
            MTVAL:      begin current_val = mtval;           wmask = 32'hFFFFFFFF; end
            // MIP:        begin current_val = mip;             wmask = 32'h00000000; end
            MCYCLE:     begin current_val = mcycle[31:0];    wmask = 32'hFFFFFFFF; end
            MCYCLEH:    begin current_val = mcycle[63:32];   wmask = 32'hFFFFFFFF; end
            MINSTRET:   begin current_val = minstret[31:0];  wmask = 32'hFFFFFFFF; end
            MINSTRETH:  begin current_val = minstret[63:32]; wmask = 32'hFFFFFFFF; end

            MVMDO:      begin current_val = mvmdo;           wmask = 32'hFFFFFFFC; end
            MVMDS:      begin current_val = mvmds;           wmask = 32'hFFFFFFFC; end
            MVMIO:      begin current_val = mvmio;           wmask = 32'hFFFFFFFC; end
            MVMIS:      begin current_val = mvmis;           wmask = 32'hFFFFFFFC; end
            MVMCTL:     begin current_val = {31'b0, mvmctl}; wmask = 32'h00000001; end

            default:    begin current_val = '0;              wmask = 32'h00000000; end
        endcase
    end

    always_comb begin
        case (operation_i)
            SET:     wr_data = (current_val | data_i) & wmask;
            CLEAR:   wr_data = (current_val & (~data_i)) & wmask;
            default: wr_data = data_i & wmask; // WRITE
        endcase
    end

    always_ff @(posedge clk) begin
        if (reset == 1'b1) begin
            // mstatus     <= '0;   // Duplicated behavior. Which one is the right one?
            mstatus[3]  <= 0;       // MIE  = 0
            mstatus[17] <= 0;       // MPRV = 0
            misa        <= 32'h40000100;   // 32 - I /* @todo: add M/Zmmul with params */
            //medeleg   <= '0;
            //mideleg   <= '0;
            mie         <= '0;
            mtvec_r     <= '0;
            //mcounteren <= '0;
            //mstatush  <= '0;
            mscratch    <= '0;
            mepc_r      <= '0;
            mcause      <= '0;
            mtval       <= '0;
            //mip       <= '0;
            mcycle      <= '0;
            minstret    <= '0;

        end 
        else begin
            mcycle      <= mcycle + 1;
            minstret    <= (killed) 
                            ? minstret 
                            : minstret + 1;
        
            if (machine_return_i == 1'b1) begin
                mstatus[3]      <= mstatus[7];          // MIE = MPIE
                privilege       <= privilegeLevel_e'(mstatus[12:11]);      // priv = MPP
            end
            else if (raise_exception_i == 1'b1) begin
                mcause[31]      <= '0;
                mcause[30:0]    <= {26'b0, exception_code_i};
                mstatus[12:11]  <= privilege;           // MPP = previous privilege
                privilege       <= privilegeLevel_e'(2'b11);
                mstatus[7]      <= mstatus[3];          // MPIE = MIE
                mstatus[3]      <= 0;                   // MIE = 0
                mepc_r          <= (exception_code_i == ECALL_FROM_MMODE || exception_code_i == BREAKPOINT) 
                                    ? pc_i 
                                    : pc_i+4;             // Return address
                mtval           <= (exception_code_i == ILLEGAL_INSTRUCTION) 
                                    ? instruction_i 
                                    : pc_i;

            end 
            else if (interrupt_ack_i == 1'b1) begin
                mcause[31]      <= '1;
                mcause[30:0]    <=  {26'b0, Interruption_Code};
                mstatus[12:11]  <= privilege;           // MPP = previous privilege
                privilege       <= privilegeLevel_e'(2'b11);
                mstatus[7]      <= mstatus[3];          // MPIE = MIE
                mstatus[3]      <= 0;                   // MIE = 0

                if(jump_i)
                    mepc_r      <= jump_target_i;
                else
                    mepc_r      <= pc_i;                // Return address
            
            end 
            else if (write_allowed == 1'b1) begin
                case(CSR)
                    MSTATUS:      mstatus         <= wr_data;
                    MISA:         misa            <= wr_data;
                    // MEDELEG:      medeleg         <= wr_data;
                    // MIDELEG:      mideleg         <= wr_data;
                    MIE:          mie             <= wr_data;
                    MTVEC:        mtvec_r         <= wr_data;
                    // MCOUNTEREN:   mcounteren      <= wr_data;
                    // MSTATUSH:     mstatush        <= wr_data;
                    MSCRATCH:     mscratch        <= wr_data;
                    MEPC:         mepc_r          <= wr_data;
                    MCAUSE:       mcause          <= wr_data;
                    MTVAL:        mtval           <= wr_data;
                    // MIP:          mip             <= wr_data;
                    MCYCLE:       mcycle[31:0]    <= wr_data;
                    MCYCLEH:      mcycle[63:32]   <= wr_data;
                    MINSTRET:     minstret[31:0]  <= wr_data;
                    MINSTRETH:    minstret[63:32] <= wr_data;
                    
                    default:    ; // no op
                endcase
            end
        end
    end

    always_comb begin
        if (read_allowed == 1'b1) begin
            case(CSR)
                //RO
                MVENDORID:      out = '0;
                MARCHID:        out = '0;
                MIMPID:         out = '0;
                MHARTID:        out = '0;
                MCONFIGPTR:     out = '0;

                //RW
                MSTATUS:        out = mstatus;
                MISA:           out = misa;
                // MEDELEG:     out = medeleg;
                // MIDELEG:     out = mideleg;
                MIE:            out = mie;
                MTVEC:          out = mtvec_r;
                // MCOUNTEREN:  out = mcounteren;
                // MSTATUSH:    out = mstatush;
                MSCRATCH:       out = mscratch;
                MEPC:           out = mepc_r;
                MCAUSE:         out = mcause;
                MTVAL:          out = mtval;
                MIP:            out = mip;
                MCYCLE:         out = mcycle[31:0];
                MCYCLEH:        out = mcycle[63:32];
                MINSTRET:       out = minstret[31:0];
                MINSTRETH:      out = minstret[63:32];

                //RO
                CYCLE:          out = mcycle[31:0];
                TIME:           out = mtime_i[31:0];
                INSTRET:        out = minstret[31:0];

            `ifdef ZIHPM
                MHPMCOUNTER3:   out = instructions_killed_counter;
                MHPMCOUNTER4:   out = context_switch_counter;
                MHPMCOUNTER5:   out = raise_exception_counter;
                MHPMCOUNTER6:   out = interrupt_ack_counter;
                MHPMCOUNTER7:   out = hazard_counter;
                MHPMCOUNTER8:   out = stall_counter;
                MHPMCOUNTER9:   out = nop_counter;
                MHPMCOUNTER10:  out = logic_counter;
                MHPMCOUNTER11:  out = arithmetic_counter;
                MHPMCOUNTER12:  out = shift_counter;
                MHPMCOUNTER13:  out = branch_counter;
                MHPMCOUNTER14:  out = jump_counter;
                MHPMCOUNTER15:  out = load_counter;
                MHPMCOUNTER16:  out = store_counter;
                MHPMCOUNTER17:  out = sys_counter;
                MHPMCOUNTER18:  out = csr_counter;
            `endif

                CYCLEH:         out = mcycle[63:32];
                TIMEH:          out = mtime_i[63:32];
                INSTRETH:       out = minstret[63:32];
                
                MVMCTL:         out = {31'b0,mvmctl};
                MVMDO:          out = mvmdo[31:0];
                MVMDS:          out = mvmds[31:0];
                MVMIO:          out = mvmio[31:0];
                MVMIS:          out = mvmis[31:0];

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
    
    if (XOSVMEnable == 1'b1) begin
        always_ff @(posedge clk) begin
            if (reset == 1'b1) begin
                mvmctl      <= '0;
                mvmdo       <= '0;
                mvmds       <= '0;
                mvmio       <= '0;
                mvmis       <= '0;
            end 
            else if (write_allowed == 1'b1) begin
                case (CSR)
                    MVMCTL: mvmctl  <= wr_data[0];
                    MVMDO:  mvmdo   <= wr_data;
                    MVMDS:  mvmds   <= wr_data;
                    MVMIO:  mvmio   <= wr_data;
                    MVMIS:  mvmis   <= wr_data;
                endcase
            end
        end
    end
    else begin
        assign mvmctl   = '0;
        assign mvmdo    = '0;
        assign mvmds    = '0;
        assign mvmio    = '0;
        assign mvmis    = '0;
    end

    assign mvmctl_o = mvmctl;
    assign mvmdo_o  = mvmdo;
    assign mvmds_o  = mvmds;
    assign mvmio_o  = mvmio;
    assign mvmis_o  = mvmis;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Interrupt Control
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk) begin
        if (reset == 1'b1) begin
            mip <= '0;
        end
        else begin
            mip <= irq_i;
        end
    end

    always_ff @(posedge clk) begin
        if (mstatus[3] && (mie & mip) != '0 && !interrupt_ack_i) begin
            interrupt_pending_o <= 1;
            if ((mip[11] & mie[11]) == 1'b1)                   // Machine External
                Interruption_Code <= M_EXT_INT;
            else if ((mip[3] & mie[3]) == 1'b1)                // Machine Software
                Interruption_Code <= M_SW_INT;
            else if ((mip[7] & mie[7]) == 1'b1)                // Machine Timer
                Interruption_Code <= M_TIM_INT;

        end 
        else begin
            interrupt_pending_o <= 0;
        end
    end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZIHPM
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

`ifdef ZIHPM
    int fd;

    always_ff @(posedge clk) begin
        if (reset == 1'b1) begin
            instructions_killed_counter <= '0;
            nop_counter                 <= '0;
            logic_counter               <= '0;
            arithmetic_counter          <= '0;
            shift_counter               <= '0;
            branch_counter              <= '0;
            jump_counter                <= '0;
            load_counter                <= '0;
            store_counter               <= '0;
            sys_counter                 <= '0;
            csr_counter                 <= '0;
            mul_counter                 <= '0;
            div_counter                 <= '0;

            hazard_counter              <= '0;
            stall_counter               <= '0;
            interrupt_ack_counter       <= '0;
            raise_exception_counter     <= '0;
            context_switch_counter      <= '0;
        end
        else begin
            instructions_killed_counter <= (killed)                                                             ? instructions_killed_counter  + 1 : instructions_killed_counter;

            hazard_counter              <= (hazard)                                                             ? hazard_counter               + 1 : hazard_counter;
            stall_counter               <= (stall)                                                              ? stall_counter                + 1 : stall_counter;

            interrupt_ack_counter       <= (interrupt_ack_i)                                                    ? interrupt_ack_counter   + 1 : interrupt_ack_counter;
            raise_exception_counter     <= (raise_exception_i)                                                  ? raise_exception_counter + 1 : raise_exception_counter;
            context_switch_counter      <= (jump_i || raise_exception_i || machine_return_i || interrupt_ack_i) ? context_switch_counter + 1 : context_switch_counter;
            nop_counter                 <= (instruction_operation_i == NOP)                                     ?   nop_counter + 1 : nop_counter;

            if (killed == 1'b0) begin
                logic_counter           <= (instruction_operation_i inside {XOR, OR, AND})                                  ? logic_counter             + 1 : logic_counter;
                arithmetic_counter      <= (instruction_operation_i inside {ADD, SUB, SLTU, SLT, LUI})                      ? arithmetic_counter        + 1 : arithmetic_counter;
                shift_counter           <= (instruction_operation_i inside {SLL, SRL, SRA})                                 ? shift_counter             + 1 : shift_counter;
                branch_counter          <= (instruction_operation_i inside {BEQ, BNE, BLT, BLTU, BGE, BGEU})                ? branch_counter            + 1 : branch_counter;
                jump_counter            <= (instruction_operation_i inside {JAL, JALR})                                     ? jump_counter              + 1 : jump_counter;
                load_counter            <= (instruction_operation_i inside {LB, LBU, LH, LHU, LW})                          ? load_counter              + 1 : load_counter;
                store_counter           <= (instruction_operation_i inside {SB, SH, SW})                                    ? store_counter             + 1 : store_counter;
                sys_counter             <= (instruction_operation_i inside {SRET, MRET, WFI, ECALL, EBREAK})                ? sys_counter               + 1 : sys_counter;
                csr_counter             <= (instruction_operation_i inside {CSRRW, CSRRWI, CSRRS, CSRRSI, CSRRC, CSRRCI})   ? csr_counter               + 1 : csr_counter;
                mul_counter             <= (instruction_operation_i inside {MUL, MULH, MULHU, MULHSU})                      ? mul_counter               + 1 : mul_counter;
                div_counter             <= (instruction_operation_i inside {DIV, DIVU, REM, REMU})                          ? div_counter               + 1 : div_counter;
            end
        end
    end

    initial begin
        fd = $fopen ("./debug/Report.txt", "w");
    end

    final begin
        $fwrite(fd,"Clock Cycles:           %0d\n", mcycle);
        $fwrite(fd,"Instructions Retired:   %0d\n", minstret);
        $fwrite(fd,"Instructions Killed:    %0d\n", instructions_killed_counter);
        $fwrite(fd,"Context Switches:       %0d\n", context_switch_counter);
        $fwrite(fd,"Exceptions Raised:      %0d\n", raise_exception_counter);
        $fwrite(fd,"Interrupts Acked:       %0d\n", interrupt_ack_counter);

        $fwrite(fd,"\nCYCLES WITH::\n");
        $fwrite(fd,"HAZARDS:                %0d\n", hazard_counter);
        $fwrite(fd,"STALL:                  %0d\n", stall_counter);

        $fwrite(fd,"\nINSTRUCTION COUNTERS:\n");
        $fwrite(fd,"NOP:                    %0d\n", nop_counter);
        $fwrite(fd,"LOGIC:                  %0d\n", logic_counter);
        $fwrite(fd,"ARITH:                  %0d\n", arithmetic_counter);
        $fwrite(fd,"SHIFT:                  %0d\n", shift_counter);
        $fwrite(fd,"BRANCH:                 %0d\n", branch_counter);
        $fwrite(fd,"JUMP:                   %0d\n", jump_counter);
        $fwrite(fd,"LOAD:                   %0d\n", load_counter);
        $fwrite(fd,"STORE:                  %0d\n", store_counter);
        $fwrite(fd,"SYS:                    %0d\n", sys_counter);
        $fwrite(fd,"CSR:                    %0d\n", csr_counter);
        $fwrite(fd,"MUL:                    %0d\n", mul_counter);
        $fwrite(fd,"DIV:                    %0d\n", div_counter);
        
    end
`endif

endmodule
