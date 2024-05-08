CFLAGS = -O2 -Wall -g -std=gnu99
LDLIBS = -lm
CC = gcc

all:main

main: main.o stringhe.o
	$(CC) main.o stringhe.o $(LDLIBS) -o stringhe

main.o: main.c stringhe.h
	$(CC) -c $(CFLAGS) main.c -o main.o

stringhe.o: stringhe.c stringhe.h
	$(CC) -c $(CFLAGS) stringhe.c -o stringhe.o
clean:
	rm -f compseparata *.o
