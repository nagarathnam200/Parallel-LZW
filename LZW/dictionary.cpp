#include "dictionary.h"

dictionary::dictionary() {

	int i;

	for(i=0;i<COUNT;i++) {
		decode[i].append(1,(char)(97+i));
		dict[decode[i]] = i;
	}
}
void dictionary::add(string key, int value) {

	if(dict.size() == 5000) {
		return;
	}
	dict[key] = value;

}

void dictionary::addNum(int key, string value) {

	 if(decode.size() == 5000) {
        return;
    }

	decode[key] = value;
}
int dictionary::retrive(string key) {

	if(dict.find(key) == dict.end()) {
		return -1;
	} else {
		return dict[key];
	}

}

string dictionary:: retriveStr(int key) {
	if(decode.find(key) == decode.end()) {
		string s;
		return s;
	} else {
		return decode[key];
	}
}

void dictionary::print(int flag) {

	if(flag == 0) {
		for( map<string, int>::iterator ii=dict.begin(); ii!=dict.end(); ++ii) {
	
			cout << (*ii).first << ": " << (*ii).second << endl;
		}
	
	} else {

		for( map<int, string>::iterator ii=decode.begin(); ii!=decode.end(); ++ii) {

            cout << (*ii).first << ": " << (*ii).second << endl;

		}

	}
}
