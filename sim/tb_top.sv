`timescale 1ns/1ns

`include "../rtl/RS5_pkg.sv"

module tb_top
    import RS5_pkg::*;
;

    logic        clk=1, rstCPU;
    
    testbench #(
        .INSTRUCTION_SET(RV32M),
        .USE_XOSVM(1'b1),
        .USE_ZIHPM(1'b1)
    ) tb (
        .clk_i(clk),
        .rst_n_i(rstCPU)
    );

///////////////////////////////////////// Clock generator //////////////////////////////
    always begin
        #5.0 clk = 0;
        #5.0 clk = 1;
    end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// RESET CPU ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    initial begin
        rstCPU = 0;                                          // RESET for CPU initialization
        
        #100 rstCPU = 1;                                     // Hold state for 100 ns
    end

endmodule
