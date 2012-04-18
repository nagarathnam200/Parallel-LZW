#include <stdio.h>

int main() {

	FILE *fp;
    fp = fopen("testData","r");
    long int i=0;

    long int size; 
    int procs;

	fseek(fp, 0, SEEK_SET);

    fread(&size, sizeof(long int), 1, fp);


    fread(&procs, sizeof(int), 1, fp);


    for(i=0; i<size; i++) {

		char c;
		
		c = fgetc(fp);
	
		printf("%c",c);
    }
    fclose(fp);

	return 0;
}
