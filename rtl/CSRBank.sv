module CSRBank 
    import my_pkg::*;
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

    input   logic               raise_exception_i,
    input   logic               machine_return_i,
    input   exceptionCode_e     exception_code_i,
    input   privilegeLevel_e    privilege_i,
    input   logic [31:0]        pc_i,
    input   logic [31:0]        instruction_i,

    input   logic [31:0]        IRQ_i,
    input   logic               interrupt_ack_i,
    output  logic               interrupt_pending_o,

    output  logic [31:0]        mtvec,
    output  logic [31:0]        mepc
);

    CSRs CSR;
    logic [31:0] mstatus, misa, mie, mtvec_r, mscratch, mepc_r, mcause, mtval, mip;
    logic [63:0] cycle, instret;
    
    logic [31:0] wr_data, wmask, current_val;
    //logic [31:0] medeleg, mideleg; // NOT IMPLEMENTED YET (REQUIRED ONLY WHEN SYSTEM HAVE S-MODE)
    interruptionCode_e Interruption_Code;

    assign mtvec = mtvec_r;
    assign mepc  = mepc_r;

    assign CSR = CSRs'(address_i);

    always_comb begin
        wmask = '1;
        case (CSR)
            MSTATUS:    begin current_val = mstatus;   wmask = 32'h007E19AA; end
            MISA:       begin current_val = misa;      wmask = 32'h3C000000; end
            //MEDELEG:    begin current_val = medeleg;   wmask = '1; end
            //MIDELEG:    begin current_val = mideleg;   wmask = '1; end
            MIE:        begin current_val = mie;       wmask = 32'h00000888; end
            MTVEC:      begin current_val = mtvec_r;   wmask = 32'hFFFFFFFC; end
            //MCOUNTEREN: begin current_val = mcounteren;wmask = '1; end
            //MSTATUSH:   begin current_val = mstatush;  wmask = '1; end
            MSCRATCH:   begin current_val = mscratch;  wmask = 32'hFFFFFFFF; end
            MEPC:       begin current_val = mepc_r;    wmask = 32'hFFFFFFFC; end
            MCAUSE:     begin current_val = mcause;    wmask = 32'hFFFFFFFF; end
            MTVAL:      begin current_val = mtval;     wmask = 32'hFFFFFFFF; end
            //MIP:        begin current_val = mip;     wmask = 32'h00000000; end

            default:    begin current_val = '0;        wmask = 32'h00000000; end
        endcase
    end

    always_comb begin
        if(operation_i == WRITE) begin
            wr_data = data_i & wmask;
        end
        else if(operation_i == SET) begin
            wr_data = (current_val | data_i) & wmask;
        end
        else if(operation_i == CLEAR) begin
            wr_data = (current_val & (~data_i)) & wmask;
        end
        else begin
            wr_data = 'Z;
        end
    end

    always_ff @(posedge clk) begin
        if (reset) begin
            mstatus     <= '0;
            mstatus[3]  <= 0;        // MIE  = 0
            mstatus[17] <= 0;       // MPRV = 0
            misa        <= 32'h40000100;   // 32 - I
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

        end 
        else if(machine_return_i) begin
            mstatus[3]  <= mstatus[7];          // MIE = MPIE
            //privilege <= mstatus[12:11]       // priv = MPP

        end
        else if(raise_exception_i) begin
            mcause[31]      <= '0;
            mcause[30:0]    <= {26'b0, exception_code_i};
            mstatus[12:11]  <= privilege_i;         // MPP previous privilege
            // privilege    <= MACHINE
            mstatus[7]      <= mstatus[3];          // MPIE = MIE
            mstatus[3]      <= 0;                   // MIE = 0
            mepc_r          <= (exception_code_i == ECALL_FROM_MMODE) 
                                ? pc_i 
                                : pc_i+4;             // Return address
            mtval           <= (exception_code_i == ILLEGAL_INSTRUCTION) 
                                ? instruction_i 
                                : pc_i;

        end 
        else if(interrupt_ack_i) begin
            mcause[31]      <= '1;
            mcause[30:0]    <=  {26'b0, Interruption_Code};
            mstatus[12:11]  <= privilege_i;           // MPP = previous privilege
            // privilege    <= MACHINE
            mstatus[7]      <= mstatus[3];          // MPIE = MIE
            mstatus[3]      <= 0;                   // MIE = 0
            mepc_r          <= pc_i;                  // Return address
        
        end 
        else if(write_enable_i && !killed) begin
            case(CSR)
                MSTATUS:      mstatus     <= wr_data;
                MISA:         misa        <= wr_data;
                //MEDELEG:    medeleg     <= wr_data;
                //MIDELEG:    mideleg     <= wr_data;
                MIE:          mie         <= wr_data;
                MTVEC:        mtvec_r     <= wr_data;
                //MCOUNTEREN: mcounteren  <= wr_data;
                //MSTATUSH:   mstatush    <= wr_data;
                MSCRATCH:     mscratch    <= wr_data;
                MEPC:         mepc_r      <= wr_data;
                MCAUSE:       mcause      <= wr_data;
                MTVAL:        mtval       <= wr_data;
                //MIP:        mip         <= wr_data;
                default:    ; // no op
            endcase
        end
    end

    always_comb begin
        if(read_enable_i && !killed) begin
            case(CSR)
                //RO
                MVENDORID:  out = '0;
                MARCHID:    out = '0;
                MIMPID:     out = '0;
                MHARTID:    out = '0;
                MCONFIGPTR: out = '0;

                //RW
                MSTATUS:    out = mstatus;
                MISA:       out = misa;
                //MEDELEG:    out = medeleg;
                //MIDELEG:    out = mideleg;
                MIE:        out = mie;
                MTVEC:      out = mtvec_r;
                //MCOUNTEREN: out = mcounteren;
                //MSTATUSH:   out = mstatush;
                MSCRATCH:   out = mscratch;
                MEPC:       out = mepc_r;
                MCAUSE:     out = mcause;
                MTVAL:      out = mtval;
                MIP:        out = mip;

                //RO
                CYCLE:      out = cycle[31:0];
                CYCLEH:     out = cycle[63:32];
                INSTRET:    out = instret[31:0];
                INSTRETH:   out = instret[63:32];
                default:    out = '0;
            endcase
        end
        else begin
            out = '0;
        end
    end

    always_ff @(posedge clk) begin
        if (reset) begin
            mip <= '0;
        end
        else begin
            mip <= IRQ_i;
        end
    end
    
    always_ff @(posedge clk) begin
        if(mstatus[3] && (mie & mip) != 0 && !interrupt_ack_i) begin
            interrupt_pending_o <= 1;
            if(mip[11] & mie[11])                   // Machine External
                Interruption_Code <= M_EXT_INT;
            else if(mip[3] & mie[3])                // Machine Software
                Interruption_Code <= M_SW_INT;
            else if(mip[7] & mie[7])                // Machine Timer
                Interruption_Code <= M_TIM_INT;

        end 
        else begin
            interrupt_pending_o <= 0;
        end
    end

//##################################################################################
    // PERFORMANCE MONITORS
    always_ff @(posedge clk) begin
        if (reset) begin
            cycle   <= '0;
            instret <= '0;
        end 
        else begin
            cycle  <= cycle + 1;
            instret <= (killed == 1) 
                        ? instret 
                        : instret + 1;
        end
    end

endmodule
