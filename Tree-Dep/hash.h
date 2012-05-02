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

#define SIZE 100000
using namespace std;

class node{

public:

	int* str;

	int worth;

	int len;

	node() {

		len = -1;

	}

};

class hashTable {

	node dict[SIZE];
    node decode[SIZE];
	long int size;
	long int collision;
	long int getEffort;
	public:

	hashTable();

	void add(int *key, int value, int len);
	void addNum(int key, string value);
	int retrive(int *key, int len);
	string retriveStr(int key);
	void print();
	long int getSize();
	long int getCollision();
	long int getRetEffort();
};
