CC=gcc
CFLAGS=-Wall -O2 -Werror=sign-compare -Werror=vla

all: main.o
	$(CC) $(CFLAGS) main.o -o a.out

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

debug:
	$(CC) -g main.c 

clean:
	rm -f *.o
	rm -f a.out
