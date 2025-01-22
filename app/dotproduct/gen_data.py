import os
import sys
import numpy as np

def generate_random_arrays(n):
    """Generates random numbers for 32-bit, 16-bit, and 8-bit arrays."""
    """v32a = np.random.randint(-2**(20), high=2**(20)-1, size=n, dtype=np.int32)"""
    """v32b = np.random.randint(-2**(20), high=2**(20)-1, size=n, dtype=np.int32)"""
    """v16a = np.random.randint(-2**(10), high=2**(10)-1, size=n, dtype=np.int16)"""
    """v16b = np.random.randint(-2**(10), high=2**(10)-1, size=n, dtype=np.int16)"""
    """v8a  = np.random.randint( -2**(2), high=2**(2)-1,  size=n, dtype=np.int8)"""
    """v8b  = np.random.randint( -2**(2), high=2**(2)-1,  size=n, dtype=np.int8)"""
    v32a = np.random.randint(-100, high=100, size=n, dtype=np.int32)
    v32b = np.random.randint(-100, high=100, size=n, dtype=np.int32)
    v16a = np.random.randint(-100, high=100, size=n, dtype=np.int16)
    v16b = np.random.randint(-100, high=100, size=n, dtype=np.int16)
    v8a  = np.random.randint(-100, high=100, size=n, dtype=np.int8)
    v8b  = np.random.randint(-100, high=100, size=n, dtype=np.int8)
    return v32a, v32b, v16a, v16b, v8a, v8b

def write_header_file(filepath, v32a, v32b, v16a, v16b, v8a, v8b):
    """Writes the generated arrays to a header file."""
    with open(filepath, 'w') as file:
        file.write("// data.h\n")
        file.write("// Generated file containing random test data\n\n")
        file.write("#ifndef DATA_H\n")
        file.write("#define DATA_H\n\n")

        file.write(f"const int32_t v32a[{len(v32a)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in v32a))
        file.write("\n};\n\n")

        file.write(f"const int32_t v32b[{len(v32b)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in v32b))
        file.write("\n};\n\n")

        file.write(f"const int16_t v16a[{len(v16a)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in v16a))
        file.write("\n};\n\n")

        file.write(f"const int16_t v16b[{len(v16b)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in v16b))
        file.write("\n};\n\n")

        file.write(f"const int8_t v8a[{len(v8a)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in v8a))
        file.write("\n};\n\n")

        file.write(f"const int8_t v8b[{len(v8b)}] = {{\n")
        file.write(",\n".join(f"    {num}" for num in v8b))
        file.write("\n};\n\n")

        file.write("#endif\n")

def main():
    if len(sys.argv) != 2:
        print("Usage: python gen_data.py <N>")
        sys.exit(1)

    try:
        n = int(sys.argv[1])
        if n <= 0:
            raise ValueError
    except ValueError:
        print("N must be a positive integer.")
        sys.exit(1)

    # Generate random data
    v32a, v32b, v16a, v16b, v8a, v8b = generate_random_arrays(n)

    # Write the data to a header file
    write_header_file("./src/data.h", v32a, v32b, v16a, v16b, v8a, v8b)

    print(f"Generated ./src/data.h with {n} random numbers in each array.")

if __name__ == "__main__":
    main()
