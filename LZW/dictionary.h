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

using namespace std;

class dictionary {

        map<string, int> dict;
		map<int, string> decode;
	public:
	dictionary();
	void add(string key, int value);
	void addNum(int value, string key);
	int retrive(string key);
	string retriveStr(int value);
	void print(int flag);
};
