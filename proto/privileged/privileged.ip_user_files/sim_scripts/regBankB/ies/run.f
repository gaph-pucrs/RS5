-makelib ies_lib/xpm -sv \
  "/soft64/xilinx/ferramentas/Vivado/2021.1/Vivado/2021.1/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
  "/soft64/xilinx/ferramentas/Vivado/2021.1/Vivado/2021.1/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \
-endlib
-makelib ies_lib/xpm \
  "/soft64/xilinx/ferramentas/Vivado/2021.1/Vivado/2021.1/data/ip/xpm/xpm_VCOMP.vhd" \
-endlib
-makelib ies_lib/dist_mem_gen_v8_0_13 \
  "../../../ipstatic/simulation/dist_mem_gen_v8_0.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../../privileged.gen/sources_1/ip/regBankB/sim/regBankB.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  glbl.v
-endlib

