#!/usr/bin/env python3
"""RTL cycle counts (KeyGen/Encaps/Decaps from the profile, CoreMark iterate() window) and Decaps
cycles per kernel class -> $WORK/results/cycles.csv, $WORK/results/cycle_classes.csv."""
import csv, glob, os
WORK = os.environ['WORK']
rows, cls = [], []
for d in sorted(glob.glob(f'{WORK}/rtl_sim/*_kat/')):
    id_ = os.path.basename(d.rstrip('/'))[:-4]
    if not os.path.exists(d + 'prof_windows.csv'):
        continue
    for r in csv.DictReader(open(d + 'prof_windows.csv')):
        rows.append(dict(ID=id_, op=r['op'], cycles=r['cycles'], source=os.path.relpath(d + 'prof_windows.csv', WORK)))
    cm = f'{WORK}/windows/{id_}_cm.csv'
    if os.path.exists(cm):
        for r in csv.DictReader(open(cm)):
            rows.append(dict(ID=id_, op='CoreMark_iterate', cycles=r['cycles'], source=os.path.relpath(cm, WORK)))
    for r in csv.DictReader(open(d + 'prof_classes.csv')):
        cls.append(dict(ID=id_, **r))
os.makedirs(f'{WORK}/results', exist_ok=True)
for name, data in (('cycles', rows), ('cycle_classes', cls)):
    if data:
        with open(f'{WORK}/results/{name}.csv', 'w', newline='') as fo:
            w = csv.DictWriter(fo, fieldnames=list(data[0].keys())); w.writeheader(); w.writerows(data)
for r in rows:
    print(f"{r['ID']} {r['op']:17s} {int(r['cycles']):>10,}")
