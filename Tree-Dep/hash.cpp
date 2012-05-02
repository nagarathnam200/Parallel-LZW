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

#define MAGIC 9999

using namespace std;

int cmpare(int *str, int strLen, int *keyP, int keyPlen) {


	if(strLen != keyPlen) {

		return 0;

	} else {
	
		int i=0;
		while(i<strLen) {

			if(str[i] != keyP[i]) {

				return 0;

			}

			i++;

		}

		return 1;

	}

}
hashTable::hashTable() {


	size = 0;

	collision = 0;

	getEffort = 0;

}
void hashTable::add(int *keyP, int value, int len) {

	//string key(keyP);
	int i=0;

	unsigned int pos = 0;

	for(i=0;i<len;i++) {
	
		 pos = (pos << 2) ^ (keyP[i]);

	}

    pos = (pos * i) % SIZE;

//	collision++;

	while(!(dict[pos].len == -1)) {

		pos = (pos + 1) % SIZE;

//		collision++;

	}


//	memcpy(dict[pos].str, keyP, (len + 1) * sizeof(int));/*Also copy the null character*/
	dict[pos].str = keyP;
	dict[pos].worth = value;
	dict[pos].len = len;

	size++;

}

void hashTable::addNum(int key, string value) {

	int pos = key % SIZE;

	while(!(decode[pos].len == -1)) {

        pos = (pos + 1) % SIZE;

    }

	int len = value.size();

	int i;

	for(i=0;i<len;i++) {

		decode[pos].str[i] = value[i];

	}
	decode[pos].worth = key;
	decode[pos].len = len;

}

int hashTable::retrive(int *keyP, int len) {


	int i=0;

    unsigned int pos = 0;

	for(i=0;i<len;i++) {

         pos = (pos << 2) ^ (keyP[i]);

    }

    pos = (pos * i) % SIZE;

	int flag = 0;

	int stop = 0;

	while(!stop) {


		if(dict[pos].len == -1) {
			stop = 1; continue;
		}

		if(cmpare(dict[pos].str, dict[pos].len, keyP, len) != 1) {
		
			pos = (pos + 1)	% SIZE;	

//			getEffort++;

		} else {

			flag = 1;

			stop = 1;
		
//			getEffort++;

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

        if(decode[pos].len == -1) {

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

		 return "";

        //return decode[pos].str;

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
