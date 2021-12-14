obj-m := accelMagGyro.o
KDIR := /home/byungjun/Embedded/SourceCode_peridrv/
PWD := $(shell pwd)
export ARCH=arm
export CROSS_COMPILE=arm-linux.gnueabi-


all :libMyperi.a

libMyperi.a : button.o led.o colorled.o buzzer.o fnd.o textlcd.o temperature.o accelMagGyro.o
	arm-linux-gnueabi-ar rc libMyperi.a led.o button.o colorled.o buzzer.o fnd.o textlcd.o temperature.o accelMagGyro.o
button.o: button.h button.c
	arm-linux-gnueabi-gcc -c button.c -o button.o
led.0: led.h led.o
	arm-linux-gnueabi-gcc -c led.c -o led.o
colorled.o: colorled.c
	arm-linux-gnueabi-gcc -c colorled.c -o colorled.o
buzzer.o: buzzer.h buzzer.c
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o
temperature.o: temperature.c
	arm-linux-gnueabi-gcc -c temperature.c -o temperature.o
fnd.o: fnd.c
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o
textlcd.o: textlcd.c
	arm-linux-gnueabi-gcc -c textlcd.c -o textlcd.o
accMagGyro.o: accMagGyro.c
	arm-linux.gnueabi-gcc -c accMagGyro.c -o accMagGyro.o
	
clean : 
	-rm *.o *.mod.c .*.cmd modules.order Module.symvers
