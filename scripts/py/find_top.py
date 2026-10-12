#!/usr/bin/env python3
"""Print the top module of a structural Verilog netlist (defined but never instantiated)."""
import re, sys
t = open(sys.argv[1]).read()
mods = re.findall(r'^module\s+(\w+)', t, re.M)
inst = set(re.findall(r'^\s*(\w+)\s+(?:#\s*\(.*?\)\s*)?\\?[\w\[\]\.]+\s*\(', t, re.M))
top = [m for m in mods if m not in inst]
print(top[-1] if top else mods[-1])
