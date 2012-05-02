CC=icpc
CFLAGS=-O3 -openmp
CFLAGS_DEBUG=-g -openmp

all: lzw

.PHONY: clean

clean: 
	rm -rf lzw lzw_debug lzwDecoder dictionary testDataGenerator testDataReader *~ *.o

lzw: lzw.o dictionary.o util.o hash.o
	$(CC) $(CFLAGS) lzw.o dictionary.o util.o hash.o -o lzw
#	$(CC) $(CFLAGS) lzwDecoder.o dictionary.o util.o hash.o -o lzwDecoder
	$(CC) $(CFLAGS) testDataGenerator.o -o tg
	$(CC) $(CFLAGS) testDataReader.o -o tr
lzw.o: lzw.cpp
	$(CC) $(CFLAGS) $< -c lzw.cpp
dictionary.o: dictionary.cpp
	$(CC) $(CFLAGS) $< -c dictionary.cpp
hash.o: hash.cpp 
	$(CC) $(CFLAGS) $< -c hash.cpp
util.o: util.cpp
	$(CC) $(CFLAGS) $< -c util.cpp
#lzwDecoder.o: lzwDecoder.cpp
#	$(CC) $(CFLAGS) $< -c lzwDecoder.cpp
	$(CC) $(CFLAGS) $< -c testDataGenerator.cpp
	$(CC) $(CFLAGS) $< -c testDataReader.cpp
