// Per-instruction trace of the execute stage, bound into RS5 (no RTL edits).
// One line per instruction that leaves execute:
//   <cycle> <pc> <instr> <cycles spent in execute (1 + hold cycles)>
// cycle counts clock edges since reset release.
module trace_mon (
    input logic        clk, reset_n, stall, hold, exec_valid,
    input logic [31:0] pc, instr
);
    int fd; longint cyc; int held;
    string fn;
    initial begin
        if (!$value$plusargs("TRACE=%s", fn)) fn = "trace.txt";
        fd = $fopen(fn, "w");
        cyc = 0; held = 0;
    end
    always @(posedge clk) begin
        if (!reset_n) begin cyc <= 0; held <= 0; end
        else begin
            cyc <= cyc + 1;
            if (exec_valid && !stall) begin
                if (hold) held <= held + 1;
                else begin
                    $fwrite(fd, "%0d %h %h %0d\n", cyc, pc, instr, held + 1);
                    held <= 0;
                end
            end
        end
    end
    final $fclose(fd);
endmodule

bind RS5 trace_mon tm (.clk(clk), .reset_n(reset_n), .stall(stall), .hold(hold),
                       .exec_valid(exec_valid), .pc(pc_execute), .instr(instruction_execute));
