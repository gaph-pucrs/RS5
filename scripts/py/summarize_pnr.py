#!/usr/bin/env python3
"""P&R summary (repro copy of the paper's scripts/summarize_pnr.py; paths relative to $WORK).
Usage: summarize_pnr.py <out.csv> <pnr_run_dir> [...]
All numbers come from files written by tcl/pnr.tcl in <run>/reports/.
Also writes implementation.csv (paper columns) next to <out.csv>."""
import sys, os, re, csv, gzip, glob

WORK = os.environ['WORK']
LABEL = {'H0': 'RS5', 'H1': '+Zbkb', 'H2': '+Zbkb+XKyber (Comb.)', 'H3': '+Zbkb+XKyber (Ser.)',
         'H4': '+XKyber (Ser.)'}

def rd(p):
    try:
        return gzip.open(p, 'rt').read() if p.endswith('.gz') else open(p).read()
    except OSError:
        return ''

def first_slack(p):
    m = re.search(r'Slack:=\s+(-?[0-9.]+)', rd(p)); return m and m.group(1)

def td_summary(d, kind):
    f = glob.glob(f'{d}/reports/td_final_{kind}/*summary.gz')
    t = rd(f[0]) if f else ''
    wns = re.search(r'WNS \(ns\):\|\s*(-?[0-9.]+)', t); tns = re.search(r'TNS \(ns\):\|\s*(-?[0-9.]+)', t)
    nv = re.search(r'Violating Paths:\|\s*(\d+)', t)
    return (wns and wns.group(1), tns and tns.group(1), nv and nv.group(1))

def parse(d):
    R = f'{d}/reports'
    r = {'ID': os.path.basename(d.rstrip('/')), 'run_dir': os.path.relpath(d, WORK)}
    rt = rd(f'{d}/runtime.txt'); r['status'] = 'OK' if 'status=OK' in rt else ('RUNNING' if not rt else 'FAIL')
    m = re.search(r'wall_s=(\d+)', rt); r['wall_s'] = m and m.group(1)
    cmd = rd(f'{d}/cmd.txt'); m = re.search(r'commit=(\w{7})', cmd); r['rtl_commit'] = m and m.group(1)
    m = re.search(r'genus_run=(\S+)', cmd); r['genus_run'] = m and os.path.relpath(m.group(1), WORK)
    n = dict(l.split(None, 1) for l in rd(f'{R}/pnr_numbers.txt').splitlines() if l.strip())
    r['core_area_um2'] = n.get('core_area_um2', '').strip(); r['die_area_um2'] = n.get('die_area_um2', '').strip()
    r['std_cell_area_um2'] = n.get('std_cell_area_um2', '').strip(); r['std_cells'] = n.get('std_cells', '').strip()
    r['util_core'] = n.get('std_util_core', '').strip()[:6]
    r['kGE_std'] = f"{float(r['std_cell_area_um2']) / 0.378 / 1000:.2f}" if r['std_cell_area_um2'] else ''
    r['setup_wns_ss_ns'] = first_slack(f'{R}/timing_setup_ss_rcworst.rpt')
    w, t, v = td_summary(d, 'setup'); r['setup_wns_allviews_ns'], r['setup_tns_ns'], r['setup_viol_paths'] = w, t, v
    r['hold_wns_ff_ns'] = first_slack(f'{R}/timing_hold_ff_rcbest.rpt')
    r['hold_wns_tt_ns'] = first_slack(f'{R}/timing_hold_tt_typical.rpt')
    w, t, v = td_summary(d, 'hold'); r['hold_wns_allviews_ns'], r['hold_tns_ns'], r['hold_viol_paths'] = w, t, v
    ct = rd(f'{R}/clock_trees_final.rpt')
    for k in ['Buffers', 'Inverters', 'Integrated Clock Gates']:
        m = re.search(r'^' + k + r'\s+(\d+)\s+([0-9.]+)', ct, re.M); r[f'clk_{k.split()[0].lower()}'] = m and m.group(1)
    sk = rd(f'{R}/skew_groups_final.rpt')
    ins = {}
    for line in sk.split('Skew Group Summary')[-1].splitlines():
        f = line.split()
        if len(f) > 5 and f[0].startswith('delay_corner_') and f[0] not in ins:
            ins[f[0]] = (f[3], f[4])
    for tag, key in [('ss', 'delay_corner_0p81v_125c_capwst:setup.late'), ('tt', 'delay_corner_0p90v_25c_captyp:both.late'),
                     ('ff', 'delay_corner_0p99v_m40c_capbst:hold.early')]:
        v = ins.get(key); r[f'clk_insertion_{tag}_min_max_ns'] = v and f'{v[0]}-{v[1]}'
    m = re.search(r'delay_corner_0p81v_125c_capwst:setup.late.*?auto computed\s+([0-9.]+)\s+([0-9.]+)', sk)
    r['clk_skew_ss_ns'] = m and m.group(2)
    p = rd(f'{R}/power_vectorless_tt.rpt')
    m = re.search(r'Total Leakage Power:\s+([0-9.eE+-]+)', p); r['leak_tt_mW'] = m and m.group(1)
    m = re.search(r'Total Power:\s+([0-9.eE+-]+)', p); r['P_vectorless_tt_mW'] = m and m.group(1)
    dr = rd(f'{R}/check_drc.rpt')
    m = re.search(r'Total Violations\s*:\s*(\d+)', dr); r['drc_viols'] = m.group(1) if m else ('0' if dr else '')
    cc = rd(f'{R}/check_connectivity.rpt')
    r['connectivity'] = 'clean' if 'Found no problems or warnings' in cc else (re.sub(r'\s+', ' ', cc.split('Begin Summary')[-1])[:80] if cc else '')
    an = rd(f'{R}/check_antenna.rpt'); r['antenna'] = 'clean' if 'No Violations Found' in an else ('?' if not an else 'viol')
    r['filler_1site_gaps'] = str(rd(f'{R}/check_filler.rpt').count('is free'))
    r['reports'] = f"{r['run_dir']}/reports/{{pnr_numbers.txt,timing_setup_ss_rcworst.rpt,timing_hold_ff_rcbest.rpt,td_final_*,clock_trees_final.rpt,power_vectorless_tt.rpt,check_drc.rpt,check_connectivity.rpt}}"
    return r

def ps(x):
    return str(round(float(x) * 1000)) if x not in (None, '') else ''


def main(out, *dirs):
    rows = [parse(d) for d in dirs]
    with open(out, 'w', newline='') as fo:
        w = csv.DictWriter(fo, fieldnames=list(rows[0].keys())); w.writeheader(); w.writerows(rows)
    impl = [dict(ID=r['ID'], label=LABEL.get(r['ID'], ''), std_cell_area_um2=r['std_cell_area_um2'],
                 kGE_0p378=r['kGE_std'], cells=r['std_cells'], core_area_um2=r['core_area_um2'],
                 setup_wns_ss_ps=ps(r['setup_wns_ss_ns']), hold_wns_ff_ps=ps(r['hold_wns_ff_ns']),
                 leak_tt_mW=r['leak_tt_mW'], source=f"{r['run_dir']}/reports/pnr_numbers.txt") for r in rows]
    with open(os.path.join(os.path.dirname(out), 'implementation.csv'), 'w', newline='') as fo:
        w = csv.DictWriter(fo, fieldnames=list(impl[0].keys())); w.writeheader(); w.writerows(impl)
    for r in rows:
        print(f"{r['ID']:10s} {r['status']} core={r['core_area_um2']} std={r['std_cell_area_um2']} cells={r['std_cells']} kGE={r['kGE_std']} "
              f"setupWNS_ss={r['setup_wns_ss_ns']} TNS={r['setup_tns_ns']} holdWNS_ff={r['hold_wns_ff_ns']} hold_tt={r['hold_wns_tt_ns']} "
              f"clkbuf={r['clk_buffers']}/{r['clk_inverters']} ICG={r['clk_integrated']} ins_tt={r['clk_insertion_tt_min_max_ns']} ins_ff={r['clk_insertion_ff_min_max_ns']} skew_ss={r['clk_skew_ss_ns']} leak={r['leak_tt_mW']} P={r['P_vectorless_tt_mW']} "
              f"DRC={r['drc_viols']} conn={r['connectivity']} gaps={r['filler_1site_gaps']}")

if __name__ == '__main__':
    main(sys.argv[1], *sys.argv[2:])
