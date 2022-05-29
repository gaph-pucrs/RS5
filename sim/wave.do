onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /PUCRS_RV_tb/dut/regB_add
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/clk
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/reset
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/rd_en
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/wr_en
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/csr_op
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/addr
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/data
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/out
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/RAISE_EXCEPTION
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/MACHINE_RETURN
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/Exception_Code
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/privilege
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/PC
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/instruction
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/mtvec
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/mepc
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/CSR
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/mstatus
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/misa
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/mie
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/mtvec_r
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/mcounteren
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/mstatush
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/mscratch
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/mepc_r
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/mcause
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/mtval
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/mip
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/mtinst
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/mtval2
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/wr_data
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/wmask
add wave -noupdate /PUCRS_RV_tb/dut/CSRBank1/current_val
add wave -noupdate -divider -height 50 {New Divider}
add wave -noupdate -label t0 {/PUCRS_RV_tb/dut/regbank1/regfile[5]}
add wave -noupdate -label t1 {/PUCRS_RV_tb/dut/regbank1/regfile[6]}
add wave -noupdate -label t2 {/PUCRS_RV_tb/dut/regbank1/regfile[7]}
add wave -noupdate -label a0 {/PUCRS_RV_tb/dut/regbank1/regfile[10]}
add wave -noupdate -label a1 {/PUCRS_RV_tb/dut/regbank1/regfile[11]}
add wave -noupdate -divider -height 50 {New Divider}
add wave -noupdate /PUCRS_RV_tb/dut/retire1/clk
add wave -noupdate /PUCRS_RV_tb/dut/retire1/reset
add wave -noupdate /PUCRS_RV_tb/dut/retire1/exception
add wave -noupdate /PUCRS_RV_tb/dut/retire1/instruction
add wave -noupdate /PUCRS_RV_tb/dut/retire1/NPC
add wave -noupdate /PUCRS_RV_tb/dut/retire1/result
add wave -noupdate /PUCRS_RV_tb/dut/retire1/jump
add wave -noupdate /PUCRS_RV_tb/dut/retire1/we
add wave -noupdate /PUCRS_RV_tb/dut/retire1/tag_in
add wave -noupdate /PUCRS_RV_tb/dut/retire1/we_mem_in
add wave -noupdate /PUCRS_RV_tb/dut/retire1/DATA_in
add wave -noupdate /PUCRS_RV_tb/dut/retire1/i
add wave -noupdate /PUCRS_RV_tb/dut/retire1/reg_we
add wave -noupdate /PUCRS_RV_tb/dut/retire1/WrData
add wave -noupdate /PUCRS_RV_tb/dut/retire1/jump_out
add wave -noupdate /PUCRS_RV_tb/dut/retire1/New_pc
add wave -noupdate /PUCRS_RV_tb/dut/retire1/write_address
add wave -noupdate /PUCRS_RV_tb/dut/retire1/DATA_out
add wave -noupdate /PUCRS_RV_tb/dut/retire1/write
add wave -noupdate /PUCRS_RV_tb/dut/retire1/Exception_Code
add wave -noupdate /PUCRS_RV_tb/dut/retire1/RAISE_EXCEPTION
add wave -noupdate /PUCRS_RV_tb/dut/retire1/MACHINE_RETURN
add wave -noupdate /PUCRS_RV_tb/dut/retire1/mem_data
add wave -noupdate /PUCRS_RV_tb/dut/retire1/curr_tag
add wave -noupdate /PUCRS_RV_tb/dut/retire1/killed
add wave -noupdate /PUCRS_RV_tb/dut/retire1/xu_sel
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {0 ps} 0}
quietly wave cursor active 0
configure wave -namecolwidth 150
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
configure wave -timelineunits ps
update
WaveRestoreZoom {0 ps} {1831 ps}
