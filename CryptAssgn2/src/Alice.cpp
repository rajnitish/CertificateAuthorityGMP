#include "Vignere.h"
#include "RSA.h"
#include <fstream>
#include <assert.h>
#include <vector>

#define CA_PUBLIC_KEY		0
#define CA_N				1
#define ALICE_PRIVATE_KEY	2
#define ALICE_N				3
#define BOB_PUBLIC_KEY		4
#define BOB_N				5

mpz_class BLOCK_SIZE;
mpz_class KEY_SIZE;


std::vector<string> vec;

void SendToBob(string E_Cs,string E_K)
{
	ofstream myfile;
	myfile.open("../BOB/Bob.comm",ios::out);

	for(int i = 0 ;i<vec.size();i++)
		myfile<<vec[i]<<endl;

	//myfile<<E_Cs<<endl;
	//myfile<<E_K<<endl;
	//myfile<<"BLOCK_SIZE"<<endl;
	myfile.close();

}



mpz_class ReadAlicePrivateData(int val)
{
	mpz_class	 pkCA;
	std::ifstream file("Alice.key");
	if (file.is_open()) {
		std::string line;

		int i = 1;
		int flag;
		while (getline(file,line)) {

			if( (val == ALICE_PRIVATE_KEY && i == 1 ) || (val == ALICE_N && i == 2 ) )
			{
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

mpz_class ReadCAPrivateKey()
{
	mpz_class	 pkCA;
	std::ifstream file("Alice.key");
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
	std::ifstream file("Alice.key");
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


mpz_class ReadBobPublicKey()
{
	mpz_class	 pkA;
	std::ifstream file("../CA/Public.key");
	if (file.is_open()) {
		std::string line;

		int i = 0;
		int flag;
		while (getline(file,line)) {

			if((i++) == 4){
				flag = pkA.set_str(line,10);
				assert (flag == 0);

			}
		}
		file.close();
	}

	return pkA;

}
mpz_class ReadBob_N()
{
	mpz_class	 n;
	std::ifstream file("../CA/Public.key");
	if (file.is_open()) {
		std::string line;

		int i = 0;
		int flag;
		while (getline(file,line)) {

			if((i++) == 5){
				flag = n.set_str(line,10);
				assert (flag == 0);

			}
		}
		file.close();
	}

	return n;

}

mpz_class convertTexttoNo(string S)
{
	mpz_class C;
	for(int i = 0 ; i<S.size();i++)
	{
		mpz_class P;
		mpz_ui_pow_ui(P.get_mpz_t(),26,i);

		C = C + P*(S[i]-97);

	}
	return C;
}
string computeRSA(mpz_class Alice_d,mpz_class Alice_n, mpz_class Bob_e,mpz_class Bob_n, string Text)
{
	mpz_class M = convertTexttoNo(Text);
	string S;
	string tmp = Text;
	string str;
	unsigned int i = 0;
	mpz_class B_SIZE = Text.size();

	if(Bob_n<Alice_n)
	{
		if( (M<Bob_n)||(M<Alice_n) )
		{
			RSA obj;
			mpz_class Eb_Cs = obj.performEncryption(M,Bob_e,Bob_n);
			mpz_class EaEb_Cs = obj.performEncryption(Eb_Cs,Alice_d,Alice_n);

			vec.push_back(EaEb_Cs.get_str(10));
			vec.push_back(B_SIZE.get_str(10));
			S += EaEb_Cs.get_str(10);
		}

		else
		{
			while(tmp.size())
			{
				mpz_class bSize = 0,bPreSize = 0;
				unsigned int j = 0;
				str.clear();
				while(bPreSize<Bob_n && tmp.size())
				{
					bPreSize = bSize ;
					mpz_class P;
					mpz_ui_pow_ui(P.get_mpz_t(),26,j);
					bSize = bSize + P*(tolower(Text[i])-97);
					if(bSize > Bob_n)
					{
						B_SIZE = j;
						j = 0;
						break;
					}

					str += Text[i];
					tmp.pop_back();
					B_SIZE = j;

					i++;j++;
				}


				RSA obj;
				mpz_class Eb_Cs = obj.performEncryption(bPreSize,Bob_e,Bob_n);
				mpz_class EaEb_Cs = obj.performEncryption(Eb_Cs,Alice_d,Alice_n);


				vec.push_back(EaEb_Cs.get_str(10));
				vec.push_back(B_SIZE.get_str(10));
				S = S + EaEb_Cs.get_str(10);

			}
		}

	}
	else
	{
		if( (M<Bob_n)||(M<Alice_n) )
		{
			RSA obj;
			mpz_class Eb_Cs = obj.performEncryption(M,Alice_d,Alice_n);
			mpz_class EaEb_Cs = obj.performEncryption(Eb_Cs,Bob_e,Bob_n);

			vec.push_back(EaEb_Cs.get_str(10));
			vec.push_back(B_SIZE.get_str(10));
			S += EaEb_Cs.get_str(10);
		}

		else
		{
			while(tmp.size())
			{
				mpz_class bSize = 0,bPreSize = 0;
				unsigned int j = 0;
				str.clear();
				while(bPreSize<Alice_n && tmp.size())
				{
					bPreSize = bSize ;
					mpz_class P;
					mpz_ui_pow_ui(P.get_mpz_t(),26,j);
					bSize = bSize + P*(tolower(Text[i])-97);
					if(bSize > Alice_n)
					{
						B_SIZE = j;
						j = 0;
						break;
					}

					str += Text[i];
					tmp.pop_back();
					B_SIZE = j;

					i++;j++;
				}


				RSA obj;
				mpz_class Eb_Cs = obj.performEncryption(bPreSize,Alice_d,Alice_n);
				mpz_class EaEb_Cs = obj.performEncryption(Eb_Cs,Bob_e,Bob_n);


				vec.push_back(EaEb_Cs.get_str(10));
				vec.push_back(B_SIZE.get_str(10));
				S = S + EaEb_Cs.get_str(10);

			}
		}

	}

	return S;

}
int main()
{

	cout<<"\n\n################################ USER :: ALICE #####################################"<<endl;



	/******* Extraction of CA private key and n  CA(d,n) from Alice file *******************************/
	mpz_class CA_d = ReadCAPrivateKey();
	mpz_class CA_n = ReadCA_N();


	/******** Extraction of Bob's Encrypted Public key and its n  from public file *********************/
	mpz_class Cip_Bob_e =  ReadBobPublicKey();
	mpz_class Cip_Bob_n =  ReadBob_N();

	/************** Decryption of Bob's Encrypted Public key and its n  ******************************/
	RSA obj;
	mpz_class Bob_e =  obj.performDecryption(Cip_Bob_e,CA_d,CA_n);
	mpz_class Bob_n =  obj.performDecryption(Cip_Bob_n,CA_d,CA_n);


	string M="theweatherismorebeautifulthanotherdaysofcalendaryearihopeyouwill";

	string K="iamnitishraj";

	cout<<" Text = "<<M<<endl;
	cout<<" Key  = "<<K<<endl;

	BLOCK_SIZE = M.size();
	KEY_SIZE = K.size();
	Vignere V;
	string Cs = V.performVignereEncyption(M,K); //Cs  = E(m, k)


	mpz_class Alice_d = ReadAlicePrivateData(ALICE_PRIVATE_KEY);
	mpz_class Alice_n = ReadAlicePrivateData(ALICE_N);


	string CIPHER = computeRSA(Alice_d,Alice_n,Bob_e,Bob_n,Cs);
	vec.push_back("$");
	string KEY 	  = computeRSA(Alice_d,Alice_n,Bob_e,Bob_n,K);

	SendToBob(CIPHER, KEY );


	return 0;
}
