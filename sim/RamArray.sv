/*!
 * \file RamArray.sv
 *
 * \brief
 * Drop-in replacement for RAM_mem built from as many RAM_mem banks as MEM_WIDTH needs.
 *
 * \detailed
 * Verilator rejects unpacked arrays of 2**29 or more elements, so a single
 * RAM_mem holds at most 2**28 bytes. RamArray splits the address space into
 * contiguous banks: the upper address bits select the bank (chip enable),
 * the lower bits address the byte inside it. Bank k is loaded with BIN_FILE
 * starting at file offset k * 2**BANK_ADDR_BITS.
 *
 * Accesses must not cross a bank boundary. RS5 addresses are word aligned,
 * so this holds for BUS_WIDTH = 32.
 */

module RamArray
#(
    parameter longint unsigned MEM_WIDTH = 65536,
    parameter int              BUS_WIDTH = 32,
    parameter string           BIN_FILE  = "../app/baremetal/tests/riscv-tests/test.bin"
)
(
    input  logic                             clk,

    input  logic                             enA_i,
    input  logic [BUS_WIDTH/8-1:0]           weA_i,
    input  logic [($clog2(MEM_WIDTH) - 1):0] addrA_i,
    input  logic [BUS_WIDTH-1:0]             dataA_i,
    output logic [BUS_WIDTH-1:0]             dataA_o,

    input  logic                             enB_i,
    input  logic [BUS_WIDTH/8-1:0]           weB_i,
    input  logic [($clog2(MEM_WIDTH) - 1):0] addrB_i,
    input  logic [BUS_WIDTH  -1:0]           dataB_i,
    output logic [BUS_WIDTH  -1:0]           dataB_o
);

    /* Largest RAM_mem Verilator accepts (2**28 bytes) */
    localparam int BANK_ADDR_BITS = 28;
    localparam int MEM_ADDR_BITS  = $clog2(MEM_WIDTH);

    if (MEM_ADDR_BITS <= BANK_ADDR_BITS) begin : single_bank
        RAM_mem #(
            .MEM_WIDTH (int'(MEM_WIDTH)),
            .BUS_WIDTH (BUS_WIDTH      ),
            .BIN_FILE  (BIN_FILE       )
        ) bank (
            .clk     (clk    ),
            .enA_i   (enA_i  ),
            .weA_i   (weA_i  ),
            .addrA_i (addrA_i),
            .dataA_i (dataA_i),
            .dataA_o (dataA_o),
            .enB_i   (enB_i  ),
            .weB_i   (weB_i  ),
            .addrB_i (addrB_i),
            .dataB_i (dataB_i),
            .dataB_o (dataB_o)
        );
    end
    else begin : banked
        localparam int SEL_BITS  = MEM_ADDR_BITS - BANK_ADDR_BITS;
        localparam int NUM_BANKS = (MEM_WIDTH + (1 << BANK_ADDR_BITS) - 1) >> BANK_ADDR_BITS;

        logic [SEL_BITS-1:0]  selA, selB;
        logic [SEL_BITS-1:0]  selA_r, selB_r;
        logic [BUS_WIDTH-1:0] dataA [NUM_BANKS];
        logic [BUS_WIDTH-1:0] dataB [NUM_BANKS];

        assign selA = addrA_i[MEM_ADDR_BITS-1:BANK_ADDR_BITS];
        assign selB = addrB_i[MEM_ADDR_BITS-1:BANK_ADDR_BITS];

        for (genvar k = 0; k < NUM_BANKS; k++) begin : bank
            /* The bank loads nothing by itself: its slice of BIN_FILE is loaded below */
            RAM_mem #(
                .MEM_WIDTH (1 << BANK_ADDR_BITS),
                .BUS_WIDTH (BUS_WIDTH          ),
                .BIN_FILE  ("/dev/null"        )
            ) mem (
                .clk     (clk                              ),
                .enA_i   (enA_i && selA == k               ),
                .weA_i   (weA_i                            ),
                .addrA_i (addrA_i[BANK_ADDR_BITS-1:0]      ),
                .dataA_i (dataA_i                          ),
                .dataA_o (dataA[k]                         ),
                .enB_i   (enB_i && selB == k               ),
                .weB_i   (weB_i                            ),
                .addrB_i (addrB_i[BANK_ADDR_BITS-1:0]      ),
                .dataB_i (dataB_i                          ),
                .dataB_o (dataB[k]                         )
            );

            initial begin
                int fd;
                longint offset;
                offset = longint'(k) << BANK_ADDR_BITS;
                fd = $fopen(BIN_FILE, "r");
                if (fd == '0) begin
                    $display("[%d] [RamArray] ERROR: %s not found.", $time(), BIN_FILE);
                    $finish();
                end

                /* Banks past the end of BIN_FILE stay empty */
                void'($fseek(fd, 0, 2));
                if (offset < $ftell(fd)) begin
                    void'($fseek(fd, int'(offset), 0));
                    void'($fread(mem.RAM, fd));
                end
                $fclose(fd);
            end
        end

        /* RAM_mem only updates its output on reads, so track the bank of the last read */
        always_ff @(posedge clk) begin
            if (enA_i && weA_i == '0)
                selA_r <= selA;
            if (enB_i && weB_i == '0)
                selB_r <= selB;
        end

        assign dataA_o = dataA[selA_r];
        assign dataB_o = dataB[selB_r];
    end

endmodule
