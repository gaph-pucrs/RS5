# Nexys A7 synthesis entry point.
# sim/rtl.f remains the common RS5 RTL source list.

-f ../../../rtl/rtl.f
-f fpga_common.f

../../../proto/RS5_FPGA_Platform.sv
