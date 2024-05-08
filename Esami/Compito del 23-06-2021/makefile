CFLAGS = -O2 -Wall -g -std=gnu99
LDLIBS = -lm
CC = gcc

all: main main2

main:main.o
	$(CC) main.o $(LDLIBS) -o main

main.o: main.c
	$(CC) -c $(CFLAGS) main.c -o main.o

main2:main2.o
	$(CC) main2.o $(LDLIBS) -o main2

main2.o: main2.c
	$(CC) -c $(CFLAGS) main2.c -o main2.o

	
