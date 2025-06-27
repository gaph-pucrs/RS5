import sys

base = 'cmp/'

def cmp(file1, file2):
    err = 0
    with open(file1, 'r') as f1:
        x_values = [float(line.strip()) for line in f1]

    with open(file2, 'r') as f2:
        y_values = [float(line.strip().rstrip(',')) for line in f2]

    if len(x_values) != len(y_values):
        raise ValueError("Input files must have the same number of lines.")

    for x, y in zip(x_values, y_values):
        err = max(err, abs(x-y))

    print(f"error: {err}")


if len(sys.argv) > 1:
    f = sys.argv[1]
    cfile = base + 'c/' + f + '.txt'
    pyfile = base + 'py/' + f + '.txt'
    cmp(cfile, pyfile)
else:
    print(f"Usage: python err.py <filename>")
