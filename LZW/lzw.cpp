#include <string.h>
#include <iostream>
#include <fstream>
#include <omp.h>
#include "util.h"

#include "dictionary.h"

#define LOWERA 97
#define MAXPROCS 256
using namespace std;

dictionary d[MAXPROCS];

vector<int> compressData(string source, int start, int end, int proc) {

	vector<int> result;

	string temp;

	temp.append(source, start, 1);

	start+=1;

	int count = COUNT;
    int index;

	if(start > end) {	//One Corner case
		result.push_back(d[proc].retrive(temp));
	}

	int prevIndex = d[proc].retrive(temp);
	while(start <= end) {
		index = d[proc].retrive(temp);
		if(index == -1) {
			d[proc].add(temp, count);
			count++;
			result.push_back(prevIndex); 
//			cout<<endl<<d.retrive(temp.substr(0, temp.length()-1));
			temp.erase(temp.begin(),temp.end()-1);
		} else{
			temp.append(source, start, 1);
			start++;
			prevIndex = index;
			if(start > end) {
				index = d[proc].retrive(temp);
				if(index == -1) {
					result.push_back(prevIndex);
					result.push_back(temp[temp.length()-1]-LOWERA);
				} else {
					result.push_back(index);
				}
			}
		}

	}

	return result;

}
int main(int argc, char **argv)
{

	int opt;
	
	int numOfProcs = 1;

	char filename[30];

	char outfile[30] = "out";
	

	while((opt = getopt(argc, argv, "p:i:o:")) != -1) {
		switch(opt) {

			case 'p':
				{
					numOfProcs = atoi(optarg);
					omp_set_num_threads(numOfProcs);
					break;
				}
			case 'i':
				{
					strcpy(filename,optarg);
                	break;

				}
			case 'o':
            {
				strcpy(outfile, optarg);
                break;
            }

		}
	}

    long int size = readSize(filename);

	int i;

	vector<int> res[MAXPROCS];



	#pragma omp parallel for firstprivate(filename, size, numOfProcs)
	for(i=0;i<numOfProcs;i++) {

		char *data = (char *)malloc(sizeof(char) * (size/numOfProcs));

		readChunk(data, filename, (i+1));

		string str(data);

		res[i] = compressData(str, 0, str.length(), i);

	}

    int j;

	FILE *fp;

	fp = fopen(outfile, "wb");

	fwrite(&size, sizeof(long int), 1, fp);

	fwrite(&numOfProcs, sizeof(int), 1, fp);

    for(j=0;j<numOfProcs;j++) {

        for(i=0;i<res[j].size();i++) {

			char c1 = res[j][i];

			fwrite(&c1, sizeof(char), 1, fp);

			printf("%d ",c1);

        }

		char c = (char)255;

		fwrite(&c, sizeof(char), 1, fp);

		printf("%d ",c);

    }

	d[1].print(0);
	fclose(fp);
}
