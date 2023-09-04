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
