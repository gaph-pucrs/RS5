add wave -noupdate -group TESTBENCH     -color {Turquoise}      /tb/*
add wave -noupdate -group RAM_MEM       -color {Violet}         /tb/RAM_MEM/*
add wave -noupdate -group DUT           -color {Blue Violet}    /tb/dut/*
add wave -noupdate -group FETCH         -color {Salmon}         /tb/dut/fetch1/*
add wave -noupdate -group DECODER       -color {Yellow}         /tb/dut/decoder1/*
add wave -noupdate -group EXECUTE       -color {Sienna}         /tb/dut/execute1/*
add wave -noupdate -group RETIRE        -color {Magenta}        /tb/dut/retire1/*
add wave -noupdate -group REGBANK       -color {Cyan}           /tb/dut/RegFileFF_blk/regbankff/*
add wave -noupdate -group CSRBANK       -color {Aquamarine}     /tb/dut/CSRBank1/*
add wave -noupdate -group VECTOR        -color {Blue Violet}    /tb/dut/execute1/vector/*
add wave -noupdate -group VECTOR_RB     -color {Cyan}           /tb/dut/execute1/vector/vectorRegbank1/*
add wave -noupdate -group VECTOR_CSR    -color {Magenta}        /tb/dut/execute1/vector/vectorCSRs1/*
add wave -noupdate -group VECTOR_ALU    -color {Sienna}         /tb/dut/execute1/vector/vectorALU1/*
add wave -noupdate -group VECTOR_LSU    -color {Turquoise}      /tb/dut/execute1/vector/vectorLSU1/*
