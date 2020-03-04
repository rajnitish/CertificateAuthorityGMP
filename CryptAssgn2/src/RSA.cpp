#ifndef RSA_cpp
#define RSA_cpp

#include "RSA.h"


mpz_class RSA::performEncryption(const mpz_class M,const mpz_class e,const mpz_class n) {
    mpz_class C;
    mpz_init(C.get_mpz_t());
    mpz_powm(C.get_mpz_t(), M.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());

    return C;
}

mpz_class RSA::performDecryption(const mpz_class C,const mpz_class d,const mpz_class n) {
    mpz_class P;
    mpz_init(P.get_mpz_t());
    mpz_powm(P.get_mpz_t(), C.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());

    return P;
}
#endif

