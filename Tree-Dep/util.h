#include <string.h>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

long int readSize(char *filename);
int readChunk(void *dest, char *filename, int chunkNum, int procs);
