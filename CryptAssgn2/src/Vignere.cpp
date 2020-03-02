#ifndef Sender_cpp
#define Sender_cpp

#include "Vignere.h"


string Vignere::performExtendVigKey()
{
	int i = 0;
	string extdKey= vigKey;
	int m_size = plainVig.size();
	while(1)
	{
		if (i == vigKey.size()) 	i = 0;
		if (extdKey.size() >= m_size)
			break;
		extdKey.push_back(vigKey[i]);
		i++;
	}
	return extdKey;
}

string Vignere::performVignereEncyption()
{
	int mSize = plainVig.size();
	string Cv;
	string vigKey = performExtendVigKey();

	for (int i = 0; i < mSize; i++)
		Cv.push_back( fmod((plainVig[i] + vigKey[i]),26 ) + 97);

	return Cv;

}

#endif

