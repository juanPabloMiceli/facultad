obj-m := nulo.o
tests-dir := ../tests/
tests := tests-drivers
KVERSION := $(shell uname -r)

all:
	make -C /lib/modules/$(KVERSION)/build SUBDIRS=$(shell pwd) modules

clean:
	make -C /lib/modules/$(KVERSION)/build SUBDIRS=$(shell pwd) clean


test: all
	make -C $(tests-dir)
	rmmod nulo.ko
	insmod nulo.ko
	./$(tests-dir)$(tests)

r:
	rmmod nulo.ko
	insmod nulo.ko