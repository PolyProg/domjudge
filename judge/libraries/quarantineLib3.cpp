/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<iostream>
#include"quarantineLib3.hpp"
using namespace std;

#define MAXN 1002
#define MAXQ 1000000

static int bit[MAXN][MAXN];
static int N;

static int x_n = 429584; // initial seed

static int my_rand(void)
{
    const int A = 1664525;
    const int C = 1013904223;
    x_n = A*x_n + C;
    return (x_n & 0x3FFFFFFF);
}

static void judge_load_picture(int n){
	N = n + 1;
	for (int i=0; i<=N; i++)
		for (int j=0; j<=N; j++)
			bit[i][j] = 0;
}

static bool judge_query(int r, int cc){
	r++; cc++;
	int c;
	int ps(0);
	while (r){
		c = cc;
		while (c){
			ps += bit[r][c];
			c -= c & -c;
		}
		r -= r & -r;
	}
	return ps%2;
}

static void toggle_bit(int r, int cc){
	int c;
	while (r<=N){
		c = cc;
		while (c<=N){
			bit[r][c]++;
			c += c & -c;
		}
		r += r & -r;
	}
}

static void judge_toggle(int r1, int c1, int r2, int c2){
	r1++; c1++; r2++; c2++;
	if (r1>r2) swap(r1,r2);
	if (c1>c2) swap(c1,c2);
	r2++; c2++;
	toggle_bit(r1,c1);
	toggle_bit(r2,c1);
	toggle_bit(r1,c2);
	toggle_bit(r2,c2);
}

int main(){
	int T, Q, r1, c1, r2, c2;
	int N;	
	int solTeam, solJudge;
	int cnt;
	int nscanned = scanf("%d",&T);
#ifdef NDEBUG
        (void) nscanned;  // removes warning about nscanned set but not used if NDEBUG is set
#endif
        assert(nscanned == 1 && "Could not read T");
	for (int i=0; i<T; i++){
		cnt=0;
                nscanned = scanf("%d",&N);
                assert(nscanned == 1 && "Could not read N");
		load_picture(N);
		judge_load_picture(N);
		Q = MAXQ/T;
		for (int j=0; j<Q; j++){
			if (my_rand()%2){
				r1 = my_rand()%N;
				c1 = my_rand()%N;
				r2 = my_rand()%N;
				c2 = my_rand()%N;
				toggle(r1,c1,r2,c2);
				judge_toggle(r1,c1,r2,c2);
			}
			else{
				cnt++;
				r1 = my_rand()%N;
				c1 = my_rand()%N;
				solTeam = query(r1,c1);
				solJudge = judge_query(r1,c1);
				if (solTeam != solJudge){
					printf("INCORRECT - picture %d query %d received %d / expected %d\n",i+1,cnt,solTeam,solJudge);
					exit(0);
				}
			}
		}
	}
	printf("OK - c124e57669a5e82fc7c3d5cee8d1642b\n");
	return 0;
}
