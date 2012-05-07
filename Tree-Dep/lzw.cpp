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

double gettime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}


vector<int> compressData(int *source, int start, int end, int procs, double* timer, double* rtimer, int* acount, int* rcount) {


	vector<int> result;

	start+=1;

	int count = COUNT;
    int index;
	double s;
	double e;

	if(start > end) {	//One Corner case
		result.push_back(d[procs].retrive(source , 1));
	}

	int prevIndex = d[procs].retrive(source, 1);
	int i = 1;

//	cout<<endl<<"Start is : "<<start<<"End is :"<<end<<endl;

	while(start <= end) {
	
		index = d[procs].retrive(source, i);

		if(index == -1) {

			if((procs % 2) == 0) {

				int tProcs = procs;

				tProcs = tProcs / 2;

				while(tProcs > 0 && index == -1) {

					index = d[tProcs].retrive(source, i);

					tProcs = tProcs / 2;

				}

			} else {

				int tProcs = procs;

				tProcs = tProcs / 3;

                while(tProcs > 0 && index == -1) {

                    index = d[tProcs].retrive(source, i);

					tProcs = tProcs / 3;

                }

			}

		}
		if(index == -1) {

			d[procs].add(source, count,i);
			count++;
			result.push_back(prevIndex);

//			cout<<endl<<"Start..."<<start; 
//			cout<<endl<<d.retrive(temp.substr(0, temp.length()-1));
			source = source + (i-1);

			i = 1;
		} else{
			i++;
			start++;
			prevIndex = index;
			
			if(start == end) {
				index = d[procs].retrive(source, i);
				if(index == -1) {
					result.push_back(prevIndex);
					result.push_back(source[i - 1]);
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

	vector<int> res[(2*MAXPROCS - 1)];

	double start = gettime();

	double diff = 0;

	double lookup = 0;

	double diffProcs[MAXPROCS];

//	double hashTableTimeAdd[MAXPROCS];

//	double hashTableTimeRetrive[MAXPROCS];

//	int countAdd[MAXPROCS];

//	int countRetrive[MAXPROCS];

	int *data[(2*MAXPROCS - 1)];
	int dataSize[(2*MAXPROCS - 1)];

	char *flag;

	flag = (char *) calloc((2*MAXPROCS - 1),  sizeof(char));

	flag[0] = 1;

//	int *tmp[MAXPROCS];

	int numBlocks = (2*numOfProcs - 1 );

	#pragma omp parallel for firstprivate(filename, size, numBlocks, numOfProcs) shared(data)
    for(i=1;i<=numBlocks;i++) {
		
		data[i] = (int *)malloc(sizeof(int) * ((size/numBlocks) + 1));

        int readSize = readChunk(data[i], filename, (i), numOfProcs);

        data[i][(readSize)] = '\0';
		
		dataSize[i] = readSize;

	}


	double sComp = gettime();

	#pragma omp parallel for firstprivate(filename, size, numOfProcs, dataSize, data) shared(res) 
	for(i=1;i<=numOfProcs;i++) {

//		hashTableTimeAdd[i] = 0;

//		hashTableTimeRetrive[i] = 0;

//		countAdd[i] = 0;

//		countRetrive[i] = 0;

		double TimeHashTableAdd = 0;

		double TimeHashTableRetrive = 0;

		int cAdd = 0;

		int cRet = 0;

		int curBlock = (i * 2 - 1);


		int endCond = 2*numOfProcs - 1;

		while(curBlock <= endCond) {

			while(!flag[curBlock]);

//			cout<<endl<<"Strating Chunk: "<<curBlock<<"In Processor: "<<i<<endl;

			res[curBlock] = compressData(data[curBlock], 0, dataSize[curBlock], i, &TimeHashTableAdd, &TimeHashTableRetrive, &cAdd, &cRet);

			flag[2*curBlock] = 1;

			curBlock = curBlock * 2;

			flag[2*curBlock + 1] = 1;

		} 

//		cout<<endl<<"This proc took: "<<(e-s);

//		hashTableTimeAdd[i] += TimeHashTableAdd;

//		hashTableTimeRetrive[i] += TimeHashTableRetrive;

//		countAdd[i] = cAdd;

//		countRetrive[i] = cRet;

	//	lookup+=(TimeHashTable);

	}

	double eComp = gettime();
	


    int j;

	FILE *fp;

	long int elementCount = 0;

	fp = fopen(outfile, "wb");

	fwrite(&size, sizeof(long int), 1, fp);

	fwrite(&numOfProcs, sizeof(int), 1, fp);

//	cout<<endl<<"Collision Details: ";

	double compTime = -1;

    for(j=1;j<=numBlocks;j++) {

		elementCount+=res[j].size();

		if(diffProcs[j] > compTime) {

			compTime = diffProcs[j];

		}

//		cout<<endl<<"Time spent on Adding in HashTable in Processor: "<<j<<" "<<hashTableTimeAdd[j];

		//cout<<endl<<"Entries Added: "<<countAdd[j];

//		cout<<endl<<"Time spent on Retriving in HashTable in Processors: "<<j<<" "<<hashTableTimeRetrive[j];

		//cout<<endl<<"Entries Retrived: "<<countRetrive[j];

//		cout<<endl<<"Processor: "<<j;

		//cout<<endl<<"Effort for Adding: "<<d[j].getCollision();

		//cout<<endl<<"Effort for retrive: "<<d[j].getRetEffort();

//		cout<<endl<<"Number of Entries in hash Table: "<<d[j].getSize();

//        for(i=0;i<res[j].size();i++) {

//			int c1 = res[j][i];

//			fwrite(&c1, sizeof(int), 1, fp);

//		printf("%d ",c1);

  //      }

	//	int c = -1;

//		fwrite(&c, sizeof(int), 1, fp);

//		printf("%d ",c);

    }

	double end = gettime();

	cout<<endl<<"Total Number of Procs: "<<numOfProcs;
	cout<<endl<<"The total Time taken is : "<<end - start;
	cout<<endl<<"The Computation Time is: "<<eComp - sComp;
	cout<<endl<<"The Element Count is: "<<elementCount;

	long int retEffort = 0;
	for(i=1;i<=numOfProcs;i++) {

			retEffort += d[i].getRetEffort();
	}

	cout<<endl<<"The Net amount of effort on retrivals: "<<retEffort;
	
	fclose(fp);
}
