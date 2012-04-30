#include <string.h>
#include <iostream>
#include <fstream>
#include <omp.h>
#include "util.h"

#include "dictionary.h"

#define LOWERA 97
#define MAXPROCS 16
using namespace std;

//dictionary d[MAXPROCS];

double gettime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}


vector<int> compressData(char* source, int start, int end, int procs, double* timer, double* rtimer, int* acount, int* rcount) {

	vector<int> result;

	dictionary di;

	char *temp = (char *) calloc(end, sizeof(char));
	
	int curTemp = 0;

//	string temp;

	temp[curTemp++] = source[start];

	start+=1;

	int count = COUNT;
    int index;
	double s;
	double e;

	if(start > end) {	//One Corner case
		result.push_back(di.retrive(temp));
	}

//	s = gettime();
	int prevIndex = di.retrive(temp);

//	cout<<endl<<"Prev Index is: "<<prevIndex;
//	*rcount = *rcount + 1;
//	e = gettime();
//	*rtimer += (e-s);
	while(start <= end) {
//		s = gettime();
		index = di.retrive(temp);

//		cout<<endl<<"In the index:"<<index<<" is the string "<<temp;
//		*rcount = *rcount + 1;
//		e = gettime();
  //      *rtimer += (e-s);

		if(index == -1) {

//			cout<<endl<<"Added: "<<temp<<" "<<count;
//			s = gettime();
			di.add(temp, count);
//			*acount = *acount + 1;
//			e = gettime();
//		    *timer += (e-s);

			count++;
			result.push_back(prevIndex); 
//			cout<<endl<<d.retrive(temp.substr(0, temp.length()-1));
			curTemp--;

			temp = temp + curTemp;

			curTemp = 1;
			
		//	temp.erase(temp.begin(),temp.end()-1);
		//	start++;//------------------>Delete this!!!!!
		} else{
			temp[curTemp++] = source[start];
			start++;
			prevIndex = index;
			
			if(start == end) {
//				s = gettime();
				index = di.retrive(temp);
//				*rcount = *rcount + 1;
//				e = gettime();
//			    *rtimer += (e-s);

				if(index == -1) {
					result.push_back(prevIndex);
					result.push_back(temp[curTemp - 1]-LOWERA);
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

	#pragma omp parallel for firstprivate(filename, size, numOfProcs) shared(data)
    for(i=0;i<numOfProcs;i++) {
		
		data[i] = (char *)malloc(sizeof(char) * ((size/numOfProcs) + 1));

        readChunk(data[i], filename, (i+1));

        data[i][(size/numOfProcs)] = '\0';
	}


	double sComp = gettime();

	#pragma omp parallel for firstprivate(filename, size, numOfProcs) shared(data)
	for(i=0;i<numOfProcs;i++) {

//		hashTableTimeAdd[i] = 0;

//		hashTableTimeRetrive[i] = 0;

//		countAdd[i] = 0;

//		countRetrive[i] = 0;

		double TimeHashTableAdd = 0;

		double TimeHashTableRetrive = 0;

		int cAdd = 0;

		int cRet = 0;

		res[i] = compressData(data[i], 0, (size)/numOfProcs, i, &TimeHashTableAdd, &TimeHashTableRetrive, &cAdd, &cRet);

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

    for(j=0;j<numOfProcs;j++) {

		elementCount+=res[j].size();

//		cout<<endl<<"Time spent on Adding in HashTable in Processor: "<<j<<" "<<hashTableTimeAdd[j];

		//cout<<endl<<"Entries Added: "<<countAdd[j];

//		cout<<endl<<"Time spent on Retriving in HashTable in Processors: "<<j<<" "<<hashTableTimeRetrive[j];

		//cout<<endl<<"Entries Retrived: "<<countRetrive[j];

//		cout<<endl<<"Processor: "<<j;

		//cout<<endl<<"Effort for Adding: "<<d[j].getCollision();

		//cout<<endl<<"Effort for retrive: "<<d[j].getRetEffort();

//		cout<<endl<<"Number of Entries in hash Table: "<<d[j].getSize();

        for(i=0;i<res[j].size();i++) {

			int c1 = res[j][i];

			fwrite(&c1, sizeof(int), 1, fp);

	//		printf("%d ",c1);

        }

		int c = -1;

		fwrite(&c, sizeof(int), 1, fp);

	//	printf("%d ",c);

    }

	double end = gettime();

	cout<<endl<<"Total Number of Procs: "<<numOfProcs;
	cout<<endl<<"The total Time taken is : "<<end - start;
	cout<<endl<<"The Computation Time is: "<<eComp - sComp;
	cout<<endl<<"The Element Count is: "<<elementCount;
	
	fclose(fp);
}
