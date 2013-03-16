/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<iostream>
#include"cyberspaceLib2.hpp"
using namespace std;

static int count_bits(int n){
	int cnt(0);
	while (n){
		n = n & (n-1);
		cnt++;
	}
	return cnt;
}

static int myabs(int a) {
  if(a<0)
     return -a;
  return a;
}
static int judge_place_exit(int N, int M){
	int best((1<<M)-1);
	for (int i=0; i<=(1<<10); i++)
		if ( count_bits(i)==M && myabs(i+i-N)<myabs(best+best-N) )
			best = i;
	return best;
}

int main() {
	int solJudge, solTeam;
	for (int i=0; i<=(1<<10); i++)
		for (int j=0; j<10; j++) {
			solTeam = place_exit(i,j);
			solJudge = judge_place_exit(i,j);
			if ( count_bits(solTeam)!=j || 
			     min(solTeam+solTeam-i,i-solTeam-solTeam) != min(solJudge+solJudge-i,i-solJudge-solJudge) ){
				printf("INCORRECT : N=%d M=%d , got %d / expected %d\n",i,j,solTeam,solJudge);
				exit(0);
			}
		}
	printf("OK - dbcd021e0b38b94aa0d34456190233a0\n");
	return 0;
}
