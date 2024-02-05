CC=gcc
CFLAGS=-Wall -O2

all: main.o
	$(CC) $(CFLAGS) main.o -lm -o a.out

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -lm

clean:
	rm -f *.o
	rm -f a.out
