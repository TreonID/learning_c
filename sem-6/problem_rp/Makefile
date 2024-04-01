CC=gcc
CFLAGS=-Wall -O2 -Werror=sign-compare -Werror=vla -Werror=maybe-uninitialized

all: main.o
	$(CC) $(CFLAGS) main.o -o a.out -lm

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

debug:
	$(CC) -g main.c 
	gdb ./a.out

.PHONY: test
test: all
	./test.sh

clean:
	rm -f *.o
	rm -f a.out
