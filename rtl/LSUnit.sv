// LOAD-STORE UNIT
//--------------------------------------------------------------------------------------------------

module LSUnit 
    import my_pkg::*;
(
    input   logic [31:0]        first_operand_i,                // Base csr_address
    input   logic [31:0]        second_operand_i,               // Offset
    input   logic [31:0]        data_i,                         // Data to be Written in memory
    input   operationType_e     operation_i,
    input   logic               enable_i,                       // enable memory operation based on instruction

    output  logic [31:0]        read_address_o,                 // Read Memory csr_address
    output  logic               read_o,                         // Signal that allows memory read
    output  logic [31:0]        write_address_o,                // Adrress to Write in memory
    output  logic [31:0]        write_data_o,                   // Data to be Written in Register Bank or in memory
    output  logic [3:0]         write_enable_o,                 // Signal that indicates the size of Write in memory(byte(1),half(2),word(4))
    output  logic               write_enable_regBank            // Write enable signal to register bank, in Stores=0 and in Loads=1
);

    logic [31:0] sum;

//--------------------------------------------------------------------------------------------------
// Generate all signals for read or write
//--------------------------------------------------------------------------------------------------

    always_comb begin
        if (enable_i == 1) begin
            if (operation_i == OP0 || operation_i == OP1) begin // LB | LBU
                read_o          = 1;
                write_data_o    = '0;
                write_enable_o  = 4'b0000;
            end 
            else if (operation_i == OP2 || operation_i == OP3) begin // LH | LHU
                read_o          = 1;
                write_data_o    = '0;
                write_enable_o  = 4'b0000;
            end 
            else if (operation_i == OP4) begin // LW
                read_o          = 1;
                write_data_o    = '0;
                write_enable_o  = 4'b0000;
            end 
            else if (operation_i == OP5) begin // SB
                read_o              = 0;
                write_data_o[31:24] = data_i[7:0];
                write_data_o[23:16] = data_i[7:0];
                write_data_o[15:8]  = data_i[7:0];
                write_data_o[7:0]   = data_i[7:0];
                case (sum[1:0])
                    2'b11:   write_enable_o = 4'b1000;
                    2'b10:   write_enable_o = 4'b0100;
                    2'b01:   write_enable_o = 4'b0010;
                    default: write_enable_o = 4'b0001;
                endcase
            end 
            else if (operation_i == OP6) begin // SH
                read_o              = 0;
                write_data_o[31:16] = data_i[15:0];    
                write_data_o[15:0]  = data_i[15:0];
                write_enable_o      = (write_address_o[1] == 1) 
                                        ? 4'b1100 
                                        : 4'b0011;
            end 
            else if (operation_i == OP7) begin // SW
                read_o              = 0;
                write_data_o[31:0]  = data_i[31:0];  
                write_enable_o      = 4'b1111;
            end 
            else begin
                read_o              = 0;
                write_data_o[31:0]  = '0;  
                write_enable_o      = '0;
            end
        end 
        else begin
            read_o              = 0;
            write_data_o[31:0]  = '0;  
            write_enable_o      = '0;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Write enable to register bank
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (operation_i == OP5 || operation_i == OP6 || operation_i == OP7) begin
            write_enable_regBank = '0;
        end
        else begin
            write_enable_regBank = '1;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Outputs assignment
//////////////////////////////////////////////////////////////////////////////

    assign sum = first_operand_i + second_operand_i;

    assign write_address_o = sum;
    assign read_address_o  = sum;

endmodule


