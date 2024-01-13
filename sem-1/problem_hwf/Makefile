CC=gcc
CFLAGS=-Wall -O2

all: main.o logic.o game.o
	$(CC) $(CFLAGS) main.o logic.o game.o -o game

main.o: main.c game.h
	$(CC) $(CFLAGS) -c main.c

logic.o: logic.c
	$(CC) $(CFLAGS) -c logic.c

game.o: game.c logic.h

clean:
	rm -f *.o
	rm -f game

.PHONY: test
test:
	@./test.bash
