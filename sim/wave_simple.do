onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/clk
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/reset_n
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/instruction_address
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/data_rtc
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/interrupt_ack
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/mtime
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/instruction
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/enable_ram
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/enable_rtc
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/enable_plic
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/enable_tb
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/mem_operation_enable
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/mem_address
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/mem_data_read
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/mem_data_write
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/mem_write_enable
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/char
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/data_ram
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/data_plic
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/data_tb
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/enable_tb_r
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/enable_rtc_r
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/enable_plic_r
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/mti
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/mei
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/irq
add wave -noupdate -group TESTBENCH -color Turquoise /testbench/iack_periph
add wave -noupdate -group RAM_MEM -color Violet /testbench/RAM_MEM/clk
add wave -noupdate -group RAM_MEM -color Violet /testbench/RAM_MEM/enA_i
add wave -noupdate -group RAM_MEM -color Violet /testbench/RAM_MEM/weA_i
add wave -noupdate -group RAM_MEM -color Violet /testbench/RAM_MEM/addrA_i
add wave -noupdate -group RAM_MEM -color Violet /testbench/RAM_MEM/dataA_i
add wave -noupdate -group RAM_MEM -color Violet /testbench/RAM_MEM/dataA_o
add wave -noupdate -group RAM_MEM -color Violet /testbench/RAM_MEM/enB_i
add wave -noupdate -group RAM_MEM -color Violet /testbench/RAM_MEM/weB_i
add wave -noupdate -group RAM_MEM -color Violet /testbench/RAM_MEM/addrB_i
add wave -noupdate -group RAM_MEM -color Violet /testbench/RAM_MEM/dataB_i
add wave -noupdate -group RAM_MEM -color Violet /testbench/RAM_MEM/dataB_o
add wave -noupdate -group RAM_MEM -color Violet /testbench/RAM_MEM/fd
add wave -noupdate -group RAM_MEM -color Violet /testbench/RAM_MEM/fd_r_a
add wave -noupdate -group RAM_MEM -color Violet /testbench/RAM_MEM/fd_r_b
add wave -noupdate -group RAM_MEM -color Violet /testbench/RAM_MEM/fd_w_a
add wave -noupdate -group RAM_MEM -color Violet /testbench/RAM_MEM/fd_w_b
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/clk
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/reset_n
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/sys_reset_i
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/stall
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/instruction_i
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mem_data_i
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mtime_i
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/irq_i
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/instruction_address_o
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mem_operation_enable_o
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mem_write_enable_o
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mem_address_o
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mem_data_o
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/interrupt_ack_o
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/jump
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/hazard
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/hold
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mmu_inst_fault
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mmu_data_fault
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/privilege
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/jump_target
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mem_read_enable
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mem_write_enable
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mem_address
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/instruction_address
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/enable_fetch
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/pc_decode
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/enable_decode
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/jump_misaligned
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/rs1
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/rs2
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/regbank_data1
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/regbank_data2
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/rd_retire
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/regbank_data_writeback
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/regbank_write_enable
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/instruction_operation_execute
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/atomic_operation_execute
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/vector_operation_execute
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/rs1_data_execute
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/rs2_data_execute
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/second_operand_execute
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/instruction_execute
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/pc_execute
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/rd_execute
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/rs1_execute
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/exc_ilegal_inst_execute
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/exc_misaligned_fetch_execute
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/exc_inst_access_fault_execute
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/instruction_compressed_execute
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/vtype
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/vlen
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/instruction_operation_retire
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/result_retire
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/killed
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/csr_read_enable
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/csr_write_enable
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/csr_operation
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/csr_addr
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/csr_data_to_write
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/csr_data_read
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mepc
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mtvec
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/RAISE_EXCEPTION
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/MACHINE_RETURN
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/interrupt_pending
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/Exception_Code
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mvmdo
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mvmio
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mvmds
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mvmis
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mvmdm
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mvmim
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mvmctl
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/mmu_en
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/jump_rollback
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/jumping
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/ctx_switch
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/bp_take_fetch
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/bp_rollback
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/compressed_decode
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/bp_target
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/ctx_switch_target
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/instruction_decode
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/bp_taken_exec
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/write_enable_exec
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/result_exec
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/jump_imm_target_exec
add wave -noupdate -group DUT -color {Blue Violet} /testbench/dut/reservation_data
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/clk
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/reset_n
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/sys_reset
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/enable_i
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/ctx_switch_i
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/ctx_switch_target_i
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/jumping_o
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/bp_take_i
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/jump_rollback_i
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/bp_target_i
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/bp_rollback_o
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/jump_misaligned_o
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/compressed_o
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/instruction_address_o
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/instruction_data_i
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/instruction_o
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/pc_o
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/iaddr_continue
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/iaddr_next
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/jumped
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/jump_target
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/iaddr_advance
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/jumped_r
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/jumped_r2
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/pc_jumped
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/pc_jumped_r
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/pc_add
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/pc
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/pc_next
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/pc_update
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/enable_r
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/idata_held
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/instruction_fetched
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/instruction_next
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/jump_rollback_r
add wave -noupdate -group FETCH -color Salmon /testbench/dut/fetch1/iaddr_not_jumped
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/clk
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/reset_n
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/enable
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/instruction_i
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/pc_i
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/rs1_data_read_i
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/rs2_data_read_i
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/writeback_i
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/result_i
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/rd_retire_i
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/regbank_we_i
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/execute_we_i
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/rollback_i
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/compressed_i
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/rs1_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/rs2_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/rd_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/instr_rs1_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/csr_address_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/rs1_data_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/rs2_data_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/second_operand_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/pc_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/instruction_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/jump_imm_target_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/compressed_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/instruction_operation_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/atomic_operation_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/vector_operation_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/hazard_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/killed_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/jump_rollback_i
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/ctx_switch_i
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/jumping_i
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/jump_misaligned_i
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/bp_take_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/bp_taken_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/bp_target_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/exc_inst_access_fault_i
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/exc_inst_access_fault_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/exc_ilegal_inst_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/exc_misaligned_fetch_o
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/killed
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/instruction_operation
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/funct3
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/funct7
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/opcode
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/decode_branch
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/decode_load
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/decode_store
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/decode_op_imm
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/decode_op
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/decode_misc_mem
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/decode_system
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/amo_invalid
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/decode_atomic
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/vector_operation
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/instruction_format
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/imm_i
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/imm_s
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/imm_b
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/imm_u
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/imm_j
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/immediate
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/jump_confirmed
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/is_load
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/is_store
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/forwardingless
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/locked_memory
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/locked_register
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/rd
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/csr_address
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/exception
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/use_rs1
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/use_rs2
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/locked_rs1
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/locked_rs2
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/hazard_mem
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/hazard_rs1
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/hazard_rs2
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/invalid_inst
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/misaligned_fetch
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/exc_inst_access_fault
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/rs1_data
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/rs2_data
add wave -noupdate -group DECODER -color Yellow /testbench/dut/decoder1/second_operand
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/clk
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/reset_n
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/stall
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/instruction_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/rs1_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/instruction_compressed_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/atomic_operation_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/vector_operation_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/privilege_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/exc_ilegal_inst_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/exc_misaligned_fetch_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/exc_inst_access_fault_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/exc_load_access_fault_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/hold_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/write_enable_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/write_enable_fwd_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/instruction_operation_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/result_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/result_fwd_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/rd_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/mem_address_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/mem_read_enable_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/mem_write_enable_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/mem_write_data_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/mem_read_data_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/csr_address_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/csr_read_enable_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/csr_data_read_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/csr_write_enable_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/csr_operation_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/csr_data_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/vtype_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/vlen_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/bp_taken_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/jump_rollback_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/ctx_switch_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/ctx_switch_target_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/interrupt_pending_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/mtvec_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/mepc_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/jump_imm_target_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/reservation_data_i
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/jump_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/interrupt_ack_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/machine_return_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/raise_exception_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/jump_target_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/exception_code_o
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/write_enable
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/exc_ilegal_csr_inst
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/sum_result
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/sum2_result
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/and_result
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/or_result
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/xor_result
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/sll_result
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/srl_result
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/sra_result
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/equal
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/less_than
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/less_than_unsigned
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/greater_equal
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/greater_equal_unsigned
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/first_operand
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/sum2_opA
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/sum2_opB
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/amo_operand
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/mem_address_vector
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/mem_address
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/mem_read_enable
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/mem_read_enable_vector
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/mem_write_enable
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/mem_write_enable_vector
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/mem_write_data
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/mem_write_data_vector
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/atomic_mem_read_enable
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/atomic_mem_write_enable
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/csr_read_enable
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/csr_write_enable
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/mul_result
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/hold_mul
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/hold_div
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/div_result
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/rem_result
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/aes_result
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/vector_scalar_result
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/vector_wr_en
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/hold_vector
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/atomic_hold
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/atomic_write_enable
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/lrsc_result
add wave -noupdate -group EXECUTE -color Sienna /testbench/dut/execute1/should_jump
add wave -noupdate -group EXECUTE /testbench/dut/RegFileFF_blk/regbankff/regfile
add wave -noupdate -group RETIRE -color Magenta /testbench/dut/retire1/clk
add wave -noupdate -group RETIRE -color Magenta /testbench/dut/retire1/reset_n
add wave -noupdate -group RETIRE -color Magenta /testbench/dut/retire1/instruction_operation_i
add wave -noupdate -group RETIRE -color Magenta /testbench/dut/retire1/result_i
add wave -noupdate -group RETIRE -color Magenta /testbench/dut/retire1/mem_data_i
add wave -noupdate -group RETIRE -color Magenta /testbench/dut/retire1/reservation_data_o
add wave -noupdate -group RETIRE -color Magenta /testbench/dut/retire1/regbank_data_o
add wave -noupdate -group RETIRE -color Magenta /testbench/dut/retire1/memory_data
add wave -noupdate -group REGBANK -color Cyan /testbench/dut/RegFileFF_blk/regbankff/clk
add wave -noupdate -group REGBANK -color Cyan /testbench/dut/RegFileFF_blk/regbankff/reset_n
add wave -noupdate -group REGBANK -color Cyan /testbench/dut/RegFileFF_blk/regbankff/rs1
add wave -noupdate -group REGBANK -color Cyan /testbench/dut/RegFileFF_blk/regbankff/rs2
add wave -noupdate -group REGBANK -color Cyan /testbench/dut/RegFileFF_blk/regbankff/rd
add wave -noupdate -group REGBANK -color Cyan /testbench/dut/RegFileFF_blk/regbankff/enable
add wave -noupdate -group REGBANK -color Cyan /testbench/dut/RegFileFF_blk/regbankff/data_i
add wave -noupdate -group REGBANK -color Cyan /testbench/dut/RegFileFF_blk/regbankff/data1_o
add wave -noupdate -group REGBANK -color Cyan /testbench/dut/RegFileFF_blk/regbankff/data2_o
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/clk
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/reset_n
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/sys_reset
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/read_enable_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/write_enable_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/operation_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/address_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/data_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/out
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/instruction_compressed_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/instruction_operation_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/vector_operation_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/hazard
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/stall
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/hold
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/killed
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/vtype_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/vlen_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/raise_exception_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/machine_return_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/exception_code_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/pc_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/next_pc_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/instruction_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/jump_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/jump_target_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/jump_misaligned_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mtime_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/irq_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/interrupt_ack_i
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/interrupt_pending_o
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/privilege_o
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mepc
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mtvec
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mvmctl_o
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mvmdo_o
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mvmio_o
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mvmds_o
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mvmis_o
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mvmim_o
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mvmdm_o
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/CSR
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/privilege
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/misa
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mstatus
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mtvec_r
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mip
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mie
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mscratch
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mepc_r
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mcause
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mtval
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mcycle
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/minstret
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mvmdo
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mvmio
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mvmds
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mvmis
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mvmdm
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mvmim
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mvmctl
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/wr_data
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/wmask
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/current_val
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/instructions_killed_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/hazard_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/stall_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/nop_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/interrupt_ack_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/raise_exception_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/context_switch_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/logic_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/addsub_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/lui_slt_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/shift_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/branch_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/jump_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/load_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/store_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/sys_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/csr_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/compressed_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/jump_misaligned_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mcountinhibit
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/Interruption_Code
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mul_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/div_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/vaddsub_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/vmul_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/vdiv_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/vmac_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/vred_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/vloadstore_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/vothers_counter
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mcause_interrupt
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mcause_exc_code
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mstatus_mpie
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mstatus_mie
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/mstatus_mpp
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/MEIP
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/MTIP
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/MSIP
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/MEIE
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/MTIE
add wave -noupdate -group CSRBANK -color Aquamarine /testbench/dut/CSRBank1/MSIE
add wave -noupdate -color Sienna /testbench/dut/execute1/pc_i
add wave -noupdate -color Sienna /testbench/dut/execute1/instruction_operation_i
add wave -noupdate -color Sienna /testbench/dut/execute1/rs1_data_i
add wave -noupdate -color Sienna /testbench/dut/execute1/rs2_data_i
add wave -noupdate -color Sienna /testbench/dut/execute1/second_operand_i
add wave -noupdate -color Sienna /testbench/dut/execute1/rd_i
add wave -noupdate -color Sienna /testbench/dut/execute1/result
add wave -noupdate -childformat {{{/testbench/dut/RegFileFF_blk/regbankff/regfile[31]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[30]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[29]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[28]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[27]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[26]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[25]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[24]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[23]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[22]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[21]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[20]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[19]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[18]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[17]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[16]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[15]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[14]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[13]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[12]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[11]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[10]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[9]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[8]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[7]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[6]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[5]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[4]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[3]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[2]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[1]} -radix hexadecimal} {{/testbench/dut/RegFileFF_blk/regbankff/regfile[0]} -radix hexadecimal}} -expand -subitemconfig {{/testbench/dut/RegFileFF_blk/regbankff/regfile[31]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[30]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[29]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[28]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[27]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[26]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[25]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[24]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[23]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[22]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[21]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[20]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[19]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[18]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[17]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[16]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[15]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[14]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[13]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[12]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[11]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[10]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[9]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[8]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[7]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[6]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[5]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[4]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[3]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[2]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[1]} {-height 16 -radix hexadecimal} {/testbench/dut/RegFileFF_blk/regbankff/regfile[0]} {-height 16 -radix hexadecimal}} /testbench/dut/RegFileFF_blk/regbankff/regfile
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {315 ns} 0}
quietly wave cursor active 1
configure wave -namecolwidth 198
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 1
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {230 ns} {372 ns}
