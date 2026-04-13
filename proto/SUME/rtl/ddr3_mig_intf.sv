interface ddr3_mig_intf;

logic [29:0]  addr;
logic [2:0]   cmd;
logic         en;
logic [511:0] wdf_data;
logic         wdf_wren_end;
logic         wdf_wren;
logic [63:0]  wdf_mask;

logic [511:0] rd_data;
logic         rd_data_end;
logic         rd_data_valid;
logic         rdy;
logic         wdf_rdy;

modport MIG (
    output rd_data,
           rd_data_end,
           rd_data_valid,
           rdy,
           wdf_rdy,
    input addr,
          cmd,
          en,
          wdf_data,
          wdf_wren_end,
          wdf_wren,
          wdf_mask
);

modport CONTROLLER (
    input rd_data,
          rd_data_end,
          rd_data_valid,
          rdy,
          wdf_rdy,
    output addr,
           cmd,
           en,
           wdf_data,
           wdf_wren_end,
           wdf_wren,
           wdf_mask
);

endinterface
