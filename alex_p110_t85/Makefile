#PROGRAMMER = avrisp2
PROGRAMMER = usbtiny
#PROGRAMMER = usbasp
CPU_GCC = attiny85
CPU_DUDE = t85

F_CPU = 1000000

CDEFS = -DF_CPU=$(F_CPU)
CFLAGS = -mmcu=$(CPU_GCC) $(CDEFS) -Wall -Os

.phony: clean

all: p110.hex

program: p110.hex
#	avrdude -c $(PROGRAMMER) -P usb -p $(CPU_DUDE) -U flash:w:p110.hex -B 20
	avrdude -c $(PROGRAMMER) -P usb -p $(CPU_DUDE) -U flash:w:p110.hex

clean:
	rm *.o *.elf *.hex *.map *.i *.s

p110.hex: p110.c
	avr-gcc $(CFLAGS) -save-temps -fverbose-asm -c p110.c -o p110.o
	avr-gcc $(CFLAGS) p110.o -o p110.elf -Wl,-Map,p110.map
	avr-objcopy -R .eeprom -O ihex p110.elf p110.hex
