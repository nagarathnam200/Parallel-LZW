#include <string.h>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

#define COUNT 5
using namespace std;

class hashTable {

	vector< map<string, int> > dict;
    vector< map<int, string> > decode;


	public:

	hashTable();

	void add(string key, int value);
	void addNum(int value, string key);
	int retrive(string key);
	string retriveStr(int value);
	void print();
};
