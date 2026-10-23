/*!\file vectorPermute.sv
 *
 * Serial permutation engine of the vector unit: vrgather (.vv/.vx/.vi),
 * vrgatherei16.vv, vslideup/vslidedown (.vx/.vi) and vcompress.vm.
 *
 * One element per cycle, in a 2-stage pipeline plus a writeback register:
 *   stage 1: read the index source (vs1 group, or the vs1 mask for vcompress)
 *            and compute the source element number for destination element i
 *   stage 2: read the vs2 register that holds the source element and extract it
 *   writeback: write that one element to vd with byte enables
 * The spec forbids vd overlapping the source groups for these instructions,
 * so writing element by element never corrupts a source.
 *
 * PERMUTE_PARALLEL is reserved for a whole-register version; only the serial
 * version (0) exists.
 */

`include "../RS5_pkg.sv"

/* verilator lint_off WIDTHEXPAND */
/* verilator lint_off WIDTHTRUNC */
module vectorPermute
    import RS5_pkg::*;
#(
    parameter int VLEN             = 64,
    parameter int VLENB            = 8,
    parameter bit PERMUTE_PARALLEL = 1'b0
) (
    input  logic                      clk,
    input  logic                      reset_n,

    /* First cycle of the instruction: latch the operands and start */
    input  logic                      start_i,
    input  iTypeVector_e              vector_operation_i,
    input  opCat_e                    opCat_i,
    input  vew_e                      vsew,
    input  vlmul_e                    vlmul,
    input  logic [$bits(VLEN)-1:0]    vl,
    input  logic                      vm,
    input  logic [4:0]                vd_i,
    input  logic [4:0]                vs1_i,
    input  logic [4:0]                vs2_i,
    input  logic [31:0]               scalar_i,

    /* Register bank reads: the two operand ports and v0 */
    output logic [4:0]                vs1_addr_o,
    output logic [4:0]                vs2_addr_o,
    input  logic [VLEN-1:0]           vs1_data_i,
    input  logic [VLEN-1:0]           vs2_data_i,
    input  logic [VLEN-1:0]           v0_mask_i,

    output logic                      busy_o,

    /* Register bank write (registered) */
    output logic [VLENB-1:0]          we_o,
    output logic [4:0]                vd_addr_o,
    output logic [VLEN-1:0]           wdata_o
);

    if (PERMUTE_PARALLEL) begin : gen_parallel
        $error("vectorPermute: PERMUTE_PARALLEL = 1 is not implemented");
    end

    localparam int VLENB_LOG2 = $clog2(VLENB);
    localparam int IDX16_LOG2 = $clog2(VLEN/16);     /* 16-bit indices per register */
    localparam int CNT_W      = 32;                  /* element counters */

//////////////////////////////////////////////////////////////////////////////
// Operands latched at start
//////////////////////////////////////////////////////////////////////////////

    iTypeVector_e           op;
    opCat_e                 opCat_r;
    vew_e                   sew;
    logic                   masked;
    logic [4:0]             vd, vs1, vs2;
    logic [CNT_W-1:0]       vl_r;
    logic [CNT_W-1:0]       vlmax;
    logic [32:0]            offset;      /* slide amount, or the .vx/.vi gather index */
    logic [2:0]             epr_log2;    /* log2 of the elements per register at SEW */

    logic [CNT_W-1:0]       vlmax_next;
    logic [$bits(VLENB)-1:0] epr_next;

    assign epr_next = VLENB >> vsew;

    always_comb begin
        unique case (vlmul)
            LMUL_2:   vlmax_next = epr_next << 1;
            LMUL_4:   vlmax_next = epr_next << 2;
            LMUL_8:   vlmax_next = epr_next << 3;
            LMUL_1_2: vlmax_next = epr_next >> 1;
            LMUL_1_4: vlmax_next = epr_next >> 2;
            LMUL_1_8: vlmax_next = epr_next >> 3;
            default:  vlmax_next = epr_next;
        endcase
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            op       <= VNOP;
            opCat_r  <= OPIVV;
            sew      <= EW8;
            masked   <= 1'b0;
            vd       <= '0;
            vs1      <= '0;
            vs2      <= '0;
            vl_r     <= '0;
            vlmax    <= '0;
            offset   <= '0;
            epr_log2 <= '0;
        end
        else if (start_i) begin
            op       <= vector_operation_i;
            opCat_r  <= opCat_i;
            sew      <= vsew;
            masked   <= !vm;
            vd       <= vd_i;
            vs1      <= vs1_i;
            vs2      <= vs2_i;
            vl_r     <= vl;
            vlmax    <= vlmax_next;
            offset   <= (opCat_i == OPIVI) ? {28'b0, vs1_i} : {1'b0, scalar_i};
            epr_log2 <= 3'(VLENB_LOG2) - 3'(vsew);
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Element counters
//////////////////////////////////////////////////////////////////////////////

    logic [CNT_W-1:0] i;        /* stage 1 element: destination (source for vcompress) */
    logic [CNT_W-1:0] k;        /* vcompress write pointer */
    logic             running;

    /* vslideup leaves elements below the offset untouched, so it starts there */
    logic [32:0]      first_i;
    assign first_i = (vector_operation_i == VSLIDEUP)
                   ? ((opCat_i == OPIVI) ? {28'b0, vs1_i} : {1'b0, scalar_i})
                   : '0;

//////////////////////////////////////////////////////////////////////////////
// Stage 1: source element number of element i
//////////////////////////////////////////////////////////////////////////////

    logic [32:0] src;
    logic        active;

    /* Index element i of the vs1 group, read with EEW = SEW, or 16 for vrgatherei16 */
    logic [31:0] index_sew;
    logic [15:0] index_16;

    always_comb begin
        unique case (sew)
            EW8:     index_sew = {24'b0, vs1_data_i[(8  * i[VLENB_LOG2-1:0]) +: 8]};
            EW16:    index_sew = {16'b0, vs1_data_i[(16 * i[VLENB_LOG2-2:0]) +: 16]};
            default: index_sew =         vs1_data_i[(32 * i[VLENB_LOG2-3:0]) +: 32];
        endcase
        index_16 = vs1_data_i[(16 * i[IDX16_LOG2-1:0]) +: 16];
    end

    always_comb begin
        if (op == VRGATHEREI16)
            vs1_addr_o = vs1 + 5'(i >> IDX16_LOG2);
        else if (op == VCOMPRESS)
            vs1_addr_o = vs1;
        else
            vs1_addr_o = vs1 + 5'(i >> epr_log2);
    end

    always_comb begin
        unique case (op)
            VRGATHER:     src = (opCat_r == OPIVV) ? {1'b0, index_sew} : offset;
            VRGATHEREI16: src = {17'b0, index_16};
            VSLIDEUP:     src = 33'(i) - offset;
            VSLIDEDOWN:   src = 33'(i) + offset;
            default:      src = 33'(i);          /* VCOMPRESS reads source element i */
        endcase

        if (op == VCOMPRESS)
            active = vs1_data_i[i];
        else
            active = !masked || v0_mask_i[i];
    end


    logic             s1_valid;
    logic [CNT_W-1:0] s1_dst;
    logic [32:0]      s1_src;
    logic             s1_in_range;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            running     <= 1'b0;
            i           <= '0;
            k           <= '0;
            s1_valid    <= 1'b0;
            s1_dst      <= '0;
            s1_src      <= '0;
            s1_in_range <= 1'b0;
        end
        else if (start_i) begin
            running     <= (first_i < 33'(vl));   /* nothing to do when vl <= offset */
            i           <= CNT_W'(first_i);
            k           <= '0;
            s1_valid    <= 1'b0;
        end
        else if (running) begin
            s1_valid    <= active;
            s1_dst      <= (op == VCOMPRESS) ? k : i;
            s1_src      <= src;
            s1_in_range <= (src < 33'(vlmax));
            if (op == VCOMPRESS && active)
                k       <= k + 1'b1;
            i           <= i + 1'b1;
            running     <= ((i + 1'b1) < vl_r);
        end
        else begin
            s1_valid    <= 1'b0;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Stage 2: read the source element and write it to its destination slot
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] element;

    assign vs2_addr_o = vs2 + 5'(s1_src >> epr_log2);

    always_comb begin
        unique case (sew)
            EW8:     element = {24'b0, vs2_data_i[(8  * s1_src[VLENB_LOG2-1:0]) +: 8]};
            EW16:    element = {16'b0, vs2_data_i[(16 * s1_src[VLENB_LOG2-2:0]) +: 16]};
            default: element =         vs2_data_i[(32 * s1_src[VLENB_LOG2-3:0]) +: 32];
        endcase
        /* Gather and slidedown read 0 past VLMAX */
        if (!s1_in_range)
            element = '0;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            we_o      <= '0;
            vd_addr_o <= '0;
            wdata_o   <= '0;
        end
        else begin
            we_o      <= '0;
            vd_addr_o <= vd + 5'(s1_dst >> epr_log2);
            unique case (sew)
                EW8: begin
                    wdata_o <= {VLENB{element[7:0]}};
                    if (s1_valid)
                        we_o[s1_dst[VLENB_LOG2-1:0]] <= 1'b1;
                end
                EW16: begin
                    wdata_o <= {(VLENB/2){element[15:0]}};
                    if (s1_valid)
                        we_o[(2 * s1_dst[VLENB_LOG2-2:0]) +: 2] <= 2'b11;
                end
                default: begin
                    wdata_o <= {(VLENB/4){element}};
                    if (s1_valid)
                        we_o[(4 * s1_dst[VLENB_LOG2-3:0]) +: 4] <= 4'b1111;
                end
            endcase
        end
    end

    assign busy_o = running || s1_valid;

endmodule
/* verilator lint_on WIDTHEXPAND */
/* verilator lint_on WIDTHTRUNC */
