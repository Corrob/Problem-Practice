EXEC = run
CC = g++
CFLAGS = -c -std=c++11 -Wall

$(EXEC): primes_spiral.o
	$(CC) -o $(EXEC) primes_spiral.o

primes_spiral.o: primes_spiral.cpp
	$(CC) $(CFLAGS) primes_spiral.cpp
