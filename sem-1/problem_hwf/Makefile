CC=gcc
CFLAGS=-Wall -O2

all: main.o logic.o
	$(CC) $(CFLAGS) main.o logic.o -o game

main.o: main.c logic.h
	$(CC) $(CFLAGS) -c main.c

logic.o: logic.c
	$(CC) $(CFLAGS) -c logic.c

clean:
	rm -f *.o
	rm -f game
