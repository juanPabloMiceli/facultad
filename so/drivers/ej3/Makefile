obj-m := letras123.o
KVERSION := $(shell uname -r)

all:
	make -C /lib/modules/$(KVERSION)/build SUBDIRS=$(shell pwd) modules

clean:
	make -C /lib/modules/$(KVERSION)/build SUBDIRS=$(shell pwd) clean

test: all
	rmmod letras123.ko
	insmod letras123.ko
	./../tests/tests-drivers

r:
	rmmod letras123.ko
	insmod letras123.ko