# Makefile

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

MCU = atmega328p
PROGRAMMER = usbasp

CFLAGS = -g -Wall -Wpedantic -Os -DF_CPU=1000000UL -DBAUD=9600UL
LDFLAGS =
LIBS =

all: rotenc.elf

rotenc.elf: rotenc.o uart.o
rotenc.o: uart.o
uart.o: uart.h

%.elf: %.o
	$(CC) $(LDFLAGS) -mmcu=$(MCU) -o $@ $^ $(LIBS)

%.o: %.c
	 $(CC) $(CFLAGS) -mmcu=$(MCU) -c -o $@ $<

%.hex: %.elf
	 $(OBJCOPY) -j .text -j .data -O ihex $< $@

flash: rotenc.hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -U flash:w:$<

clean:
	rm -f *.elf *.hex *.map *.o
