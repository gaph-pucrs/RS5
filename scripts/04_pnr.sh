#!/bin/bash
# 04_pnr.sh -- Innovus 21.1 (stylus) place & route of the Genus netlist (tcl/pnr.tcl):
# floorplan at 0.68 row utilization (square core), end caps + well taps, VDD/VSS rings (M5/M6)
# and stripes, place_opt, tie cells, CCOpt CTS, post-CTS hold fix, timing/SI-driven route,
# two post-route setup/hold optimization passes, fillers, QRC extraction, signoff-style reports.
# Outputs used downstream (in $WORK/pnr/<ID>/outputs/):
#   RS5_postroute.v            gate-level netlist (no physical-only cells)
#   RS5_typ.sdf                cell + interconnect delays, typical corner / typical RC  -> step 05
#   RS5_typical.spef           extracted parasitics, typical RC                        -> step 06
#   RS5_postroute.sdc          constraints with the propagated clock                    -> step 06
# Closure criterion: setup WNS >= 0 at the worst-case corner (0.81 V/125 C/RC worst), hold WNS >= 0
# at the best-case (0.99 V/-40 C/RC best) and typical (0.90 V/25 C/RC typical) corners
# (checked from the reports, $WORK/results/pnr_summary.csv).
# Usage: 04_pnr.sh <ID|all> ...
source "$(dirname "$0")/common.sh"
load_tool "$MOD_INNOVUS" || die "Innovus not available"
need_pdk
RC=0
for ID in $(ids "$@"); do
    SYN=$WORK/synth/$ID
    grep -q status=OK "$SYN/runtime.txt" 2>/dev/null || die "$ID: synthesis missing, run 03_synth.sh $ID"
    O=$WORK/pnr/$ID
    rm -rf "$O"; start_run "$O"
    CMD=(innovus -stylus -no_gui -overwrite -log "$O/innovus"
         -execute "set OUT_DIR $O; set SYN_DIR $SYN; set NCPU $NCPU_PNR"
         -files "$REPRO/scripts/tcl/pnr.tcl")
    { echo "# genus_run=$SYN"; grep '^# rtl_root' "$SYN/cmd.txt"
      echo "# tcl=$REPRO/scripts/tcl/pnr.tcl md5=$(md5 "$REPRO/scripts/tcl/pnr.tcl")"
      echo "# netlist md5=$(md5 "$SYN/gate_level/RS5_logic_mapped.v")"
      printf '%q ' "${CMD[@]}"; echo; } >> "$O/cmd.txt"
    info "$ID: Innovus P&R"
    ( cd "$O" && timed "$O" "${CMD[@]}" )
    status "$O" "$(grep -q PAPER2_PNR_DONE "$O/stdout.log" && [ -s "$O/outputs/RS5_typ.sdf" ] && echo OK || echo FAIL)" || { RC=1; continue; }
done
# summary of every finished P&R run + timing-closure check
mkdir -p "$WORK/results"
DONE=$(for d in "$WORK"/pnr/*/; do grep -q status=OK "$d/runtime.txt" 2>/dev/null && echo "$d"; done)
if [ -n "$DONE" ]; then
    # shellcheck disable=SC2086
    python3 "$REPRO/scripts/py/summarize_pnr.py" "$WORK/results/pnr_summary.csv" $DONE
    python3 - "$WORK/results/pnr_summary.csv" <<'PY' || RC=1
import csv, sys
bad = []
for r in csv.DictReader(open(sys.argv[1])):
    for c in ('setup_wns_ss_ns', 'hold_wns_ff_ns', 'hold_wns_tt_ns'):
        if r[c] in ('', None) or float(r[c]) < 0: bad.append(f"{r['ID']} {c}={r[c]}")
print('timing closure:', 'OK' if not bad else 'VIOLATED ' + ', '.join(bad))
sys.exit(1 if bad else 0)
PY
fi
exit $RC
