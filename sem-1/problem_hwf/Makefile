CC=gcc
CFLAGS=-Wall -O2

.PHONY:all
all: main.o logic.o
	$(CC) $(CFLAGS) main.o logic.o -o game

main.o:
	$(CC) $(FLAGS) -c main.c

logic.o:
	$(CC) $(FLAGS) -c logic.c

.PHONY:clean
clean:
	rm -f *.o
	rm -f game
