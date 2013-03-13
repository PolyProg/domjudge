#include <stdio.h>
#include <stdlib.h>
#include "cryptoLib3.h"

#ifndef FROM_STDIN
#define FROM_STDIN 1
#endif

static const int TESTCASES = 10;
static const int MAX_BYTE = 1<<8;
static const int MAX_WORD = 1<<16;
static const int SBOX1_PRIME = 65537;
static const int SBOX2_PRIME = 257;
static const int NUMBER_OF_SBOXES = 3;
static const int KEY_ROUNDS = 16;

static void assertByte(int input) {
  if(input<0 || input >= MAX_BYTE) {
    fprintf(stderr, "Invalid range: %d is not between 0 and %d\n",
            input, MAX_BYTE - 1);
    exit(1);
  }
}

static void assertWord(int input) {
  if(input<0 || input >= MAX_WORD) {
    fprintf(stderr, "Invalid range: %d is not between 0 and %d\n",
            input, MAX_WORD - 1);
    exit(1);
  }
}

static int sBox0(int input, int key) {
  assertByte(input);
  assertByte(key);

  return input ^ key;
}

static int sBox1(int input, int key) {
  assertByte(input);
  assertByte(key);

  long long int e = input + 256*key + 1;
  e = ((e * e) % SBOX1_PRIME) - 1;
  return (e % MAX_BYTE) ^ ((e / MAX_BYTE) % MAX_BYTE);
}

static int sBox2(int input, int key) {
  assertByte(input);
  assertByte(key);

  return (((input + 1) * (key + 1)) % SBOX2_PRIME) % MAX_BYTE;
}

int sBox(int input, int key, int sBox) {
  assertByte(input);
  assertByte(key);

  switch(sBox) {
    case 0:
      return sBox0(input, key);
    case 1:
      return sBox1(input, key);
    case 2:
      return sBox2(input, key);
    default:
      fprintf(stderr, "Incorrect sBox.");
      exit(1);
  }
}

int keySchedule(int key, int schedule) {
  long long int extendedKey;

  assertWord(key);

  extendedKey = key | (key % MAX_BYTE)<<16LL;
  return (extendedKey>>schedule) % MAX_BYTE;
}


int feistel(int plaintext, int key) {
  assertWord(plaintext);
  assertWord(key);

  int i;
  for(i=0; i < NUMBER_OF_SBOXES * KEY_ROUNDS; ++i) {
    int keyI, boxI, roundKey, left, right, newLeft, newRight;

    keyI = i / NUMBER_OF_SBOXES;
    boxI = i % NUMBER_OF_SBOXES;

    roundKey = keySchedule(key, keyI);
    left = plaintext % MAX_BYTE;
    right = (plaintext / MAX_BYTE) % MAX_BYTE;

    newLeft = right;
    newRight = left ^ sBox(right, roundKey, boxI);

    plaintext = newLeft + newRight * MAX_BYTE;
  }
  return plaintext;
}

int encrypt(int plaintext, int key1, int key2) {
  assertWord(plaintext);
  assertWord(key1);
  assertWord(key2);

  return feistel(feistel(plaintext, key1), key2);
}

long long int answer(int key1, int key2) {
  assertWord(key1);
  assertWord(key2);

  return key1 + key2*(1LL<<16LL);
}

int main(int argc, char** argv) {
  if(FROM_STDIN) {
    while(1) {
      int p1, c1, p2, c2, p3, c3;
      if(6!=scanf("%d %d %d %d %d %d\n", &p1, &c1, &p2, &c2, &p3, &c3)) {
        perror("Couldn't read input");
        return 3;
      }
      if(p1 == -1) {
        break;
      }
      long long int ans = challenge(p1, c1, p2, c2, p3, c3);
      printf("%lld\n", ans);
    }
  } else {
    int tc, i;
    srand(0);
    for(tc=0;tc<TESTCASES;++tc) {
      int key1 = rand() % MAX_WORD;
      int key2 = rand() % MAX_WORD;
      int plaintext[3], ciphertext[3];
      for(i=0;i<3;++i) {
        plaintext[i] = rand() % MAX_WORD;
        ciphertext[i] = encrypt(plaintext[i], key1, key2);
      }
      long long int ans = challenge(plaintext[0], ciphertext[0],
                                    plaintext[1], ciphertext[1],
                                    plaintext[2], ciphertext[2]);
      if(answer(key1, key2) != ans) {
        printf("Incorrect answer.");
        return 1;
      } else {
        printf(".");
        fflush(stdout);
      }
    }
  }
  return 0;
}
