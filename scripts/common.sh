# common.sh -- sourced by every step script. Loads scripts/config/repro.env and defines helpers.
# REPRO is the root of the package (the directory that holds rtl_*/, sw/, scripts/, results/).
# shellcheck shell=bash
set -u -o pipefail

REPRO=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
export REPRO
# shellcheck source=config/repro.env
source "$REPRO/scripts/config/repro.env"
mkdir -p "$WORK"
WORK=$(cd "$WORK" && pwd); export WORK
mkdir -p "$REPRO_TMPDIR" && export TMPDIR=$REPRO_TMPDIR

ALL_IDS="H0 H1 H2 H3 H4"
# Lean RV32IM+Zicsr core shared by all configurations (Genus top parameters / Verilator defines).
LEAN_GENUS='{COMPRESSED 0} {ZKNEEnable 0} {ZKNHEnable 0} {ZICONDEnable 0} {ZCBEnable 0} {HPMCOUNTEREnable 0} {AMOEXT 0}'
LEAN_VERILATOR='+define+V_COMPRESSED=0 +define+V_ZKNE=0 +define+V_ZKNH=0'

die()  { echo "ERROR: $*" >&2; exit 1; }
info() { echo "[$(date +%H:%M:%S)] $*"; }

# cfg <ID> <column>: column of scripts/config/configs.tsv (tree genus verilator sw desc)
cfg() {
    local col
    case $2 in tree) col=2;; genus) col=3;; verilator) col=4;; sw) col=5;; desc) col=6;;
               *) die "cfg: unknown column $2";; esac
    local v
    v=$(awk -F'\t' -v id="$1" -v c=$col '$1 == id {print $c}' "$REPRO/scripts/config/configs.tsv")
    [ -n "$v" ] || die "unknown configuration ID '$1' (expected one of: $ALL_IDS)"
    echo "$v"
}

# expand "all" into the list of IDs
ids() { if [ "${1:-all}" = all ]; then echo "$ALL_IDS"; else echo "$*"; fi; }

md5() { md5sum "$1" | cut -c1-32; }

# start_run <out_dir>: create the run directory and the provenance header of cmd.txt
start_run() {
    mkdir -p "$1"
    {
        echo "# $(date -Is) host=$(hostname) user=${USER:-?}"
        echo "# step=$(basename "$0") md5=$(md5 "$0") repro=$REPRO"
        echo "# PERIOD_NS=$PERIOD_NS IN_DLY_NS=$IN_DLY_NS pdk_env=$PDK_ENV${PDK_ENV_MD5:+ md5=$PDK_ENV_MD5}"
    } > "$1/cmd.txt"
}

# need_pdk: load scripts/config/pdk.env (library files and cell names, site-local) and check it.
# Called by the steps that use the standard-cell library (03-06).
need_pdk() {
    [ -f "$PDK_ENV" ] || die "$PDK_ENV missing: cp scripts/config/pdk.env.example scripts/config/pdk.env and fill it in"
    # shellcheck disable=SC1090
    source "$PDK_ENV"
    PDK_ENV_MD5=$(md5 "$PDK_ENV")
    local v
    for v in LIB_SS LIB_TT LIB_FF LEF_TECH LEF_CELLS QRC_WORST QRC_TYP QRC_BEST CELLS_VERILOG; do
        [ -n "${!v:-}" ] && [ -f "${!v}" ] || die "pdk.env: $v='${!v:-}' is not a file"
    done
    for v in ENDCAP_LEFT ENDCAP_RIGHT WELLTAP_CELL TIE_CELLS FILLER_CELLS CTS_BUF_CELLS CTS_INV_CELLS \
             CTS_ICG_CELLS CLK_BUF_PATTERNS ICG_PATTERN; do
        [ -n "${!v:-}" ] && [[ ${!v} != *'<'* ]] || die "pdk.env: $v is not set"
    done
}

# rtl_dir <ID>: RTL folder of the configuration (rtl_base, rtl_comb or rtl_ser)
rtl_dir() {
    local d=$REPRO/rtl_$(cfg "$1" tree)
    [ -f "$d/RS5.sv" ] || die "$d: RTL folder missing"
    echo "$d"
}

# rtl_md5 <rtl dir>: md5 of all its sources (relative path + content), identifies the RTL version
rtl_md5() {
    ( cd "$1" && find . -name '*.sv' | LC_ALL=C sort | xargs md5sum | md5sum | cut -c1-32 )
}

# tree_info <rtl dir>: one provenance line
tree_info() {
    echo "rtl_root=$1 rtl_md5=$(rtl_md5 "$1")"
}

# timed <out_dir> <cmd...>: run cmd with stdout/stderr to <out_dir>/stdout.log, write runtime.txt
timed() {
    local out=$1; shift
    local t0 rc
    t0=$(date +%s)
    "$@" > "$out/stdout.log" 2>&1 < /dev/null
    rc=$?
    echo "rc=$rc wall_s=$(( $(date +%s) - t0 ))" > "$out/runtime.txt"
    return $rc
}

# status <out_dir> <OK|FAIL> [message]: append status to runtime.txt and print it
status() {
    echo "status=$2${3:+ $3}" >> "$1/runtime.txt"
    info "$(basename "$1"): $2${3:+ ($3)} [$(head -1 "$1/runtime.txt")]"
    [ "$2" = OK ]
}
