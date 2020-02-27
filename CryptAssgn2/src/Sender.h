#include <string.h>
#include <iostream>
#include <math.h>

using namespace std;
class Sender
{
	string vigKey;
	string message;

public:

	void setOriginalMessage(string M){message = M;};
	void setVigKey(string K){vigKey = K;};
	string performExtendVigKey();
	string performVignereEncyption();


};
