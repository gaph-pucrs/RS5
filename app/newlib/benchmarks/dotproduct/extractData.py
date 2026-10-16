import os
import re
import numpy as np
from pathlib import Path

def extract_data_from_files(results_folder='results'):
    """
    Extract vector data from files named vlenX_mY.txt
    Returns a numpy array ordered by AVL, SEW, VLEN
    """
    data_list = []
    scalar_data_extracted = False

    # Pattern to match filename: vlenX_mY.txt
    filename_pattern = re.compile(r'vlen(\d+)_m(\d+)\.txt')

    # Pattern to match data lines: VECTOR Xb - AVL = Y, cycles = Z
    vector_pattern = re.compile(r'VECTOR\s+(\d+)b\s*-\s*AVL\s*=\s*(\d+),\s*cycles\s*=\s*(\d+)')

    # Pattern to match scalar lines: SCALAR Xb - AVL = Y, cycles = Z
    scalar_pattern = re.compile(r'SCALAR\s+(\d+)b\s*-\s*AVL\s*=\s*(\d+),\s*cycles\s*=\s*(\d+)')

    # Iterate through files in the results folder
    results_path = Path(results_folder)

    if not results_path.exists():
        raise FileNotFoundError(f"Results folder '{results_folder}' not found")

    for file_path in results_path.glob('vlen*_m*.txt'):
        filename = file_path.name

        # Extract VLEN and LMUL from filename
        filename_match = filename_pattern.match(filename)
        if not filename_match:
            continue

        vlen = int(filename_match.group(1))
        lmul = int(filename_match.group(2))

        # Read file and extract data
        with open(file_path, 'r') as f:
            for line in f:
                # Extract VECTOR data
                vector_match = vector_pattern.search(line)
                if vector_match:
                    sew = int(vector_match.group(1))
                    avl = int(vector_match.group(2))
                    cycles = int(vector_match.group(3))

                    # Append as [AVL, SEW, VLEN, LMUL, cycles]
                    data_list.append([avl, sew, vlen, lmul, cycles])

                # Extract SCALAR data (only from first file)
                if not scalar_data_extracted:
                    scalar_match = scalar_pattern.search(line)
                    if scalar_match:
                        sew = int(scalar_match.group(1))
                        avl = int(scalar_match.group(2))
                        cycles = int(scalar_match.group(3))

                        # Append with VLEN=0, LMUL=0
                        data_list.append([avl, sew, 0, 0, cycles])

        # Mark scalar data as extracted after processing first file
        if not scalar_data_extracted:
            scalar_data_extracted = True

    if not data_list:
        raise ValueError("No data found in the files")

    # Convert to numpy array
    data_array = np.array(data_list)

    # Sort by AVL, then SEW, then VLEN, then LMUL
    sorted_indices = np.lexsort((data_array[:, 3], data_array[:, 2], data_array[:, 1], data_array[:, 0]))
    data_array = data_array[sorted_indices]

    return data_array

def main():
    # Extract data
    data = extract_data_from_files('results')

    print(f"Extracted data shape: {data.shape}")
    print(f"Columns: [AVL, SEW, VLEN, LMUL, cycles]")
    print("\nFirst 10 rows:")
    print(data[:10])

    # Optionally save to file
    np.save('vector_data.npy', data)
    print("\nData saved to 'vector_data.npy'")

    # Also save as CSV for easy inspection
    np.savetxt('vector_data.csv', data, delimiter=',',
               header='AVL,SEW,VLEN,LMUL,cycles',
               comments='', fmt='%d')
    print("Data saved to 'vector_data.csv'")

if __name__ == "__main__":
    main()