#include <string.h>
#include <iostream>
#include <math.h>
#include <limits.h>
#include <gmp.h>
#include <gmpxx.h>


using namespace std;
class Vignere
{
	string vigKey;
	string plainVig;
	string CipVig;

public:

	void setOriginalMessage(string M){plainVig = M;};
	void setVigKey(string K){vigKey = K;};
	void setCipVig(string K){CipVig = K;};

	string performExtendVigKey(int TextSize, string key);
	string performVignereEncyption(string,string);
	string performVignereDecryption(string,string);


};
