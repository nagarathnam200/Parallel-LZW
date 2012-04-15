#include "util.h"

int main() {
	char x[16] = {0};

	readChunk(&x, "test.bin", 2);	

	int i = 0;

	for(i=0; i<16; i++) {
		printf("%d",x[i]);
	}	
}
