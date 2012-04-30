#include <string.h>
#include <iostream>
#include <fstream>
#include <omp.h>
#include "util.h"

#include "dictionary.h"

#define LOWERA 97
#define MAXPROCS 16
using namespace std;

double gettime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}


vector<int> compressData(string source, int start, int end, int proc) {

	vector<int> result;

	dictionary d;

	string temp;

	temp.append(source, start, 1);

	start+=1;

	int count = COUNT;
    int index;
	double s;
	double e;

	if(start > end) {	//One Corner case
		result.push_back(d.retrive(temp));
	}

	int prevIndex = d.retrive(temp);
	while(start <= end) {
		index = d.retrive(temp);
		if(index == -1) {

//			cout<<endl<<"Added: "<<temp<<" "<<count;
			d.add(temp, count);
			count++;
			result.push_back(prevIndex); 
//			cout<<endl<<d.retrive(temp.substr(0, temp.length()-1));
			temp.erase(temp.begin(),temp.end()-1);
		} else{
			temp.append(source, start, 1);
			start++;
			prevIndex = index;
			
			if(start == end) {
				index = d.retrive(temp);
				if(index == -1) {
					result.push_back(prevIndex);
					result.push_back(temp[temp.length()-1]-LOWERA);
				} else {
					result.push_back(index);
				}
				start++;
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
	strcat(outfile, filename);
    long int size = readSize(filename);

	int i;

	vector<int> res[MAXPROCS];

	double start = gettime();

	double diff = 0;

	double lookup = 0;

	double diffProcs[MAXPROCS];

	double hashTableTimeAdd[MAXPROCS];

	double hashTableTimeRetrive[MAXPROCS];

	int countAdd[MAXPROCS];

	int countRetrive[MAXPROCS];

	char *data[MAXPROCS];

	#pragma omp parallel for
	for(i=0;i<numOfProcs;i++) {
		
		data[i] = (char *)malloc(sizeof(char) * (size/numOfProcs));

		readChunk(data[i], filename, (i+1));

	}

	double sComp = gettime();
	#pragma omp parallel for firstprivate(filename, size, numOfProcs) shared(data)
	for(i=0;i<numOfProcs;i++) {

		string str(data[i]);

		res[i] = compressData(str, 0, (size)/numOfProcs, i);

//		cout<<endl<<"This proc took: "<<(e-s);

	}
	double eComp = gettime();

    int j;

	FILE *fp;

	long int elementCount = 0;

	fp = fopen(outfile, "wb");

	fwrite(&size, sizeof(long int), 1, fp);

	fwrite(&numOfProcs, sizeof(int), 1, fp);

    for(j=0;j<numOfProcs;j++) {

		elementCount+=res[j].size();

//		cout<<endl<<"Processor "<<j<<" has "<<d[j].getCollision();

        for(i=0;i<res[j].size();i++) {

			int c1 = res[j][i];

			fwrite(&c1, sizeof(int), 1, fp);

//			printf("%d ",c1);

        }

		int c = -1;

		fwrite(&c, sizeof(int), 1, fp);

//		printf("%d ",c);

    }

	double end = gettime();

	cout<<endl<<"Total Number of Procs: "<<numOfProcs;
	cout<<endl<<"The total Time taken is : "<<end - start;
	cout<<endl<<"The Element Count is: "<<elementCount;
	cout<<endl<<"The Computation Time is: "<<eComp - sComp;
	
	fclose(fp);
}
