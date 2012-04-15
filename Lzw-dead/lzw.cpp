#include <string.h>
#include <iostream>
#include <fstream>
#include <omp.h>

#include "dictionary.h"

#define COUNT 5
#define LOWERA 97
#define MAXPROCS 256
using namespace std;

dictionary d[MAXPROCS];

vector<int> compressData(string source, int start, int end, int proc) {

	int length = source.length();

	if(end > length) {

		end = length-1;

	}

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
	
	int numOfProcs = 0;
	

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
					 if (dup2(open(optarg, O_RDONLY), STDIN_FILENO) < 0)
                		{
                   			 perror("");
		                     exit(0);
         		        }

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
	string data;

	cin>>data;



	int load = data.length();

	int perProcessor = load;
	
	if(numOfProcs > 0) {
		
		perProcessor = load/numOfProcs;

	}

	int count =0;

	int k  =0;

	vector<int> res[MAXPROCS];

//	cout<<endl<<"The Load is "<<load;
	#pragma omp parallel firstprivate(data, count,perProcessor)
		{

			#pragma omp for lastprivate(k)
			for(count = 0;count < load;count +=perProcessor) {

//		cout<<endl<<"For Processor: "<<k;
//		cout<<endl<<"Count Starts at : "<<count;
				k = count/perProcessor;
				res[k] = compressData(data, count, count+perProcessor-1,k);
//				#pragma omp critical 

			}
	    }
		
		int i;
		int j;

		#pragma omp barrier
		k+=1;
		for(j=0;j<k;j++) {
	
			for(i=0;i<res[j].size();i++) {
					cout<<res[j][i]<<" ";
			}

			cout<<endl;

		}
}
