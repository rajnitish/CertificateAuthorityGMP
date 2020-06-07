#include "KeyGen.h"
#include <fstream>
#include "RSA.h"

using namespace std;

#define ALICE 0
#define BOB   1

void SendToUser(KeySet KS,KeySet CA_KS, bool user)
{
	ofstream myfile;
	if(user == ALICE)
		myfile.open("../ALICE/Alice.key",ios::out);
	if(user == BOB)
		myfile.open("../BOB/Bob.key",ios::out);
	myfile<<KS.d<<"\n";
	myfile<<KS.n<<"\n";

	myfile<<CA_KS.d<<"\n";
	myfile<<CA_KS.n<<endl;
	myfile.close();

}

void publishPublic(KeySet KS1,KeySet KS2,KeySet KS3)
{

	ofstream myfile;
	myfile.open("Public.key",ios::out);

	mpz_class skA = KS1.e;
	mpz_class n = KS1.n;

	RSA obj;

	mpz_class E_e_alice = obj.performEncryption(KS2.e,skA,n);
	mpz_class E_n_alice = obj.performEncryption(KS2.n,skA,n);


	myfile<<"Alice\n";
	myfile<<E_e_alice<<endl;
	myfile<<E_n_alice<<endl;

	mpz_class E_e_bob = obj.performEncryption(KS3.e,skA,n);
	mpz_class E_n_bob = obj.performEncryption(KS3.n,skA,n);

	myfile<<"Bob\n";
	myfile<<E_e_bob<<endl;
	myfile<<E_n_bob<<endl;


	myfile.close();

}



int main(void) {

	cout<<"\n\n################################ CERTIFICATE AUTHORITY #####################################"<<endl;


	mpz_class CA_P,CA_Q,CA_E;
	mpz_class Alice_P,Alice_Q,Alice_E;
	mpz_class Bob_P, Bob_Q, Bob_E;


	KeyGen K1,K2,K3;

	int flag;

	flag = CA_P.set_str("162259276829213363391578010288127",10);	       	assert (flag == 0);
	flag = CA_Q.set_str("618970019642690137449562111",10);   	       		assert (flag == 0);
	flag = CA_E.set_str("170141183460469231731687303715884105727",10);  	assert (flag == 0);

	cout<<"CA_P = "<<CA_P<<endl;
	cout<<"CA_Q = "<<CA_Q<<endl;
	cout<<"CA_E = "<<CA_E<<endl;
	cout<<" Generating CA keys "<<endl;

	KeySet CA_KS = K1.generateKeys(CA_P,CA_Q,CA_E);


	flag = Alice_P.set_str("1123456667890987666543211",10);	       			assert (flag == 0);
	flag = Alice_Q.set_str("53644737765488792839237440001",10);   	       	assert (flag == 0);
	flag = Alice_E.set_str("424264068711928514640506617262909423",10);  	assert (flag == 0);


	cout<<"Alice_P = "<<Alice_P<<endl;
	cout<<"Alice_Q = "<<Alice_Q<<endl;
	cout<<"Alice_E = "<<Alice_E<<endl;
	cout<<" Generating Alice keys and sharing secret keys with Alice in Alice.key file"<<endl;

	KeySet Alice_KS = K2.generateKeys(Alice_P,Alice_Q,Alice_E);
	SendToUser(Alice_KS,CA_KS,ALICE);


	flag = Bob_P.set_str("22360679774997896964091",10);			    assert (flag == 0);
	flag = Bob_Q.set_str("13666666666666631",10);					assert (flag == 0);
	flag = Bob_E.set_str("123456789878987654321",10);				assert (flag == 0);


	cout<<"Bob_P = "<<Bob_P<<endl;
	cout<<"Bob_Q = "<<Bob_Q<<endl;
	cout<<"Bob_E = "<<Bob_E<<endl;
	cout<<" Generating Bob keys and sharing secret keys with Bob in Bob.key file "<<endl;

	KeySet Bob_KS = K3.generateKeys(Bob_P,Bob_Q,Bob_E);


	cout<<"CA:: CA_e 	= "<<CA_KS.e<<endl;
	cout<<"CA:: CA_d 	= "<<CA_KS.d<<endl;
	cout<<"CA:: CA_n 	= "<<CA_KS.n<<endl;
	cout<<endl;
	cout<<"CA:: Alice_e 	= "<<Alice_KS.e<<endl;
	cout<<"CA:: Alice_d 	= "<<Alice_KS.d<<endl;
	cout<<"CA:: Alice_n 	= "<<Alice_KS.n<<endl;
	cout<<endl;
	cout<<"CA:: Bob_e 	= "<<Bob_KS.e<<endl;
	cout<<"CA:: Bob_d 	= "<<Bob_KS.d<<endl;
	cout<<"CA:: Bob_n 	= "<<Bob_KS.n<<endl;
	cout<<endl;

	SendToUser(Bob_KS,CA_KS,BOB);

	cout<<"Publishing Encrypted CA's public keys using RSA with public keys of Alice "<<endl;

	cout<<"Publishing Encrypted CA's public keys using RSA with public keys of Bob "<<endl;

	publishPublic(CA_KS, Alice_KS,Bob_KS);

	return 0;
}



