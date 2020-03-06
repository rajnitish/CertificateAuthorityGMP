#include <string.h>
#include <iostream>
#include <math.h>
#include <limits.h>
#include <gmp.h>
#include <gmpxx.h>

using namespace std;



class RSA
{

public:

	mpz_class performEncryption(const mpz_class M,const mpz_class e,const mpz_class n) ;
	mpz_class performDecryption(const mpz_class C,const mpz_class d,const mpz_class n);

};
