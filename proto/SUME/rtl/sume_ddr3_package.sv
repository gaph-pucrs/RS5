package SUME_ddr3_pkg;
parameter int MIG_DATA_WIDTH = 512;
parameter int WDF_MASK_WIDTH = MIG_DATA_WIDTH/8;
parameter int DDR3_ADDR_WIDTH = 30;
parameter int COMMAND_WIDTH = 16;
parameter int STATUS_WIDTH = 16;

parameter int BUF_SIZE = MIG_DATA_WIDTH/32;
parameter int BYTES_AMOUNT = BUF_SIZE * 4;
parameter int START_BIT = 0; // 1 bit
parameter int CMD_BITS = 1; // 3 bits

parameter int CALIBRATE = 0;
// parameter int WRITE_PENDING = 1;
// parameter int READ_REQ_PENDING = 2;
// parameter int READ_RESPONSE_PENDING = 3;
parameter int READ_DONE = 1;

parameter logic [2:0] CMD_READ  = 3'b001;
parameter logic [2:0] CMD_WRITE = 3'b000;

parameter logic [31:0] DDR3_ADDR_BASE = 32'h9000_0000;

parameter logic [7:0] DDR3_ADDR             = (8'h04); // w 
parameter logic [7:0] COMMAND_ADDR          = (8'h08); // w
parameter logic [7:0] STATUS_ADDR           = (8'h0C); // r  
parameter logic [7:0] W_PERF_COUNT_ADDR     = (8'h10); // r 
parameter logic [7:0] R_ACK_PERF_COUNT_ADDR = (8'h14); // r 
parameter logic [7:0] R_DLV_PERF_COUNT_ADDR = (8'h18); // r 

//always starting at the max size, in h80
parameter logic [7:0] WRITE_BUFFER_ADDR_LOW = (8'h80); //(BUF_SIZE*2*4); // 128 //h80
parameter logic [7:0] WRITE_BUFFER_ADDR_TOP = ((WRITE_BUFFER_ADDR_LOW + BUF_SIZE * 4) -1); // 191 //hBF
parameter logic [7:0] READ_BUFFER_ADDR_LOW  = (WRITE_BUFFER_ADDR_TOP + 1); //192 //hC0
parameter logic [7:0] READ_BUFFER_ADDR_TOP  = ((READ_BUFFER_ADDR_LOW + (BUF_SIZE * 4)) -1);// 255 //hFF

endpackage
