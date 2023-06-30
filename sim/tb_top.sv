timeunit 1ns; timeprecision 1ns;

`include "./testbench.sv"

module tb_top
    import RS5_pkg::*;
;

    logic        clk=1, rstCPU;
    
    testbench tb(
        .clk_i(clk),
        .rst_i(rstCPU)
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
        rstCPU = 1;                                          // RESET for CPU initialization
        
        #100 rstCPU = 0;                                     // Hold state for 100 ns
    end

endmodule
