
CC=icpc
CFLAGS=-O3 -openmp
CFLAGS_DEBUG=-g -openmp

all: lzw

.PHONY: clean

clean: 
	rm -rf util *~ *.o

lzw: util.o utilTester.o
	$(CC) $(CFLAGS) utilTester.o util.o -o utils
util.o: util.cpp
	$(CC) $(CFLAGS) $< -c util.cpp
utilTester.o: utilTester.cpp
	$(CC) $(CFLAGS) $< -c utilTester.cpp
