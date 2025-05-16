`include "RS5_pkg.sv"
    
module decompresser 
    import RS5_pkg::*;
#(
    parameter mul_e MULEXT    = MUL_M,
    parameter bit   ZCBEnable = 1'b0
)
(
    input  logic [15:0] instruction_i,
    output logic [31:0] instruction_o
);

    logic [1:0]  op;
    logic [3:0]  funct4;
    logic [5:0]  funct6;
    logic [2:0]  funct3;
    logic [1:0]  funct2;
    logic [2:0]  zcb_funct;

    logic [11:0] CIW_imm;
    logic [4:0]  CIW_rd;

    logic [11:0] lw_sw_imm;
    logic [4:0]  lsu_rs1;
    logic [4:0]  lsu_rs2;

    logic [11:0] lsu_zcb_imm;
    logic [11:0] lh_zcb_imm;

    logic [19:0] CJ_imm;
    logic [4:0]  CJ_rd;

    logic [11:0] branch_imm;
    logic [4:0]  branch_rs1;

    logic [5:0]  CB_imm;
    logic [4:0]  CB_rd;

    logic [5:0]  CI_imm;
    logic [4:0]  CI_rd;

    logic [4:0]  CS_rs1;
    logic [4:0]  CS_rs2;

    logic [5:0]  CSS_imm;
    logic [4:0]  CSS_rs2;

    logic [4:0]  CR_rs1;
    logic [4:0]  CR_rs2;

    logic [31:0] expansion_C0, expansion_C1, expansion_C2;

    assign op        = instruction_i[1:0];
    assign funct4    = instruction_i[15:12];
    assign funct6    = instruction_i[15:10];
    assign funct3    = instruction_i[15:13];
    assign funct2    = instruction_i[6:5];
    assign zcb_funct = instruction_i[4:2];

    always_comb begin
        unique case (op)
            2'b00:   instruction_o = expansion_C0;
            2'b01:   instruction_o = expansion_C1;
            2'b10:   instruction_o = expansion_C2;
            default: instruction_o = '0;
        endcase
    end

    /* EXPANDED ARGUMENTS */
    // CIW instructions (C.ADDI4SPN)
    assign CIW_imm = {2'b00, instruction_i[10:7], instruction_i[12:11], instruction_i[5], instruction_i[6], 2'b00};
    assign CIW_rd  = {2'b01, instruction_i[4:2]};

    // C.LW and C.SW
    assign lw_sw_imm = {5'b00000, instruction_i[5], instruction_i[12:10], instruction_i[6], 2'b00};

    // Registers for load/store instructions
    assign lsu_rs1 = {2'b01, instruction_i[9:7]};
    assign lsu_rs2 = {2'b01, instruction_i[4:2]};

    // C.LBU, C.SB, C.SH
    assign lsu_zcb_imm = {10'b0, instruction_i[5], instruction_i[6]};

    // C.LHU, C.LH
    assign lh_zcb_imm = {10'b0, instruction_i[5], 1'b0};

    // C.J and C.JAL
    assign CJ_imm = {
        instruction_i[12], instruction_i[8], instruction_i[10:9], instruction_i[6], 
        instruction_i[7], instruction_i[2], instruction_i[11], instruction_i[5:3], {9 {instruction_i[12]}}
    };
    assign CJ_rd = {4'b0000, ~instruction_i[15]};

    // C.BEQZ, C.BNEZ
    assign branch_imm = {
        {4 {instruction_i[12]}}, instruction_i[6:5], instruction_i[2], instruction_i[11:10], 
        instruction_i[4:3], instruction_i[12]
    };
    assign branch_rs1 = {2'b01, instruction_i[9:7]};

    // C.LI, C.LUI, C.ADDI, C.ADDI16SP
    assign CI_rd  = instruction_i[11:7];
    assign CI_imm = {instruction_i[12], instruction_i[6:2]};

    // C.SRLI, C.SRAI
    assign CB_rd  = {2'b01, instruction_i[9:7]};
    assign CB_imm = {instruction_i[12], instruction_i[6:2]};

    // C.AND, C.OR, C.XOR, C.SUB
    assign CS_rs1 = {2'b01, instruction_i[9:7]};
    assign CS_rs2 = {2'b01, instruction_i[4:2]};

    // C.SWSP
    assign CSS_imm = {instruction_i[8:7], instruction_i[12:9]};
    assign CSS_rs2 = instruction_i[6:2];

    // C.JR, C.JALR
    assign CR_rs1  = instruction_i[11:7];
    assign CR_rs2  = instruction_i[6:2];

    /* op = C0 */

    logic [31:0] expansion_zcb0;

    always_comb begin
        unique case (funct3) inside
            3'b000:  expansion_C0 = {CIW_imm, 5'h02, 3'b000, CIW_rd, 7'b0010011}; /* C.ADDI4SPN */
            3'b010:  expansion_C0 = {lw_sw_imm, lsu_rs1, 3'b010, lsu_rs2, 7'b0000011}; /* C.LW */
            3'b110:  expansion_C0 = {lw_sw_imm[11:5], lsu_rs2, lsu_rs1, 3'b010, lw_sw_imm[4:0], 7'b0100011}; /* C.SW */
            3'b100:  expansion_C0 = expansion_zcb0; /* C.LBU C.LH(U) C.SB, C.SH */
            default: expansion_C0 = '0;
        endcase
    end

    /* op = C1 */

    logic [31:0] expansion_zcb1;

    always_comb begin
        unique case ({funct6, funct2}) inside
            8'b000?????: expansion_C1 = {{6{CI_imm[5]}}, CI_imm, CI_rd, 3'b000, CI_rd, 7'b0010011}; /* C.ADDI, C.NOP */
            8'b001?????: expansion_C1 = {CJ_imm, CJ_rd, 7'b1101111}; /* C.JAL */
            8'b101?????: expansion_C1 = {CJ_imm, CJ_rd, 7'b1101111}; /* C.J */
            8'b010?????: expansion_C1 = {{6{CI_imm[5]}}, CI_imm, 5'b00000, 3'b000, CI_rd, 7'b0010011}; /* C.LI */
            8'b011?????: begin
                expansion_C1 = (CI_rd == 5'd2)
                    ? {{3{CI_imm[5]}}, CI_imm[2:1], CI_imm[3], CI_imm[0], CI_imm[4], 4'b0000, CI_rd, 3'b000, CI_rd, 7'b0010011} /* C.ADDI16SP */
                    : {{14{CI_imm[5]}}, CI_imm, CI_rd, 7'b0110111}; /* C.LUI */
            end
            8'b110?????: expansion_C1 = {branch_imm[11:5], 5'b00000, branch_rs1, 3'b000, branch_imm[4:0], 7'b1100011}; /* C.BEQZ */
            8'b111?????: expansion_C1 = {branch_imm[11:5], 5'b00000, branch_rs1, 3'b001, branch_imm[4:0], 7'b1100011}; /* C.BNEZ */
            8'b100?00??: expansion_C1 = {7'b0000000, CB_imm[4:0], CB_rd, 3'b101, CB_rd, 7'b0010011}; /* C.SRLI */
            8'b100?01??: expansion_C1 = {7'b0100000, CB_imm[4:0], CB_rd, 3'b101, CB_rd, 7'b0010011}; /* C.SRAI */
            8'b100?10??: expansion_C1 = {{6{CB_imm[5]}}, CB_imm, CB_rd, 3'b111, CB_rd, 7'b0010011}; /* C.ANDI */
            8'b1001111?: expansion_C1 = expansion_zcb1; /* C.ZEXT.B, C.NOT, C.MUL */
            8'b10001111: expansion_C1 = {7'b0000000, CS_rs2, CS_rs1, 3'b111, CS_rs1, 7'b0110011}; /* C.AND */
            8'b10001110: expansion_C1 = {7'b0000000, CS_rs2, CS_rs1, 3'b110, CS_rs1, 7'b0110011}; /* C.OR */
            8'b10001101: expansion_C1 = {7'b0000000, CS_rs2, CS_rs1, 3'b100, CS_rs1, 7'b0110011}; /* C.XOR */
            8'b10001100: expansion_C1 = {7'b0100000, CS_rs2, CS_rs1, 3'b000, CS_rs1, 7'b0110011}; /* C.SUB */
            default:     expansion_C1 = '0;
        endcase
    end

    /* op = C2 */

    always_comb begin
        unique case (funct4) inside
            4'b010?: expansion_C2 = {4'b0000, CI_imm[1:0], CI_imm[5:2], 2'b00, 5'h02, 3'b010, CI_rd, 7'b0000011}; /* C.LWSP */
            4'b000?: expansion_C2 = {6'b000000, CI_imm, CI_rd, 3'b001, CI_rd, 7'b0010011}; /* C.SLLI */
            4'b110?: expansion_C2 = {4'b0000, CSS_imm[5:3], CSS_rs2, 5'h02, 3'b010, CSS_imm[2:0], 2'b00, 7'b0100011}; /* C.SWSP */
            4'b1000: expansion_C2 = (CR_rs2 == '0) 
                        ? {12'b0, CR_rs1, 3'b000, 5'b00000, 7'b1100111} /* C.JR */
                        : {7'b0000000, CR_rs2, 5'b00000, 3'b000, CR_rs1, 7'b0110011}; /* C.MV */
            4'b1001: begin
                if (CR_rs2 == '0) begin
                    if (CR_rs1 == '0) begin
                        expansion_C2 = {12'd1, 5'b00000, 3'b000, 5'b00000, 7'b1110011}; /* C.EBREAK */
                    end
                    else begin
                        expansion_C2 = {12'b0, CR_rs1, 3'b000, 5'b00001, 7'b1100111}; /* C.JALR */
                    end
                end
                else begin
                    expansion_C2 = {7'b0000000, CR_rs2, CR_rs1, 3'b000, CR_rs1, 7'b0110011}; /* C.ADD */ 
                end
            end
            default: expansion_C2 = '0;
        endcase
    end

    /* Zcb instructions */

    if (ZCBEnable) begin : gen_zcb_on
        always_comb begin
            unique case ({funct2, zcb_funct}) inside
                5'b10???: expansion_zcb1 = (MULEXT != MUL_OFF) ? {7'b0000001, CS_rs2, CS_rs1, 3'b000, CS_rs1, 7'b0110011} : '0; /* C.MUL */
                5'b11101: expansion_zcb1 = {4'b1111, 8'hff, CB_rd, 3'b100, CB_rd, 7'b0010011};  /* C.NOT */
                5'b11000: expansion_zcb1 = {4'b0000, 8'hff, CB_rd, 3'b111, CB_rd, 7'b0010011}; /* C.ZEXT.B */
                default:  expansion_zcb1 = '0;
            endcase
        end

        always_comb begin
            unique case (instruction_i[12:10]) inside
                3'b000:  expansion_zcb0 = {lsu_zcb_imm, lsu_rs1, 3'b100, lsu_rs2, 7'b0000011}; /* C.LBU */
                3'b001:  expansion_zcb0 = {lh_zcb_imm,  lsu_rs1, {~instruction_i[6], 2'b01}, lsu_rs2, 7'b0000011}; /* C.LHU, C.LH */
                3'b010:  expansion_zcb0 = {lsu_zcb_imm[11:5], lsu_rs2, lsu_rs1, 3'b000, lsu_zcb_imm[4:0], 7'b0100011}; /* C.SB */
                3'b011:  expansion_zcb0 = {lsu_zcb_imm[11:5], lsu_rs2, lsu_rs1, 3'b001, lsu_zcb_imm[4:0], 7'b0100011}; /* C.SH */
                default: expansion_zcb0 = '0;
            endcase
        end
    end
    else begin : gen_zcb_off
        assign expansion_zcb1 = '0;
        assign expansion_zcb0 = '0;
    end

endmodule
