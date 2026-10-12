#!/bin/bash
# 03_synth.sh -- Genus 21.1 physical synthesis (syn_generic/syn_map/syn_opt -physical) of one
# configuration at PERIOD_NS (2.0 ns = 500 MHz), TSMC 28 nm HPC+ tcbn28hpcplusbwp30p140 (files in
# scripts/config/pdk.env), MMMC views 0.81 V/125 C/RC worst (setup), 0.90 V/25 C/RC typical,
# 0.99 V/-40 C/RC best (hold).
# Core parameters: lean RV32IM+Zicsr (common.sh LEAN_GENUS) + the ID's Zbkb/XKyber/multiplier.
# Usage: 03_synth.sh <ID|all> ...
# Output: $WORK/synth/<ID>/gate_level/RS5_logic_mapped.v, RS5.sdc, reports/RS5_{qor,area,timing*,power*}.rpt
source "$(dirname "$0")/common.sh"
load_tool "$MOD_GENUS" || die "Genus not available"
need_pdk
RC=0
for ID in $(ids "$@"); do
    RTL=$(rtl_dir "$ID") || exit 1
    O=$WORK/synth/$ID
    rm -rf "$O"; start_run "$O"
    PARAMS="$LEAN_GENUS $(cfg "$ID" genus)"
    CMD=(genus -no_gui -overwrite -log "$O/genus"
         -execute "set OUT_DIR $O; set RTL_ROOT $RTL; set PERIOD $PERIOD_NS; set PARAMS {$PARAMS}; set NCPU $NCPU_SYNTH"
         -files "$REPRO/scripts/tcl/synth.tcl")
    { echo "# $(tree_info "$RTL")"; echo "# tcl=$REPRO/scripts/tcl/synth.tcl md5=$(md5 "$REPRO/scripts/tcl/synth.tcl")"
      printf '%q ' "${CMD[@]}"; echo; } >> "$O/cmd.txt"
    info "$ID: Genus at $PERIOD_NS ns ($(cfg "$ID" desc))"
    ( cd "$O" && timed "$O" "${CMD[@]}" )
    status "$O" "$(grep -q VERIFY_SYNTH_DONE "$O/stdout.log" && [ -s "$O/gate_level/RS5_logic_mapped.v" ] && echo OK || echo FAIL)" || RC=1
done
exit $RC
