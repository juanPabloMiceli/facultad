obj-m := azar.o
KVERSION := $(shell uname -r)

all:
	make -C /lib/modules/$(KVERSION)/build SUBDIRS=$(shell pwd) modules

clean:
	make -C /lib/modules/$(KVERSION)/build SUBDIRS=$(shell pwd) clean

test: all
	rmmod azar.ko
	insmod azar.ko
	./../tests/tests-drivers

r:
	rmmod azar.ko
	insmod azar.ko