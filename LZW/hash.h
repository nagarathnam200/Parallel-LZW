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
#define SIZE 5000
using namespace std;

class node{

public:

	int str[6];

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

	void add(int *key, int value);
	void addNum(int key, string value);
	int retrive(int *key);
	string retriveStr(int key);
	void print();
	long int getSize();
	long int getCollision();
	long int getRetEffort();
};
