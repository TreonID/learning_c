CC=gcc
CFLAGS=-Wall -O2

all: main.o
	$(CC) $(CFLAGS) main.o -o a.out

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

debug:
	$(CC) -g main.c 

.PHONY: test
test: all
	./test.sh

clean:
	rm -f *.o
	rm -f a.out
