#!/bin/bash
# 07_analyze.sh -- consolidate everything under $WORK/results and compare it with the paper's numbers in results/.
#   cycles.csv, cycle_classes.csv  RTL cycles (py/summarize_cycles.py)
#   pnr_summary.csv, implementation.csv  post-route area/timing/leakage (py/summarize_pnr.py)
#   power_windows.csv, power_hier.csv, check_equivalence.csv  (py/collect_power.py)
#       E_uJ = P_mW * cycles * PERIOD_NS * 1e-6
#   kernel_energy.csv  Decaps energy split Keccak / lattice / rest (py/kernel_energy.py)
# then py/compare_ref.py (exact for binaries/cycles/windows, 0.5 % for area/power/energy).
# Usage: 07_analyze.sh
source "$(dirname "$0")/common.sh"
mkdir -p "$WORK/results"
python3 "$REPRO/scripts/py/summarize_cycles.py" || die "summarize_cycles.py failed"
DONE=$(for d in "$WORK"/pnr/*/; do grep -q status=OK "$d/runtime.txt" 2>/dev/null && echo "$d"; done)
# shellcheck disable=SC2086
[ -n "$DONE" ] && { python3 "$REPRO/scripts/py/summarize_pnr.py" "$WORK/results/pnr_summary.csv" $DONE > /dev/null || die "summarize_pnr.py failed"; }
RC=0
if ls "$WORK"/power/*/power_*.rpt > /dev/null 2>&1; then
    python3 "$REPRO/scripts/py/collect_power.py" || RC=1
    python3 "$REPRO/scripts/py/kernel_energy.py" > /dev/null || RC=1
fi
echo; echo "== comparison with the paper's reference results (results/) =="
python3 "$REPRO/scripts/py/compare_ref.py" || RC=1
exit $RC
