//------------------------------------------------------------------------------
// Standalone self-checking testbench for DMWBCtrl.
//
// Validates the parameterizable data-width datapath - in particular the
// multi-beat fill/eviction lane logic that the scalar riscv-tests cannot reach
// (they only exercise DATA_WIDTH == MEM_WIDTH == 32).
//
// Strategy: drive cold misses, dirty hits and conflict evictions, then read the
// evicted address back so a *read from main memory* must observe the value that
// was written back. This exercises write-back across every beat lane.
//
// Override DATA_WIDTH / MEM_WIDTH with verilator -G to sweep configurations.
//------------------------------------------------------------------------------

module tb_dmwb_unit #(
    parameter int unsigned DATA_WIDTH  = 32,
    parameter int unsigned MEM_WIDTH   = 32,
    parameter int unsigned ADDR_WIDTH  = 16,
    parameter int unsigned CACHE_WIDTH = 8,
    parameter int unsigned OFFSET_WIDTH= 4
);

    timeunit 1ns; timeprecision 1ns;

    localparam int unsigned DATA_BYTES = DATA_WIDTH/8;
    localparam int unsigned MEM_BYTES  = MEM_WIDTH/8;
    localparam int unsigned CACHE_SIZE = (1 << CACHE_WIDTH);   // bytes
    localparam int unsigned MODEL_AW   = 14;                   // 16 KiB main-mem model
    localparam int unsigned MODEL_SIZE = (1 << MODEL_AW);

    logic clk = 0;
    always #5 clk = ~clk;

    logic rst_n;

    /* Core side */
    logic                    ce;
    logic [DATA_BYTES-1:0]   we;
    logic [ADDR_WIDTH-1:0]   addr;
    logic [DATA_WIDTH-1:0]   din;
    logic [DATA_WIDTH-1:0]   dout;
    logic                    busy;

    /* Cache SRAM side */
    logic                    cache_ce;
    logic [DATA_BYTES-1:0]   cache_we;
    logic [CACHE_WIDTH-1:0]  cache_addr;
    logic [DATA_WIDTH-1:0]   cache_rdata;
    logic [DATA_WIDTH-1:0]   cache_wdata;

    /* Main memory side */
    logic                    mem_ce;
    logic [MEM_BYTES-1:0]    mem_we;
    logic [ADDR_WIDTH-1:0]   mem_addr;
    logic [MEM_WIDTH-1:0]    mem_rdata;
    logic [MEM_WIDTH-1:0]    mem_wdata;
    logic                    mem_busy;

    DMWBCtrl #(
        .ADDR_WIDTH  (ADDR_WIDTH ),
        .CACHE_WIDTH (CACHE_WIDTH),
        .OFFSET_WIDTH(OFFSET_WIDTH),
        .DATA_WIDTH  (DATA_WIDTH ),
        .MEM_WIDTH   (MEM_WIDTH  )
    ) dut (
        .clk(clk), .rst_n(rst_n),
        .ce_i(ce), .we_i(we), .address_i(addr), .data_i(din), .data_o(dout), .busy_o(busy),
        .cache_ce_o(cache_ce), .cache_we_o(cache_we), .cache_addr_o(cache_addr),
        .cache_data_i(cache_rdata), .cache_data_o(cache_wdata),
        .mem_ce_o(mem_ce), .mem_we_o(mem_we), .mem_addr_o(mem_addr),
        .mem_data_i(mem_rdata), .mem_data_o(mem_wdata), .mem_busy_i(mem_busy)
    );

    //--------------------------------------------------------------------------
    // Cache SRAM model: synchronous, byte-writable, 1-cycle latency, never busy
    //--------------------------------------------------------------------------
    logic [7:0] csram [CACHE_SIZE];
    always_ff @(posedge clk) begin
        if (cache_ce) begin
            if (cache_we == '0) begin
                for (int i = 0; i < DATA_BYTES; i++)
                    cache_rdata[8*i +: 8] <= csram[cache_addr + i];
            end
            else begin
                for (int i = 0; i < DATA_BYTES; i++)
                    if (cache_we[i]) csram[cache_addr + i] <= cache_wdata[8*i +: 8];
            end
        end
    end

    //--------------------------------------------------------------------------
    // Main memory model: synchronous, byte-writable, zero latency (busy = 0)
    //--------------------------------------------------------------------------
    logic [7:0] mmem [MODEL_SIZE];
    assign mem_busy = 1'b0;
    always_ff @(posedge clk) begin
        if (mem_ce) begin
            if (mem_we == '0) begin
                for (int i = 0; i < MEM_BYTES; i++)
                    mem_rdata[8*i +: 8] <= mmem[(mem_addr + i) & (MODEL_SIZE-1)];
            end
            else begin
                for (int i = 0; i < MEM_BYTES; i++)
                    if (mem_we[i]) mmem[(mem_addr + i) & (MODEL_SIZE-1)] <= mem_wdata[8*i +: 8];
            end
        end
    end

    //--------------------------------------------------------------------------
    // Reference helpers
    //--------------------------------------------------------------------------
    function automatic logic [DATA_WIDTH-1:0] ref_word(input int byte_addr);
        logic [DATA_WIDTH-1:0] v;
        for (int i = 0; i < DATA_BYTES; i++)
            v[8*i +: 8] = mmem[(byte_addr + i) & (MODEL_SIZE-1)];
        return v;
    endfunction

    int errors = 0;

    // Hold the request until the controller is idle for the access, then a
    // couple of extra cycles so the (idempotent) hit settles, and sample.
    task automatic do_read(input int a, output logic [DATA_WIDTH-1:0] d);
        @(negedge clk);
        ce = 1'b1; we = '0; addr = a[ADDR_WIDTH-1:0]; din = '0;
        @(posedge clk);
        while (busy) @(posedge clk);   // wait out any miss burst
        @(posedge clk);                // hit read issued -> data next cycle
        @(posedge clk);
        d = dout;
        @(negedge clk); ce = 1'b0;
    endtask

    task automatic do_write(input int a, input logic [DATA_WIDTH-1:0] d);
        @(negedge clk);
        ce = 1'b1; we = '1; addr = a[ADDR_WIDTH-1:0]; din = d;
        @(posedge clk);
        while (busy) @(posedge clk);   // wait out any miss burst (evict+fill)
        @(posedge clk);                // write hit commits
        @(negedge clk); ce = 1'b0; we = '0;
    endtask

    task automatic check(input string name, input logic [DATA_WIDTH-1:0] got, exp);
        if (got !== exp) begin
            $display("  [FAIL] %s: got %h exp %h", name, got, exp);
            errors++;
        end
        else begin
            $display("  [ ok ] %s: %h", name, got);
        end
    endtask

    //--------------------------------------------------------------------------
    // Stimulus
    //--------------------------------------------------------------------------
    logic [DATA_WIDTH-1:0] rd, exp;
    int A0, A1;

    initial begin
        // distinct, address-derived init pattern
        for (int i = 0; i < MODEL_SIZE; i++)
            mmem[i] = 8'((i * 7) ^ (i >> 5));
        for (int i = 0; i < CACHE_SIZE; i++)
            csram[i] = '0;

        ce = 0; we = '0; addr = '0; din = '0;
        rst_n = 0;
        repeat (4) @(posedge clk);
        rst_n = 1;
        @(posedge clk);

        $display("DMWBCtrl unit test  DATA_WIDTH=%0d MEM_WIDTH=%0d", DATA_WIDTH, MEM_WIDTH);

        // A0 and A1 share the cache index but differ in tag (conflict)
        A0 = DATA_BYTES * 2;                 // an aligned word in line 0
        A1 = A0 + CACHE_SIZE;               // same index, different tag

        // 1) cold read miss -> must fetch A0 from main memory
        exp = ref_word(A0);
        do_read(A0, rd);
        check("cold read A0", rd, exp);

        // 2) write A0 (dirty hit), then read it back from cache
        exp = {DATA_WIDTH{1'b1}} ^ {DATA_WIDTH{1'b0}};
        exp = '0; for (int i = 0; i < DATA_BYTES; i++) exp[8*i +: 8] = 8'hA0 + 8'(i);
        do_write(A0, exp);
        do_read(A0, rd);
        check("read-after-write A0 (cache)", rd, exp);

        // 3) read A1 -> conflict miss, evicts the dirty A0 line to main memory
        do_read(A1, rd);
        check("conflict read A1", rd, ref_word(A1));

        // 4) read A0 again -> A1 resident, so this misses and (after evicting the
        //    now-clean A1 line) refills A0 *from main memory*. The value must be
        //    the one written in step 2, proving the write-back reached memory.
        do_read(A0, rd);
        check("write-back persisted at A0", rd, exp);

        // 5) main-memory bytes at A0 must literally hold the written value
        check("main memory bytes at A0", ref_word(A0), exp);

        repeat (4) @(posedge clk);
        if (errors == 0)
            $display("RESULT: PASS (DATA_WIDTH=%0d MEM_WIDTH=%0d)", DATA_WIDTH, MEM_WIDTH);
        else
            $display("RESULT: FAIL (%0d errors)", errors);
        $finish;
    end

    // safety timeout
    initial begin
        #100000;
        $display("RESULT: FAIL (timeout)");
        $finish;
    end

endmodule
