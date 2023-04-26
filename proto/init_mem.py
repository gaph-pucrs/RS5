with open("../app/berkeley_suite/test.bin", "rb") as file_in:
    rd = file_in.read(-1)
    byteArray = bytearray(rd)

    while len(byteArray) < 65536:
        byteArray.append(0)

with open("./Berkeley_Privileged.coe", "w") as file_out:
    file_out.write("memory_initialization_radix=16;\n")
    file_out.write("memory_initialization_vector=\n")

    for i in range(0, len(byteArray)-4, 4):
        file_out.write(str(hex(byteArray[i+3])[2:].zfill(2)))
        file_out.write(str(hex(byteArray[i+2])[2:].zfill(2)))
        file_out.write(str(hex(byteArray[i+1])[2:].zfill(2)))
        file_out.write(str(hex(byteArray[i+0])[2:].zfill(2)))
        file_out.write(",\n")

    file_out.write("00000000;")
