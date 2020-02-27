#include <string.h>
#include <iostream>

using namespace std;
class Sender
{
	string vigKey;
	string message;

public:

	void setOriginalMessage(string M){message = M};
	void setVigKey(string K){vigKey = K};
	string performExtendVigKey();
	string performVignereEncyption();


};

string Sender::performExtendVigKey()
{
	int i = 0;
    string extdKey = vigKey;
    int m_size = message.size();
	while(1)
	{
		if (i == m_size) 	i = 0;
		if (extdKey.size() == m_size)
			break;
		extdKey.push_back(vigKey[i]);

		i++;
	}
	return extdKey;
}

string Sender::performVignereEncyption()
{
	    int mSize = message.size();
	   string Cv;
	   string vigKey = performExtendVigKey();

	    for (int i = 0; i < mSize; i++)

	        Cv.push_back( ( (message[i] + vigKey[i]) %26 )+95);

	    return Cv;

}

