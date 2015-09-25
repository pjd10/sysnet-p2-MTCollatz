CFLAGS = -g -lrt -pthread -Wall
CC = gcc

objects =  mt-collatz.o thread.o 

test: $(objects)
	$(CC) $(CFLAGS) -o mt-collatz $(objects)
thread: thread.o
	$(CC) $(CFLAGS) -o thread thread.o
mt-collatz: mt-collatz.o
	$(CC) $(CFLAGS) -o mt-collatz mt-collatz.o

thread.o: thread.c thread.h 
mt-collatz.o: mt-collatz.c thread.h
.PHONY : clean
clean: 
	rm mt-collatz $(objects)
