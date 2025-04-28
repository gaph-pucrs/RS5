import sys

base = 'logs/'

def cmp(file1, file2, output_file):
    with open(file1, 'r') as f1:
        x_values = [float(line.strip()) for line in f1]

    with open(file2, 'r') as f2:
        y_values = [float(line.strip().rstrip(',')) for line in f2]

    if len(x_values) != len(y_values):
        raise ValueError("Input files must have the same number of lines.")

    with open(output_file, 'w') as out:
        for x, y in zip(x_values, y_values):
            out.write(f"{x - y:.8f}\n")


# cfile = 'logs/c/cout_conv1_relu.txt'
# pyfile = 'logs/py/cout_conv1_relu.txt'
# outfile = 'logs/cmp/cout_conv1_relu.txt'

if len(sys.argv) > 1:
    f = sys.argv[1]
    cfile = base + 'c/' + f + '.txt'
    pyfile = base + 'py/' + f + '.txt'
    out = base + 'cmp/' + f + '.txt'
    cmp(cfile, pyfile, out)
else:
    print(f"Usage: python err.py <filename>")