CC = gcc

GLIB_INCS = -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include
BINUTILS_INCS = -Ibuild/bfd -Ilib/binutils/include

GLIB_LIBS = -L/usr/lib64 -lglib-2.0
# BINUTILS_LIBS = -Lbuild/usr/local/x86_64-pc-linux-gnu/riscv64-unknown-linux-gnu/lib/ -lopcodes -lbfd -lz -ldl -lzstd
BINUTILS_LIBS = -Lbuild/usr/local/x86_64-pc-linux-gnu/riscv64-unknown-linux-gnu/lib/ -lopcodes -lbfd -lz -ldl

SOURCES = $(wildcard src/c/*.c)
HEADERS = $(wildcard src/c/include/*.h)

CFLAGS = -shared -fPIC -std=c11 $(GLIB_INCS) $(BINUTILS_INCS) -Isrc/c/include
LDFLAGS = $(GLIB_LIBS) $(BINUTILS_LIBS)

binutils:
	mkdir -p build/usr/local/

	cd build && CC_FOR_TARGET=riscv64-unknown-linux-gnu-gcc $(PWD)/lib/binutils/configure \
		--target=riscv64-unknown-linux-gnu \
		\
		--prefix=$(PWD)/build/usr/local \
		--enable-plugins \
		--disable-multilib \
		\
		--disable-werror \
		--disable-nls \
		--with-expat=yes  \
		--disable-gdb \
		--enable-shared \
		--disable-sim \
		--disable-libdecnumber \
		--disable-readline \
		--with-isa-spec=20191213

	make -C build
	make -C build install

rvfi_tools.so: $(HEADERS) $(SOURCES)
	mkdir -p build/rvfi_tools/
	$(CC) $(SOURCES) -o build/rvfi_tools/rvfi_tools.so $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf build/rvfi_tools/rvfi_tools.so

deepclean: clean
	rm -r build
