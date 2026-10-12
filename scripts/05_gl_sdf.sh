#!/bin/bash
# 05_gl_sdf.sh -- delay-annotated gate-level simulation (Xcelium 23.03) of the post-route netlist,
# one SAIF (switching activity) file per window.
#   * netlist: $WORK/pnr/<ID>/outputs/RS5_postroute.v + cell Verilog models (CELLS_VERILOG, pdk.env)
#   * delays:  RS5_typ.sdf (cell + interconnect, typical corner, typical RC), compiled with
#              xmsdfc and annotated on testbench.dut (COMPILED_SDF_FILE, MTM TYPICAL). Timing checks
#              are off (-notimingchecks; timing is closed by STA in step 04). Pulses shorter than a
#              cell delay are filtered by the simulator's default inertial delay model, so the SAIF
#              counts the glitches a real gate would propagate.
#   * testbench: tb/tb_gl_sdf.sv, clock period PERIOD_NS (V_HALF_PERIOD = PERIOD_NS/2), every DUT
#              input delayed by IN_DLY_NS (transport): the memory model answers at the clock edge
#              with zero delay, while the DUT flops see the clock after the CTS insertion delay
#              (~0.08-0.13 ns at tt); without the delay those inputs would race the flops.
#   * windows: $WORK/windows/<ID>_<set>.csv (step 02); py/gl_runscript.py converts cycles to time
#              and brackets each window with dumpsaif ... / dumpsaif -end.
# Sets: ops (KeyGen/Encaps/Decaps, KAT program), kernels (sampled Decaps calls, KAT program),
#       cm (CoreMark iterate()).
# Acceptance: SDF 100 % annotated; KAT 6/6 PASS (or CoreMark validated); the simulation ends in
#       the same cycle as the RTL run (py/check_gl.py).
# Optional sets ops_k<k> / kernels_k<k> use KAT vector k instead of 0 (input-variability runs, not
# used in the paper; binary <sw>_k<k> from KAT_COUNTS=k 01_build_sw.sh, RTL run KAT_COUNT=k 02_rtl_sim.sh).
# Usage: 05_gl_sdf.sh <ID|all> <ops|kernels|cm|ops_k<k>|kernels_k<k>|all>
# Output: $WORK/gl/<ID>_<set>/{<window>.saif, xrun_stdout.log, sdf_annotate.log, cmd.txt, runtime.txt}
source "$(dirname "$0")/common.sh"
[ $# -eq 2 ] || die "usage: $(basename "$0") <ID|all> <ops|kernels|cm|all>"
load_tool "$MOD_XCELIUM" || die "Xcelium not available"
need_pdk
CELLS=$CELLS_VERILOG
TB=$REPRO/scripts/tb/tb_gl_sdf.sv
HALF=$(python3 -c "print($PERIOD_NS / 2)")
if [ "$2" = all ]; then SETS="ops kernels cm"; else SETS=$2; fi
RC=0
for ID in $(ids "$1"); do
  for SET in $SETS; do
    RTL=$(rtl_dir "$ID") || exit 1
    P=$WORK/pnr/$ID/outputs
    NET=$P/RS5_postroute.v; SDF=$P/RS5_typ.sdf
    WIN=$WORK/windows/${ID}_${SET}.csv
    SFX=""; [[ $SET == *_k* ]] && SFX="_k${SET##*_k}"
    if [ "$SET" = cm ]; then BIN=$WORK/sw/coremark/app.bin; REF=$WORK/rtl_sim/${ID}_coremark; KIND=coremark
    else BIN=$WORK/sw/$(cfg "$ID" sw)$SFX/app.bin; REF=$WORK/rtl_sim/${ID}_kat$SFX; KIND=kat; fi
    for f in "$NET" "$SDF" "$WIN" "$BIN" "$REF/stdout.log"; do [ -f "$f" ] || die "$ID/$SET: missing $f"; done
    O=$WORK/gl/${ID}_${SET}
    rm -rf "$O"; start_run "$O"
    TOP=$(python3 "$REPRO/scripts/py/find_top.py" "$NET")
    ln -sf "$BIN" "$O/test.bin"; cp "$WIN" "$O/windows.csv"
    python3 "$REPRO/scripts/py/gl_runscript.py" "$WIN" "$HALF" > "$O/run.tcl"
    printf 'COMPILED_SDF_FILE = "%s",\nSCOPE = testbench.dut,\nMTM_CONTROL = "TYPICAL",\nLOG_FILE = "sdf_annotate.log";\n' \
        "$O/RS5_typical.sdf.X" > "$O/sdf.cmd"
    CMD=(xrun -64bit -sv -timescale 1ns/1ps -sdf_cmd_file sdf.cmd -notimingchecks -access +r
         -define "V_IN_DLY=$IN_DLY_NS" -define "V_GL_TOP=$TOP" -define SYNTH -define "V_HALF_PERIOD=$HALF"
         -incdir "$REPRO/scripts/tb" -incdir "$RTL" -top testbench -input run.tcl
         -v "$CELLS" "$NET" "$RTL/RS5_pkg.sv" "$RTL/plic.sv" "$RTL/rtc.sv" "$REPRO/scripts/tb/RAM_mem.sv" "$TB")
    { echo "# netlist=$NET md5=$(md5 "$NET") top=$TOP"; echo "# sdf=$SDF md5=$(md5 "$SDF")"
      echo "# bin=$BIN md5=$(md5 "$BIN")"; echo "# windows=$WIN"; echo "# tb=$TB md5=$(md5 "$TB")"
      echo "# $(tree_info "$RTL")"; echo "xmsdfc $SDF -output $O/RS5_typical.sdf.X"
      printf '%q ' "${CMD[@]}"; echo; } >> "$O/cmd.txt"
    info "$ID/$SET: Xcelium SDF-annotated, $(($(wc -l < "$WIN") - 1)) windows"
    ( cd "$O" && xmsdfc "$SDF" -output "$O/RS5_typical.sdf.X" > xmsdfc_stdout.log 2>&1 ) \
        || die "$ID/$SET: xmsdfc failed ($O/xmsdfc.log)"
    ( cd "$O" && timed "$O" "${CMD[@]}" )
    mv "$O/stdout.log" "$O/xrun_stdout.log"
    sdf_ok=$(grep -q 'Annotation completed successfully' "$O/xrun_stdout.log" \
             && grep -q 'No. of Pathdelays.*Annotated = 100.00%' "$O/xrun_stdout.log" && echo 1 || echo 0)
    verdict=$(python3 "$REPRO/scripts/py/check_gl.py" "$O" "$REF" "$KIND")
    status "$O" "$([ "$sdf_ok" = 1 ] && [ "${verdict%% *}" = OK ] && echo OK || echo FAIL)" \
        "SDF annotated=$([ "$sdf_ok" = 1 ] && echo 100% || echo NO); ${verdict#* }" || RC=1
  done
done
exit $RC
