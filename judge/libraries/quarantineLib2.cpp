/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<time.h>
#include<iostream>
#include"quarantineLib2.hpp"
using namespace std;

#define MAXN 1000
#define MAXQ 10000000

static bool p[MAXN][MAXN];
static int ps[MAXN+1][MAXN+1];

static int x_n = 429584; // initial seed

static int my_rand(void)
{
    const int A = 1664525;
    const int C = 1013904223;
    x_n = A*x_n + C;
    return (x_n & 0x3FFFFFFF);
}

static void create_picture(int N){
	for (int i=0; i<N; i++)
		for (int j=0; j<N; j++)
			p[i][j] = my_rand()%2;
	for (int i=0; i<=N; i++)
		ps[i][0] = ps[0][i] = 0;
	for (int i=1; i<=N; i++)
		for (int j=1; j<=N; j++)
			ps[i][j] = ps[i][j-1] + ps[i-1][j] - ps[i-1][j-1] + p[i-1][j-1];
}

static bool judge_query(int r1, int c1, int r2, int c2){
	r2++; c2++;
	return ps[r2][c2] - ps[r2][c1] - ps[r1][c2] + ps[r1][c1] > (r2-r1)*(c2-c1)/2;
}

int main(){
	int T, Q, r1, c1, r2, c2;
	int N;	
	int solTeam, solJudge;
	assert(scanf("%d",&T)==1);
	Q = MAXQ/T;
	for (int i=0; i<T; i++){
		assert(scanf("%d",&N)==1);
		create_picture(N);
		load_picture(p,N);
		for (int j=0; j<Q; j++){
			r1 = my_rand()%N;
			c1 = my_rand()%N;
			r2 = my_rand()%N;
			c2 = my_rand()%N;
			if (r2<r1) swap(r1,r2);
			if (c2<c1) swap(c1,c2);
			solTeam = query(r1,c1,r2,c2);
			solJudge = judge_query(r1,c1,r2,c2);
			if (solTeam != solJudge){
				printf("INCORRECT - picture %d query %d received %d / expected %d\n",i+1,j+1,solTeam,solJudge);
				exit(0);
			}
		}
	}
	printf("OK - ea43a765b6871c13a7a9bfd32235c732\n");
	return 0;
}
