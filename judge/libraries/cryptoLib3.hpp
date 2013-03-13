#ifndef _CRYPTO_LIB_3_H_
#define _CRYPTO_LIB_3_H_

int encrypt(int plaintext, int key1, int key2);

long long int answer(int key1, int key2);

// Helper methods
int sBox(int input, int key, int sBox);
int keySchedule(int key, int schedule);
int feistel(int plaintext, int key);

// You will have to write the following function:
long long int challenge(int plaintext1, int ciphertext1,
                        int plaintext2, int ciphertext2,
                        int plaintext3, int ciphertext3);

#endif  //_CRYPTO_LIB_3_H_
