#include "Vignere.h"
#include "RSA.h"
#include <fstream>
#include <assert.h>
#include <math.h>
#include <vector>


#define CA_PUBLIC_KEY		0
#define CA_N				1
#define BOB_PRIVATE_KEY		2
#define BOB_N				3
#define ALICE_PUBLIC_KEY	4
#define ALICE_N				5

std::vector<string> vec;


mpz_class ReadCAPrivateKey()
{
	mpz_class	 pkCA;
	std::ifstream file("Bob.key");
	if (file.is_open()) {
		std::string line;

		int i = 1;
		int flag;
		while (getline(file,line)) {

			if(i == 3){
				flag = pkCA.set_str(line,10);
				assert (flag == 0);
				break;
			}
			i++;
		}
		file.close();
	}

	return pkCA;
}

mpz_class ReadCA_N()
{
	mpz_class	 pkCA;
	std::ifstream file("Bob.key");
	if (file.is_open()) {
		std::string line;

		int i = 1;
		int flag;
		while (getline(file,line)) {

			if(i == 4){
				flag = pkCA.set_str(line,10);
				assert (flag == 0);
				break;
			}
			i++;
		}
		file.close();
	}

	return pkCA;
}


mpz_class ReadAlicePublicKey()
{
	mpz_class	 pkA;
	std::ifstream file("../CA/Public.key");
	if (file.is_open()) {
		std::string line;

		int i = 0;
		int flag;
		while (getline(file,line)) {

			if((i++) == 1){
				flag = pkA.set_str(line,10);
				assert (flag == 0);

			}
		}
		file.close();
	}

	return pkA;

}
mpz_class ReadAlice_N()
{
	mpz_class	 n;
	std::ifstream file("../CA/Public.key");
	if (file.is_open()) {
		std::string line;

		int i = 0;
		int flag;
		while (getline(file,line)) {

			if((i++) == 2){
				flag = n.set_str(line,10);
				assert (flag == 0);

			}
		}
		file.close();
	}

	return n;

}

void ReadCommFile()
{

	std::ifstream file("Bob.comm");
	if (file.is_open()) {
		std::string line;

		int i = 1;
		int flag;
		while (getline(file,line)) {
			vec.push_back(line);
			i++;
		}
		file.close();
	}

}


mpz_class ReadCommFileMessageCipher()
{
	mpz_class	 n;
	std::ifstream file("Bob.comm");
	if (file.is_open()) {
		std::string line;

		int i = 1;
		int flag;
		while (getline(file,line)) {

			if(i == 1){
				flag = n.set_str(line,10);
				assert (flag == 0);

			}
			i++;
		}
		file.close();
	}

	return n;
}

mpz_class ReadCommFileKeyCipher()
{
	mpz_class	 n;
	std::ifstream file("Bob.comm");
	if (file.is_open()) {
		std::string line;

		int i = 1;
		int flag;
		while (getline(file,line)) {

			if(i == 2){
				flag = n.set_str(line,10);
				assert (flag == 0);

			}
			i++;
		}
		file.close();
	}

	return n;
}

mpz_class ReadBobPrivateData(int val)
{
	mpz_class	 pk;
	std::ifstream file("Bob.key");
	if (file.is_open()) {
		std::string line;

		int i = 1;
		int flag;
		while (getline(file,line)) {


			if( (val == BOB_PRIVATE_KEY && i == 1 ) || (val == BOB_N && i == 2 ) )
			{
				flag = pk.set_str(line,10);
				assert (flag == 0);
				break;

			}
			i++;
		}
		file.close();
	}

	return pk;
}

void ReadBlockAndKeySize(mpz_class &b,mpz_class &k)
{
	std::ifstream file("Bob.comm");
	if (file.is_open()) {
		std::string line;

		int i = 1;
		int flag;
		while (getline(file,line)) {


			if( i == 3 )
			{
				flag = b.set_str(line,10);
				assert (flag == 0);

			}
			if( i == 4 )
			{
				flag = k.set_str(line,10);
				assert (flag == 0);
				break;

			}
			i++;
		}
		file.close();
	}

}
string convertNumbertoText(mpz_class C, unsigned int strSize)
{
	string str;
	for(int i = strSize-1; i>=0;i--)
	{
		mpz_class X,P;
		mpz_ui_pow_ui(P.get_mpz_t(),26,i);
		mpz_fdiv_q(X.get_mpz_t(),C.get_mpz_t(),P.get_mpz_t());
		C = C%P;
		str += ('a' + X.get_ui());

	}

	reverse(str.begin(),str.end());
	return str;
}


string computeRSA(mpz_class Alice_e,mpz_class Alice_n, mpz_class Bob_d,mpz_class Bob_n, mpz_class Text,mpz_class BLOCK_SIZE)
{
	string S="";
	string tmp = Text.get_str(10);

	string str;
	unsigned i = 0;
	unsigned int bSize = BLOCK_SIZE.get_ui();

	cout<<" bSize  = "<<bSize<<endl;

	if(Bob_n<Alice_n)
	{
		if( (Text<Bob_n)||(Text <Alice_n) )
		{
			RSA obj;
			mpz_class Eb_Cs = obj.performDecryption(Text,Alice_e,Alice_n);
			mpz_class Cs = obj.performDecryption(Eb_Cs,Bob_d,Bob_n);

			S += convertNumbertoText(Cs,bSize);
			cout<<"1. SHINI = "<<S<<endl;

		}
		else
		{
			cout<< "1. THIS SECTION"<<endl;
			while(tmp.size()){
				str.clear();
				string X = Text.get_str(10);
				if(tmp.size()>=bSize)
				{
					str = X.substr(i,bSize);
					tmp.erase(0,bSize);
				}
				else
				{
					str =	tmp;
					tmp.clear();
				}


				i += bSize;


				RSA obj;
				mpz_class STR;
				STR.set_str(str,10);
				mpz_class Eb_Cs = obj.performDecryption(STR,Alice_e,Alice_n);
				mpz_class Cs = obj.performDecryption(Eb_Cs,Bob_d,Bob_n);

				S += convertNumbertoText(Cs,bSize);
			}
		}

	}
	else
	{
		if( (Text<Bob_n)||(Text <Alice_n) )
		{
			RSA obj;
			mpz_class Eb_Cs = obj.performDecryption(Text,Bob_d,Bob_n);
			mpz_class Cs = obj.performDecryption(Eb_Cs,Alice_e,Alice_n);

			S += convertNumbertoText(Cs,bSize);
			cout<<"2. SHINI = "<<S<<endl;


		}
		else
		{
			cout<< "2. THIS SECTION"<<endl;
			while(tmp.size()){
				str.clear();
				string X = Text.get_str(10);
				if(tmp.size()>=bSize)
				{
					str = X.substr(i,bSize);
					tmp.erase(0,bSize);
				}
				else
				{
					str =	tmp;
					tmp.clear();
				}


				i += bSize;


				RSA obj;
				mpz_class STR;
				STR.set_str(str,10);
				mpz_class Eb_Cs = obj.performDecryption(STR,Alice_e,Alice_n);
				mpz_class Cs = obj.performDecryption(Eb_Cs,Bob_d,Bob_n);

				S += convertNumbertoText(Cs,bSize);
			}
		}
	}


	return S;

}

int main()
{

	cout<<"\n\n################################ USER :: BOB #####################################"<<endl;


	/******* Extraction of CA private key and n  CA(d,n) from Alice file *******************************/
	mpz_class CA_d = ReadCAPrivateKey();
	mpz_class CA_n = ReadCA_N();

	/******** Extraction of Alice's Encrypted Public key and its n  from public file *********************/
	mpz_class Cip_Alice_e =  ReadAlicePublicKey();
	mpz_class Cip_Alice_n =  ReadAlice_N();

	RSA obj;
	mpz_class Alice_e =  obj.performDecryption(Cip_Alice_e,CA_d,CA_n);
	mpz_class Alice_n =  obj.performDecryption(Cip_Alice_n,CA_d,CA_n);


	mpz_class Bob_d = ReadBobPrivateData(BOB_PRIVATE_KEY);
	mpz_class Bob_n = ReadBobPrivateData(BOB_N);

	ReadCommFile();

	string CipM,VigKey;
	for(int i = 0;i<vec.size();i = i+2)
	{
		if(!vec[i].compare("$")) break;

		mpz_class Data,B_SIZE;
		Data.set_str(vec[i],10);
		B_SIZE.set_str(vec[i+1],10);
		CipM += computeRSA(Alice_e,Alice_n,Bob_d,Bob_n, Data, B_SIZE);
	}
	bool flag = false;
	for(int i = 0;i<vec.size()-1;i = i+2)
	{
		if(!vec[i].compare("$")){
			flag = true;
			i = i-1;
			continue;
		}
		if(flag)
		{
			mpz_class Data,B_SIZE;
			Data.set_str(vec[i],10);
			B_SIZE.set_str(vec[i+1],10);
			VigKey += computeRSA(Alice_e,Alice_n,Bob_d,Bob_n, Data, B_SIZE);

		}
	}


	cout<<" BOB:: CipM   "<<CipM<<endl;
	cout<<" BOB:: VigKey "<<VigKey<<endl;

	Vignere V;
	string M = V.performVignereDecryption(CipM,VigKey);

	cout<<"M = "<<M<<endl;

	cout<<endl;


	return 0;
}
