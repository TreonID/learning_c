CC=gcc
CFLAGS=-Wall -O2


all: main.o list.o
	$(CC) $(CFLAGS) main.o list.o -o a.out

main.o: main.c list.h
	$(CC) $(CFLAGS) -c main.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

clean:
	rm -f *.o
	rm -f a.out
