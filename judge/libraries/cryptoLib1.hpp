#ifndef HC2_CRYPTO_LIB_1_H_
#define HC2_CRYPTO_LIB_1_H_

typedef struct Ciphertext_s {
    mpz_t E;
    mpz_t F;
} Ciphertext;

typedef struct PublicKey_s {
    mpz_t p;
    mpz_t g;
    mpz_t y;
} PublicKey;

typedef struct Plaintext_s {
  mpz_t m;
} Plaintext;

Ciphertext encrypt(Plaintext plaintext, PublicKey key, mpz_t r);
Plaintext decrypt(Ciphertext ct, PublicKey key, mpz_t x);

#endif
