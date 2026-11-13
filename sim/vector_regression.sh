#!/bin/bash

# Vector regression tests. Run from the sim/ folder.
# Requirements (see "Vector regression tests" in README.md):
#   - VEnable = 1, VLEN = 512 (the tests' expected results assume it) and the program
#     are set below on the xrun command line, so testbench.sv needs no editing
#   - Compile with GCC 13, or add -fno-tree-vectorize to GCC_RISCV in
#     app/baremetal/tests/vector-tests/Makefile. Newer GCC auto-vectorizes the tests and breaks them.

source_folders=("../app/baremetal/tests/vector-tests/operations" "../app/baremetal/tests/vector-tests/mem_operations")
destination_folder="../app/baremetal/tests/vector-tests/test"
makefile_path="../app/baremetal/tests/vector-tests/"
results_folder="../app/baremetal/tests/vector-tests/results"
passed_folder="${results_folder}/passed"
failed_folder="${results_folder}/failed"

mkdir -p "$passed_folder"
mkdir -p "$failed_folder"

# Clean the Passed and Failed folders
rm -f "$passed_folder"/*
rm -f "$failed_folder"/*

# Iterate over each file in the source folders
for file in $(for folder in "${source_folders[@]}"; do ls "$folder"/*.c; done); do
    # Extract the filename
    filename=$(basename "$file")
    filename_without_extension="${filename%.*}"

    # Copy the file to the destination folder
    cp "$file" "$destination_folder/$filename"

    make -C "$makefile_path" clean all

    # Run the command and capture the output
    output_file="${destination_folder}/${filename_without_extension}.txt"
    xrun -f sim.xrun -defparam testbench.VEnable=1 -defparam testbench.VLEN=512 -gpg 'testbench.BIN_FILE => "../app/baremetal/tests/vector-tests/test.bin"' | tee "$output_file"

    # Check the output file for the PASSED string
    if grep -q "PASSED: test/${filename}!" "$output_file"; then
        # Move the output file to the Passed folder
        mv "$output_file" "$passed_folder/"
    else
        # Move the output file to the Failed folder
        mv "$output_file" "$failed_folder/"
    fi

    rm "$destination_folder/$filename"

    echo
    echo
    echo
done

# Tests in class_disabled/ run with every vector class parameter set to 0
class_off="-defparam testbench.VLogicEnable=0 -defparam testbench.VMinMaxEnable=0 -defparam testbench.VMergeEnable=0"
class_off="$class_off -defparam testbench.VDivEnable=0 -defparam testbench.VRedLogicEnable=0"
class_off="$class_off -defparam testbench.VRedMinMaxEnable=0 -defparam testbench.VRedSumEnable=0"
for file in ../app/baremetal/tests/vector-tests/class_disabled/*.c; do
    filename=$(basename "$file")
    filename_without_extension="${filename%.*}"
    cp "$file" "$destination_folder/$filename"
    make -C "$makefile_path" clean all
    output_file="${destination_folder}/${filename_without_extension}.txt"
    xrun -f sim.xrun -defparam testbench.VEnable=1 -defparam testbench.VLEN=512 $class_off -gpg 'testbench.BIN_FILE => "../app/baremetal/tests/vector-tests/test.bin"' | tee "$output_file"
    if grep -q "PASSED: test/${filename}!" "$output_file"; then
        mv "$output_file" "$passed_folder/"
    else
        mv "$output_file" "$failed_folder/"
    fi
    rm "$destination_folder/$filename"
done

echo "Passed: $(ls "$passed_folder" | wc -l)  Failed: $(ls "$failed_folder" | wc -l)"
ls "$failed_folder"
