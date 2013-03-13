#ifndef _CRYPTO_LIB_2_H_
#define _CRYPTO_LIB_2_H_

int encrypt(int plaintext, int key1, int key2);
int decrypt(int ciphertext, int key1, int key2);

// Helper methods
int sBox(int input, int key, int sBox);
int keySchedule(int key, int schedule);
int feistel(int plaintext, int key);

#endif  //_CRYPTO_LIB_2_H_
