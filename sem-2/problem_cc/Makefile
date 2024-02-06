CC=gcc
CFLAGS=-Wall -O2

all: main.o my_list.o
	$(CC) $(CFLAGS) main.o my_list.o -o a.out

main.o: main.c my_list.h
	$(CC) $(CFLAGS) -c main.c

my_list.o: my_list.c my_list.h
	$(CC) $(CFLAGS) -c my_list.c

clean:
	rm -f *.o
	rm -f a.out
