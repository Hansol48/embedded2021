obj-m := buzzer.o
KDIR := /home/byungjun/Embedded/SourceCode_peridrv/
PWD := $(shell pwd)
export ARCH=arm
export CROSS_COMPILE=arm-linux.gnueabi-


all :libMyPeri.a

libMyPeri.a : button.o buzzer.o 
	arm-linux-gnueabi-ar rc libMyPeri.a button.o buzzer.o
button.o: button.h button.c
	arm-linux-gnueabi-gcc -c button.c -o button.o
buzzer.0: buzzer.h buzzer.c
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o

	
clean : 
	-rm *.o *.mod.c .*.cmd modules.order Module.symvers
