#!/bin/bash
# run_all.sh -- whole flow for the given configurations.
#   01 software (once; PREBUILT=1 copies sw/prebuilt instead of compiling), then per ID:
#   02 RTL sim -> 03 synthesis -> 04 P&R -> 05 SDF gate-level sim (sets in parallel) -> 06 power;
#   finally 07 analysis + comparison with results/. The RTL of each ID is read from rtl_<tree>/.
# Usage:  scripts/run_all.sh [all | H0 H1 ...]          (default: all)
# Env:    SETS="ops kernels cm"   gate-level/power sets (ops is the longest: ~1 h per ID)
#         STEPS="01 02 03 04 05 06 07"  subset of steps to run (e.g. STEPS="01 02 07" without the PDK)
#         MAXPAR (scripts/config/repro.env)  IDs processed in parallel
# Logs:   $WORK/logs/<step>[_<ID>].log ; per-run provenance in each output dir (cmd.txt, runtime.txt)
S=$(cd "$(dirname "$0")" && pwd)
source "$S/common.sh"
IDS=$(ids "$@")
SETS=${SETS:-ops kernels cm}
STEPS=${STEPS:-01 02 03 04 05 06 07}
L=$WORK/logs; mkdir -p "$L"
has() { [[ " $STEPS " == *" $1 "* ]]; }

info "WORK=$WORK IDs: $IDS | sets: $SETS | steps: $STEPS"
if has 01; then
    "$S/01_build_sw.sh" 2>&1 | tee "$L/01_build_sw.log"; [ "${PIPESTATUS[0]}" = 0 ] || die "step 01 failed"
fi

one_id() {   # whole per-ID pipeline; stops at the first failing step
    local id=$1 set pids rc
    if has 02; then "$S/02_rtl_sim.sh" "$id" > "$L/02_rtl_sim_$id.log" 2>&1 || return 2; fi
    if has 03; then "$S/03_synth.sh"   "$id" > "$L/03_synth_$id.log"   2>&1 || return 3; fi
    if has 04; then "$S/04_pnr.sh"     "$id" > "$L/04_pnr_$id.log"     2>&1 || return 4; fi
    if has 05; then
        pids=""; rc=0
        for set in $SETS; do "$S/05_gl_sdf.sh" "$id" "$set" > "$L/05_gl_sdf_${id}_$set.log" 2>&1 & pids="$pids $!"; done
        for p in $pids; do wait "$p" || rc=5; done
        [ $rc = 0 ] || return 5
    fi
    if has 06; then
        for set in $SETS; do "$S/06_power.sh" "$id" "$set" > "$L/06_power_${id}_$set.log" 2>&1 || return 6; done
    fi
    return 0
}

FAILED=""
running=0
for id in $IDS; do
    ( one_id "$id"; rc=$?
      if [ $rc = 0 ]; then info "$id: done"; else info "$id: FAILED at step 0$rc (see $L/0${rc}_*_$id*.log)"; fi
      exit $rc ) &
    running=$((running + 1))
    if [ $running -ge "$MAXPAR" ]; then wait -n || FAILED="$FAILED x"; running=$((running - 1)); fi
done
while [ $running -gt 0 ]; do wait -n || FAILED="$FAILED x"; running=$((running - 1)); done

if has 07; then "$S/07_analyze.sh" 2>&1 | tee "$L/07_analyze.log"; fi
[ -z "$FAILED" ] || die "at least one configuration failed (see $L)"
info "all done; results in $WORK/results"
