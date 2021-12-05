obj-m = buzzer.o
KDIR := /home/byungjun/Embedded/SourceCode_peridrv/
PWD := $(shell pwd)
export ARCH=arm
export CROSS_COMPILE=arm-linux.gnueabi-

all : libMyperi.a
libMyPeri.a: led.o buzzer.o
	arm-linux-gnueabi-ar rc libMyperi.a led.o buzzer.o
buzzer.o: buzzer.h buzzer.c
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o
led.o: led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o

clean : 
	-rm *.o *.mod.c .*.cmd modules.order Module.symvers
