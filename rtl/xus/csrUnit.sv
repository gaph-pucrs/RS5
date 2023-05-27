module csrUnit 
    import my_pkg::*;
(
    input   logic [31:0]        first_operand_i,
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic [31:0]        instruction_i,
    /* verilator lint_on UNUSEDSIGNAL */
    input   operationType_e     operation_i,
    input   privilegeLevel_e    privilege_i,

    output  logic               read_enable_o,
    output  logic               write_enable_o,
    output  csrOperation_e      operation_o,
    output  logic [11:0]        address_o,
    output  logic [31:0]        data_o,
    output  logic               exception_o
);

    logic csr_rd_en_int, csr_wr_en_int;
    logic [4:0] rd, rs1;

    assign rd  = instruction_i[11:7];
    assign rs1 = instruction_i[19:15];

    assign address_o = instruction_i[31:20];

    assign read_enable_o = csr_rd_en_int & !exception_o;
    assign write_enable_o = csr_wr_en_int & !exception_o;

    always_comb begin
        if (operation_i == OP0 || operation_i == OP3) begin // CSSRW | CSSRWI
            csr_wr_en_int = 1;
            if (rd == '0) begin
                csr_rd_en_int = 0;
            end
            else begin
                csr_rd_en_int = 1;
            end
        end 
        else if (operation_i == OP1 || operation_i == OP2 || operation_i == OP4 || operation_i == OP5) begin // CSRRS/C | CSRRS/CI
            csr_rd_en_int = 1;
            if (rs1 == '0) begin
                csr_wr_en_int = 0;
            end
            else begin
                csr_wr_en_int = 1;
            end
        end 
        else begin
            csr_rd_en_int = 0;
            csr_wr_en_int = 0;
        end
    end

    always_comb begin      
        if (operation_i == OP0 || operation_i == OP1 || operation_i == OP2) begin
            data_o = first_operand_i;
        end
        else begin
            data_o = {27'b0, rs1};
        end
    end

    always_comb begin
        if      (operation_i == OP0 || operation_i == OP3) begin
            operation_o = WRITE;
        end
        else if (operation_i == OP1 || operation_i == OP4) begin
            operation_o = SET;
        end
        else if (operation_i == OP2 || operation_i == OP5) begin
            operation_o = CLEAR;
        end
        else begin
            operation_o = NONE;
        end
    end
    
    always_comb begin
        // Raise exeption if CSR is read only and write enable is true
        if (address_o[11:10] == 2'b11 && csr_wr_en_int) begin
            exception_o = 1;
        end
        // Check Level privileges
        else if (address_o[9:8] > privilege_i && (csr_rd_en_int || csr_wr_en_int)) begin
            exception_o = 1;
        end
        // No exception is raised
        else begin
            exception_o = 0;
        end
    end

endmodule
