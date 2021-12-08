obj-m = fnd.o
KDIR := /home/byungjun/Embedded/SourceCode_peridrv/
PWD := $(shell pwd)
export ARCH=arm
export CROSS_COMPILE=arm-linux.gnueabi-

all :libMyperi.a
libMyperi.a : button.o led.o buzzer.o fnd.o
	arm-linux-gnueabi-ar rc libMyperi.a led.o button.o buzzer.o button.o
button.o: button.h button.o
	arm-linux-gnueabi-gcc -c button.c -o button.o
led.0: led.h led.o
	arm-linux-gnueabi-gcc -c led.c -o led.o
buzzer.o: buzzer.h buzzer.o
	arm-linux-gnueabi-gcc -c buzzer.c -o  buzzer.o
fnd.o: fnd.h fnd.o
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o	


clean : 
	-rm *.o *.mod.c .*.cmd modules.order Module.symvers
