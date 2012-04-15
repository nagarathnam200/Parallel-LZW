#include <stdio.h>
#include <stdlib.h>

int main() {

	FILE *fp;

	fp = fopen("test.bin","wb");

	int size = 10;

	scanf("%d",&size);

	int procs = 2;

	scanf("%d",&procs);

	fwrite(&size, sizeof(int), 1, fp);

	fwrite(&procs, sizeof(int), 1, fp);

	int i = 0;

	char c = 0;

	for(i=0;i<size;i++) {

		fwrite(&c, sizeof(char), 1, fp);

		c++;

	}

	return 0;
}
