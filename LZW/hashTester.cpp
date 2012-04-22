#include "hash.h"

int main() {

	hashTable h;

	h.add("Naga",1);

	h.add("Karthi",2);

	h.add("Sridhar",3);

	h.addNum(3, "Sridhar");

	h.addNum(2, "Karthi");

	h.addNum(1,"Naga");

	cout<<h.retrive("Naga");

	cout<<h.retriveStr(1);

	cout<<h.retrive("Karthi");

	cout<<h.retriveStr(2);

	cout<<h.retrive("Sridhar");

	cout<<h.retriveStr(3);




}
