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

/*
void display(mpz_class message, keyset k) {
    mpz_class e = k["public"].first;
    mpz_class d = k["private"].first;
    mpz_class n = k["public"].second;

    mpz_class encrypted = encrypt(message.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());
    mpz_class decrypted = decrypt(encrypted.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());

    // The decrypted message must be equal to the original
    assert(message == decrypted);

    cout << "Public key = (e: " << e << ", n: " << n << ")" << endl;
    cout << "Private key = (d: " << d << ", n: " << n << ")" << endl;
    cout << "Original message: " << message << endl;
    cout << "Encrypted message: " << encrypted << endl;
    cout << "Decrypted message: " << decrypted << endl;
    cout << endl;
}

template<typename T>
void display(T msg, T pi, T qi, T ei) {
    cout << "Initializing with p = " << pi << ", q = " << qi << ", e = " << ei << endl;

    mpz_t n, d;
    mpz_inits(n, d, NULL);

    mpz_class p{pi};
    mpz_class q{qi};
    mpz_class e{ei};
    mpz_class original{msg};

    auto k = rsa_keys(p.get_mpz_t(), q.get_mpz_t(), e.get_mpz_t());
    display(original, k);
    mpz_clears(n, d, NULL);
}

*/
#endif

