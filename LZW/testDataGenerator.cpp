#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1024

#define PROCS 2 

#define FACTOR 16

#define ALPHA 4

int main() {

	FILE *fp[6];

	fp[0] = fopen("testData1","wb");
	fp[1] = fopen("testData2","wb");
	fp[2] = fopen("testData4","wb");
	fp[3] = fopen("testData8","wb");
	fp[4] = fopen("testData16","wb");
	fp[5] = fopen("testData32","wb");

	srand(time(NULL));
	long int i=0;

	long int size = SIZE;

	size*=SIZE;

	size*=FACTOR;

	int procs = 1;

	int count = 0;

	for(count = 0; count < 6; count++) {

		fwrite(&size, sizeof(long int), 1, fp[count]);

		

	}

	    fwrite(&procs, sizeof(int), 1, fp[0]);

		procs = 2;

		fwrite(&procs, sizeof(int), 1, fp[1]);

		procs = 4;

		fwrite(&procs, sizeof(int), 1, fp[2]);

		procs = 8;

		fwrite(&procs, sizeof(int), 1, fp[3]);

		procs = 16;

		fwrite(&procs, sizeof(int), 1, fp[4]);

		procs = 32;

		fwrite(&procs, sizeof(int), 1, fp[5]);


	int k = 0;
	for(k=0; k<FACTOR; k++) {//50 MB
		for(i=0; i<SIZE; i++) {// 1MB
		
			int j;

			for(j=0; j<SIZE; j++) { //1kB
				int c = (rand() % ALPHA) + 97;
				int m = 0;
				for(m=0; m<6; m++) {

					fwrite(&c, sizeof(int), 1, fp[m]);

				}
			}
		}
	}
	int m = 0;
    for(m=0; m<6; m++) {
		fclose(fp[m]);
	}
	return 0;
}

