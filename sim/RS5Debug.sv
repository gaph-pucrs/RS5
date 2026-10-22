/*!
 * \file RS5Debug.sv
 *
 * \brief
 * Instruction trace logging module in the sail-riscv 0.7 format.
 *
 * \detailed
 * Instructions are captured when they leave execute and are printed when
 * they reach retire, so the register write-back and load data are known.
 * The output can be diffed against `riscv_sim_rv32d` once the disassembly
 * is removed from its instruction lines, e.g.:
 * sed -E 's/^(\[[0-9]+\] \[[MSU]\]: 0x[0-9A-F]+ \(0x[0-9A-F]+\)).*$/\1/'
 *
 * \author
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * GAPH - Hardware Design Support Group <https://nsesd.pucrs.br/en/pages/groups/gaph.html>
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul <https://pucrs.br/>
*/

module RS5Debug
    import RS5_pkg::*;
#(
    parameter bit COMPRESSED = 1'b0
);
    string file_name;
    int fd;

    initial begin
        file_name = $sformatf("%m.log");
        fd = $fopen(file_name, "w");
    end

    /* Sail RV32 physical addresses are 34 bits wide, hence printed in binary */
    function automatic string paddr_str(input logic [31:0] addr);
        return $sformatf("0b%034b", {2'b00, addr});
    endfunction

    /* Sail prints bit vectors as uppercase hex padded to their width */
    function automatic string hex_str(input logic [31:0] data, input int bits);
        string s;
        case (bits)
            8:       s = $sformatf("%02h", data[7:0]);
            16:      s = $sformatf("%04h", data[15:0]);
            64:      s = $sformatf("%016h", data);
            default: s = $sformatf("%08h", data);
        endcase
        return {"0x", s.toupper()};
    endfunction

    function automatic string data_str(input logic [31:0] data, input logic is_byte, input logic is_half);
        return hex_str(data, is_byte ? 8 : is_half ? 16 : 32);
    endfunction

    function automatic string priv_str(input privilegeLevel_e priv);
        case (priv)
            USER:       return "U";
            SUPERVISOR: return "S";
            default:    return "M";
        endcase
    endfunction

    function automatic string csr_str(input logic [11:0] addr);
        CSRs csr = CSRs'(addr);
        if (csr == VLENBYTES)
            return "vlenb";
        return csr.name().tolower();
    endfunction

    /* Sail keeps mstatus in a 64 bit bitfield, so even RV32 prints it 64 bits wide */
    function automatic int csr_bits(input logic [11:0] addr);
        return (CSRs'(addr) == MSTATUS) ? 64 : 32;
    endfunction

    function automatic string exc_str(input exceptionCode_e code);
        case (code)
            INSTRUCTION_ADDRESS_MISALIGNED: return "misaligned-fetch";
            INSTRUCTION_ACCESS_FAULT:       return "fetch-access-fault";
            ILLEGAL_INSTRUCTION:            return "illegal-instruction";
            BREAKPOINT:                     return "breakpoint";
            LOAD_ADDRESS_MISALIGNED:        return "misaligned-load";
            LOAD_ACCESS_FAULT:              return "load-access-fault";
            STORE_AMO_ADDRESS_MISALIGNED:   return "misaligned-store/amo";
            STORE_AMO_ACCESS_FAULT:         return "store/amo-access-fault";
            ECALL_FROM_UMODE:               return "u-call";
            ECALL_FROM_SMODE:               return "s-call";
            ECALL_FROM_MMODE:               return "m-call";
            INSTRUCTION_PAGE_FAULT:         return "fetch-page-fault";
            LOAD_PAGE_FAULT:                return "load-page-fault";
            STORE_AMO_PAGE_FAULT:           return "store/amo-page-fault";
            default:                        return "reserved";
        endcase
    endfunction

//////////////////////////////////////////////////////////////////////////////
// Raw instruction
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] instruction;
    if (COMPRESSED) begin : gen_compressed_on
        /* Execute only sees the decompressed instruction, so track the raw one */
        logic [31:0] instruction_decode;
        always_ff @(posedge RS5.clk) begin
            if (RS5.fetch1.enable_i || RS5.fetch1.is_jumping)
                instruction_decode <= RS5.fetch1.gen_compressed_on.instruction_built;
            if (RS5.enable_decode)
                instruction <= instruction_decode;
        end
    end
    else begin : gen_compressed_off
        assign instruction = RS5.instruction_execute;
    end

//////////////////////////////////////////////////////////////////////////////
// Trace
//////////////////////////////////////////////////////////////////////////////

    typedef struct {
        logic            valid;
        string           log;
        logic            load;
        logic            is_byte;
        logic            is_half;
        exceptionCode_e  exception;
        logic            mret;
        logic            irq;
        privilegeLevel_e priv;
    } entry_t;

    entry_t entry, entry_mem, entry_ret;
    int     step;
    logic   fresh;

    logic stepped, fetch_fault;
    /* Execute holds an all-zero (valid looking) ctrl until decode first loads it */
    logic started;
    always_ff @(posedge RS5.clk or negedge RS5.reset_n) begin
        if (!RS5.reset_n)
            started <= 1'b0;
        else if (RS5.enable_decode)
            started <= 1'b1;
    end

    assign stepped     = started && !RS5.stall && !RS5.hold && (RS5.exec_valid || RS5.ctrl_execute.exc_ilegal_inst);
    assign fetch_fault = RS5.RAISE_EXCEPTION && RS5.ctrl_execute.exc_inst_access_fault;

    /* An AMO is held in execute while it loads, modifies and stores: amo_operand
     * carries the loaded value one cycle before it carries the value stored back */
    logic [31:0] amo_loaded;
    always_ff @(posedge RS5.clk) begin
        if (!RS5.stall)
            amo_loaded <= RS5.execute1.amo_operand;
    end

    /* Execute: everything known when the instruction is committed */
    /* LR/SC and vector memory/register effects are not traced */
    always_comb begin
        entry.valid     = stepped || fetch_fault;
        entry.log       = "";
        entry.load      = 1'b0;
        entry.is_byte   = RS5.ctrl_execute.is_byte;
        entry.is_half   = RS5.ctrl_execute.is_half;
        entry.exception = RS5.RAISE_EXCEPTION ? RS5.Exception_Code : NE;
        entry.mret      = RS5.MACHINE_RETURN;
        entry.irq       = RS5.interrupt_ack_o;
        entry.priv      = RS5.privilege;

        if (stepped) begin
            if (RS5.ctrl_execute.compressed) begin
                entry.log = {entry.log, $sformatf("mem[X,%s] -> %s\n", paddr_str(RS5.pc_execute), hex_str(instruction, 16))};
                entry.log = {entry.log, $sformatf("[%0d] [%s]: %s (%s)\n", step, priv_str(RS5.privilege), hex_str(RS5.pc_execute, 32), hex_str(instruction, 16))};
            end
            else begin
                entry.log = {entry.log, $sformatf("mem[X,%s] -> %s\n", paddr_str(RS5.pc_execute),        hex_str(instruction, 16))};
                entry.log = {entry.log, $sformatf("mem[X,%s] -> %s\n", paddr_str(RS5.pc_execute + 32'd2), hex_str(32'(instruction[31:16]), 16))};
                entry.log = {entry.log, $sformatf("[%0d] [%s]: %s (%s)\n", step, priv_str(RS5.privilege), hex_str(RS5.pc_execute, 32), hex_str(instruction, 32))};
            end

            if (!RS5.RAISE_EXCEPTION) begin
                /* printed value is pre-WARL, read CSRBank back if legalization diverges */
                if (RS5.csr_write_enable)
                    entry.log = {entry.log, $sformatf("CSR %s <- %s (input: %s)\n", csr_str(RS5.csr_addr), hex_str(RS5.CSRBank1.wr_data, csr_bits(RS5.csr_addr)), hex_str(RS5.CSRBank1.wr_data, 32))};
                else if (RS5.ctrl_execute.is_csr)
                    entry.log = {entry.log, $sformatf("CSR %s -> %s\n", csr_str(RS5.csr_addr), hex_str(RS5.csr_data_read, 32))};

                if (RS5.ctrl_execute.is_store)
                    entry.log = {entry.log, $sformatf("mem[%s] <- %s\n", paddr_str(RS5.mem_address_exec), data_str(RS5.rs2_data_execute, RS5.ctrl_execute.is_byte, RS5.ctrl_execute.is_half))};

                if (RS5.ctrl_execute.is_amo) begin
                    entry.log = {entry.log, $sformatf("mem[RW,%s] -> %s\n", paddr_str(RS5.mem_address_exec), hex_str(amo_loaded, 32))};
                    entry.log = {entry.log, $sformatf("mem[%s] <- %s\n",    paddr_str(RS5.mem_address_exec), hex_str(RS5.execute1.amo_operand, 32))};
                end

                entry.load = RS5.ctrl_execute.is_load;
            end
        end
    end

    /* Mirror the execute -> mem_access -> retire registers */
    always_ff @(posedge RS5.clk or negedge RS5.reset_n) begin
        if (!RS5.reset_n) begin
            step            <= 0;
            fresh           <= 1'b0;
            entry_mem.valid <= 1'b0;
            entry_ret.valid <= 1'b0;
        end
        else begin
            if (stepped)
                step <= step + 1;
            if (!RS5.stall) begin
                entry_ret <= entry_mem;
                entry_mem <= entry;
            end
            fresh <= !RS5.stall;
        end
    end

    /* AMOs write rd while held in execute, before they are committed */
    string rd_write, rd_pending;
    always_comb begin
        rd_write = "";
        if (RS5.ctrl_retire.rd_we && RS5.rd_retire != '0)
            rd_write = $sformatf("x%0d <- %s\n", RS5.rd_retire, hex_str(RS5.regbank_data_writeback, 32));
    end

    always_ff @(posedge RS5.clk or negedge RS5.reset_n) begin
        if (!RS5.reset_n)
            rd_pending <= "";
        else if (fresh && entry_ret.valid)
            rd_pending <= "";
        else
            rd_pending <= {rd_pending, rd_write};
    end

    /* Retire: the write-back and load data of the oldest instruction */
    always_ff @(posedge RS5.clk) begin
        if (fd != 0 && fresh && entry_ret.valid) begin
            $fwrite(fd, "%s", entry_ret.log);

            if (entry_ret.load)
                $fwrite(fd, "mem[R,%s] -> %s\n",
                    paddr_str(RS5.result_retire),
                    data_str(
                        entry_ret.is_byte ? 32'(RS5.retire1.byte_data) : entry_ret.is_half ? 32'(RS5.retire1.half_data) : RS5.retire1.mem_data_i,
                        entry_ret.is_byte,
                        entry_ret.is_half
                    )
                );

            $fwrite(fd, "%s%s", rd_pending, rd_write);

            /* CSRBank was updated when the instruction left execute */
            if (entry_ret.exception != NE) begin
                $fwrite(fd, "trapping from %s to M to handle %s\n", priv_str(entry_ret.priv), exc_str(entry_ret.exception));
                $fwrite(fd, "handling exc#%s at priv M with tval %s\n", hex_str(32'(entry_ret.exception), 8), hex_str(RS5.CSRBank1.mtval, 32));
                $fwrite(fd, "CSR mstatus <- %s\n", hex_str(RS5.CSRBank1.mstatus, 64));
            end

            if (entry_ret.mret) begin
                $fwrite(fd, "CSR mstatus <- %s\n", hex_str(RS5.CSRBank1.mstatus, 64));
                $fwrite(fd, "ret-ing from M to %s\n", priv_str(RS5.CSRBank1.privilege));
            end

            /* Sail takes the interrupt at the start of the next step */
            if (entry_ret.irq) begin
                $fwrite(fd, "Handling interrupt: %s\n", hex_str(32'(RS5.CSRBank1.mcause_exception_code), 8));
                $fwrite(fd, "handling int#%s at priv M with tval 0x00000000\n", hex_str(32'(RS5.CSRBank1.mcause_exception_code), 8));
                $fwrite(fd, "CSR mstatus <- %s\n", hex_str(RS5.CSRBank1.mstatus, 64));
            end
        end
    end

    final begin
        $fclose(fd);
    end

endmodule
