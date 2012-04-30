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
#define MAGIC 9999

using namespace std;


hashTable::hashTable() {

	size = 0;

	collision = 0;

	getEffort = 0;

}
void hashTable::add(string &key, int value) {


	int i=0;

	unsigned int pos = 0;

	for(i=0;i<key.size();i++) {
	
		 pos = (pos << 2) ^ (key[i] & 7);

	}

    pos = (pos * i) % SIZE;

	collision++;

	while(!(dict[pos].str.empty())) {

		pos = (pos + 1) % SIZE;

		collision++;

	}


	dict[pos].str = key;
	dict[pos].worth = value;

	size++;

}

void hashTable::addNum(int key, string value) {

	int pos = key % SIZE;

	while(!(decode[pos].str.empty())) {

        pos = (pos + 1) % SIZE;

    }

	decode[pos].str = value;
	decode[pos].worth = key;

}

int hashTable::retrive(string &key) {

	int i=0;

    unsigned int pos = 0;

	for(i=0;i<key.size();i++) {

         pos = (pos << 2) ^ (key[i] & 7);

    }

    pos = (pos * i) % SIZE;

	int flag = 0;

	int stop = 0;


	while(!stop) {

		if(dict[pos].str.empty()) {
			stop = 1; continue;
		}

		if((dict[pos].str.compare(key)) != 0) {
		
			pos = (pos + 1)	% SIZE;	

			getEffort++;

		} else {

			flag = 1;

			stop = 1;
		
			getEffort++;

		}

	}

	if(flag) {

		return dict[pos].worth;

	} else {

		return -1;

	}

}
	
string hashTable::retriveStr(int key) {

	int pos = key % SIZE;

	int flag = 0;

    int stop = 0;

    while(!stop) {

        if(decode[pos].str.empty()) {

            stop = 1; continue;

        }

        if(decode[pos].worth != key) {

            pos = (pos + 1) % SIZE;

        } else {

            flag = 1;

            stop = 1;

        }

    }

    if(flag) {

        return decode[pos].str;

    } else {

        return "";

    }


}
long int hashTable::getSize() {

	return size;
}
long int hashTable::getCollision() {

	return collision;

}
long int hashTable::getRetEffort() {

	return getEffort;

}
