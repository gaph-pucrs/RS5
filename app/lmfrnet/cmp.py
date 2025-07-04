import sys
import subprocess
import numpy as np

MULTIP = 10000

def main():
    if len(sys.argv) < 2:
        print("Usage: python process_file.py <filename>")
        sys.exit(1)

    input_filename = "cmp/c/" + sys.argv[1] + ".txt"
    output_filename = input_filename

    try:
        # Generate data
        print(f"[!] Generating input file: ./model.bin > {input_filename}")
        with open(input_filename, 'w') as f:
            subprocess.run(['./model.bin'], stdout=f, check=True)

        # Read values from the input file
        with open(input_filename, 'r') as f:
            values = [float(line.strip()) for line in f if line.strip()]

        # Convert to numpy array
        v = np.array(values)

        # Transform the array
        v = v / MULTIP

        # Write to output file
        with open(output_filename, 'w') as f:
            for value in v:
                f.write(f"{value}\n")

        print(f"[+] Quantized data for compare generated in {output_filename}")

        print(f"[!] Executing: python3 err.py {sys.argv[1]}")
        subprocess.run(['python3', 'err.py', sys.argv[1]], check=True)
        
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()

