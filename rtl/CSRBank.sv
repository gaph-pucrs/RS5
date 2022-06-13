import my_pkg::*;
import CSRs_pkg::*;

module CSRBank (
    input logic         clk,
    input logic         reset,
    input logic         rd_en,
    input logic         wr_en,
    input logic         killed,
    input csr_ops       csr_op,
    input logic [11:0]  addr,
    input logic [31:0]  data,
    output logic [31:0] out,

    input logic         RAISE_EXCEPTION,
    input logic         MACHINE_RETURN,
    input EXCEPT_CODE   Exception_Code,
    input Privilege     privilege,
    input logic [31:0]  PC,
    input logic [31:0]  instruction,

    input logic [31:0]  IRQ,
    input logic Interupt_ACK,
    output logic Interupt_pending,

    output logic [31:0] mtvec,
    output logic [31:0] mepc
    );

    CSRs CSR;
    logic [31:0] mstatus, /*misa, mie, mtvec_r,*/ mcounteren, mstatush, /*mscratch, mepc_r, mcause, mtval, mip,*/ mtinst, mtval2;
    logic [31:0] wr_data, wmask, current_val;
    IMISA misa = new;
    IMIE mie = new;
    IMTVEC mtvec_r = new;
    IMSCRATCH mscratch = new;
    IMEPC mepc_r = new;
    IMTVAL mtval = new;
    IMCAUSE mcause = new;
    IMIP mip = new;
    //logic [31:0] medeleg, mideleg; // NOT IMPLEMENTED YET (REQUIRED ONLY WHEN SYSTEM HAVE S-MODE)
    INTERRUPT_CODE Interuption_Code;

    always @(posedge clk) begin
        mtvec <= mtvec_r.value;
        mepc <= mepc_r.value;
    end


    assign CSR = CSRs'(addr);

    always_comb begin
        wmask <= '1;
        case (CSR)
            MSTATUS:    begin current_val <= mstatus;   wmask <= 32'h007E19AA; end
            //MISA:       begin current_val <= misa;      wmask <= 32'h3C000000; end
            //MEDELEG:    begin current_val <= medeleg;   wmask <= '1; end
            //MIDELEG:    begin current_val <= mideleg;   wmask <= '1; end
            //MIE:        begin current_val <= mie.value;       wmask <= 32'h00000888; end
            //MTVEC:      begin current_val <= mtvec_r;   wmask <= 32'hFFFFFFFC; end
            //MCOUNTEREN: begin current_val <= mcounteren;wmask <= '1; end
            //MSTATUSH:   begin current_val <= mstatush;  wmask <= '1; end
            //MSCRATCH:   begin current_val <= mscratch;  wmask <= 32'hFFFFFFFF; end
            //MEPC:       begin current_val <= mepc_r;    wmask <= 32'hFFFFFFFC; end
            //MCAUSE:     begin current_val <= mcause;    wmask <= 32'hFFFFFFFF; end
            //MTVAL:      begin current_val <= mtval;     wmask <= 32'hFFFFFFFF; end

            default:    begin current_val <= '0;        wmask <= 32'h00000000; end
        endcase
    end

    always_comb
        if(csr_op==WRITE)
            wr_data <= data & wmask;
        else if(csr_op==SET)
            wr_data <= (current_val | data) & wmask;
        else if(csr_op==CLEAR)
            wr_data <= (current_val & (~data)) & wmask;
        else
            wr_data <= 'Z;

    always @(negedge reset or posedge clk) begin
        if(!reset) begin
            mstatus <= '0;
            mstatus[3] <= 0;        // MIE  = 0
            mstatus[17] <= 0;       // MPRV = 0
            misa.reset();
            //medeleg <= '0;
            //mideleg <= '0;
            mie.reset();
            mtvec_r.reset();
            //mcounteren <= '0;
            //mstatush <= '0;
            mscratch.reset();
            mepc_r.reset();
            mcause.reset();
            mtval.reset();

        end else if(MACHINE_RETURN) begin
            mstatus[3]      <= mstatus[7];          // MIE = MPIE
            // privilege = mstatus[12:11]           // priv = MPP

        end else if(RAISE_EXCEPTION) begin
            mcause.SET_EXCEPTION();
            mcause.SET_CODE(Exception_Code);
            mstatus[12:11]  <= privilege;           // MPP previous privilege
            // privilege    <= MACHINE
            mstatus[7]      <= mstatus[3];          // MPIE = MIE
            mstatus[3]      <= 0;                   // MIE = 0
            mepc_r.write((Exception_Code==ECALL_FROM_MMODE) ? PC : PC+4, csr_ops'(WRITE));   // Return address
            mtval.write((Exception_Code==ILLEGAL_INSTRUCTION) ? instruction : PC, csr_ops'(WRITE));

        end else if(Interupt_ACK) begin
            mcause.SET_INTERRUPT();
            mcause.SET_CODE(Interuption_Code);
            mstatus[12:11]  <= privilege;           // MPP = previous privilege
            // privilege    <= MACHINE
            mstatus[7]      <= mstatus[3];          // MPIE = MIE
            mstatus[3]      <= 0;                   // MIE = 0
            mepc_r.write( PC, csr_ops'(WRITE));     // Return address
        
        end else if(wr_en==1 && killed==0) begin
            case(CSR)
                MSTATUS:    mstatus     <= wr_data;
                MISA:       misa.write(data, csr_op);
                //MEDELEG:    medeleg     <= wr_data;
                //MIDELEG:    mideleg     <= wr_data;
                MIE:        mie.write(data, csr_op);
                MTVEC:      mtvec_r.write(data, csr_op);
                //MCOUNTEREN: mcounteren  <= wr_data;
                //MSTATUSH:   mstatush    <= wr_data;
                MSCRATCH:   mscratch.write(data, csr_op);
                MEPC:       mepc_r.write(data, csr_op);
                MCAUSE:     mcause.write(data, csr_op);
                MTVAL:      mtval.write(data, csr_op);
            endcase
        end
    end

    always_comb
        if(rd_en==1 && killed==0)
            case(CSR)
                MVENDORID:  out <= '0;
                MARCHID:    out <= '0;
                MIMPID:     out <= '0;
                MHARTID:    out <= '0;
                MCONFIGPTR: out <= '0;

                MSTATUS:    out <= mstatus;
                MISA:       out <= misa.read();
                //MEDELEG:    out <= medeleg;
                //MIDELEG:    out <= mideleg;
                MIE:        out <= mie.read();
                MTVEC:      out <= mtvec_r.read();
                //MCOUNTEREN: out <= mcounteren;
                //MSTATUSH:   out <= mstatush;
                MSCRATCH:   out <= mscratch.read();
                MEPC:       out <= mepc_r.read();
                MCAUSE:     out <= mcause.read();
                MTVAL:      out <= mtval.read();
                MIP:        out <= mip.read();
            endcase
        else
            out <= '0;

    always @(negedge reset or posedge clk)
        if(!reset)
            mip.reset();
        else
            mip.write(IRQ, csr_ops'(WRITE));
    

    always @(posedge clk)
        if(mstatus[3]==1 && (mie.read() & mip.read()) && Interupt_ACK==0) begin
            Interupt_pending <= 1;
            if(mip.MEIP & mie.MEIE)                   // Machine External
                Interuption_Code <= M_EXT_INT;
            else if(mip.MSIP & mie.MSIE)                // Machine Software
                Interuption_Code <= M_SW_INT;
            else if(mip.MTIP & mie.MTIE)                // Machine Timer
                Interuption_Code <= M_TIM_INT;

        end else
            Interupt_pending <= 0;
    

endmodule