/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<iostream>
#include"cyberspaceLib1.hpp"
using namespace std;

#define MAX_N 1000001

static int x_n = 429584; // initial seed

static int my_rand(void)
{
    const int A = 1664525;
    const int C = 1013904223;
    x_n = A*x_n + C;

    return (x_n & 0x3FFFFFFF);
}

static int judge_entry_time(int a[], int p[], int N){
	int e(0);
	for (int i=0; i<=N; i++)
		e = max(a[i],e) + p[i];
	return e;
}

int main(){
	int T;
	int solTeam, solJudge;
	int a[MAX_N], p[MAX_N];
	int N;
	assert(scanf("%d",&T)==1);
	for (int i=0; i<T; i++){
		assert(scanf("%u",&N)==1);
		a[0] = my_rand()%1000;
		p[0] = my_rand()%1000;
		for (int j=1; j<=N; j++){
			a[j] = (my_rand()%1000) + a[j-1];
			p[j] = my_rand()%1000;
		}
		solJudge = judge_entry_time(a,p,N);
		solTeam = entry_time(a,p,N);
		if (solTeam != solJudge){
			printf("INCORRECT - test %d received %d / expected %d\n",i+1,solTeam,solJudge);
			exit(0);
		}
	}
	printf("OK - b54a18363981c7c9e8c40366ce1a9f8f\n");
	return 0;
}
