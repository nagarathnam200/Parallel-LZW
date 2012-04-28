#include <string.h>
#include <iostream>
#include <fstream>
#include <omp.h>
#include "util.h"

#include "dictionary.h"

#define LOWERA 97
#define MAXPROCS 16
using namespace std;

dictionary d[MAXPROCS];

double gettime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}


void compressData(string source, int start, int end, int proc, double* timer, double* rtimer, int* acount, int* rcount) {

			double s;

			double e;

			s = gettime();
			d[proc].add("Naga", 6);
			e = gettime();
			#pragma omp critical
			{
			cout<<endl<<"The Time taken to add in proc: "<< proc <<" : "<<(e-s);
			}

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

	#pragma omp parallel 
	{
	#pragma omp for firstprivate(filename, size, numOfProcs)
	for(i=0;i<numOfProcs;i++) {

		diffProcs[i] = 0;

		hashTableTimeAdd[i] = 0;

		hashTableTimeRetrive[i] = 0;

		countAdd[i] = 0;

		countRetrive[i] = 0;

		char *data = (char *)malloc(sizeof(char) * (size/numOfProcs));

		readChunk(data, filename, (i+1));

		string str(data);

		double TimeHashTableAdd = 0;

		double TimeHashTableRetrive = 0;

		double s = gettime();

		compressData(str, 0, (size)/numOfProcs, i, &TimeHashTableAdd, &TimeHashTableRetrive, &countAdd[i], &countRetrive[i]);

		double e = gettime();

//		cout<<endl<<"This proc took: "<<(e-s);

		diffProcs[i] += (e-s);

		hashTableTimeAdd[i] += TimeHashTableAdd;

		hashTableTimeRetrive[i] += TimeHashTableRetrive;

	//	lookup+=(TimeHashTable);

	}
	}

    int j;

	FILE *fp;

	long int elementCount = 0;

	fp = fopen(outfile, "wb");

	fwrite(&size, sizeof(long int), 1, fp);

	fwrite(&numOfProcs, sizeof(int), 1, fp);

	//cout<<endl<<"Collision Details: ";

    for(j=0;j<numOfProcs;j++) {

		elementCount+=res[j].size();

		//cout<<endl<<"Computation time on Processor: "<<j<<" "<<diffProcs[j];

		//cout<<endl<<"Time spent on Adding in HashTable in Processor: "<<j<<" "<<hashTableTimeAdd[j];

		//cout<<endl<<"Entries Added: "<<countAdd[j];

		//cout<<endl<<"Time spent on Retriving in HashTable in Processors: "<<j<<" "<<hashTableTimeRetrive[j];

		//cout<<endl<<"Entries Retrived: "<<countRetrive[j];

		//cout<<endl<<"Processor: "<<j;

		//cout<<endl<<"Effort for Adding: "<<d[j].getCollision();

		//cout<<endl<<"Effort for retrive: "<<d[j].getRetEffort();

		//cout<<endl<<"Number of Entries in hash Table: "<<d[j].getSize();

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

	//cout<<endl<<"Total Number of Procs: "<<numOfProcs;
	//cout<<endl<<"The total Time taken is : "<<end - start;
//	cout<<endl<<"The Element Count is: "<<elementCount;
	
	fclose(fp);
}
