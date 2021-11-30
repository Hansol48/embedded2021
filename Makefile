obj-m = led.o
KDIR := /home/byungjun/Embedded/SourceCode_peridrv/
PWD := $(shell pwd)
export ARCH=arm
export CROSS_COMPILE=arm-linux.gnueabi-

all :led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o
	arm-linux-gnueabi-ar rc libMyperi.a led.o

clean : 
	-rm *.o *.mod.c .*.cmd modules.order Module.symvers
