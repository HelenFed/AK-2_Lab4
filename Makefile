ccflags-y := -I$(PWD)/inc
ifneq ($(KERNELRELEASE),)
	obj-m := hello1.o hello2.o
else
	KDIR ?= /lib/modules/`uname -r`/build
default:
	$(MAKE) -C $(KDIR) M=$$PWD
clean:
	$(MAKE) -C $(KDIR) N=$$PWD clean
endif
