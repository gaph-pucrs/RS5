#!/usr/bin/env python3

from argparse import ArgumentParser

def build_coi(input_file):
    with open(input_file, "rb") as file_in:
        rd = file_in.read(-1)
        byteArray = bytearray(rd)

        while len(byteArray) < 65536:
            byteArray.append(0)

    with open("./memimage.coe", "w") as file_out:
        file_out.write("memory_initialization_radix=16;\n")
        file_out.write("memory_initialization_vector=\n")

        for i in range(0, len(byteArray)-4, 4):
            file_out.write(str(hex(byteArray[i+3])[2:].zfill(2)))
            file_out.write(str(hex(byteArray[i+2])[2:].zfill(2)))
            file_out.write(str(hex(byteArray[i+1])[2:].zfill(2)))
            file_out.write(str(hex(byteArray[i+0])[2:].zfill(2)))
            file_out.write(",\n")

        file_out.write("00000000;")

if __name__ == "__main__":
    parser = ArgumentParser(description="Converts binary file to COE file")
    parser.add_argument("input_file", help="Input binary file")

    args = parser.parse_args()

    build_coi(args.input_file)
