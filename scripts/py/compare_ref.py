#!/usr/bin/env python3
"""Compare a reproduction ($WORK) with the paper's reference results (results/).

Usage: compare_ref.py [--rel-tol 0.005]
Only rows present on both sides are compared, so a partial reproduction (e.g. one ID, or no
`ops` set) is checked for what it contains. Exact match is required for software md5, cycles and
windows; area, power and energy are compared with a relative tolerance (default 0.5 %).
Exit status 1 if any compared value differs.
"""
import csv, glob, hashlib, os, sys

WORK = os.environ['WORK']
REF = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', 'results')
TOL = float(sys.argv[sys.argv.index('--rel-tol') + 1]) if '--rel-tol' in sys.argv else 0.005
bad, n_cmp = [], 0


def load(path, key):
    if not os.path.exists(path):
        return {}
    return {tuple(r[k] for k in key): r for r in csv.DictReader(open(path))}


def cmp_table(name, ref_path, work_path, key, exact=(), approx=()):
    global n_cmp
    ref, work = load(ref_path, key), load(work_path, key)
    common = sorted(set(ref) & set(work))
    worst = 0.0
    for k in common:
        for c in exact:
            n_cmp += 1
            if str(ref[k][c]).strip() != str(work[k][c]).strip():
                bad.append(f'{name} {k} {c}: ref={ref[k][c]} work={work[k][c]}')
        for c in approx:
            a, b = ref[k][c], work[k][c]
            if a in ('', None) or b in ('', None):
                continue
            n_cmp += 1
            a, b = float(a), float(b)
            rel = abs(b - a) / abs(a) if a else abs(b)
            worst = max(worst, rel)
            if rel > TOL:
                bad.append(f'{name} {k} {c}: ref={a} work={b} ({100 * rel:+.2f} %)')
    if common:
        print(f'{name:22s} {len(common):4d} rows compared'
              + (f', worst relative difference {100 * worst:.3f} %' if approx else ''))
    else:
        print(f'{name:22s}    - (no common rows: not reproduced yet)')


def main():
    global n_cmp
    # software binaries
    ok = 0
    for line in open(os.path.join(REF, 'sw_md5.txt')):
        md5, rel = line.split()
        f = os.path.join(WORK, 'sw', rel)
        if os.path.exists(f):
            n_cmp += 1
            got = hashlib.md5(open(f, 'rb').read()).hexdigest()
            if got != md5:
                bad.append(f'sw {rel}: md5 {got} != ref {md5}')
            else:
                ok += 1
    print(f'{"software md5":22s} {ok:4d} identical')
    # windows (start/end cycles must be identical)
    for f in sorted(glob.glob(os.path.join(REF, 'windows', '*.csv'))):
        name = os.path.basename(f)
        cmp_table(f'windows/{name}', f, os.path.join(WORK, 'windows', name), ['op'],
                  exact=['start_cycle', 'end_cycle'])
    cmp_table('cycles', os.path.join(REF, 'cycles.csv'), os.path.join(WORK, 'results', 'cycles.csv'),
              ['ID', 'op'], exact=['cycles'])
    cmp_table('implementation', os.path.join(REF, 'implementation.csv'),
              os.path.join(WORK, 'results', 'implementation.csv'), ['ID'],
              exact=['cells'], approx=['std_cell_area_um2', 'core_area_um2', 'leak_tt_mW'])
    cmp_table('power_windows', os.path.join(REF, 'power_windows.csv'),
              os.path.join(WORK, 'results', 'power_windows.csv'), ['ID', 'set', 'window'],
              exact=['cycles'], approx=['P_mW', 'P_leak', 'P_int', 'P_sw', 'P_clock', 'E_uJ'])
    cmp_table('power_hier', os.path.join(REF, 'power_hier.csv'),
              os.path.join(WORK, 'results', 'power_hier.csv'), ['ID', 'set', 'window', 'block'],
              approx=['P_mW'])
    cmp_table('kernel_energy', os.path.join(REF, 'kernel_energy.csv'),
              os.path.join(WORK, 'results', 'kernel_energy.csv'), ['ID'],
              approx=['E_decaps_uJ', 'E_keccak_uJ', 'E_lattice_uJ'])
    cmp_table('check_equivalence', os.path.join(REF, 'check_equivalence.csv'),
              os.path.join(WORK, 'results', 'check_equivalence.csv'), ['run'], exact=[])
    eq = load(os.path.join(WORK, 'results', 'check_equivalence.csv'), ['run'])
    ref_eq = load(os.path.join(REF, 'check_equivalence.csv'), ['run'])
    for k in sorted(set(eq) & set(ref_eq)):
        n_cmp += 1
        if eq[k]['gl_end_cycle'] != ref_eq[k]['end_cycle']:
            bad.append(f'check_equivalence {k}: end cycle {eq[k]["gl_end_cycle"]} != ref {ref_eq[k]["end_cycle"]}')
    print(f'\n{n_cmp} values compared, {len(bad)} differences (relative tolerance {100 * TOL:.2f} %)')
    for b in bad:
        print('  DIFF', b)
    sys.exit(1 if bad else 0)


if __name__ == '__main__':
    main()
