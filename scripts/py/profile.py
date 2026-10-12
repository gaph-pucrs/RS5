#!/usr/bin/env python3
"""Cycle profile from the execute-stage trace (trace_bind.sv).

trace line: <cycle> <pc hex> <instr hex (decompressed 32-bit)> <cycles in execute>
Cycles of instruction i = cycle[i+1] - cycle[i]  (includes fetch bubbles / stalls
that follow it), so the sum over a window equals the window's wall cycles.

Call stack: jal/jalr with rd=ra push the return address (pc + len, len from the
objdump listing); an instruction whose pc equals a pushed return address pops
down to it (handles ret, tail calls and longjmp-free code).

Usage: profile.py <trace> <app.nm> <app.lst> <out_prefix>
Outputs: <out>_windows.csv  (op,start_cycle,end_cycle,cycles,instructions)
         <out>_functions.csv (op,function,class,exclusive,inclusive,calls)
         <out>_classes.csv   (op,class,cycles,fraction)
"""
import sys, re, bisect, csv, collections

OPS = {'KeyGen': 'pqcrystals_kyber512_ref_keypair',
       'Encaps': 'pqcrystals_kyber512_ref_enc',
       'Decaps': 'pqcrystals_kyber512_ref_dec'}

# 7 classes. Helpers (emulated bitmanip) inherit the class of their caller.
HELPERS = re.compile(r'^_rvk_emu_|^_rv32_')
def classify(f):
    if f is None: return 'other'
    if f == 'sha3_f1600_rvb32': return '1 keccak_permutation'
    if f in ('sha3_init', 'sha3_update', 'sha3_final', 'sha3', 'shake_xof', 'shake_out',
             'kyber_shake128_absorb', 'kyber_shake256', 'kyber_shake256_prf',
             'kyber_shake256_rkprf'):
        return '2 keccak_sponge_glue'
    if re.search(r'_(ntt|invntt|basemul|montgomery_reduce|barrett_reduce|csubq|fqmul|poly_tomont|'
                 r'poly_reduce|polyvec_reduce|polyvec_csubq|poly_add|poly_sub|polyvec_add|'
                 r'pointwise_acc_montgomery|basemul_montgomery|invntt_tomont|poly_ntt|polyvec_ntt)', f):
        return '3 poly_arith_ntt'
    if re.search(r'(rej_uniform|gen_matrix|cbd_eta|getnoise)', f):
        return '4 sampling'
    if re.search(r'_(poly|polyvec)_(compress|decompress|tobytes|frombytes|tomsg|frommsg)|pack_|unpack_', f):
        return '5 compress_pack'
    if f in ('memcpy', 'memset', 'memchr', 'strlen') or re.search(r'_(verify|cmov)$', f):
        return '6 mem_verify_cmov'
    return '7 other'   # indcpa/kem glue, randombytes (KAT DRBG), AES, ...

def load_syms(nm):
    s = []
    for line in open(nm):
        p = line.split()
        if len(p) == 4 and p[2] in 'TtWw':
            s.append((int(p[0], 16), int(p[1], 16), p[3]))
    s.sort()
    return s

def load_len(lst):
    L = {}
    r = re.compile(r'^\s*([0-9a-f]+):\s+([0-9a-f]{4}|[0-9a-f]{8})\s')
    for line in open(lst):
        m = r.match(line)
        if m: L[int(m.group(1), 16)] = len(m.group(2)) // 2
    return L

def main(trace, nm, lst, out):
    syms = load_syms(nm); starts = [a for a, _, _ in syms]
    ilen = load_len(lst)
    cache = {}
    def fn(pc):
        if pc in cache: return cache[pc]
        i = bisect.bisect_right(starts, pc) - 1
        r = syms[i][2] if i >= 0 and pc < syms[i][0] + max(syms[i][1], 1) else None
        cache[pc] = r; return r
    entry = {v: next(a for a, _, n in syms if n == v) for v in OPS.values()}
    rows = [l.split() for l in open(trace)]
    cyc = [int(r[0]) for r in rows]; pcs = [int(r[1], 16) for r in rows]; ins = [int(r[2], 16) for r in rows]
    stack = []   # (return address, function name)
    win = {}     # op -> [start_idx, end_idx]
    active = None; active_depth = None
    excl = collections.defaultdict(lambda: collections.Counter())
    incl = collections.defaultdict(lambda: collections.Counter())
    calls = collections.defaultdict(lambda: collections.Counter())
    klass = collections.defaultdict(lambda: collections.Counter())
    for i in range(len(rows) - 1):
        pc = pcs[i]; f = fn(pc)
        # pop frames whose return address we reached
        if stack and any(pc == ra for ra, _ in stack):
            while stack:
                ra, _ = stack.pop()
                if ra == pc: break
            if active and len(stack) < active_depth:
                win[active][1] = i; active = None
        if active is None:
            for op, sym in OPS.items():
                if pc == entry[sym] and op not in win:
                    active = op; active_depth = len(stack); win[op] = [i, None]
        d = cyc[i + 1] - cyc[i]
        if active:
            excl[active][f] += d
            frames = [n for _, n in stack[active_depth:]] + [f]
            for n in set(frames): incl[active][n] += d
            # class: innermost non-helper frame
            c = None
            for n in reversed(frames):
                if n and not HELPERS.search(n): c = classify(n); break
            klass[active][c or 'other'] += d
        w = ins[i]; op7 = w & 0x7f; rd = (w >> 7) & 31
        if op7 in (0x6f, 0x67) and rd in (1, 5):
            ra = pc + ilen.get(pc, 4)
            tgt = None
            stack.append((ra, f))
            if active: calls[active][fn(pcs[i + 1])] += 1
    with open(out + '_windows.csv', 'w', newline='') as fo:
        wr = csv.writer(fo); wr.writerow(['op', 'start_cycle', 'end_cycle', 'cycles', 'instructions'])
        for op, (a, b) in win.items():
            wr.writerow([op, cyc[a], cyc[b], cyc[b] - cyc[a], b - a])
    with open(out + '_functions.csv', 'w', newline='') as fo:
        wr = csv.writer(fo); wr.writerow(['op', 'function', 'class', 'exclusive', 'inclusive', 'calls'])
        for op in win:
            for f, v in sorted(incl[op].items(), key=lambda x: -x[1]):
                wr.writerow([op, f, classify(f), excl[op].get(f, 0), v, calls[op].get(f, 0)])
    with open(out + '_classes.csv', 'w', newline='') as fo:
        wr = csv.writer(fo); wr.writerow(['op', 'class', 'cycles', 'fraction'])
        for op, (a, b) in win.items():
            tot = cyc[b] - cyc[a]
            for c, v in sorted(klass[op].items()):
                wr.writerow([op, c, v, f'{v / tot:.4f}'])
    for op, (a, b) in win.items():
        print(op, cyc[b] - cyc[a])

if __name__ == '__main__':
    main(*sys.argv[1:5])
