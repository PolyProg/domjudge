/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include "takeawayLib1.hpp"
using namespace std;

#define MAX_N 50
#define UNDEF -1

int p[MAX_N], n[MAX_N], t[MAX_N];
int N, T;
int ourGold, ourSilver, ourBronze;
int yourGold, yourSilver, yourBronze;
int cnt;

void read_case() {
	scanf("%d",&N);
	for (int i=0; i<MAX_N; i++)
		p[i] = n[i] = t[i] = UNDEF;
	for (int i=0; i<N; i++)
		scanf("%d %d %d", &p[i], &n[i], &t[i]);
	scanf("%d %d %d", &ourGold, &ourSilver, &ourBronze);
	yourGold = yourSilver = yourBronze = UNDEF;
	cnt = 0;
}

void gold_medalist(int yourGoldMedalist) {
	yourGold = yourGoldMedalist;
	cnt++;
}

void silver_medalist(int yourSilverMedalist) {
	yourSilver = yourSilverMedalist;
	cnt++;
}

void bronze_medalist(int yourBronzeMedalist) {
	yourBronze = yourBronzeMedalist;
	cnt++;
}

int main() {
	scanf("%d",&T);
	while (T--)	{
		read_case();
		find_medalists(N,p,n,t);
		if (cnt!=3 || ourGold!=yourGold || ourSilver!=yourSilver || ourBronze!=yourBronze) {
			printf("Incorrect\n");
			exit(0);
		}
		
	}
	printf("Correct12ddc26cc360428ead273b131b509946\n");
	return 0;
}
