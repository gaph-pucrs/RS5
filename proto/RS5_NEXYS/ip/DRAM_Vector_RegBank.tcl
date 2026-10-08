# DRAM_Vector_RegBank
#
# Distributed Memory Generator
# Simple dual-port RAM
# Depth: 32
# Data width: 8
#
# The remaining port/register options intentionally use the Distributed
# Memory Generator defaults:
# - non-registered inputs
# - non-registered dual-port address
# - non-registered outputs
# - no input/output clock enable
# - 0 pipeline stages

set ip_name DRAM_Vector_RegBank

if {[llength [get_ips -quiet $ip_name]] > 0} {
    error "IP '$ip_name' already exists in the current project."
}

create_ip \
    -name dist_mem_gen \
    -vendor xilinx.com \
    -library ip \
    -version 8.0 \
    -module_name $ip_name

set_property -dict [list \
    CONFIG.depth {32} \
    CONFIG.data_width {8} \
    CONFIG.memory_type {simple_dual_port_ram} \
] [get_ips $ip_name]
