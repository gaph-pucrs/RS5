add wave -noupdate -group TESTBENCH     -color {Turquoise}      /*
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/gen_mult_fast/mult_state_q
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/gen_mult_fast/mult_state_d
                         
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/alu_operand_a_kyber
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/alu_operand_b_kyber
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/barrett_imd_d                                       
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/barrett_imd_we
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/barrett_imd_d
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/gen_mult_fast/mult_op_a
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/gen_mult_fast/mult_op_b
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/mac_res_d

add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/gen_mult_fast/adjust_result_high
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/gen_mult_fast/adjust_result_low
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/gen_mult_fast/adjust_result_low_mux_sel
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/gen_mult_fast/adjust_adder_low_op_a
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/gen_mult_fast/adjust_result_low_mask

add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/gen_mult_fast/adjust_adder_op_b_inv
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/gen_mult_fast/adjust_adder_high
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/gen_mult_fast/adjust_adder_high_op_a
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/gen_mult_fast/adjust_adder_high_op_b
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/gen_mult_fast/adjust_adder_high_carry_in
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/gen_mult_fast/adjust_result_high_mux_sel
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/gen_mult_fast/adjust_adder_low_op_b
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/gen_mult_fast/adjust_adder_low
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/gen_mult_fast/adjust_adder_low_carry_in

add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/mac_res
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/*
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/imd_val_q
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/imd_val_d
add wave -noupdate -group CRYPTO        -color {Orange}         sim:/testbench/dut/execute1/gen_zmmul_on/gen_mul_fast_ibex/multdiv_i/imd_val_we
add wave -noupdate -group RAM_MEM       -color {Violet}         /RAM_MEM/*
add wave -noupdate -group DUT           -color {Blue Violet}    /dut/*
add wave -noupdate -group FETCH         -color {Salmon}         /dut/fetch1/*
add wave -noupdate -group DECODER       -color {Yellow}         /dut/decoder1/*
add wave -noupdate -group EXECUTE       -color {Sienna}         /dut/execute1/*
add wave -noupdate -group RETIRE        -color {Magenta}        /dut/retire1/*
add wave -noupdate -group REGBANK       -color {Cyan}           /dut/RegFileFF_blk/regbankff/*
add wave -noupdate -group CSRBANK       -color {Aquamarine}     /dut/CSRBank1/*
add wave -noupdate -group VECTOR        -color {Blue Violet}    /dut/execute1/v_gen_on/vector/*
add wave -noupdate -group VECTOR_RB     -color {Cyan}           /dut/execute1/v_gen_on/vector/vectorRegbank1/*
add wave -noupdate -group VECTOR_CSR    -color {Magenta}        /dut/execute1/v_gen_on/vector/vectorCSRs1/*
add wave -noupdate -group VECTOR_ALU    -color {Sienna}         /dut/execute1/v_gen_on/vector/vectorALU1/*
add wave -noupdate -group VECTOR_LSU    -color {Turquoise}      /dut/execute1/v_gen_on/vector/vectorLSU1/*