/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include "giftLib1.h"
#include <time.h>

#define MAX_Q 0
#define MAX_T 100

static int years[MAX_T];
static int qCnt, T;
static FILE* fin;

BOOL is_heidi_in(double year) {
	if (++qCnt > MAX_Q) {
		printf("Too many queries\n");
		exit(0);
	}
	if (year >= years[T])
		return 0;
	if (year < years[T])
		return 1;
}

static void read_cases() {
	fscanf(fin, "%d",&T);
	int t = T;
	while (t--)
		fscanf(fin, "%d", &years[t]);
}

int main() {
  fin = stdin;
	read_cases();
	int maxi=0;
	while (T--) 	{
		qCnt = 0;
		int answer = find_heidi();
		if (answer != years[T]) {
			printf("Incorrect\n");
			exit(0);
		}
		if (qCnt>maxi)
			maxi = qCnt;
	}
	printf("Correct 1ac0b464eb2b2ab64c07c357246d46b1\n");
	return 0;
}
