#include "Vignere.h"
#include "RSA.h"
#include <fstream>
#include <assert.h>


void SendToAlice(string E_Cs,string E_K)
{
	ofstream myfile;
	myfile.open("../ALICE/Alice.comm",ios::out);
	myfile<<E_Cs<<endl;
	myfile<<E_K<<endl;
	myfile.close();

}

void ReadPrivateKey(mpz_class e)
{
	std::ifstream file("Bob.key");
	if (file.is_open()) {
		std::string line;

		int i = 0;
		while (getline(file,line)) {
				cout<<line<<endl;
		}
		file.close();
	}

	//mpz_class Pk =
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

				cout<<line<<endl;
			}
		}
		file.close();
	}

	return pkA;

}
mpz_class ReadAliceN()
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

				cout<<line<<endl;
			}
		}
		file.close();
	}

	return n;

}


void convertTexttoNumber(string S,mpz_class &C, mpz_class &K)
{
	bool flag = false;
	int j = 0;
	for(int i = 0 ; i<S.size();i++)
	{
		if(!flag) C = C + pow(26,i)*(S[i]-97);
		if(S[i] == '$') flag = true;
		if(flag) {
			K = K + pow(26,j)*(S[i]-97);
			j++;
		}
	}

}
int main()
{
	string M,K;
	cout<<" Enter Original Message "<<endl;
	cin>>M;
	cout<<" Enter Key"<<endl;
	cin>>K;

	Vignere V;
	V.setOriginalMessage(M);
	V.setVigKey(K);
	string Cs = V.performVignereEncyption(); //Cs  = E(m, k)
	string C = Cs + "$" + K;  //Cs||k

	mpz_class pkA = ReadAlicePublicKey();
	mpz_class n = ReadAliceN();

	mpz_class C_Num,K_Num;
	convertTexttoNumber(C,C_Num,K_Num);

	RSA obj;
	mpz_class E_Cs = obj.performEncryption(C_Num,pkA,n);
	mpz_class E_K  = obj.performEncryption(K_Num,pkA,n);

	SendToAlice(E_Cs.get_str(10), E_K.get_str(10) );

	return 0;
}
