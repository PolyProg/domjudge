/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include "takeawayLib2.hpp"
using namespace std;

#define MAX_N 50
#define UNDEF -1

int p[MAX_N], n[MAX_N], t[MAX_N];
int N, T;
int ourMin, ourMax;
int yourMin, yourMax;
int cnt;
FILE* fin;

void read_case() {
	fscanf(fin, "%d",&N);
	for (int i=0; i<MAX_N; i++)
		p[i] = n[i] = t[i] = UNDEF;
	for (int i=0; i<N; i++)
		fscanf(fin, "%d %d %d", &p[i], &n[i], &t[i]);
	fscanf(fin, "%d %d", &ourMin, &ourMax);
	yourMin = yourMax = UNDEF;
	cnt = 0;
}

void min_balloons(int yourMinBound) {
	yourMin = yourMinBound;
	cnt++;
}

void max_balloons(int yourMaxBound) {
	yourMax = yourMaxBound;
	cnt++;
}

int main() {
        fin = stdin;
	fscanf(fin, "%d",&T);
	while (T--)	{
		read_case();
		count_balloons(N,p,n,t);
		if (cnt!=2 || ourMin!=yourMin || ourMax!=yourMax) {
			printf("Incorrect\n");
			exit(0);
		}
		
	}
	printf("Correctf52cac7981d3b301410e7cab97a3c2a5\n");
	return 0;
}
