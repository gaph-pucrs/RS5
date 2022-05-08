import my_pkg::*;

module CSRBank (
    input logic clk,
    input logic reset,
    input logic rd_en,
    input logic wr_en,
    input csr_ops csr_op,
    input logic [11:0] addr,
    input logic [31:0] data,
    output logic [31:0] out,

    input logic RAISE_EXCEPTION,
    input logic [30:0] EXCEPTION_CODE,
    input Privilege privilege,
    input logic [31:0] PC,
    input logic [31:0] instruction
    );

    CSRs CSR;
    logic [31:0] mvendorid, marchid, mimpid, mhartid, mconfigptr, mstatus, misa, medeleg, mideleg, mie, mtvec, mcounteren, mstatush, mscratch, mepc, mcause, mtval, mip, mtinst, mtval2;
    logic [31:0] wr_data, wmask, current_val;

    always_comb begin
        wmask <= '1;
        case (csr_add)
            // RO regs
            12'hF11: CSR <= MVENDORID;
            12'hF12: CSR <= MARCHID;
            12'hF13: CSR <= MIMPID;
            12'hF14: CSR <= MHARTID;
            12'hF15: CSR <= MCONFIGPTR;

            // RW REGS
            12'h300: begin CSR <= MSTATUS; current_val <= mstatus; wmask <= '1; end
            12'h301: begin CSR <= MISA; current_val <= misa; wmask <= '1; end
            12'h302: begin CSR <= MEDELEG; current_val <= medeleg; wmask <= '1; end
            12'h303: begin CSR <= MIDELEG; current_val <= mideleg; wmask <= '1; end
            12'h304: begin CSR <= MIE; current_val <= mie; wmask <= '1; end
            12'h305: begin CSR <= MTVEC; current_val <= mtvec; wmask <= '1; end
            12'h306: begin CSR <= MCOUNTEREN; current_val <= mcounteren; wmask <= '1; end
            12'h310: begin CSR <= MSTATUSH; current_val <= mstatush; wmask <= '1; end

            12'h340: begin CSR <= MSCRATCH; current_val <= mscratch; wmask <= '1; end
            12'h341: begin CSR <= MEPC; current_val <= mepc; wmask <= '1; end
            12'h342: begin CSR <= MCAUSE; current_val <= mcause; wmask <= '1; end
            12'h343: begin CSR <= MTVAL; current_val <= mtval; wmask <= '1; end
            12'h344: begin CSR <= MIP; current_val <= mip; wmask <= '1; end
            12'h34A: begin CSR <= MTINST; current_val <= mtinst; wmask <= '1; end
            12'h34B: begin CSR <= MTVAL2; current_val <= mtval2; wmask <= '1; end
        endcase
    end

    always_comb
        if(csr_op==write)
            wr_data <= data & wmask;
        else if(csr_op==set)
            wr_data <= (current_val | data) & wmask;
        else if(csr_op==clear)
            wr_data <= (current_val & !data) & wmask;
        else
            wr_data <= 'Z;

    always @(negedge reset or posedge clk) begin
        if(!reset) begin
            mvendorid <= '0;
            marchid <= '0;
            mimpid <= '0;
            mhartid <= '0;
            mconfigptr <= '0;
        
            mstatus <= '0;
            misa <= '0;
            medeleg <= '0;
            mideleg <= '0;
            mie <= '0;
            mtvec <= '0;
            mcounteren <= '0;
            mstatush <= '0;
            mscratch <= '0;
            mepc <= '0;
            mcause <= '0;
            mtval <= '0;
            mip <= '0;
            mtinst <= '0;
            mtval2 <= '0;

        end else if(RAISE_EXCEPTION) begin

            mcause          <= 0 & EXCEPTION_CODE;
            mstatus[12:11]  <= privilege;           // MPP previous privilege
            mstatus[7]      <= mstatus[3];          // MPIE = MIE
            mstatus[3]      <= 0;                   // MIE = 0
            //mepc            <= PC+4;                // Return address
            mtval           <= (EXCEPTION_CODE==ILLEGAL_INSTRUCTION) ? instruction : PC;
        
        end else if(wr_en) begin
            case(CSR)
                MSTATUS:    mstatus     <= wr_data;
                MEDELEG:    medeleg     <= wr_data;
                MIDELEG:    mideleg     <= wr_data;
                MIE:        mie         <= wr_data;
                MTVEC:      mtvec       <= wr_data;
                MCOUNTEREN: mcounteren  <= wr_data;
                MSTATUSH:   mstatush    <= wr_data;
                MSCRATCH:   mscratch    <= wr_data;
                MEPC:       mepc        <= wr_data;
                MCAUSE:     mcause      <= wr_data;
                MTVAL:      mtval       <= wr_data;
                MIP:        mip         <= wr_data;
                MTINST:     mtinst      <= wr_data;
                MTVAL2:     mtval2      <= wr_data;
            endcase
        end
    end


endmodule;