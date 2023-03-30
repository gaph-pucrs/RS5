module rtc (
    input         clk,
    input         reset,
    input  [3:0]  addr,
    //input  [7:0]  we,
    input  [63:0] data_i,
    output [63:0] data_o,
    //output [63:0] mtime_o,
    //output [63:0] mtimecmp_o
);
    logic mtime [63:0];
    logic mtimecmp [63:0];

    always_ff @(posedge clk) begin
        if (reset) begin
            mtime    <= '0;
            mtimecmp <= '0;
        end 
        else begin
            mtime <= mtime + 1;
            if (mtime >= mtimecmp) begin
            // Interrupt generation
            // .
            // .
            // .
            end
        end
    end

    always_ff @(posedge clk) begin
    if (!reset) begin
        ///////////////////////////// Writes  ///////////////////////////////////////////
        if (addr != '0) begin
            if (addr[3]) begin                                
                // data_o[63:47] <= data_i[63:47];
            end 
            if (addr[2]) begin                                 
               // data_i[47:31];
            end
            if (addr[1]) begin                                 
                // data_i[31:15];
            end
            if (addr[0]) begin                                 
                // data_i[15:0];
            end
        end
    end
    end

endmodule
