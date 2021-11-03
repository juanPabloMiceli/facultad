obj-m := hello.o
KVERSION := $(shell uname -r)



all:
	make -C /lib/modules/$(KVERSION)/build SUBDIRS=$(shell pwd) modules

clean:
	make -C /lib/modules/$(KVERSION)/build SUBDIRS=$(shell pwd) clean

test:
	./../tests/tests-drivers

r:
	insmod azar.ko
	rmmod azar.ko