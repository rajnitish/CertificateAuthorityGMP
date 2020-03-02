#include <string.h>
#include <iostream>
#include <math.h>
#include <limits.h>
#include <gmp.h>
#include <gmpxx.h>
#include <assert.h>

using namespace std;


struct KeySet
{
	mpz_class e;
	mpz_class d;
	mpz_class n;

	KeySet(){}

	KeySet(mpz_class e,
	mpz_class d,
	mpz_class n)
	{
		this->e = e;
		this->d = d;
		this->n = n;
	}
};

class KeyGen
{
public:
	KeySet generateKeys(const mpz_class p, const mpz_class q, const mpz_class e);
};
