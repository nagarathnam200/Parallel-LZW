#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "dictionary.h"

#define MAX_PROCS 256

dictionary d[MAX_PROCS];


int counter = 5;
string deCompress(string str) {

	static int dicCount = -1;
	

	dicCount++;

	istringstream iss(str, istringstream::in);

	int num;

	char ch;

	string entry;

	int prevcode, currentcode;

	iss >> prevcode;

	cout<<d[dicCount].retriveStr(prevcode);

	while(iss >> num) {
		currentcode = num;

		string s = d[dicCount].retriveStr(currentcode);

		if(s.empty()) {

			string dest = d[dicCount].retriveStr(prevcode);

			dest.append(1,dest[0]);

			cout<<dest;

			d[dicCount].addNum(currentcode, dest);
	
			prevcode = currentcode;

			counter = ++currentcode;

		} else {

			cout<<s;
			
			ch = s[0];

			d[dicCount].addNum(counter++, 
								d[dicCount].retriveStr(prevcode).append(1,ch));

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

					infile.open(optarg, ifstream::in);

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

	string line;
	while(getline(infile,line)) {
		deCompress(line);		
		counter = 5;
	}
	cout<<endl;
//	d[2].print(5);
}
