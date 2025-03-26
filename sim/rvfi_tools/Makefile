


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

clean:
	rm -r build