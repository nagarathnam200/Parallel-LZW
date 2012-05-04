#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1024 

#define PROCS 2 

#define FACTOR 16

#define ALPHA 64 

int main() {

	FILE *fp[7];

	fp[0] = fopen("testData1","wb");
	fp[1] = fopen("testData2","wb");
	fp[2] = fopen("testData4","wb");
	fp[3] = fopen("testData8","wb");
	fp[4] = fopen("testData16","wb");
	fp[5] = fopen("testData32","wb");
	fp[6] = fopen("testData64","wb");

	srand(time(NULL));
	long int i=0;

	long int size = SIZE;

	size*=SIZE;

	size*=FACTOR;

	int procs = 1;

	int count = 0;

	long int s[7];

	int pr[7] = {1,2,4,8,16,32,64};

	for(count = 0; count < 7; count++) {

		int temp;

		pr[count] = 2* pr[count] - 1;

		temp = size / pr[count];

		s[count] = pr[count] * temp;

		printf("\nSize is : %ld",s[count]);

		fwrite(&s[count], sizeof(long int), 1, fp[count]);

		

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

		procs = 64;

		fwrite(&procs, sizeof(int), 1, fp[6]);


	int k = 0;
				int m = 0;
				for(m=0; m<7; m++) {

					for(i=0; i < s[m]; i++) {

						int c = (rand() % ALPHA) + 97;

						fwrite(&c, sizeof(int), 1, fp[m]);

					}

				}
    for(m=0; m<7; m++) {
		fclose(fp[m]);
	}
	return 0;
}

