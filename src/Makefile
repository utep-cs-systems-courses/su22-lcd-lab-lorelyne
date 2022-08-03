
COMMON_OBJECTS =
CPU 	       = msp430g2553
CFLAGS	       = -mmcu=${CPU} -Os -I../h
LDFLAGS	       = -L../lib -L/opt/ti/msp430_gcc/include/

CC 	       = msp430-elf-gcc
AS	       = msp430-elf-gcc -mmcu=${CPU} -c

all: animations.elf

animations.elf: ${COMMON_OBJECTS} animations.o wdt_handler.o switches.o main.o buzzer.o stateMachines.o led.o ../lib/libTimer.a
	 ${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lLcd -lShape -lp2sw

load: animations.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf *~

led.o: led.h

wdInterruptHandler.o: stateMachines.h buzzer.h led.h switches.h

stateMachines.o: led.h buzzer.h stateMachines.h

buzzer.o: buzzer.h

switches.o: switches.h led.h stateMachines.h buzzer.h

p2_interrupt_handler.o: switches.h 
