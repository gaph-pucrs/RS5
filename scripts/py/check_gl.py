#!/usr/bin/env python3
"""Acceptance check of one gate-level run: functional result and same end cycle as the RTL run.
Usage: check_gl.py <gl_run_dir> <rtl_run_dir> <kat|coremark>   (prints a one-line verdict, exit 1 on failure)"""
import os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from collect_power import end_time, end_cycle, RTL_HALF_NS, TCLK_NS

gl, rtl, kind = sys.argv[1:4]
log = open(f'{gl}/xrun_stdout.log', errors='replace').read()
c_gl = end_cycle(end_time(f'{gl}/xrun_stdout.log', r'Simulation complete via \$finish\(1\) at time (\d+) NS'), TCLK_NS / 2)
c_rtl = end_cycle(end_time(f'{rtl}/stdout.log', r'# (\d+) END OF SIMULATION'), RTL_HALF_NS)
if kind == 'kat':
    res = re.findall(r'\[(PASS|FAIL)\]', log); func_ok = res.count('PASS') == 6 and 'FAIL' not in res
    func = f'KAT {res.count("PASS")}/6 PASS'
else:
    func_ok = 'Correct operation validated' in log; func = 'CoreMark ' + ('validated' if func_ok else 'NOT validated')
nsaif = len([f for f in os.listdir(gl) if f.endswith('.saif')])
ok = func_ok and c_gl is not None and c_gl == c_rtl
print(f'{"OK" if ok else "FAIL"} {func}; end cycle gl={c_gl} rtl={c_rtl}; {nsaif} SAIF')
sys.exit(0 if ok else 1)
