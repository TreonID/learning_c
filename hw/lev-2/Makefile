CC=gcc
CFLAGS=-Wall -O2


all: main.o list.o mask.o
	$(CC) $(CFLAGS) main.o list.o mask.o -o a.out

main.o: main.c list.h mask.h
	$(CC) $(CFLAGS) -c main.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

mask.o:	mask.c mask.h
	$(CC) $(CFLAGS) -c mask.c

clean:
	rm -f *.o
	rm -f a.out
