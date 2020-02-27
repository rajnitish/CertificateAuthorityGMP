#include "Sender.h"
#include <iostream>

using namespace std;

int main(void) {

	Sender obj;
	obj.setVigKey("AYUSHAYUSHAYUSH");
	obj.setOriginalMessage("GEEKSFORGEEKS");
	cout<<obj.performVignereEncyption()<<endl;

	return 0;
}

