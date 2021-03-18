# Location of the linux kernel
KDIR=/usr/src/linux-headers-5.4.83-v7l+
PWD=$(shell pwd)

#The compiler
export CROSS_COMPILE:=arm-linux-gnueabihf-

obj-m := module_test.o
module_test-objs := main.o io.o

default:
	$(MAKE) -C $(KDIR) ARCH=arm M=$(PWD) modules 

#clean:
	@rm -f *.o .*.cmd .*.flags *.mod.c *.order *.mod
	@rm -f .*.*.cmd *.symvers *~ *.*~ TODO.*
	@rm -fR .tmp*
	@rm -f .tmp_version

