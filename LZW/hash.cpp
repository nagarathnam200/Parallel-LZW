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
using namespace std;

hashTable::hashTable(): dict(500),decode(500) {

}
void hashTable::add(string key, int value) {

	if(value > 1000) return;

	int i=0;

	int pos = 0;

	for(i=0;i<key.size();i++) {

		pos += (i*key[i]);

		pos = pos % 500;

	}

	dict[pos][key] =  value;

	

}

void hashTable::addNum(int key, string value) {


	int pos = key % 500;

	decode[pos][key] = value;
}

int hashTable::retrive(string key) {

	int i=0;

    int pos = 0;

    for(i=0;i<key.size();i++) {

        pos += (i*key[i]);

        pos = pos % 500;

    }

	
    if(dict[pos].find(key) == dict[pos].end()) {
                return -1;
    } else {
                return dict[pos][key];
    }

}
	
string hashTable::retriveStr(int key) {

	int pos = key % 500;

	if(decode[pos].find(key) == decode[pos].end()) {

			return "";

	} else {
			return decode[pos][key];
	}

}
