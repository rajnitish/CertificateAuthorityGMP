#include "KeyGen.h"
#include <fstream>

using namespace std;

void SendToAlice(KeySet KS)
{
	ofstream myfile;
	myfile.open("../ALICE/Alice.key",ios::out);
	myfile<<KS.d;
	myfile<<"\n";
	myfile<<KS.n<<endl;
	myfile.close();

}

void SendToBob(KeySet KS)
{
	ofstream myfile;
	myfile.open("../BOB/Bob.key",ios::out);
	myfile<<KS.d;
	myfile<<"\n";
	myfile<<KS.n<<endl;
	myfile.close();

}
void publishPublic(KeySet KS1,KeySet KS2)
{
	ofstream myfile;
	myfile.open("Public.key",ios::out);

	myfile<<"Alice\n";
	myfile<<KS1.e<<endl;
	myfile<<KS1.n<<endl;


	myfile<<"Bob"<<endl;
	myfile<<KS2.e<<endl;
	myfile<<KS2.n<<endl;

	myfile.close();

}


int main(void) {

	mpz_class Alice_P,Alice_Q,Alice_E;
	mpz_inits(Alice_P.get_mpz_t(), Alice_Q.get_mpz_t(), Alice_E.get_mpz_t(),NULL);


	KeyGen K1,K2;

	int flag;

	flag = Alice_P.set_str("162259276829213363391578010288127",10);	       assert (flag == 0); // operation failed
	flag = Alice_Q.set_str("618970019642690137449562111",10);   	       assert (flag == 0); // operation failed
	flag = Alice_E.set_str("170141183460469231731687303715884105727",10);  assert (flag == 0); // operation failed

	cout<<" Generating Alice keys "<<endl;

	KeySet Alice_KS = K1.generateKeys(Alice_P,Alice_Q,Alice_E);

	SendToAlice(Alice_KS);

	mpz_class Bob_P, Bob_Q, Bob_E;
	mpz_inits(Bob_P.get_mpz_t(), Bob_Q.get_mpz_t(), Bob_E.get_mpz_t(),NULL);

	flag = Bob_P.set_str("1123456667890987666543211",10);			    assert (flag == 0); // operation failed
	flag = Bob_Q.set_str("53644737765488792839237440001",10);			assert (flag == 0); // operation failed
	flag = Bob_E.set_str("424264068711928514640506617262909423",10);	assert (flag == 0); // operation failed

	cout<<" Generating Bob keys "<<endl;

	KeySet Bob_KS = K2.generateKeys(Bob_P,Bob_Q,Bob_E);

	SendToBob(Bob_KS);

	cout<<"Publishing keys "<<endl;

	publishPublic(Alice_KS,Bob_KS);

	return 0;
}



