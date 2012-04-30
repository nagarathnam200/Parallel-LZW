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
#include "hash.h"

#define COUNT 5

#define DICSIZE 500
using namespace std;

class dictionary {

	hashTable ht;

	public:
	dictionary();
	void add(int *key, int value);
	void addNum(int value, string key);
	int retrive(int *key);
	string retriveStr(int value);
	long int getCollision();
	long int getRetEffort();
	long int getSize();
};
