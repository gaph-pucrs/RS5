DEFINES=BATCHNORMALIZATION

all:
	gcc model.c -o model.bin -lm -D$(DEFINES) -DINT_HANDLER

clean:
	rm *.bin
