#include "dictionary.h"

dictionary::dictionary() {

	int *arr[COUNT];

	int i;

	for(i=1;i<COUNT;i++) {

		arr[i] = (int *) malloc(2*sizeof(int));

		arr[i][0] = i;
		arr[i][1] = 0;
	
		ht.add(arr[i], i, 1);
	}	

//	ht.addNum(0,"a");
//	ht.addNum(1,"b");
//	ht.addNum(2,"c");
//	ht.addNum(3,"d");
//	ht.addNum(4,"e");
}
void dictionary::add(int *key, int value, int len) {

	if(ht.getSize() > DICSIZE) return;
	ht.add(key, value, len);

}

void dictionary::addNum(int key, string value) {

	ht.addNum(key,value);
}
int dictionary::retrive(int *key, int len) {

//	cout<<endl<<"Retriving Key: "<<key;	
	return ht.retrive(key, len);

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
