`include "RS5_pkg.sv"
    
module decompresser 
    import RS5_pkg::*;
(
    input  logic [15:0] instruction_i,
    output logic [31:0] instruction_o
);

    logic [1:0]  op;
    logic [3:0]  funct4;
    logic [2:0]  funct3;
    logic [1:0]  funct2;
    logic [1:0]  funct;

    logic [11:0] CIW_imm;
    logic [4:0]  CIW_rd;

    logic [11:0] lw_sw_imm;
    logic [4:0]  lw_sw_rs1;
    logic [4:0]  lw_sw_rs2;

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

    assign op     = instruction_i[1:0];
    assign funct4 = instruction_i[15:12];
    assign funct3 = instruction_i[15:13];
    assign funct2 = instruction_i[11:10];
    assign funct  = instruction_i[6:5];

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
    assign lw_sw_rs1 = {2'b01, instruction_i[9:7]};
    assign lw_sw_rs2 = {2'b01, instruction_i[4:2]};

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

    always_comb begin
        unique case (funct3)
            3'b000:  expansion_C0 = {CIW_imm, 5'h02, 3'b000, CIW_rd, 7'b0010011}; /* C.ADDI4SPN */
            3'b010:  expansion_C0 = {lw_sw_imm, lw_sw_rs1, 3'b010, lw_sw_rs2, 7'b0000011}; /* C.LW */
            3'b110:  expansion_C0 = {lw_sw_imm[11:5], lw_sw_rs2, lw_sw_rs1, 3'b010, lw_sw_imm[4:0], 7'b0100011}; /* C.SW */
            default: expansion_C0 = '0;
        endcase
    end

    /* op = C1 */

    always_comb begin
        unique case ({funct3, funct2, funct}) inside
            7'b000????: expansion_C1 = {{6{CI_imm[5]}}, CI_imm, CI_rd, 3'b000, CI_rd, 7'b0010011}; /* C.ADDI, C.NOP */
            7'b001????: expansion_C1 = {CJ_imm, CJ_rd, 7'b1101111}; /* C.JAL */
            7'b101????: expansion_C1 = {CJ_imm, CJ_rd, 7'b1101111}; /* C.J */
            7'b010????: expansion_C1 = {{6{CI_imm[5]}}, CI_imm, 5'b00000, 3'b000, CI_rd, 7'b0010011}; /* C.LI */
            7'b011????: begin
                expansion_C1 = (CI_rd == 5'd2)
                    ? {{3{CI_imm[5]}}, CI_imm[2:1], CI_imm[3], CI_imm[0], CI_imm[4], 4'b0000, CI_rd, 3'b000, CI_rd, 7'b0010011} /* C.ADDI16SP */
                    : {{14{CI_imm[5]}}, CI_imm, CI_rd, 7'b0110111}; /* C.LUI */
            end
            7'b110????: expansion_C1 = {branch_imm[11:5], 5'b00000, branch_rs1, 3'b000, branch_imm[4:0], 7'b1100011}; /* C.BEQZ */
            7'b111????: expansion_C1 = {branch_imm[11:5], 5'b00000, branch_rs1, 3'b001, branch_imm[4:0], 7'b1100011}; /* C.BNEZ */
            7'b10000??: expansion_C1 = {7'b0000000, CB_imm[4:0], CB_rd, 3'b101, CB_rd, 7'b0010011}; /* C.SRLI */
            7'b10001??: expansion_C1 = {7'b0100000, CB_imm[4:0], CB_rd, 3'b101, CB_rd, 7'b0010011}; /* C.SRAI */
            7'b10010??: expansion_C1 = {{6{CB_imm[5]}}, CB_imm, CB_rd, 3'b111, CB_rd, 7'b0010011}; /* C.ANDI */
            7'b1001111: expansion_C1 = {7'b0000000, CS_rs2, CS_rs1, 3'b111, CS_rs1, 7'b0110011}; /* C.AND */
            7'b1001110: expansion_C1 = {7'b0000000, CS_rs2, CS_rs1, 3'b110, CS_rs1, 7'b0110011}; /* C.OR */
            7'b1001101: expansion_C1 = {7'b0000000, CS_rs2, CS_rs1, 3'b100, CS_rs1, 7'b0110011}; /* C.XOR */
            7'b1001100: expansion_C1 = {7'b0100000, CS_rs2, CS_rs1, 3'b000, CS_rs1, 7'b0110011}; /* C.SUB */
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

endmodule
