/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include "giftLib3.hpp"
using namespace std;

#define MAX_Q 200
#define MAX_T 1000

static int years[MAX_T];
static int qCnt, T;
static bool canLie;
static FILE* fin;
static int lCnt;

static int x_n = 879788114;
static int myrand()
{
  const int A = 1103515245;
  const int C = 12345;
  int res;
  x_n = A*x_n + C;

  res = (x_n & 0x3FFFFFFF) / (65536);
  return res;
}

static bool is_heidi_really_in(double year) {
	if (++qCnt > MAX_Q) {
		printf("Too many queries\n");
		exit(0);
	}
	if (year >= years[T])
		return 0;
        else //if (year < years[T])
		return 1;
}

bool is_heidi_in(double year) {
	bool correct = is_heidi_really_in(year);
	if (canLie && myrand()%(1+T/100)< 1 && year > 100000 && year < 900000) {
		canLie = false;
        ++lCnt;
		return !correct;
	}
	else {
		canLie = true;
		return correct;
	}		
}

static void read_cases() {
	fscanf(fin, "%d",&T);
	int t = T;
	while (t-- != 0)
		fscanf(fin, "%d", &years[t]);
}

int main() {
        fin = stdin;
	read_cases();
	int maxi = 0;
	while (T--) 	{
		qCnt = 0;
        lCnt = 0;
		canLie = myrand()%2;
		TAnswer answer = find_heidi();
		if (answer.year1 != years[T] && answer.year2 != years[T]) {
			printf("Incorrect\n");
			exit(0);
		}
		if (qCnt>maxi)
			maxi = qCnt;
	}
	printf("Correct f11cc9de4736bbc2719aa318ecfbecf2\n");
	return 0;
}
