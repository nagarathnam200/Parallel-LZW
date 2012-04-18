#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "dictionary.h"

#define MAX_PROCS 256

dictionary d[MAX_PROCS];


int counter = COUNT;
string deCompress(string str) {

	static int dicCount = -1;
	

	dicCount++;

	int ctr = 0;

	char num;

	char ch;

	string entry;

	char prevcode, currentcode;

	prevcode = str[ctr++];

	cout<<d[dicCount].retriveStr((int)prevcode);

	while((num = str[ctr++]) != -1) {
		currentcode = num;

		string s = d[dicCount].retriveStr((int)currentcode);

		if(s.empty()) {

			string dest = d[dicCount].retriveStr((int)prevcode);

			dest.append(1,dest[0]);

			cout<<dest;

			d[dicCount].addNum(currentcode, dest);
	
			prevcode = currentcode;

			counter = ++currentcode;

		} else {

			cout<<s;
			
			ch = s[0];

//			cout<<endl <<"For count "<<counter<<" String: "<< d[dicCount].retriveStr((int)prevcode) << " Character "<<ch<<" PrevCode "<<(int)prevcode<<" Current "<<(int)currentcode;
			d[dicCount].addNum(counter++, 
								d[dicCount].retriveStr((int)prevcode).append(1,ch));

			prevcode = currentcode;
		}
	}

	return str;
}

int main(int argc, char **argv) {
	int opt;

    int numOfProcs = 1;

	char *Data;

	ifstream infile;

	char input[30];
	
	int lSize;

    while((opt = getopt(argc, argv, "p:i:o:")) != -1) {
        switch(opt) {

            case 'p':
                {
                    numOfProcs = atoi(optarg);
                    break;
                }
            case 'i':
                {

					strcpy(input, optarg);
                    break;

                }
            case 'o':
            {
                if (dup2(open(optarg, O_CREAT | O_WRONLY, 0644), STDOUT_FILENO) < 0)
                {
                    perror("");
                    exit(EXIT_FAILURE);
                }

                break;
            }

        }
    }

	FILE *fp;

	fp = fopen(input, "rb");

	long int size;	

	fread(&size, sizeof(long int), 1, fp);

    fwrite(&size, sizeof(long int), 1, stdout);	

	int procs;

	fread(&procs, sizeof(int), 1, fp);

	fwrite(&procs, sizeof(int), 1, stdout);


	int i;

	for(i=0;i<numOfProcs;i++) {

		string line;

		char c;

		fread(&c, sizeof(char), 1, fp);

//		printf("%d ",c);

		while(c != (char)255) {

			line.append(1,c);

			fread(&c, sizeof(char), 1, fp);

//			printf("%d ", c);

		}

		line.append(1,c);

		deCompress(line);		
		counter = COUNT;
	}

	fclose(fp);

//	d[0].print(1);
}
