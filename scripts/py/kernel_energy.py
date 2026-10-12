#!/usr/bin/env python3
"""Decaps energy attribution per kernel class (SDF-annotated runs).

P_keccak  = cycle-weighted mean power of the sampled Keccak-f1600 calls (first/mid/last);
P_lattice = cycle-weighted mean power of polyvec_ntt, polyvec_pointwise_acc, polyvec_invntt;
cycles per class from the RTL profile ($WORK/rtl_sim/<ID>_kat/prof_classes.csv):
keccak = classes 1+2, lattice = 3, rest = 4..7.
E_class = P_class * cycles_class * T_clk; E_rest = E_Decaps(measured) - E_keccak - E_lattice,
reported with its implied power P_rest = E_rest / (cycles_rest * T_clk) as a plausibility check.
Reads $WORK/results/power_windows.csv (collect_power.py); writes $WORK/results/kernel_energy.csv.
(repro copy of the paper's scripts/kernel_energy.py; SDF only, paths from $WORK.)
"""
import csv, os

WORK = os.environ['WORK']
TCLK_NS = float(os.environ.get('PERIOD_NS', '2.0'))
K = TCLK_NS * 1e-6                      # uJ per (mW * cycle)
PW = list(csv.DictReader(open(f'{WORK}/results/power_windows.csv')))
out = []
for id_ in sorted({r['ID'] for r in PW}):
    prof = f'{WORK}/rtl_sim/{id_}_kat/prof_classes.csv'
    k = [r for r in PW if r['ID'] == id_ and r['set'] == 'kernels']
    o = [r for r in PW if r['ID'] == id_ and r['set'] == 'ops' and r['window'] == 'Decaps']
    if not (os.path.exists(prof) and k and o):
        continue
    cls = {r['class'][0]: int(r['cycles']) for r in csv.DictReader(open(prof)) if r['op'] == 'Decaps'}
    ck = cls.get('1', 0) + cls.get('2', 0)
    cl = cls.get('3', 0)
    cr = sum(v for c, v in cls.items() if c not in '123')

    def wavg(names):
        s = [r for r in k if any(r['window'].startswith(n) for n in names)]
        return sum(float(r['P_mW']) * int(r['cycles']) for r in s) / sum(int(r['cycles']) for r in s)

    pk = wavg(['sha3_f1600'])
    pl = wavg(['polyvec_ntt', 'polyvec_pointwise', 'polyvec_invntt'])
    e_tot = float(o[0]['E_uJ'])
    ek, el = pk * ck * K, pl * cl * K
    er = e_tot - ek - el
    out.append(dict(ID=id_, cycles_decaps=int(o[0]['cycles']), cyc_keccak=ck, cyc_lattice=cl, cyc_rest=cr,
                    P_keccak=round(pk, 4), P_lattice=round(pl, 4), P_decaps=o[0]['P_mW'],
                    E_decaps_uJ=round(e_tot, 3), E_keccak_uJ=round(ek, 3), E_lattice_uJ=round(el, 3),
                    E_rest_uJ=round(er, 3), P_rest_implied=round(er / (cr * K), 4) if cr else '',
                    frac_keccak=round(ek / e_tot, 3), frac_lattice=round(el / e_tot, 3),
                    frac_rest=round(er / e_tot, 3)))
if out:
    with open(f'{WORK}/results/kernel_energy.csv', 'w', newline='') as fo:
        wr = csv.DictWriter(fo, fieldnames=list(out[0].keys()))
        wr.writeheader()
        wr.writerows(out)
for r in out:
    print(r)
if not out:
    print('kernel_energy: needs the ops and kernels sets of at least one ID (nothing written)')
