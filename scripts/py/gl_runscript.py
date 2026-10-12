#!/usr/bin/env python3
"""Xcelium Tcl run script that dumps one SAIF per window (repro copy of the generator embedded in
the paper's scripts/run_gl_sdf_v2.sh).

Usage: gl_runscript.py <windows.csv> <half_period_ns>  > run.tcl
windows.csv: op,start_cycle,end_cycle in cycles of the RTL execute trace. Cycle c is the c-th
rising clock edge after reset release (t = 100 ns): t(c) = t0 + 2*half*c, with t0 the first
rising edge strictly after 100 ns (the testbench clock toggles every `half` ns from t = 0, so
rising edges are at half*(2k+1)). Gate-level and RTL runs execute the same cycles, which
step 05 checks by comparing the simulation end cycle with the RTL run.
"""
import csv, math, sys

half = float(sys.argv[2]); per = 2 * half
k = math.floor((100.0 / half - 1) / 2) + 1          # first rising edge strictly after 100 ns
t0 = half * (2 * k + 1)
t = 0.0
for r in csv.DictReader(open(sys.argv[1])):
    s = t0 + per * int(r['start_cycle']); e = t0 + per * int(r['end_cycle'])
    print(f'run {s - t:.3f} ns')
    print(f'dumpsaif -scope testbench.dut -depth to_cells -internal -output {r["op"]}.saif -overwrite')
    print(f'run {e - s:.3f} ns'); print('dumpsaif -end'); t = e
    print(f'puts "WINDOW {r["op"]} start_ns={s:.3f} end_ns={e:.3f}"')
print('run'); print('exit')
