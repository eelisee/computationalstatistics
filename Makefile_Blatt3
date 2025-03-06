CC = gcc
CFLAGS = -Wall -O2

all: main

main: main.o scalar_standard.o scalar_kahan.o scalar_sorted.o
	$(CC) $(CFLAGS) -o main main.o scalar_standard.o scalar_kahan.o scalar_sorted.o

main.o: main.c scalar.h
	$(CC) $(CFLAGS) -c main.c
 
scalar_standard.o: scalar_standard.c scalar.h
	$(CC) $(CFLAGS) -c scalar_standard.c

scalar_kahan.o: scalar_kahan.c scalar.h
	$(CC) $(CFLAGS) -c scalar_kahan.c

scalar_sorted.o: scalar_sorted.c scalar.h
	$(CC) $(CFLAGS) -c scalar_sorted.c

clean:
	rm -f *.o main