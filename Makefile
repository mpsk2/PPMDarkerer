CC=gcc
AS=nasm

ASFLAGS=-felf64
CFLAGS=-Wall -pedantic --std=c11

OBJ=main.o darker.o darkerer.o ppm_reader.o

all: main

main: $(OBJ)
	gcc $(OBJ) -o main

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.asm
	$(AS) $(ASFLAGS) $<	

clean:
	rm -rf *.o main
