/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<time.h>
#include"quarantineLib1.hpp"
using namespace std;

#define MAXN 1000
#define MAXQ 10000000

static bool p[MAXN][MAXN];
static int row[MAXN], col[MAXN];

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
		row[i] = col[i] = 0;
	for (int i=0; i<N; i++)
		for (int j=0; j<N; j++){
			p[i][j] = my_rand()%2;
			row[i] += p[i][j];
			col[j] += p[i][j];
		}
}

static bool judge_query(int r, int c, int N){
	return ( row[r] + col[c] - p[r][c] ) >= N;
}

int main(){
	int T, Q, r, c;
	int N;
	int solTeam, solJudge;
	assert(scanf("%d",&T)==1);
	Q = MAXQ/T;
	for (int i=0; i<T; i++){
		assert(scanf("%d",&N)==1);
		create_picture(N);
		load_picture(p,N);
		for (int j=0; j<Q; j++){
			r = my_rand()%N;
			c = my_rand()%N;
			solTeam = query(r,c);
			solJudge = judge_query(r,c,N);
			if (solTeam != solJudge){
				printf("INCORRECT - test %d received %d / expected %d\n",i+1,solTeam,solJudge);
				exit(0);
			}
		}
	}
	printf("OK - f7e32100ed674311bdff7f3896936962\n");
	return 0;
}
