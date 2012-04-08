#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

	FILE *fp;
	fp = fopen("testData","w");
	srand(time(NULL));
	long int i=0;

	for(i=0; i<100000; i++) {
		fputc((rand() % 4) + 97, fp);
	}
	fputc('\n', fp);
	fclose(fp);
	return 0;
}

