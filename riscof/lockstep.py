#!/usr/bin/env python3
"""Diff the RS5Debug trace of a riscof test against its sail-riscv reference trace.

Usage: ./lockstep.py <work_dir>/rv32i_m/*/src/*.S

Both models trace in the sail-riscv 0.7 format, but they do not trace the same
span: sail enters the test through its reset vector, keeps running after the DUT
has stopped on the tohost write, and is the only one that can disassemble. What
is left once that is normalized away has to be identical, so any difference is a
divergence between RS5 and the reference model.

Three of them are known and expected:
  - misa reads back with S set, as the sail RV32 model always implements S and
    has no option to drop it
  - an illegal instruction whose first halfword is not a 32 bit opcode is fetched
    whole by RS5, which then reports it in mtval, while sail stops after that
    halfword and reports mtval as zero
  - the C hint code points (c.addi rd, 0) retire without a register write in
    sail, while RS5 writes the unchanged value back
"""

import re
import sys
from pathlib import Path

INSN    = re.compile(r'^\[(\d+)\] \[([MSU])\]: 0x([0-9A-F]{8}) \((0x[0-9A-F]+)\)')
DUT_LOG = 'riscof_tb.dut.debug.log'

def normalize(path, limit=None):
    """Drop what only one of the models traces and renumber the steps."""
    out, fetch, started, step = [], [], False, 0

    for line in open(path):
        line = line.rstrip('\n')

        if line.startswith(('htif', 'clint')):      # sail platform tracing
            continue

        insn = INSN.match(line)
        if insn:
            if not started:
                if int(insn.group(3), 16) < 0x80000000:
                    fetch = []                      # sail reset vector at 0x1000
                    continue
                started = True
            if limit is not None and step >= limit:
                break
            out += fetch + ['[{}] [{}]: 0x{} ({})'.format(step, *insn.group(2, 3, 4))]
            fetch = []
            step += 1
        elif line.startswith('mem[X,'):
            fetch.append(line)                      # held back until the step is kept
        elif started:
            out.append(line)                        # sail banner is dropped this way

    return out, step

def compare(test_dir):
    dut_log  = test_dir / 'dut' / DUT_LOG
    ref_logs = [l for l in (test_dir / 'ref').glob('*.log') if l.name != 'sail.log']

    if not dut_log.exists() or not ref_logs:
        print('{}: no trace, nothing to compare'.format(test_dir.name))
        return 0

    dut, steps = normalize(dut_log)
    ref, _     = normalize(ref_logs[0], steps)

    if dut == ref:
        print('{}: match ({} steps)'.format(test_dir.name, steps))
        return 0

    for tag, lines in (('dut', dut), ('ref', ref)):
        (test_dir / '{}.trace'.format(tag)).write_text('\n'.join(lines) + '\n')

    diff = next((i for i, (a, b) in enumerate(zip(ref, dut)) if a != b), min(len(ref), len(dut)))
    step = next((l for l in reversed(dut[:diff + 1]) if l.startswith('[')), '[?]')

    print('{}: MISMATCH at {}'.format(test_dir.name, step))
    print('  ref: {}'.format(ref[diff] if diff < len(ref) else '<end of trace>'))
    print('  dut: {}'.format(dut[diff] if diff < len(dut) else '<end of trace>'))
    print('  diff {}/ref.trace {}/dut.trace'.format(test_dir, test_dir))
    return 1

if __name__ == '__main__':
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    sys.exit(max(compare(Path(d)) for d in sys.argv[1:]))
