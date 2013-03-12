#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "cryptoLib1.h"

#if 0
static void unitTest() {
    mpz_t x, r;
    PublicKey pk;
    Plaintext orig;

    mpz_init_set_si(pk.p, 1000003);
    mpz_init_set_si(pk.g, 2);
    mpz_init_set_si(x, 4242);
    mpz_init_set_si(r, 123456);
    mpz_init_set_si(orig.m, 654321);
    mpz_init(pk.y);

    mpz_powm(pk.y, pk.g, x, pk.p);

    Ciphertext ct = encrypt(orig, pk, r);
    if(mpz_get_si(ct.E) != 509777) {
      printf("Encrypt failed (wrong ct.E).\n");
      exit(0);
    }
    if(mpz_get_si(ct.F) != 709498) {
      printf("Encrypt failed (wrong ct.F).\n");
      exit(0);
    }
    Plaintext res = decrypt(ct, pk, x);
    if (mpz_cmp(res.m, orig.m)!=0) {
      printf("Decrypt failed (m' != m)\n");
      gmp_printf("Expected: %Zd\n", orig.m);
      gmp_printf("Got:      %Zd\n", res.m);
      exit(0);
    } else {
      printf("Unit test OK\n");
    }
}
#endif

static void testDecrypt() {
    /*
      Input format is:
      - Number of testcases
      - For each testcase:   E  F  p  g  y  x  m  m2
    */
    int ntc, i;
    if(1!=scanf("%d\n", &ntc)) {
      printf("Input failure.\n");
      exit(1);
    }
    for(i=0;i<ntc;++i) {
      Ciphertext ct;
      PublicKey pk;
      Plaintext got;
      mpz_t x;
      Plaintext m1, m2;
      mpz_init(ct.E);
      mpz_init(ct.F);
      mpz_init(pk.p);
      mpz_init(pk.g);
      mpz_init(pk.y);
      mpz_init(x);
      mpz_init(m1.m);
      mpz_init(m2.m);
      if(8!=gmp_scanf("%Zd %Zd %Zd %Zd %Zd %Zd %Zd %Zd\n", ct.E, ct.F, pk.p, pk.g, pk.y, x, m1.m, m2.m)) {
        printf("Input failure %d.\n", i);
        exit(1);
      }

      got = decrypt(ct, pk, x);
      if(mpz_cmp(got.m, m1.m)!=0) {
        gmp_printf("\nTestcase %d  Wrong answer: expected %Zd got:\n%Zd\n", i, m1.m, got.m);
        exit(0);
      } else {
        printf(".");
      }
      mpz_clear(got.m);
      mpz_clear(ct.E);
      mpz_clear(ct.F);
      mpz_clear(pk.p);
      mpz_clear(pk.g);
      mpz_clear(pk.y);
      mpz_clear(x);
      mpz_clear(m1.m);
      mpz_clear(m2.m);
    }
}

int main(int argc, char** argv) {
  testDecrypt();

  printf("\n");
  printf("OK - 54ec725043cfc34e86f1e2f62b84d280\n");
  return 0;
}
