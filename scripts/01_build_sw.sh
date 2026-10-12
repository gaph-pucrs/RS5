#!/bin/bash
# 01_build_sw.sh -- build the benchmark binaries with riscv64-elf-gcc 15.2.0.
#   ML-KEM-512 (FIPS 203) KAT program, RV32IM + Zicsr, -Os, one build per ISA combination:
#     base   -march=rv32im_zicsr                     (H0)
#     zbkb   -march=rv32im_zicsr_zbkb                (H1)   Keccak with Zbkb rotates/andn
#     xkyber -march=rv32im_zicsr + -DKYBER_ISE       (H4)   lattice kernels with XKyber instructions
#     both   -march=rv32im_zicsr_zbkb + -DKYBER_ISE  (H2, H3)
#   The XKyber builds use the six XKyber mnemonics in inline assembly (sw/common/mlkem_ref), so the
#   assembler must know them (GAPH build of binutils). Without such an assembler, PREBUILT=1 copies
#   the paper's binaries from sw/prebuilt/ instead of compiling (same md5 as results/sw_md5.txt).
#   multest (optional conformance test of mul/mulh/mulhsu/mulhu), RV32IM -Os
#   CoreMark, RV32IM -O2, ITERATIONS=1                (all IDs)
# Each program prints its result on the RS5 testbench console (KAT: 6 x [PASS]).
# Optional: KAT_COUNTS="1 2 ..." also builds the four ML-KEM programs for other official KAT vectors
#   (-DKAT_COUNT=k, see sw/kat/ and py/gen_kat_header.py) as <build>_k<k>, for the input-variability
#   runs (not used in the paper). Count 0 (the default build) is the vector used in the paper.
# Usage: [PREBUILT=1] [KAT_COUNTS="1 2 ..."] 01_build_sw.sh
# Output: $WORK/sw/<build>/app.{bin,elf,lst,nm} (+ flags.txt when compiled), $WORK/sw/MD5SUMS
source "$(dirname "$0")/common.sh"
OUT=$WORK/sw
start_run "$OUT"

if [ "${PREBUILT:-0}" = 1 ]; then
    echo "# PREBUILT=1: binaries copied from $REPRO/sw/prebuilt" >> "$OUT/cmd.txt"
    for d in "$REPRO"/sw/prebuilt/*/; do
        b=$(basename "$d"); mkdir -p "$OUT/$b"; cp "$d"app.* "$OUT/$b/"
    done
    ( cd "$OUT" && md5sum ./*/app.bin | sed 's|  \./|  |' > MD5SUMS )
    info "software copied from sw/prebuilt:"; cat "$OUT/MD5SUMS"
    exit 0
fi

load_tool "$MOD_RISCV" || die "riscv64-elf toolchain not available (or run with PREBUILT=1)"
echo "# $(riscv64-elf-gcc --version | head -1)" >> "$OUT/cmd.txt"
echo 'kybermul a0, a1, a2' | riscv64-elf-as -march=rv32im -o /dev/null - 2>/dev/null \
    || die "riscv64-elf-as does not know the XKyber instructions; use an XKyber-enabled binutils or PREBUILT=1"

build() {   # build <name> <ARCH> <SRC> [EXTRA_DEFS]
    local cmd=(make -C "$REPRO/sw" NAME="$1" ARCH="$2" SRC="$3" BUILD_DIR="$OUT" EXTRA_DEFS="${4:-}")
    echo "${cmd[*]}" >> "$OUT/cmd.txt"
    "${cmd[@]}" > "$OUT/build_$1.log" 2>&1 || die "build $1 failed, see $OUT/build_$1.log"
}
build base   rv32im_zicsr             kyber/src
build zbkb   rv32im_zicsr_zbkb        kyber/src
build xkyber rv32im_zicsr_xkyber      kyber/src
build both   rv32im_zicsr_zbkb_xkyber kyber/src
build multest rv32im_zicsr            multest/src
for k in ${KAT_COUNTS:-}; do
    [ "$k" = 0 ] && continue
    build base_k$k   rv32im_zicsr             kyber/src -DKAT_COUNT=$k
    build zbkb_k$k   rv32im_zicsr_zbkb        kyber/src -DKAT_COUNT=$k
    build xkyber_k$k rv32im_zicsr_xkyber      kyber/src -DKAT_COUNT=$k
    build both_k$k   rv32im_zicsr_zbkb_xkyber kyber/src -DKAT_COUNT=$k
done

# CoreMark: built out of tree (its Makefile writes next to the sources)
rm -rf "$OUT/coremark_src"; cp -r "$REPRO/sw/coremark" "$OUT/coremark_src"
echo "make -C $OUT/coremark_src" >> "$OUT/cmd.txt"
make -C "$OUT/coremark_src" > "$OUT/build_coremark.log" 2>&1 || die "CoreMark build failed"
mkdir -p "$OUT/coremark"
cp "$OUT/coremark_src/coremark.bin" "$OUT/coremark/app.bin"
cp "$OUT/coremark_src/coremark.elf" "$OUT/coremark/app.elf"
cp "$OUT/coremark_src/coremark.lst" "$OUT/coremark/app.lst"
riscv64-elf-nm -S -n "$OUT/coremark/app.elf" > "$OUT/coremark/app.nm"

( cd "$OUT" && md5sum ./*/app.bin | sed 's|  \./|  |' > MD5SUMS )
info "software built:"; cat "$OUT/MD5SUMS"
