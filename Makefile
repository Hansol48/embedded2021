obj-m = colorled.o
KDIR := /home/byungjun/Embedded/SourceCode_peridrv/
PWD := $(shell pwd)
export ARCH=arm
export CROSS_COMPILE=arm-linux.gnueabi-

<<<<<<< HEAD
all :libMyPeri.a
libMyperi.a : button.o led.o buzzer.o fnd.o textlcd.o colorled.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o button.o colorled.o buzzer.o fnd.o textlcd.o
button.o: button.h button.c
	arm-linux-gnueabi-gcc -c button.c -0 button.o
led.0: led.h, led.o
=======
all :libMyperi.a
libMyperi.a : button.o led.o
	arm-linux-gnueabi-ar rc libMyperi.a led.o button.o
button.o: button.h button.c
	arm-linux-gnueabi-gcc -c button.c -o button.o
led.0: led.h led.o
	arm-linux-gnueabi-gcc -c led.c -o led.o
colorled.o: colorled.h colorled.c
	arm-linux-gnueabi-gcc -c colorled.c -o colorled.o
buzzer.o: buzzer.h buzzer.c
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o
fnd.o: fnd.c
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o
textlcd.o: textlcd.c
	arm-linux-gnueabi-gcc -c textlcd.c -o textlcd.o

	
clean : 
	-rm *.o *.mod.c .*.cmd modules.order Module.symvers
