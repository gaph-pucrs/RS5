#!/bin/bash
# 06_power.sh -- average power of every window from its real switching activity (Genus 21.1 power
# engine, tcl/power.tcl), on the post-route design:
#   netlist  $WORK/pnr/<ID>/outputs/RS5_postroute.v   (+ RS5_postroute.sdc: propagated clock)
#   wires    RS5_typical.spef (read_spef, rc corner typical)
#   library  typical corner (0.90 V, 25 C), LIB_TT in scripts/config/pdk.env
#   activity $WORK/gl/<ID>_<set>/<window>.saif from the SDF-annotated run (step 05), read with
#            read_stimulus -dut_instance testbench.dut; it carries toggle counts and state times of
#            every net, glitches included, so no default toggle rate is used.
# Acceptance: every net driver annotated from the SAIF ("Driver nets ... 100.00%").
# A vectorless report (default toggle probability 0.5) is written for reference only.
# Usage: 06_power.sh <ID|all> <ops|kernels|cm|ops_k<k>|kernels_k<k>|all>
# Output: $WORK/power/<ID>_<set>/power_<window>.rpt, power_<window>_hier.rpt
source "$(dirname "$0")/common.sh"
[ $# -eq 2 ] || die "usage: $(basename "$0") <ID|all> <ops|kernels|cm|all>"
load_tool "$MOD_GENUS" || die "Genus not available"
need_pdk
if [ "$2" = all ]; then SETS="ops kernels cm"; else SETS=$2; fi
RC=0
for ID in $(ids "$1"); do
  for SET in $SETS; do
    G=$WORK/gl/${ID}_${SET}
    grep -q status=OK "$G/runtime.txt" 2>/dev/null || die "$ID/$SET: gate-level run missing or failed ($G)"
    O=$WORK/power/${ID}_${SET}
    rm -rf "$O"; start_run "$O"
    STIM=""; n=0
    for s in "$G"/*.saif; do STIM="$STIM {$(basename "$s" .saif) $s}"; n=$((n + 1)); done
    CMD=(genus -no_gui -overwrite -log "$O/genus"
         -execute "set PNR $WORK/pnr/$ID; set OUT_DIR $O; set STIM {$STIM}"
         -files "$REPRO/scripts/tcl/power.tcl")
    { echo "# tcl=$REPRO/scripts/tcl/power.tcl md5=$(md5 "$REPRO/scripts/tcl/power.tcl")"; printf '%q ' "${CMD[@]}"; echo; } >> "$O/cmd.txt"
    info "$ID/$SET: Genus power, $n windows"
    ( cd "$O" && timed "$O" "${CMD[@]}" )
    nrpt=$(ls "$O"/power_*_hier.rpt 2>/dev/null | wc -l)
    nfull=$(grep -cE '^ +Driver nets .* 100\.00%' "$O/stdout.log")
    status "$O" "$(grep -q POWER_GENUS_POSTROUTE_DONE "$O/stdout.log" && [ "$nrpt" = "$n" ] && [ "$nfull" = "$n" ] \
        && echo OK || echo FAIL)" "$nrpt/$n windows, $nfull/$n SAIF 100% annotated" || RC=1
  done
done
exit $RC
