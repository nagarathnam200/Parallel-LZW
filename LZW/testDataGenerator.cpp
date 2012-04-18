#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 32

#define PROCS 8 

int main() {

	FILE *fp;
	fp = fopen("testData8","wb");
	srand(time(NULL));
	long int i=0;

	long int size = SIZE;

	size*=SIZE;

	size*=1024;

	int procs = PROCS;

	fwrite(&size, sizeof(long int), 1, fp);

	fwrite(&procs, sizeof(int), 1, fp);


	int k = 0;
	for(k=0; k<1024; k++) {//500 MB
		for(i=0; i<SIZE; i++) {// 1MB
		
			int j;

			for(j=0; j<SIZE; j++) { //1kB
				char c = (rand() % 4) + 97;
			
				fwrite(&c, sizeof(char), 1, fp);
			}
		}
	}
	fclose(fp);
	return 0;
}

