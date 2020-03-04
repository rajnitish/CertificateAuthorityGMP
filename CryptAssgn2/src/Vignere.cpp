#ifndef Sender_cpp
#define Sender_cpp

#include "Vignere.h"


string Vignere::performExtendVigKey(int TextSize, string key)
{
	int i = 0;
	string extdKey;
	while(1)
	{
		if (i == key.size()) 	i = 0;
		if (extdKey.size() >= TextSize)
			break;
		extdKey.push_back(key[i]);
		i++;
	}
	return extdKey;
}


string Vignere::performVignereEncyption(string Text,string Key)
{
	string Cv;
	string vigKey = performExtendVigKey(Text.size(),Key);



	for (int i = 0; i < Text.size(); i++)
	{

		int e = fmod((tolower(Text[i])- 97 + tolower(vigKey[i]) - 97),26 );
		Cv += 'a' + e;
	}

	return Cv;

}

string Vignere::performVignereDecryption(string Cip,string Key)
{
	string P;
	string vigKey = performExtendVigKey(Cip.size(),Key);

	for (int i = 0; i < Cip.size(); i++)
	{
		int d = Cip[i] - vigKey[i] + 26;
		P += 'a' + fmod((d+26),26 );
	}

	return P;

}

#endif

