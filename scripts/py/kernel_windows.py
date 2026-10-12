#!/usr/bin/env python3
"""Pick representative call windows of kernel functions inside one operation window.

Usage: kernel_windows.py <trace> <app.nm> <app.lst> <prof_windows.csv> <op> <out.csv> [spec ...]
  spec = <function>:<which>  with which in first|mid|last (default first); function names are
  matched as exact symbol or as suffix after the KYBER namespace (e.g. poly_ntt).
Output CSV (run_gl_sdf.sh format): op,start_cycle,end_cycle  (op = <kernel>_<which>), sorted,
non-overlapping (a window that overlaps an earlier one is dropped and reported on stderr).
Call window = [cycle of the first instruction of the call, cycle of the instruction at its
return address), same stack model as profile.py (jal/jalr with rd=ra/t0 push, pop at return pc).
"""
import sys, csv, bisect, re
sys.path.insert(0, __file__.rsplit('/', 1)[0])
from profile import load_syms, load_len

def main(trace, nm, lst, winf, op, out, *specs):
    syms = load_syms(nm); starts = [a for a, _, _ in syms]; ilen = load_len(lst)
    byname = {}
    for a, s, n in syms: byname.setdefault(n, a)
    def resolve(f):
        if f in byname: return f
        c = [n for n in byname if n.endswith('_' + f)]
        if len(c) != 1: sys.exit(f'cannot resolve {f}: {c[:5]}')
        return c[0]
    targets = []
    for sp in specs:
        f, _, which = sp.partition(':'); targets.append((resolve(f), f, which or 'first'))
    W = {r['op']: (int(r['start_cycle']), int(r['end_cycle'])) for r in csv.DictReader(open(winf))}
    s0, e0 = W[op]
    entry = {byname[t]: t for t, _, _ in targets}
    calls = {t: [] for t, _, _ in targets}
    stack = []; open_calls = []   # (ret_addr, sym, start_cycle)
    rows = [l.split() for l in open(trace)]
    for i in range(len(rows) - 1):
        cyc = int(rows[i][0]); pc = int(rows[i][1], 16); w = int(rows[i][2], 16)
        if stack and any(pc == ra for ra in stack):
            while stack:
                ra = stack.pop()
                if ra == pc: break
            while open_calls and len(stack) < open_calls[-1][3]:
                ra, sym, st, depth = open_calls.pop()
                calls[sym].append((st, cyc))
        if s0 <= cyc < e0 and pc in entry:
            open_calls.append((None, entry[pc], cyc, len(stack)))
        op7 = w & 0x7f; rd = (w >> 7) & 31
        if op7 in (0x6f, 0x67) and rd in (1, 5):
            stack.append(pc + ilen.get(pc, 4))
    rowsout = []
    for t, short, which in targets:
        c = [x for x in calls[t] if s0 <= x[0] and x[1] <= e0]
        if not c: sys.exit(f'no complete call of {t} inside {op}')
        pick = {'first': c[0], 'mid': c[len(c) // 2], 'last': c[-1]}[which]
        rowsout.append((f'{short}_{which}', pick[0], pick[1], len(c)))
    rowsout.sort(key=lambda r: r[1])
    kept = []; last_end = -1
    for r in rowsout:
        if r[1] < last_end: print(f'drop overlapping window {r}', file=sys.stderr); continue
        kept.append(r); last_end = r[2]
    with open(out, 'w', newline='') as fo:
        wr = csv.writer(fo); wr.writerow(['op', 'start_cycle', 'end_cycle', 'cycles', 'calls_in_op'])
        for n, a, b, k in kept: wr.writerow([n, a, b, b - a, k])
    for r in kept: print(*r)

if __name__ == '__main__':
    main(*sys.argv[1:])
