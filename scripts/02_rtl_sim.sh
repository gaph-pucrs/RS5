#!/bin/bash
# 02_rtl_sim.sh -- RTL simulation (Verilator 5.052) of one configuration: functional check,
# cycle profile and the cycle windows that the gate-level step will turn into SAIF files.
#   1. ML-KEM-512 KAT program: KeyGen/Encaps/Decaps on the count-0 FIPS 203 vector; pass = 6 x [PASS].
#      tb/trace_bind.sv writes the execute-stage trace (<cycle> <pc> <instr> <exec cycles>).
#   2. py/profile.py on the trace: cycles of KeyGen/Encaps/Decaps (entry -> return of the
#      pqcrystals_kyber512_ref_{keypair,enc,dec} calls) and per kernel class.
#   3. windows (cycle numbers of the RTL trace = rising clock edges after reset release):
#        $WORK/windows/<ID>_ops.csv      KeyGen, Encaps, Decaps
#        $WORK/windows/<ID>_kernels.csv  8 sampled calls inside Decaps (py/kernel_windows.py)
#        $WORK/windows/<ID>_cm.csv       CoreMark iterate() (CoreMark run on the same RTL)
#   4. optional (MULTEST=1): RV32M mul/mulh/mulhsu/mulhu conformance test, pass = 0 errors.
# With KAT_COUNT=k (k > 0) only the KAT program of vector k runs (build <sw>_k<k> from
# KAT_COUNTS=... 01_build_sw.sh); outputs get the suffix _k<k> (rtl_sim/<ID>_kat_k<k>,
# windows/<ID>_{ops,kernels}_k<k>.csv). Optional input-variability runs, not used in the paper.
# Usage: [KAT_COUNT=k] 02_rtl_sim.sh <ID|all> ...
# Output: $WORK/rtl_sim/<ID>_{kat,coremark[,multest]}/, $WORK/windows/<ID>_*.csv
source "$(dirname "$0")/common.sh"
load_tool "$MOD_VERILATOR" || die "Verilator not available"
TB="$REPRO/scripts/tb/tb_rtl.sv $REPRO/scripts/tb/trace_bind.sv"
KERNELS="polyvec_ntt polyvec_pointwise_acc_montgomery sha3_f1600_rvb32:first sha3_f1600_rvb32:mid
         sha3_f1600_rvb32:last cbd_eta1 polyvec_invntt_tomont polyvec_compress"

# verilate <rtl dir> <defines>: build (once) and print the simulator path. Builds are serialized
# with a lock: concurrent Verilator builds of the same model corrupt the shared object directory.
verilate() {
    local rtl=$1 defs=$2 key obj
    key=$(echo "$rtl $defs $(rtl_md5 "$rtl") $(md5sum $TB | cut -c1-32 | tr '\n' ' ')" | md5sum | cut -c1-12)
    obj=$WORK/verilator/$key
    mkdir -p "$WORK/verilator"
    (
        flock 9
        if [ ! -x "$obj/Vtestbench" ]; then
            local files
            files="$rtl/RS5_pkg.sv $(ls "$rtl"/*.sv | grep -v RS5_pkg.sv | tr '\n' ' ') $rtl/aes/*.sv"
            files="$files $rtl/vector/*.sv $rtl/RingBuffer/RingBuffer.sv $REPRO/scripts/tb/RAM_mem.sv $TB"
            mkdir -p "$obj"
            local cmd="verilator --binary -j 8 -O3 --x-assign fast --x-initial fast -Wno-fatal -Wno-lint -Wno-style \
--timescale 1ns/1ns --top-module testbench -I$rtl -I$rtl/aes -I$rtl/vector -I$rtl/RingBuffer \
$defs -Mdir $obj $files"
            echo "$cmd" > "$obj/verilate_cmd.txt"
            eval "$cmd" > "$obj/verilate.log" 2>&1 || { echo "Verilator build failed: $obj/verilate.log" >&2; exit 1; }
        fi
    ) 9> "$WORK/verilator/.lock" || return 1
    echo "$obj/Vtestbench"
}

# simulate <out> <sim> <bin> [trace]: run the program (the testbench loads ./test.bin)
simulate() {
    local out=$1 sim=$2 bin=$3 trace=${4:-/dev/null}
    rm -rf "$out"; start_run "$out"
    mkdir -p "$out/results" "$out/debug" "$out/result_kyber"
    ln -sf "$bin" "$out/test.bin"
    { echo "# $(tree_info "$RTL")"; echo "# bin=$bin md5=$(md5 "$bin")"
      echo "# simulator=$sim ($(cat "$(dirname "$sim")/verilate_cmd.txt"))"; echo "$sim +TRACE=$trace"; } >> "$out/cmd.txt"
    ( cd "$out" && timed "$out" timeout 3600 "$sim" "+TRACE=$trace" )
}

K=${KAT_COUNT:-0}; SFX=""; [ "$K" != 0 ] && SFX="_k$K"
RC=0
for ID in $(ids "$@"); do
    RTL=$(rtl_dir "$ID") || exit 1
    DEFS="$(cfg "$ID" verilator) $LEAN_VERILATOR"
    SW=$WORK/sw/$(cfg "$ID" sw)$SFX
    [ -f "$SW/app.bin" ] || die "$SW/app.bin missing: run 01_build_sw.sh"
    SIM=$(verilate "$RTL" "$DEFS") || die "$ID: Verilator build failed"
    mkdir -p "$WORK/windows"

    # 1-3: KAT, profile, windows
    O=$WORK/rtl_sim/${ID}_kat$SFX
    simulate "$O" "$SIM" "$SW/app.bin" "$O/trace.txt"
    npass=$(grep -c '^\[PASS\]' "$O/stdout.log"); nfail=$(grep -c '^\[FAIL\]' "$O/stdout.log")
    status "$O" "$([ "$npass" = 6 ] && [ "$nfail" = 0 ] && echo OK || echo FAIL)" "KAT $npass/6 PASS" || { RC=1; continue; }
    python3 "$REPRO/scripts/py/profile.py" "$O/trace.txt" "$SW/app.nm" "$SW/app.lst" "$O/prof" > "$O/profile.log" \
        || die "$ID: profile.py failed"
    python3 - "$O/prof_windows.csv" "$WORK/windows/${ID}_ops$SFX.csv" <<'PY'
import csv, sys
rows = list(csv.DictReader(open(sys.argv[1])))
with open(sys.argv[2], 'w', newline='') as fo:
    w = csv.writer(fo, lineterminator='\n'); w.writerow(['op', 'start_cycle', 'end_cycle'])
    for r in rows: w.writerow([r['op'], r['start_cycle'], r['end_cycle']])
PY
    # shellcheck disable=SC2086
    python3 "$REPRO/scripts/py/kernel_windows.py" "$O/trace.txt" "$SW/app.nm" "$SW/app.lst" "$O/prof_windows.csv" Decaps \
        "$WORK/windows/${ID}_kernels$SFX.csv" $KERNELS > "$O/kernel_windows.log" 2>&1 || die "$ID: kernel_windows.py failed"
    info "$ID${SFX} cycles: $(tr '\n' ' ' < "$O/profile.log" | cut -c1-80)"
    [ "$K" != 0 ] && continue          # other KAT vectors: no CoreMark / multest

    # CoreMark: one iterate() call
    C=$WORK/rtl_sim/${ID}_coremark
    simulate "$C" "$SIM" "$WORK/sw/coremark/app.bin" "$C/trace.txt"
    status "$C" "$(grep -q 'Correct operation validated' "$C/stdout.log" && echo OK || echo FAIL)" "CoreMark" || { RC=1; continue; }
    t_end=$(grep -oE '^# [0-9]+ END OF SIMULATION' "$C/stdout.log" | awk '{print $2}')
    printf 'op,start_cycle,end_cycle\nALL,0,%d\n' $(( (t_end - 105) / 10 )) > "$C/all_window.csv"
    python3 "$REPRO/scripts/py/kernel_windows.py" "$C/trace.txt" "$WORK/sw/coremark/app.nm" "$WORK/sw/coremark/app.lst" \
        "$C/all_window.csv" ALL "$WORK/windows/${ID}_cm.csv" iterate > "$C/kernel_windows.log" 2>&1 \
        || die "$ID: CoreMark window failed"

    # optional RV32M conformance
    if [ "${MULTEST:-0}" = 1 ]; then
        M=$WORK/rtl_sim/${ID}_multest
        simulate "$M" "$SIM" "$WORK/sw/multest/app.bin"
        got=$(grep -E '^-?[0-9]+$' "$M/stdout.log" | tr '\n' ' ')
        status "$M" "$([ "$got" = "0 0 1 0 2 0 3 0 4294967295 " ] && echo OK || echo FAIL)" "multest: $got" || RC=1
    fi
done
exit $RC
