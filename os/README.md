# MAestro for RS5

This folder contains the MAestro kernel and libraries for RS5.

## Building

Prior to building the applications in the `app` folder, please build the kernel
and support libraries.
To do this, simply run `make` in each subfolder, or run:

```
make -C libmutils
make -C libmemphis
make -C MAestro
```

Then build the app. For instance, here we will use `hello`:
```
make -C app/hello
```

## Simulating

Build the memory image by running rambuild.py inside `sim` folder:
```
./rambuild.py
```
This command produces ram.bin, now, change the simulation binary to ram.bin in `testbench.sv`:
```
localparam string        BIN_FILE = "./ram.bin";
```