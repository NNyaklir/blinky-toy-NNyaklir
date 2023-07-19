# makfile configuration
COMMON_OBJECTS  = blinkyToy.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: blinkyToy.elf

blinkyToy.elf: ${COMMON_OBJECTS}    ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ 

load: blinkyToy.elf
	msp430loader.sh blinkyToy.elf

clean:
	rm -f *.o *.elf

