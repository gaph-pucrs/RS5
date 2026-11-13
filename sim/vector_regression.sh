#!/bin/bash

# Vector regression tests. Run from the sim/ folder.
#
# Every test is compiled once and simulated on each VLEN x LLEN configuration:
#   VLENS="128 256 512" and LLENS="32 64" by default; override them from the
#   environment, e.g. VLENS=512 LLENS=32 ./vector_regression.sh
# The configurations of one test run in parallel, each with its own Xcelium
# library (xcelium_vlen<V>_llen<L>.d). Results are saved per configuration in
#   app/baremetal/tests/vector-tests/results/vlen<V>_llen<L>/{passed,failed}/<test>.txt
# A simulation that runs longer than SIM_TIMEOUT seconds (300 by default) is
# killed and counted as failed, so a hung test does not stop the regression.
#
# Requirements (see "Vector regression tests" in README.md):
#   - VEnable and the program are set on the xrun command line, so testbench.sv
#     needs no editing
#   - Compile with GCC 13, or add -fno-tree-vectorize to GCC_RISCV in
#     app/baremetal/tests/vector-tests/Makefile. Newer GCC auto-vectorizes the tests and breaks them.

VLENS=${VLENS:-"128 256 512"}
LLENS=${LLENS:-"32 64"}
SIM_TIMEOUT=${SIM_TIMEOUT:-300}

tests_folder="../app/baremetal/tests/vector-tests"
source_folders=("$tests_folder/operations" "$tests_folder/mem_operations")
destination_folder="$tests_folder/test"
results_folder="$tests_folder/results"
bin_file="$tests_folder/test.bin"

# Tests in class_disabled/ run with every vector class parameter set to 0
class_off="-defparam testbench.VLogicEnable=0 -defparam testbench.VMinMaxEnable=0 -defparam testbench.VMergeEnable=0"
class_off="$class_off -defparam testbench.VDivEnable=0 -defparam testbench.VRedLogicEnable=0"
class_off="$class_off -defparam testbench.VRedMinMaxEnable=0 -defparam testbench.VRedSumEnable=0"

configs=()
for vlen in $VLENS; do
    for llen in $LLENS; do
        configs+=("vlen${vlen}_llen${llen}")
        rm -rf "$results_folder/vlen${vlen}_llen${llen}"
        mkdir -p "$results_folder/vlen${vlen}_llen${llen}/passed" "$results_folder/vlen${vlen}_llen${llen}/failed"
    done
done

# run_config <config> <test file name> <extra xrun arguments>
run_config() {
    local config=$1 filename=$2 extra=$3
    local vlen=${config#vlen}; vlen=${vlen%_llen*}
    local llen=${config#*_llen}
    local output_file="$results_folder/$config/${filename%.*}.txt"

    timeout "$SIM_TIMEOUT" xrun -f sim.xrun -xmlibdirname "xcelium_${config}.d" -l "xrun.${config}.log" \
        -defparam testbench.VEnable=1 -defparam testbench.VLEN=$vlen -defparam testbench.LLEN=$llen $extra \
        -gpg "testbench.BIN_FILE => \"$bin_file\"" > "$output_file" 2>&1

    if grep -q "PASSED: test/${filename}!" "$output_file"; then
        mv "$output_file" "$results_folder/$config/passed/"
    else
        mv "$output_file" "$results_folder/$config/failed/"
    fi
}

# run_test <test file> <extra xrun arguments>
run_test() {
    local file=$1 extra=$2
    local filename
    filename=$(basename "$file")

    cp "$file" "$destination_folder/$filename"
    make -C "$tests_folder" clean all > /dev/null

    for config in "${configs[@]}"; do
        run_config "$config" "$filename" "$extra" &
    done
    wait

    rm "$destination_folder/$filename"
    echo "$filename done"
}

for file in $(for folder in "${source_folders[@]}"; do ls "$folder"/*.c; done); do
    run_test "$file" ""
done

for file in "$tests_folder"/class_disabled/*.c; do
    run_test "$file" "$class_off"
done

echo
for config in "${configs[@]}"; do
    echo "$config  Passed: $(ls "$results_folder/$config/passed" | wc -l)  Failed: $(ls "$results_folder/$config/failed" | wc -l)"
done
for config in "${configs[@]}"; do
    failed=$(ls "$results_folder/$config/failed")
    [ -n "$failed" ] && echo "$config failed:" $failed
done
exit 0
