add wave -noupdate -group TESTBENCH     -color {Turquoise}      /*
add wave -noupdate -group RAM_MEM       -color {Violet}         /RAM_MEM/*
add wave -noupdate -group DUT           -color {Blue Violet}    /dut/*
add wave -noupdate -group FETCH         -color {Salmon}         /dut/fetch1/*
add wave -noupdate -group DECODER       -color {Yellow}         /dut/decoder1/*
add wave -noupdate -group EXECUTE       -color {Sienna}         /dut/execute1/*
add wave -noupdate -group RETIRE        -color {Magenta}        /dut/retire1/*
add wave -noupdate -group REGBANK       -color {Cyan}           /dut/RegFileFF_blk/regbankff/*
add wave -noupdate -group CSRBANK       -color {Aquamarine}     /dut/CSRBank1/*
add wave -noupdate -group VECTOR        -color {Blue Violet}    /dut/execute1/vector/*
add wave -noupdate -group VECTOR_RB     -color {Cyan}           /dut/execute1/vector/vectorRegbank1/*
add wave -noupdate -group VECTOR_CSR    -color {Magenta}        /dut/execute1/vector/vectorCSRs1/*
add wave -noupdate -group VECTOR_ALU    -color {Sienna}         /dut/execute1/vector/vectorALU1/*
add wave -noupdate -group VECTOR_LSU    -color {Turquoise}      /dut/execute1/vector/vectorLSU1/*
