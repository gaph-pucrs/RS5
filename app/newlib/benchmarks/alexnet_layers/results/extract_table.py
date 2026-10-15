#!/usr/bin/env python3
"""
Extract AlexNet layer timing data from result files and generate a LaTeX table.

Columns: conv layer, VLEN, channels, avg cycles/ch, conv cycles,
         relu cycles, maxpool cycles, total cycles.

Overflow handling:
  - Negative values are treated as signed 32-bit overflows and converted to
    unsigned (add 2^32).
  - After conversion, if conv+relu+maxpool differs from total by more than
    TOLERANCE, a true 32-bit accumulator overflow is suspected and signalled
    with a dagger marker (†) on the affected row.
"""

import re
import os
import sys

RESULTS_DIR = os.path.dirname(os.path.abspath(__file__))

LAYERS = ['conv1', 'conv2', 'conv3', 'conv4', 'conv5', 'fc']

# (file_key, display_label)
CONFIGS = [
    ('scalar',  'Scalar'),
    ('vlen64',  '64'),
    ('vlen128', '128'),
    ('vlen256', '256'),
]

UINT32 = 1 << 32
TOLERANCE = 0.01  # 1 % relative tolerance for consistency check


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def to_u32(val: int) -> int:
    """Reinterpret a signed 32-bit value as unsigned."""
    return val + UINT32


def fmt(n, dagger=False, speedup=None) -> str:
    """Format a number normalized to 10^6 (2 decimal places)."""
    n = float(n)
    s = rf'${n / 1e6:.2f}$'
    s += r'$^\dagger$' if dagger else ''
    if speedup is not None:
        s += rf' $({speedup:.2f}\times)$'
    return s


def fmt_float(n, dagger=False, speedup=None) -> str:
    """Format a float normalized to 10^6 (2 decimal places)."""
    return fmt(n, dagger, speedup)


# ---------------------------------------------------------------------------
# Parser
# ---------------------------------------------------------------------------

def parse_fc_file(filepath: str):
    """
    Parse an FC layer result file.

    Sums matmul+bias and ReLU cycles across FC6/FC7/FC8 sub-layers and reads
    the grand total.  Returns a dict compatible with the conv layer dict, with
    num_channels and avg_cycles set to None (not applicable for FC).
    """
    if not os.path.exists(filepath):
        return None

    try:
        with open(filepath, 'r') as fh:
            content = fh.read()
    except OSError as exc:
        print(f'Warning: cannot read {filepath}: {exc}', file=sys.stderr)
        return None

    matmul_matches = re.findall(r'FC\d+\s+matmul\+bias\s*:\s*(-?\d+)\s*cycles', content)
    relu_matches   = re.findall(r'FC\d+\s+ReLU\s*:\s*(-?\d+)\s*cycles', content)
    total_m        = re.search(r'Total fc layers\s*:\s*(-?\d+)\s*cycles', content)

    if not matmul_matches or total_m is None:
        return None

    def cvt(v):
        return to_u32(v) if v < 0 else v

    matmul_c = sum(cvt(int(v)) for v in matmul_matches)
    relu_c   = sum(cvt(int(v)) for v in relu_matches)
    total_c  = cvt(int(total_m.group(1)))

    computed = matmul_c + relu_c
    overflow_32bit = False
    if total_c > 0:
        if abs(computed - total_c) / total_c > TOLERANCE:
            overflow_32bit = True
    elif computed > 0:
        overflow_32bit = True

    return {
        'num_channels': None,   # not applicable
        'avg_cycles':   None,   # not applicable
        'conv_cycles':  matmul_c,
        'relu_cycles':  relu_c,
        'mpool_cycles': 0,
        'total_cycles': total_c,
        'neg_fields':   [],
        'overflow_32b': overflow_32bit,
    }


def parse_file(filepath: str):
    """
    Parse a simulation result file.

    Returns a dict with timing data, or None if the file is missing or
    contains no timing data.
    """
    if not os.path.exists(filepath):
        return None

    try:
        with open(filepath, 'r') as fh:
            content = fh.read()
    except OSError as exc:
        print(f'Warning: cannot read {filepath}: {exc}', file=sys.stderr)
        return None

    # Per-channel cycles: (channel_id, cycles)
    ch_pattern = re.compile(r'\(\s*\d+\s*,\s*(-?\d+)\s*\)')
    raw_ch_cycles = [int(m) for m in ch_pattern.findall(content)]

    if not raw_ch_cycles:
        return None  # Simulation did not produce timing output

    # Convert any negative per-channel values (unlikely but handle anyway)
    ch_cycles = [to_u32(c) if c < 0 else c for c in raw_ch_cycles]
    num_channels = len(ch_cycles)
    avg_cycles = sum(ch_cycles) / num_channels

    # Summary totals
    conv_m  = re.search(r'Total conv\+bias\s*:\s*(-?\d+)\s*cycles', content)
    relu_m  = re.search(r'ReLU\s*:\s*(-?\d+)\s*cycles', content)
    mpool_m = re.search(r'MaxPool\s*:\s*(-?\d+)\s*cycles', content)
    total_m = re.search(r'Total layer\s*:\s*(-?\d+)\s*cycles', content)

    # MaxPool is optional (conv3/4/5 have no pooling layer)
    if not all([conv_m, relu_m, total_m]):
        return None

    raw_conv  = int(conv_m.group(1))
    raw_relu  = int(relu_m.group(1))
    raw_mpool = int(mpool_m.group(1)) if mpool_m else 0
    raw_total = int(total_m.group(1))

    # Convert negative values (signed → unsigned 32-bit)
    neg_fields = []
    def cvt(key, v):
        if v < 0:
            neg_fields.append(key)
            return to_u32(v)
        return v

    conv_c  = cvt('conv',    raw_conv)
    relu_c  = cvt('relu',    raw_relu)
    mpool_c = cvt('maxpool', raw_mpool)
    total_c = cvt('total',   raw_total)

    # Consistency check: does conv + relu + maxpool ≈ total?
    computed = conv_c + relu_c + mpool_c
    overflow_32bit = False
    if total_c > 0:
        if abs(computed - total_c) / total_c > TOLERANCE:
            overflow_32bit = True
    elif computed > 0:
        overflow_32bit = True

    return {
        'num_channels': num_channels,
        'avg_cycles':   avg_cycles,
        'conv_cycles':  conv_c,
        'relu_cycles':  relu_c,
        'mpool_cycles': mpool_c,
        'total_cycles': total_c,
        'neg_fields':   neg_fields,   # fields that were negative and converted
        'overflow_32b': overflow_32bit,
    }


# ---------------------------------------------------------------------------
# LaTeX generation
# ---------------------------------------------------------------------------

def generate_latex(data: dict) -> str:
    header = r"""% AlexNet convolutional layer timing results
% Requires: booktabs, multirow, siunitx (or just compile as-is)
% Dagger ($^\dagger$) marks rows where a 32-bit accumulator overflow is
% suspected (converted values are unreliable).
\begin{table}[htbp]
  \centering
  \caption{AlexNet Convolutional Layer Timing Results}
  \label{tab:alexnet-timing}
  \resizebox{\textwidth}{!}{%
  \begin{tabular}{|l|l|l|c|c|c|c|c|}
    \hline
    \textbf{Layer} & \textbf{Channels} & \textbf{VLEN} &
    \textbf{Avg Cyc./Ch. ($\times 10^6$)} & \textbf{Conv/Matmul+Bias ($\times 10^6$ cyc.)} &
    \textbf{ReLU ($\times 10^6$ cyc.)} & \textbf{MaxPool ($\times 10^6$ cyc.)} &
    \textbf{Total ($\times 10^6$ cyc.)} \\
    \hline\hline"""

    footer = r"""  \end{tabular}
  }\\[4pt]
\end{table}"""

    rows = [header]

    for layer in LAYERS:
        layer_rows = data[layer]
        n_rows = len(layer_rows)
        layer_label = layer.upper().replace('CONV', r'Conv~')

        # Determine channel count from any available data row (same for all configs)
        is_fc = (layer == 'fc')
        num_ch = next((d['num_channels'] for _, d in layer_rows if d is not None), None)
        if is_fc:
            ch_cell = r'---'
        else:
            ch_cell = str(num_ch) if num_ch is not None else r'\textit{N/A}'

        # Scalar data is the baseline for per-operation speedup (first config = scalar)
        scalar_d = layer_rows[0][1]

        def op_speedup(scalar_val, current_val):
            """Return speedup ratio or None if unavailable."""
            if scalar_val and current_val:
                return scalar_val / current_val
            return None

        for idx, (cfg_label, d) in enumerate(layer_rows):
            # Col 1: layer name (multirow)
            layer_col = (f'    \\multirow{{{n_rows}}}{{*}}{{{layer_label}}}'
                         if idx == 0 else '    ')
            # Col 2: channels (multirow)
            ch_col = (f'\\multirow{{{n_rows}}}{{*}}{{{ch_cell}}}'
                      if idx == 0 else '')

            if d is None:
                row = (f'{layer_col} & {ch_col} & {cfg_label} & '
                       r'\multicolumn{5}{c|}{\textit{N/A}} \\')
            else:
                dag = d['overflow_32b']
                is_scalar = (idx == 0) or scalar_d is None or dag

                sp_avg   = None if (is_scalar or d['avg_cycles'] is None) else op_speedup(scalar_d['avg_cycles'],   d['avg_cycles'])
                sp_conv  = None if is_scalar else op_speedup(scalar_d['conv_cycles'],  d['conv_cycles'])
                sp_relu  = None if is_scalar else op_speedup(scalar_d['relu_cycles'],  d['relu_cycles'])
                sp_mpool = None if is_scalar else op_speedup(scalar_d['mpool_cycles'], d['mpool_cycles'])
                sp_total = None if is_scalar else op_speedup(scalar_d['total_cycles'], d['total_cycles'])

                avg_cell  = (r'---' if d['avg_cycles'] is None
                             else fmt_float(d['avg_cycles'], dag, sp_avg))
                mpool_cell = (r'---' if is_fc
                              else fmt(d['mpool_cycles'], False, sp_mpool))

                row = (
                    f'{layer_col} & {ch_col} & {cfg_label}'
                    f' & {avg_cell}'
                    f' & {fmt(d["conv_cycles"],  dag, sp_conv)}'
                    f' & {fmt(d["relu_cycles"],  False, sp_relu)}'
                    f' & {mpool_cell}'
                    f' & {fmt(d["total_cycles"], dag, sp_total)}'
                    r' \\'
                )

            rows.append(row)

        rows.append('    \\hline')

    return '\n'.join(rows)


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main():
    data = {}

    for layer in LAYERS:
        layer_rows = []
        for cfg_key, cfg_label in CONFIGS:
            filename = 'scalar.txt' if cfg_key == 'scalar' else f'{cfg_key}.txt'
            filepath = os.path.join(RESULTS_DIR, layer, filename)
            result = parse_fc_file(filepath) if layer == 'fc' else parse_file(filepath)

            if result is None:
                status = 'no data'
            elif result['overflow_32b']:
                status = '32-bit OVERFLOW'
            elif result['neg_fields']:
                status = f'neg→u32: {result["neg_fields"]}'
            else:
                status = 'ok'

            print(f'  {layer}/{cfg_key}: {status}', file=sys.stderr)
            layer_rows.append((cfg_label, result))

        data[layer] = layer_rows

    latex = generate_latex(data)
    print(latex)

    out_path = os.path.join(RESULTS_DIR, 'alexnet_table.tex')
    with open(out_path, 'w') as fh:
        fh.write(latex)
        fh.write('\n')
    print(f'\nSaved → {out_path}', file=sys.stderr)


if __name__ == '__main__':
    main()
