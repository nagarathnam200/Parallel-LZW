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
#define SIZE 50000
using namespace std;

typedef struct __node{

	string str;
	int worth;

}node;

class hashTable {

	node dict[SIZE];
    node decode[SIZE];
	long int size;
	long int collision;
	public:

	hashTable();

	void add(string key, int value);
	void addNum(int key, string value);
	int retrive(string key);
	string retriveStr(int key);
	void print();
	long int getSize();
	long int getCollision();
};
