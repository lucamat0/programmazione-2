CFLAGS = -O2 -Wall -g -std=gnu99
CC = gcc

main: main.o coppie.o
	$(CC) main.o coppie.o -o main

main.o: main.c coppie.h 
	$(CC) -c $(CFLAGS) main.c -o main.o

coppie.o: coppie.c coppie.h
	$(CC) -c $(CFLAGS) coppie.c -o coppie.o
clean: 
	rm -f compseparata *.0
