# XKyber and Zbkb on RS5: post-layout energy of ML-KEM-512 (ISCAS 2027)

This branch reproduces the implementation and energy results of

> V. B. Zanini, I. I. Weber, and F. G. Moraes, "Energy of Lattice and Keccak Instruction Set
> Extensions for ML-KEM on an Embedded RISC-V," in *Proc. IEEE International Symposium on Circuits
> and Systems (ISCAS)*, 2027 - SUBMITED.

The paper adds the standard Zbkb extension (Keccak) and XKyber, six custom instructions for
modular arithmetic, centered binomial sampling and coefficient compression, to the RS5 RISC-V core
(RV32IM). It measures the energy of complete ML-KEM-512 operations by delay-annotated gate-level
simulation of the placed-and-routed core in TSMC 28 nm at 500 MHz. The two extensions reduce
decapsulation energy by 42.0 % (serialized XKyber) to 45.6 % (combinational XKyber) for 7.6 % to
9.8 % more core area.

The branch is self-contained: the RTL, the software, the scripts and the paper's numbers are all
here, and the flow downloads nothing. It is an orphan branch; the default branch of the repository
is the current RS5, which has evolved since.

## Layout

| Folder | Content |
|---|---|
| `rtl_base/` | RS5 RTL of H0 and H1 |
| `rtl_comb/` | RS5 RTL of H2 (combinational XKyber) |
| `rtl_ser/` | RS5 RTL of H3 and H4 (serialized XKyber) |
| `sw/` | ML-KEM-512 (pq-crystals reference + XKyber hooks), CoreMark, multest, the official KAT file; `sw/prebuilt/`: the paper's binaries |
| `scripts/` | the flow: `run_all.sh`, one script per step (`01…07_*.sh`), `config/`, Genus/Innovus scripts (`tcl/`), testbenches (`tb/`), analysis (`py/`) |
| `results/` | the paper's numbers (CSV) and, in `results/reports/`, the aggregated area and power reports they were read from |

## Configurations

All five are the same lean RS5 core (RV32IM + Zicsr; no compressed instructions, Zkne, Zknh, Zicond,
Zcb, HPM counters or AMO) at 500 MHz. Each RTL folder is configured by top-level parameters, listed
in `scripts/config/configs.tsv`.

| ID | Paper label | Extensions | RTL | Multiplier | Software |
|---|---|---|---|---|---|
| H0 | RS5 | none | `rtl_base` | RS5 serial multiplier | `base` |
| H1 | +Zbkb | Zbkb | `rtl_base` | RS5 serial multiplier | `zbkb` |
| H4 | +XKyber | XKyber, serialized (the unused Zbkb execute logic remains) | `rtl_ser` | RS5 multiplier extended with XKyber | `xkyber` |
| H3 | +Both (Ser.) | Zbkb + XKyber, serialized | `rtl_ser` | RS5 multiplier extended with XKyber | `both` |
| H2 | +Both (Comb.) | Zbkb + XKyber, combinational (Gewehr et al.) | `rtl_comb` | `ibex_multdiv_fast` | `both` |

## Quick start

Without the Cadence tools and the standard-cell library (about 2 minutes): binaries, RTL simulation,
cycle counts and measurement windows, compared with the paper.

```bash
PREBUILT=1 STEPS="01 02 07" scripts/run_all.sh all
```

The run ends with `146 values compared, 0 differences`. Outputs go to `work/` (`WORK=...` to change it).

The whole flow, with the Cadence tools and the library (about 2 hours for the five configurations,
four in parallel):

```bash
cp scripts/config/pdk.env.example scripts/config/pdk.env
vi scripts/config/pdk.env              # library files and cell names (not versioned)
vi scripts/config/repro.env            # tool modules, threads, MAXPAR
scripts/run_all.sh all                 # ends with "1216 values compared, 0 differences"
scripts/run_all.sh H0                  # one configuration
SETS="kernels cm" scripts/run_all.sh H0   # skip the long whole-operation windows
STEPS="05 06 07" scripts/run_all.sh H2    # rerun some steps
```

Each step can also be run alone (`scripts/02_rtl_sim.sh H0`, `scripts/05_gl_sdf.sh H0 cm`, ...).
Every run directory has `cmd.txt` (exact command and md5 of its inputs) and `runtime.txt` (return
code, wall time and `status=OK|FAIL`).

## Requirements

| Item | Version used | Notes |
|---|---|---|
| Verilator | 5.052 | step 02; needs a C++20 host compiler |
| Python | ≥ 3.8 | standard library only |
| GNU make, bash ≥ 4.3, flock | | |
| riscv64-elf-gcc | 15.2.0, newlib-nano, binutils with XKyber | step 01. The XKyber builds use the six XKyber mnemonics in inline assembly, so the assembler must know them (GAPH build). Without it, `PREBUILT=1` copies `sw/prebuilt/`; the compiled binaries are identical (`results/sw_md5.txt`) |
| Cadence Genus | 21.1 | synthesis (03) and power (06) |
| Cadence Innovus | 21.1, stylus | place and route (04) |
| Cadence Xcelium | 23.03 | delay-annotated gate-level simulation (05) |
| TSMC 28 nm HPC+ standard cells `tcbn28hpcplusbwp30p140` | | steps 03–06; under NDA, not included. Liberty, LEF, QRC tech files, cell Verilog models and cell names go in `scripts/config/pdk.env` |

Per configuration: about 0.35 GB of disk and 2 h 15 min with 3–4 threads, dominated by the `ops`
gate-level run (57–68 min). Steps 03, 04 and 06 hold one Genus/Innovus license each; step 05 holds
one Xcelium license per running set.

## Where each number of the paper comes from

All values are in `results/`. The `source`/`report` columns of the CSVs point to the report each
value was read from, relative to `results/reports/`. Energy is E = P × cycles × 2 ns.

| Paper | Value | File (columns) |
|---|---|---|
| Table II, Area, Slack | kGE (NAND2 = 0.378 µm²), setup WNS | `results/implementation.csv` (`kGE_0p378`, `setup_wns_ss_ps`) |
| Table II, Cycles KG/Enc/Dec | RTL cycles | `results/cycles.csv` (`op` = KeyGen/Encaps/Decaps) |
| Table II, Energy KG/Enc/Dec/CM | post-route, SDF-annotated | `results/power_windows.csv` (`E_uJ`; `set` = ops, and cm for CoreMark) |
| Table II, CoreMark cycles | 453.9 k (444.5 k in H2) | `results/cycles.csv` (`op` = CoreMark_iterate) |
| Fig. 2 | Decaps energy by kernel, Keccak share | `results/kernel_energy.csv` (`E_keccak_uJ`, `E_lattice_uJ`, `E_rest_uJ`, `frac_keccak`) |
| Table III, this work | 2.07 / 2.67 kGE; 7.6 / 9.8 %; 49.1 / 45.9 % | `results/implementation.csv` (H2, H3 − H0); `results/cycles.csv` (Decaps, H0 → H2/H3) |
| Abstract, Sec. V-C | Decaps energy −42.0 % (Ser.), −45.6 % (Comb.) | `results/power_windows.csv`: 23.291 → 13.503 (H3) / 12.669 µJ (H2) |
| Sec. V-A | area +3.2 % (Zbkb), +7.6 % (Comb.), +9.8 % (Ser.) | `results/implementation.csv` (`std_cell_area_um2` over H0) |
| Sec. V-A | multiplier 931 → 1,601 µm²; multiplier-divider 1,354 µm² | `results/reports/hw/pnr/{H1,H3}_2.0/reports/area.rpt` (`mul1`), `H2_2.0` (`multdiv_i`) |
| Sec. V-B | XKyber on top of Zbkb: −32.4 % Encaps, −37.6 % Decaps cycles | `results/cycles.csv` (H1 → H3) |
| Sec. V-C | Decaps latency/energy: Zbkb −13.3/−9.7 %, XKyber −32.6/−24.5 %, both −45.9/−42.0 % (Ser.), −49.1/−45.6 % (Comb.) | `results/cycles.csv`, `results/power_windows.csv` (H1, H4, H3, H2 over H0) |
| Sec. V-C | Comb. vs Ser.: 6.0 % fewer cycles, 6.2 % less energy, 2.0 % less area | `results/cycles.csv`, `results/power_windows.csv`, `results/implementation.csv` (H2 vs H3) |
| Sec. V-C | savings add up: 236.4 + 580.4 = 816.8 kcycles | `results/cycles.csv` (Decaps: H0−H1, H1−H3 = H0−H4, H0−H3) |
| Sec. V-C | Decaps power 6.54 → 7.00 mW | `results/power_windows.csv` (`P_mW`, H0 and H3) |
| Sec. V-C | XKyber −68 % of the lattice energy; Zbkb −27 % of the Keccak energy; Zbkb +8 % on the lattice code | `results/kernel_energy.csv` (H4, H1 over H0) |
| Sec. V-C | Keccak 64 % of the energy, 56 % of the cycles; 7.9 vs 5.8 mW | `results/kernel_energy.csv` (H3: `frac_keccak`, `cyc_keccak`/`cycles_decaps`, `P_keccak`, `P_lattice`) |
| Sec. V-C | CoreMark energy +8.4 % (Ser.), +0.9 % (Comb.); −2.1 % cycles (Comb.) | `results/power_windows.csv` (`set` = cm), `results/cycles.csv` (H3, H2 over H0) |

Other files in `results/`: `power_hier.csv` (power per block), `check_equivalence.csv` (gate-level
end cycle and KAT per run), `windows/` (the measurement windows, in RTL cycles) and `sw_md5.txt`.
`results/reports/` holds the post-route area reports (`hw/pnr/<ID>_2.0/reports/`), the power
reports per window and per block (`sim/power/<ID>_sdf_{ops,kern,cm}/`; `kern` is the set called
`kernels` here) and the RTL cycle profiles (`sim/rtl/`, `sim/windows/`).

## RTL folders

Each folder holds only the sources the flow reads: the RS5 core (`*.sv`, `aes/`, `vector/`) and
the `RingBuffer` it instantiates. The XKyber datapath is in `execute.sv` and in the multiplier
(`mul.sv` for the serialized realization, `ibex_multdiv_fast.sv` for the combinational one).

They come from the development history of RS5, with one fix each:

| Folder | Origin | Fix |
|---|---|---|
| `rtl_base` | RS5 commit `80a7c1d` | none |
| `rtl_comb` | RS5 commit `80a7c1d` | MULH/MULHSU signed mode in the `ibex_multdiv_fast` path (`execute.sv`) |
| `rtl_ser` | RS5 commit `4318713` | RV32M high multiply in the serialized XKyber multiplier (`mul.sv`) |

Both XKyber variants broke the standard RV32M high multiply: in the serialized core, `op_a` was
reloaded with the XKyber operand in the RV32M states, so MULH/MULHSU/MULHU returned wrong values;
in the combinational core, `multdiv_signed_mode_i` was hard-wired to unsigned, which broke MULH and
MULHSU. The ML-KEM software issues `mulhu` (division-free compression), so the unfixed cores fail
the KAT. Each fix restores the behaviour of the original RS5 multiplier without touching the XKyber
datapath; `sw/multest` checks it (`MULTEST=1 scripts/02_rtl_sim.sh all`).

## Flow, step by step

### 01: software (`scripts/01_build_sw.sh`, sources in `sw/`)

**ML-KEM-512 (FIPS 203).** The reference implementation of pq-crystals/kyber (`main` @ `3edd5af`)
was ported onto the RISC-V harness of the original Kyber code:

- KEM layer: keypair from d‖z, encapsulation without H(m) and KDF, decapsulation with implicit
  rejection J(z‖c) = SHAKE256(z‖c, 32);
- `(ρ,σ) = G(d‖k)` with k = 2;
- division-free compression (the KyberSlash fix), so the baseline is the current reference rather
  than `divu`.

With `KYBER_ISE` defined, `cbd`, `ntt`, `poly` and `polyvec` call the XKyber instructions through
inline assembly. Keccak-f1600 is `sha3_f1600_rvb32`, which uses Zbkb rotations and andn when built
for `zbkb`. The program runs KeyGen, Encaps and Decaps on the count-0 vector of
`sw/kat/PQCkemKAT_1632.rsp` and prints `[PASS]` six times (seed, pk, sk, ct, ss, ss after Decaps).

| Build | `-march` | Defines | Configurations |
|---|---|---|---|
| `base` | `rv32im_zicsr` | (none) | H0 |
| `zbkb` | `rv32im_zicsr_zbkb` | (none) | H1 |
| `xkyber` | `rv32im_zicsr` | `-DKYBER_ISE` | H4 |
| `both` | `rv32im_zicsr_zbkb` | `-DKYBER_ISE` | H2, H3 |

All four use `-Os`. The step also builds CoreMark (RV32IM `-O2`, `ITERATIONS=1`, no crypto code; it
measures what the extensions cost on ordinary code) and multest (optional RV32M check). The
source/link order is fixed in `sw/Makefile`, so the six binaries match `results/sw_md5.txt`.
`PREBUILT=1` copies `sw/prebuilt/` instead of compiling.

### 02: RTL simulation, profile and windows (`scripts/02_rtl_sim.sh`)

Verilator simulates the RTL folder with the ID's parameters and the RS5 testbench
(`scripts/tb/tb_rtl.sv`, RAM model `scripts/tb/RAM_mem.sv`). `scripts/tb/trace_bind.sv` writes one
line per instruction leaving execute: `<cycle> <pc> <instr> <cycles in execute>`. A cycle is a
rising clock edge counted from reset release, the same unit in RTL and gate-level runs. From the
trace:

- **Cycle profile** (`py/profile.py`): cycles of each operation, from the entry to the return of
  `pqcrystals_kyber512_ref_{keypair,enc,dec}`, split into seven kernel classes (Keccak permutation,
  sponge glue, NTT/polynomial arithmetic, sampling, compression/packing, memory/verify, other).
- **Power windows** (`$WORK/windows/`): `<ID>_ops.csv` (KeyGen, Encaps, Decaps); `<ID>_kernels.csv`
  (eight calls inside Decaps: the first, middle and last Keccak-f1600 permutations and the first
  call of `polyvec_ntt`, `polyvec_pointwise_acc_montgomery`, `polyvec_invntt_tomont`, `cbd_eta1`,
  `polyvec_compress`); `<ID>_cm.csv` (one CoreMark `iterate()` call).
- **Checks:** KAT 6/6, CoreMark "Correct operation validated"; with `MULTEST=1`, 0 multiply errors.

### 03: synthesis (`scripts/03_synth.sh`, `scripts/tcl/synth.tcl`)

Genus 21.1 physical synthesis (`syn_generic/syn_map/syn_opt -physical`, effort high, clock gating)
at 2.0 ns. The design is the RS5 top with the lean-core parameters plus the ID's
`MUL_TYPE/ZBKBEnable/XKYBEREnable`. The constraints (`scripts/tcl/constraints.sdc`, RS5's own with
only the period changed) apply the clock, a false path from `reset_n`, 0.1 ns input transition,
max fanout 1 on the inputs and a 500 fF output load. MMMC views: 0.81 V, 125 °C, RC worst (setup);
0.90 V, 25 °C, RC typical; 0.99 V, −40 °C, RC best (hold).

### 04: place and route (`scripts/04_pnr.sh`, `scripts/tcl/pnr.tcl`)

Innovus 21.1 (stylus): square core at 0.68 row utilization, routing on M2–M6, end caps and well
taps every 20 µm, VDD/VSS rings on M5/M6 with stripes every 25 µm; `place_opt_design`, tie cells;
CCOpt CTS and post-CTS hold fix; timing- and SI-driven routing with two post-route setup/hold
passes; fillers, ECO route, QRC extraction. Outputs: `RS5_postroute.v`, `RS5_typ.sdf` (typical
corner and RC), `RS5_typical.spef`, `RS5_postroute.sdc`, reports. Acceptance: setup WNS ≥ 0 at the
worst-case corner and hold WNS ≥ 0 at the best-case and typical corners; all five close at 2.0 ns.

### 05: delay-annotated gate-level simulation (`scripts/05_gl_sdf.sh`, `scripts/tb/tb_gl_sdf.sv`)

Xcelium simulates the routed netlist (plus the cell Verilog models) running the same binary as in
step 02.

- **Delays.** `xmsdfc` compiles `RS5_typ.sdf`, annotated on `testbench.dut` (`COMPILED_SDF_FILE`,
  `MTM_CONTROL = "TYPICAL"`), so every cell and wire switches with its extracted delay and the
  simulation contains the glitches. The simulator's inertial delay filters pulses shorter than a
  cell can propagate. Timing checks are off (timing is closed by STA in step 04). The run must
  report 100 % of the SDF path delays annotated.
- **Clock and inputs.** Clock period 2.0 ns at 1 ps precision; every DUT input is delayed by
  `IN_DLY_NS = 0.25` ns, because the RAM model answers at the clock edge while the DUT flip-flops see
  the clock after the CTS insertion delay (0.075–0.116 ns at tt).
- **Windows → SAIF.** `py/gl_runscript.py` converts each window to time, t(c) = t0 + c·T (t0 = first
  rising edge after reset release), and brackets it with `dumpsaif ... -depth to_cells -internal` /
  `dumpsaif -end`.
- **Acceptance** (`py/check_gl.py`): KAT 6/6 (or CoreMark validated) and the run ends in exactly the
  same cycle as the RTL run, so the RTL windows select the same work.

### 06: power (`scripts/06_power.sh`, `scripts/tcl/power.tcl`)

Genus 21.1 loads the routed netlist, `RS5_postroute.sdc`, the extracted parasitics and the
typical-corner library (0.90 V, 25 °C), reads the SAIF of each window
(`read_stimulus -dut_instance testbench.dut`) and writes `power_<window>.rpt` (leakage, internal,
switching by category) and `power_<window>_hier.rpt` (per block). The SAIF must annotate 100 % of
the net drivers. Genus is used rather than Innovus/Voltus because it maps the whole flat Xcelium
SAIF; Innovus annotated about 11 %.

### 07: analysis (`scripts/07_analyze.sh`)

- **Energy per window:** E[µJ] = P[mW] × cycles × 2·10⁻⁶ (`py/collect_power.py`).
- **Decaps energy by kernel** (`py/kernel_energy.py`): P_keccak and P_lattice are the cycle-weighted
  mean powers of the sampled Keccak and NTT/pointwise/inverse-NTT calls; times the cycles of each
  class (Keccak = permutation + sponge glue; lattice = NTT/polynomial arithmetic) they give E_keccak
  and E_lattice; E_rest is the measured Decaps energy minus both.
- **Comparison with `results/`** (`py/compare_ref.py`): exact for binaries, cycles, windows, cell
  counts and end cycles; 0.5 % relative tolerance for area, leakage, power and energy. Exit status
  1 if anything differs.

Outputs in `$WORK`: `sw/`, `rtl_sim/<ID>_{kat,coremark}/`, `windows/`, `synth/<ID>/`, `pnr/<ID>/`,
`gl/<ID>_<set>/`, `power/<ID>_<set>/`, `results/*.csv`, `logs/`.

Optional, not used in the paper: `KAT_COUNTS="1 2 ..."` (step 01) and `KAT_COUNT=k` (steps 02 and
05) run the ML-KEM programs on other vectors of the KAT file.

## Notes

- **Provenance.** The paper's numbers come from an earlier campaign with the same tools, scripts and
  operating point; `results/reports/` keeps its reports. This package was then rerun from scratch
  (all five configurations, steps 01–07): netlists, post-route reports and power reports identical
  to the campaign, 1216 values compared, 0 differences.
- **Pitfalls met during the campaign.** Xcelium ignored `SDF_FILE` in the SDF command file; the
  compiled SDF (`COMPILED_SDF_FILE`) works. The SAIF must be dumped from and read at
  `testbench.dut`, or the annotation silently drops. The energy period must equal the simulated
  clock (`PERIOD_NS` drives both). Concurrent Verilator builds of one model corrupt it (step 02 uses
  `flock`). `$(wildcard)` link order depends on the file system (`sw/Makefile` lists the sources).
  Genus/Innovus temporary files go to `$WORK/tmp`, not `/tmp`.

## Limitations

- Power is computed at the typical corner (0.90 V, 25 °C) with typical RC parasitics; the SDF comes
  from the same view. There is no IR-drop analysis.
- The Decaps split by kernel uses sampled calls (Keccak: three permutations, which differ by about
  ±2 %; lattice: one call of each function); the rest is the residual, and the power it implies
  (5.6–5.9 mW) is consistent with the measured windows.
- The combinational realization (H2) also replaces the base multiplier (`ibex_multdiv_fast`), so H2
  vs H3 compares complete realizations, not only the XKyber logic.
- The software is the `-Os` reference C code without optimized assembly; the relative gains hold
  for that baseline.
- A few (3–10) DRC violations remain on power-grid vias after routing; they do not affect the
  netlist, the SPEF or the SDF.

## License

RS5 and this flow are under the MIT license (`LICENSE`); `RingBuffer` is MIT (GAPH, its `LICENSE` in
each `rtl_*/RingBuffer/`); `ibex_multdiv_fast.sv` is Apache-2.0 (lowRISC, header in the file).
Third-party software keeps its original headers and terms: the pq-crystals Kyber reference
(`sw/common/mlkem_ref`), the riscv-crypto benchmark code by PQShield (`sw/common/keccak`,
`sw/common/include/rvk_*`, `riscv_crypto*.h`, `test_rvkat*`), Intel TinyCrypt
(`sw/common/tinycrypt`), the lowRISC simple-system support code, and EEMBC CoreMark (`sw/coremark`,
see its `LICENSE.md`). The standard-cell library is not distributed.
