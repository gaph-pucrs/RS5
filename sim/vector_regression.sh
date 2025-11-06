#!/bin/bash

source_folder="../app/vector-tests/operations"
destination_folder="../app/vector-tests/test"
makefile_path="../app/vector-tests/"
results_folder="../app/vector-tests/results"
passed_folder="${results_folder}/passed"
failed_folder="${results_folder}/failed"

mkdir -p "$passed_folder"
mkdir -p "$failed_folder"

# Clean the Passed and Failed folders
rm -f "$passed_folder"/*
rm -f "$failed_folder"/*

# Iterate over each file in the source folder
for file in "$source_folder"/*; do
    # Extract the filename
    filename=$(basename "$file")
    filename_without_extension="${filename%.*}"

    # Copy the file to the destination folder
    cp "$file" "$destination_folder/$filename"

    make -C "$makefile_path" clean all

    # Run the command and capture the output
    output_file="${destination_folder}/${filename_without_extension}.txt"
    xrun -f sim.xrun | tee "$output_file"

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
