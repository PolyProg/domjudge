#include <stdio.h>
#include <stdlib.h>
#include "cryptoLib2.h"

static const int TESTCASES = 100000;
static const int MAX_BYTE = 1<<8;
static const int MAX_WORD = 1<<16;
static const int SBOX1_PRIME = 65537;
static const int SBOX2_PRIME = 257;
static const int NUMBER_OF_SBOXES = 3;
static const int KEY_ROUNDS = 16;

static int x_n = 429584; // initial seed
static int my_rand(void)
{
    const int A = 1664525;
    const int C = 1013904223;
    x_n = A*x_n + C;

    return (x_n & 0x3FFFFFFF);
}

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

int main(int argc, char** argv) {
  int tc;
  for(tc=0;tc<TESTCASES;++tc) {
    int key1 = my_rand() % MAX_WORD;
    int key2 = my_rand() % MAX_WORD;
    int plaintext = my_rand() % MAX_WORD;
    int ciphertext = encrypt(plaintext, key1, key2);
    int ans = decrypt(ciphertext, key1, key2);
    if(plaintext != ans) {
      printf("Incorrect answer.");
      return 0;
    }
  }
  printf("OK - 983b6576e1b54131fc6d1c5a6629d176\n");
  return 0;
}
