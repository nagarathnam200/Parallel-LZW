#include "util.h"
int readChunk(void *dest, char *filename, int chunkNum) {

	FILE *fp;

	fp = fopen(filename, "rb");

	int size = -1;

	fread(&size, sizeof(int), 1, fp);

	if((size == -1) || (size == 0)) return 0;

	int procs = -1;

	fread(&procs, sizeof(int), 1, fp);

	if((procs == -1) || (procs == 0)) return 0;

	int len = size/procs;

	fseek(fp, (len * (chunkNum-1)), SEEK_CUR);

	fread(dest, 1, len, fp);

	fclose(fp);

	return 1;
}
