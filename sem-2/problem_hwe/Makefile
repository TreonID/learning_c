CC=gcc
CFLAGS=-Wall -O2

all: main.o
	$(CC) $(CFLAGS) main.o -o a.out -lm

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -lm

debug:
	$(CC) -g main.c -lm

clean:
	rm -f *.o
	rm -f a.out
