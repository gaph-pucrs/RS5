import os
import sys
import numpy as np

def rand_array(N, dtype):
    return np.random.randint(0, 256, N, dtype)

def rand_sel(N, dtype):
    return np.random.randint(0, 256, N, dtype)

def write_header_file(filepath, N, I, SCALE, SEL, O, O_GOLD):
    """Writes the generated arrays to a header file."""
    with open(filepath, 'w') as file:
        file.write("// data.h\n")
        file.write("// Generated file containing random test data\n\n")
        file.write("#ifndef DATA_H\n")
        file.write("#define DATA_H\n\n")

        file.write(f"const unsigned int N = {N};\n\n")

        file.write(f"const int SCALE = {SCALE};\n\n")

        file.write(f"const int I[{len(I)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in I))
        file.write("\n};\n\n")

        file.write(f"const uint8_t SEL[{len(SEL)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in SEL))
        file.write("\n};\n\n")

        file.write(f"int o[{len(O)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in O))
        file.write("\n};\n\n")

        file.write(f"int o_gold[{len(O_GOLD)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in O_GOLD))
        file.write("\n};\n\n")

        file.write("#endif\n")

def main():
    if len(sys.argv) != 2:
        print("Usage: python gen_data.py <N>")
        N = 8192
    else:
        try:
            N = int(sys.argv[1])
            if N <= 0:
                raise ValueError
        except ValueError:
            print("N must be a positive integer.")
            sys.exit(1)

    # Generate random data
    # Generate inputs
    I     = rand_array(N, np.int32)
    SCALE = rand_array(1, np.int32)[0]
    SEL   = rand_sel(N, np.uint8)

    # Create the empty o matrix
    o = np.zeros(N).astype(np.int32)
    o_gold = o

    # Write the data to a header file
    script_dir = os.path.dirname(os.path.abspath(__file__))
    header_file_path = os.path.join(script_dir, "../src/data.h")
    write_header_file(header_file_path, N, I, SCALE, SEL, o, o_gold)

    print(f"Generated data.h with {N} random numbers in each array.")

if __name__ == "__main__":
    main()