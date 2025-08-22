import os
import re
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
from collections import defaultdict

benchmarks_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../app/lmfrnet/results/")
benchmarks_list = [entry for entry in os.listdir(benchmarks_dir) if os.path.isdir(os.path.join(benchmarks_dir, entry)) and entry != "scalar"]
benchmarks_list = sorted(benchmarks_list)

scalar_cycles = 0
scalar_pattern = re.compile(r"\[SCALAR\] The execution took (\d+) cycles\.")
with open(os.path.join(benchmarks_dir, "scalar/verilator_scalar.txt")) as f:
    content = f.read()
    match = scalar_pattern.search(content)
    if match:
        scalar_cycles = int(match.group(1))

data = defaultdict(list)
for benchmark in benchmarks_list:
    path = os.path.join(benchmarks_dir, benchmark)
    csv_file = os.path.join(path, benchmark + ".csv")
    df = pd.read_csv(csv_file)

    vlen = int(df.at[0, "VLEN"])
    lmul = int(df.at[0, "LMUL"])
    cycles = int(df.at[0, "CYCLES"])

    data[vlen].append({"LMUL": lmul, "CYCLES": cycles, "SCALAR": scalar_cycles})

VLENs = sorted(data.keys())
LMULs = sorted({entry["LMUL"] for entries in data.values() for entry in entries})

bar_width = 0.1
x = np.arange(len(VLENs))

for i, lmul in enumerate(LMULs):
    cycles = [next(item["CYCLES"] for item in data[vlen] if item["LMUL"] == lmul) for vlen in VLENs]
    plt.bar(x + (i+2)*bar_width, cycles, width=bar_width, label=f"LMUL = {lmul}")

# plt.bar(0, scalar_cycles, width =bar_width, label=f"SCALAR")
plt.axhline(scalar_cycles, color="purple", linestyle="--", linewidth=2, label="SCALAR")

# plt.xticks(x + bar_width*(len(LMULs)-1)/2, VLENs)
plt.xticks(x + bar_width*(len(LMULs)+3)/2, VLENs) 
plt.xlabel("VLEN")
plt.yticks(np.arange(0,11e8,1e8))
plt.ylabel("CYCLES")
# plt.legend()
plt.legend(bbox_to_anchor=(1, 0.8))
plt.title("Cycles vs VLEN for different LMULs")
plt.show()
plt.savefig(os.path.join(benchmarks_dir, "charts.png"))