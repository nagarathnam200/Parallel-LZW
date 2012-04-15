#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

#define PROCS 2

int main() {

	FILE *fp;
	fp = fopen("testData","wb");
	srand(time(NULL));
	long int i=0;

	int size = SIZE;
	int procs = PROCS;

	fwrite(&size, sizeof(int), 1, fp);

	fwrite(&procs, sizeof(int), 1, fp);

	for(i=0; i<SIZE; i++) {
	
		char c = (rand() % 4) + 97;
		
		fwrite(&c, sizeof(char), 1, fp);
	}
	fclose(fp);
	return 0;
}

