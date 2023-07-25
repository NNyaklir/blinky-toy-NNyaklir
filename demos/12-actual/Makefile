# makfile configuration
COMMON_OBJECTS  = blinkyToy.o led.o buzzer.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: blinkyToy.elf

blinkyToy.elf: ${COMMON_OBJECTS}    
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../lib/libTimer.a 

load: blinkyToy.elf
	msp430loader.sh blinkyToy.elf

clean: $^
	rm -f *.o *.elf

led.c: led.h
buzzer.c: buzzer.h
