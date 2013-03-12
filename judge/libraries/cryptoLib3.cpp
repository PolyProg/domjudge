#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

#include "cryptoLib3.hpp"

static int x_n = 773137898;
static int my_rand()
{
  const int A = 1103515245;
  const int C = 12345;
  int res;
  x_n = A*x_n + C;

  res = (x_n & 0x3FFFFFFF) / (65536);
  return res;
}
Ciphertext encrypt(Plaintext plaintext, PublicKey key, mpz_t r)
{
  Ciphertext ct;
  mpz_init(ct.E);
  
  /* E = m * y^r (mod p) */
  mpz_powm(ct.E, key.y, r, key.p);
  mpz_mul(ct.E, ct.E, plaintext.m);
  mpz_mod(ct.E, ct.E, key.p);

  mpz_init(ct.F);
  /* F = g^(-r) */
  mpz_neg(ct.F, r);
  mpz_powm(ct.F, key.g, ct.F, key.p);
  
  return ct;
}

#if 0
static void unitTest() {
    gmp_randstate_t rs;
    mpz_t x, r;
    PublicKey pk;
    mpz_t pminus1, pminus2;
    Plaintext m1, m2;
    int correct = 0;
    int ntc = 100;
    int i;

    /* Note: in the real test, p will change all the time */
    mpz_init_set_si(pk.p, 1000003);
    mpz_init_set_si(pminus1, 1000003-1);
    mpz_init_set_si(pminus2, 1000003-2);
    gmp_randinit_default(rs);
    mpz_init(pk.g);
    mpz_init(pk.y);
    mpz_init(x);
    mpz_init(r);
    mpz_init(m1.m);
    mpz_init(m2.m);
    srand(time(0));
    for(i=0;i<ntc;++i) {
      Plaintext m;
      Ciphertext ct;

      mpz_urandomm(pk.g, rs, pminus2);
      mpz_add_ui(pk.g, pk.g, 2);
      mpz_urandomm(x, rs, pminus1);
      mpz_urandomm(r, rs, pminus1);
      mpz_urandomm(m1.m, rs, pk.p);
      mpz_urandomm(m2.m, rs, pk.p);
      mpz_powm(pk.y, pk.g, x, pk.p);

      ct = encrypt(m1, pk, r);

      if (rand()%2==0) {
        m = decrypt(ct, pk, m1, m2);
      } else {
        m = decrypt(ct, pk, m2, m1);
      }

      if(mpz_cmp(m.m, m1.m)==0) {
        correct++;
      } else {
      }

      mpz_clear(ct.E);
      mpz_clear(ct.F);
    }
    mpz_clear(pk.p);
    mpz_clear(pminus1);
    mpz_clear(pminus2);
    mpz_clear(pk.g);
    mpz_clear(pk.y);
    mpz_clear(x);
    mpz_clear(r);
    mpz_clear(m1.m);
    mpz_clear(m2.m);
    gmp_randclear(rs);
    printf("You were correct %3.0f%% of the time.\n", correct*100./ntc);
    printf("(You should aim for 75%% correct.)\n");
}
#endif

static void testDecrypt() {
    int correct = 0;
    int mincorrect = 5616;
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
      Plaintext m1, m2, mleft, mright;
      mpz_init(ct.E);
      mpz_init(ct.F);
      mpz_init(pk.p);
      mpz_init(pk.g);
      mpz_init(pk.y);
      mpz_init(x);
      mpz_init(m1.m);
      mpz_init(m2.m);
      mpz_init(mleft.m);
      mpz_init(mright.m);
      if(8!=gmp_scanf("%Zd %Zd %Zd %Zd %Zd %Zd %Zd %Zd\n", ct.E, ct.F, pk.p, pk.g, pk.y, x, m1.m, m2.m)) {
        printf("Input failure %d.\n", i);
        exit(1);
      }

      if (my_rand()%2 == 0) {
        mpz_set(mleft.m, m1.m);
        mpz_set(mright.m, m2.m);
      } else {
        mpz_set(mleft.m, m2.m);
        mpz_set(mright.m, m1.m);
      }
      got = decrypt(ct, pk, mleft, mright);

      if(mpz_cmp(got.m, m1.m)==0) {
        correct++;
      } else {
      }

      printf(".");
      mpz_clear(ct.E);
      mpz_clear(ct.F);
      mpz_clear(pk.p);
      mpz_clear(pk.g);
      mpz_clear(pk.y);
      mpz_clear(x);
      mpz_clear(m1.m);
      mpz_clear(m2.m);
      mpz_clear(mleft.m);
      mpz_clear(mright.m);
    }
    if(correct < mincorrect) {
      printf("\n");
      printf("Not enough correct answers: %d expected at least: %d\n", correct, mincorrect);
      printf("Peformance: %3.5f%% expected performance: %3.5f%%\n", correct*100./ntc, mincorrect*100./ntc);
      exit(0);
    }
}

int main(int argc, char** argv) {
  /*unitTest();*/
  testDecrypt();

  printf("\n");
  printf("OK - a03cf946a04f9ae2fd30c3e7d20a7009\n");
  return 0;
}
