# Example newlib application

This application uses newlib bindings present in [common](app/common) folder.
To create you own application, follow the directory structure present in this folder:

```
src/
    include/
            *.h
    *.c
Makefile
```

Copy this directory `Makefile` to your application folder too.

You can edit two parameters in `Makefile`:

* `MEM_SIZE`: memory size (in bytes). Default is 65536.
* `ARCH`: RISC-V architecture to build the application. Default (minimum) is rv32i_zicsr.

To edit the hardware memory size, edit `MEM_WIDTH` in [testbench](sim/testbench.sv), or enter the BRAM properties in Vivado.
To edit the BRAM size, remember that the word size is 4 bytes, i.e., the default value is 16384, that means we have 16384 4-byte words, hence 65536 bytes.
      