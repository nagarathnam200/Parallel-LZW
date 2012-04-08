#include "dictionary.h"

dictionary::dictionary() {
	decode[0] = "a";
	decode[1] = "b";
	decode[2] = "c";
	decode[3] = "d";
	dict["a"] = 0;
	dict["b"] = 1;
	dict["c"] = 2;
	dict["d"] = 3;
}
void dictionary::add(string key, int value) {

	if(dict.size() == 500) {
		return;
	}
	dict[key] = value;

}

void dictionary::addNum(int key, string value) {

	 if(decode.size() == 500) {
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
