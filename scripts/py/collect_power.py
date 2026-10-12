#!/usr/bin/env python3
"""Aggregate the post-route Genus power reports of the SDF-annotated runs into CSVs.

Reads   $WORK/windows/<ID>_<set>.csv            (window cycles, from step 02)
        $WORK/power/<ID>_<set>/power_<win>.rpt   (+ _hier.rpt, from step 06)
        $WORK/gl/<ID>_<set>/xrun_stdout.log      (end time, KAT, from step 05)
        $WORK/rtl_sim/<ID>_{kat,coremark}/stdout.log (RTL end time, from step 02)
Writes  $WORK/results/power_windows.csv  one row per ID/set/window: P split (leakage/internal/
                                         switching; register/logic/clock) and E = P * cycles * T_clk
        $WORK/results/power_hier.csv     level-1 blocks + multiplier sub-blocks, per window
        $WORK/results/check_equivalence.csv  gate-level end cycle vs RTL end cycle, KAT / CoreMark
E[uJ] = P[mW] * 1e-3 * cycles * T_clk[ns] * 1e-9 * 1e6 = P * cycles * T_clk * 1e-6.
(repro copy of the paper's scripts/collect_power.py; SDF runs only, paths from $WORK, T_clk from
$PERIOD_NS, equivalence computed against the RTL run instead of a fixed constant.)
"""
import csv, glob, math, os, re, sys

WORK = os.environ['WORK']
TCLK_NS = float(os.environ.get('PERIOD_NS', '2.0'))
RTL_HALF_NS = 5.0            # tb/tb_rtl.sv clock (cycle counts do not depend on it)


def t0(half):
    """First rising clock edge strictly after reset release (100 ns); edges at half*(2k+1)."""
    k = math.floor((100.0 / half - 1) / 2) + 1
    return half * (2 * k + 1)


def end_cycle(t_ns, half):
    return math.floor((t_ns - t0(half)) / (2 * half) + 1e-9) if t_ns is not None else None


def end_time(log, pattern):
    if not os.path.exists(log):
        return None
    m = re.findall(pattern, open(log, errors='replace').read())
    return int(m[-1]) if m else None


def categories(rpt):
    d = {}
    for line in open(rpt):
        p = line.split()
        if len(p) >= 5 and p[0] in ('register', 'logic', 'clock', 'Subtotal'):
            d[p[0]] = [float(x) for x in p[1:5]]
    return d


def main():
    rows, hier, eq = [], [], []
    for d in sorted(glob.glob(f'{WORK}/power/*_*/')):
        run = os.path.basename(d.rstrip('/'))
        id_, set_ = run.split('_', 1)
        winf = f'{WORK}/windows/{run}.csv'
        if not os.path.exists(winf):
            continue
        cyc = {r['op']: int(r['end_cycle']) - int(r['start_cycle']) for r in csv.DictReader(open(winf))}
        for rpt in sorted(glob.glob(d + 'power_*.rpt')):
            w = os.path.basename(rpt)[6:-4]
            if w.endswith('_hier') or w == 'vectorless' or w not in cyc:
                continue
            c = categories(rpt)
            if 'Subtotal' not in c:
                continue
            leak, intl, sw, tot = c['Subtotal']
            rows.append(dict(ID=id_, set=set_, window=w, cycles=cyc[w], P_mW=round(tot, 4),
                             P_leak=round(leak, 4), P_int=round(intl, 4), P_sw=round(sw, 4),
                             P_reg=round(c['register'][3], 4), P_logic=round(c['logic'][3], 4),
                             P_clock=round(c['clock'][3], 4),
                             E_uJ=round(tot * cyc[w] * TCLK_NS * 1e-6, 4),
                             report=os.path.relpath(rpt, WORK)))
            hr = rpt[:-4] + '_hier.rpt'
            if os.path.exists(hr):
                for line in open(hr):
                    p = line.split()
                    if len(p) >= 8 and p[6] in ('1', '2') and re.match(r'^[\d.]+e?[-+]?\d*$', p[5]):
                        name = p[7].split('/')
                        blk = name[-1] if p[6] == '1' else name[-2] + '/' + name[-1]
                        if p[6] == '2' and not re.search(r'mul1|multdiv|div1|ibuf', blk):
                            continue
                        hier.append(dict(ID=id_, set=set_, window=w, block=blk, P_mW=float(p[5])))
    for d in sorted(glob.glob(f'{WORK}/gl/*_*/')):
        run = os.path.basename(d.rstrip('/'))
        id_, set_ = run.split('_', 1)
        if not os.path.exists(d + 'runtime.txt'):
            continue
        log = open(d + 'xrun_stdout.log', errors='replace').read()
        t_gl = end_time(d + 'xrun_stdout.log', r'Simulation complete via \$finish\(1\) at time (\d+) NS')
        sfx = '_k' + set_.split('_k')[1] if '_k' in set_ else ''
        rtl = f'{WORK}/rtl_sim/{id_}_{"coremark" if set_ == "cm" else "kat" + sfx}/stdout.log'
        t_rtl = end_time(rtl, r'# (\d+) END OF SIMULATION')
        c_gl, c_rtl = end_cycle(t_gl, TCLK_NS / 2), end_cycle(t_rtl, RTL_HALF_NS)
        func = ' '.join(re.findall(r'\[(PASS|FAIL)\]', log)) if set_ != 'cm' else \
            ('CoreMark validated' if 'Correct operation validated' in log else 'CoreMark NOT validated')
        eq.append(dict(run=run, gl_end_ns=t_gl, gl_end_cycle=c_gl, rtl_end_cycle=c_rtl,
                       equal='yes' if c_gl is not None and c_gl == c_rtl else 'NO', functional=func,
                       runtime=open(d + 'runtime.txt').read().split()[1]))
    os.makedirs(f'{WORK}/results', exist_ok=True)
    for name, data, fields in [('power_windows', rows, list(rows[0].keys()) if rows else []),
                               ('power_hier', hier, ['ID', 'set', 'window', 'block', 'P_mW']),
                               ('check_equivalence', eq, list(eq[0].keys()) if eq else [])]:
        if not data:
            continue
        with open(f'{WORK}/results/{name}.csv', 'w', newline='') as fo:
            wr = csv.DictWriter(fo, fieldnames=fields)
            wr.writeheader()
            wr.writerows(data)
    print(len(rows), 'power rows;', len(hier), 'hier rows;', len(eq), 'gate-level runs')
    bad = [e['run'] for e in eq if e['equal'] != 'yes' or 'FAIL' in e['functional'] or 'NOT' in e['functional']]
    if bad:
        print('EQUIVALENCE/FUNCTIONAL CHECK FAILED:', ' '.join(bad))
        sys.exit(1)


if __name__ == '__main__':
    main()
