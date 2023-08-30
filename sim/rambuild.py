#! /bin/env python3

def build_ram():
	binary = open("./ram.bin", 'wb')
	with open("../os/MAestro/kernel.bin", 'rb') as os:
		binary.write(os.read())

	binary.write(bytearray(int(65536/2 - binary.tell())))

	with open("../app/coremark/coremark.bin", 'rb') as app:
		binary.write(app.read())

	print(binary.tell())

if __name__ == "__main__":
	build_ram()
