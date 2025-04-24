cfile = 'logs/c/xxx.txt'
pyfile = 'logs/py/cout_relu.txt'
outfile = 'logs/zzz.txt'

def subtract_files(file1, file2, output_file):
    # Read values from first file
    with open(file1, 'r') as f1:
        x_values = [float(line.strip()) for line in f1]

    # Read values from second file
    with open(file2, 'r') as f2:
        y_values = [float(line.strip().rstrip(',')) for line in f2]

    # Check if both files have the same number of lines
    if len(x_values) != len(y_values):
        raise ValueError("Input files must have the same number of lines.")

    # Compute differences and write to output file
    with open(output_file, 'w') as out:
        for x, y in zip(x_values, y_values):
            out.write(f"{x - y:.8f}\n")

# Example usage
subtract_files(cfile, pyfile, outfile)