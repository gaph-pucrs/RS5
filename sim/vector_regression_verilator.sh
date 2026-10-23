#!/bin/bash

# Vector regression with Verilator (runs from the sim/ folder wherever it is called from).
# Verilates the testbench once for the given VLEN, then builds and runs every
# test in operations/, mem_operations/ and custom/, loading each program at run
# time with +BIN=.
#
# Usage: ./vector_regression_verilator.sh [VLEN] [test.c ...]
#   VLEN defaults to 512, which the Ara-derived tests need (16 elements of 32 bits).
#   With test names, only those tests run (searched in the three folders).
# Logs go to app/baremetal/tests/vector-tests/results_verilator/<VLEN>/{passed,failed}.

cd "$(dirname "$0")" || exit 2

VLEN=${1:-512}
shift

tests_root="../app/baremetal/tests/vector-tests"
test_dir="${tests_root}/test"
results="${tests_root}/results_verilator/${VLEN}"
obj="obj_vreg_${VLEN}"

mkdir -p "${results}/passed" "${results}/failed" debug results
rm -f "${results}"/passed/* "${results}"/failed/*

echo "-- Verilating VLEN=${VLEN} into ${obj}"
verilator --cc --exe --binary -j 0 -Wall -Wno-WIDTHTRUNC -Wno-fatal \
    -GVEnable=1 -GVLEN="${VLEN}" --Mdir "${obj}" \
    testbench.sv -I../rtl -I../rtl/aes -I../rtl/vector -I../RingBuffer/rtl \
    --timescale 1ns/1ns > "${results}/verilator.log" 2>&1
if [ ! -x "${obj}/Vtestbench" ]; then
    echo "Verilator build failed, see ${results}/verilator.log"
    exit 2
fi

if [ $# -gt 0 ]; then
    tests=()
    for name in "$@"; do
        tests+=( $(ls "${tests_root}"/{operations,mem_operations,custom}/"${name}" 2>/dev/null) )
    done
else
    tests=( "${tests_root}"/operations/*.c "${tests_root}"/mem_operations/*.c "${tests_root}"/custom/*.c )
fi

passed=0
failed=0
for file in "${tests[@]}"; do
    filename=$(basename "${file}")
    name="${filename%.*}"
    log="${results}/${name}.txt"

    cp "${file}" "${test_dir}/${filename}"
    if ! make -s -C "${tests_root}" clean all > "${log}" 2>&1; then
        echo "BUILD FAILED ${filename}"
        mv "${log}" "${results}/failed/"
        rm -f "${test_dir}/${filename}"
        failed=$((failed + 1))
        continue
    fi

    timeout 600 "${obj}/Vtestbench" +BIN="${tests_root}/test.bin" >> "${log}" 2>&1

    if grep -q "PASSED: test/${filename}!" "${log}"; then
        mv "${log}" "${results}/passed/"
        passed=$((passed + 1))
    else
        echo "FAILED ${filename}"
        mv "${log}" "${results}/failed/"
        failed=$((failed + 1))
    fi
    rm -f "${test_dir}/${filename}"
done

echo "-- VLEN=${VLEN}: ${passed} passed, ${failed} failed"
[ "${failed}" -eq 0 ]
