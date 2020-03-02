#include "KeyGen.h"

KeySet KeyGen::generateKeys(const mpz_class p, const mpz_class q, const mpz_class e)
{

    mpz_class d, phi_n, gcd;
    mpz_inits(d.get_mpz_t(), phi_n.get_mpz_t(), gcd.get_mpz_t(), NULL);


    mpz_class n{p * q};
    mpz_class p_1{p - 1};
    mpz_class q_1{q - 1};

    mpz_lcm(phi_n.get_mpz_t(), p_1.get_mpz_t(), q_1.get_mpz_t());


    assert(e > 1);
    assert(e < phi_n);


    mpz_gcd(gcd.get_mpz_t(), e.get_mpz_t(), phi_n.get_mpz_t());
    assert(gcd == 1);
    mpz_invert(d.get_mpz_t(), e.get_mpz_t(), phi_n.get_mpz_t());


    mpz_class calc = e * d % phi_n;
    assert(calc == 1);

    KeySet result(e,d,n);

    return result;

}
