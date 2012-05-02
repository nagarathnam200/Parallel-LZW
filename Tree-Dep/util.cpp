#include "util.h"
long int readSize(char *filename) {
	FILE *fp;
	
	fp = fopen(filename, "rb");

	long int size;

	fread(&size, sizeof(long int), 1, fp);

	fclose(fp);

	return size;
}
int readChunk(void *dest, char *filename, int chunkNum, int procs) {

	FILE *fp;

	fp = fopen(filename, "rb");

	long int size = -1;

	fread(&size, sizeof(long int), 1, fp);

	if((size == -1) || (size == 0)) {
		
		fclose(fp);

		return 0;
	}

	int p;

	fread(&p, sizeof(int), 1, fp);

	int numOfBlocks = 2*procs - 1;

	long int len = size/numOfBlocks;

	fseek(fp, (len * (chunkNum-1) * sizeof(int)), SEEK_CUR);

	int readSize = fread(dest, sizeof(int), len, fp);

	fclose(fp);

	return readSize;
}
