
CC=icpc
CFLAGS=-O3 -openmp
CFLAGS_DEBUG=-g -openmp

all: lzw

.PHONY: clean

clean: 
	rm -rf lzw lzw_debug lzwDecoder dictionary *~ *.o

lzw: lzw.o dictionary.o lzwDecoder.o
	$(CC) $(CFLAGS) lzw.o dictionary.o -o lzw
	$(CC) $(CFLAGS) lzwDecoder.o dictionary.o -o lzwDecoder
lzw.o: lzw.cpp
	$(CC) $(CFLAGS) $< -c lzw.cpp
lzwDecoder.o: lzwDecoder.cpp
	$(CC) $(CFLAGS) $< -c lzwDecoder.cpp
dictionary.o: dictionary.cpp
	$(CC) $(CFLAGS) $< -c dictionary.cpp
