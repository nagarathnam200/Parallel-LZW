#include "dictionary.h"

dictionary::dictionary() {

	ht.add("a",0);
	ht.add("b",1);
	ht.add("c",2);
	ht.add("d",3);
	ht.add("e",4);

	ht.addNum(0,"a");
	ht.addNum(1,"b");
	ht.addNum(2,"c");
	ht.addNum(3,"d");
	ht.addNum(4,"e");
}
void dictionary::add(char *key, int value) {

	if(ht.getSize() > DICSIZE) return;
	ht.add(key, value);

}

void dictionary::addNum(int key, string value) {

	ht.addNum(key,value);
}
int dictionary::retrive(char *key) {

//	cout<<endl<<"Retriving Key: "<<key;	
	return ht.retrive(key);

}

string dictionary:: retriveStr(int key) {

	return ht.retriveStr(key);

}

long int dictionary:: getCollision() {

	return ht.getCollision();

}

long int dictionary:: getSize() {

	return ht.getSize();

}

long int dictionary:: getRetEffort() {

	return ht.getRetEffort();

}
/*void dictionary::print(int flag) {

	if(flag == 0) {
		for( map<string, int>::iterator ii=dict.begin(); ii!=dict.end(); ++ii) {
	
			cout << (*ii).first << ": " << (*ii).second << endl;
		}
	
	} else {

		for( map<int, string>::iterator ii=decode.begin(); ii!=decode.end(); ++ii) {

            cout << (*ii).first << ": " << (*ii).second << endl;

		}

	}
}*/
