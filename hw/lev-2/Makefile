CC=gcc
CFLAGS=-Wall -O2


all: main.o list.o mask.o permut.o cycle.o
	$(CC) $(CFLAGS) main.o list.o mask.o permut.o cycle.o -o a.out

main.o: main.c list.h mask.h permut.h cycle.h
	$(CC) $(CFLAGS) -c main.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

mask.o:	mask.c mask.h
	$(CC) $(CFLAGS) -c mask.c

permut.o: permut.c permut.h  cycle.h list.h mask.h 
	$(CC) $(CFLAGS) -c permut.c

cycle.o: cycle.c cycle.h
	$(CC) $(CFLAGS) -c cycle.c

clean:
	rm -f *.o
	rm -f a.out
