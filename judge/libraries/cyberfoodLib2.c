/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<math.h>
#include"cyberfoodLib2.h"

static long long int solJudge, solTeam;
static int nSamples;
static int score=0;

static long long int min(long long int a, long long int b) {
  if(a<b) return a;
  return b;
}
static long long int max(long long int a, long long int b) {
  if(a>b) return a;
  return b;
}
static int x_n = 429588; // initial seed
static int my_rand(void)
{
    const int A = 1664525;
    const int C = 1013904223;
    x_n = A*x_n + C;

    return (x_n & 0x3FFFFFFF);
}
static long long int my_rand_long(void) {
  return my_rand() + my_rand()*0x40000000ll;
}

long long int eat(){
	if (!nSamples){
		printf("Too many samples\n");
		exit(0);
	 }
	 nSamples--;
	 return 1+my_rand_long()%solJudge;
}

int main() {
	int T, i;
	double tol;
	assert(scanf("%d",&T)==1);
	for (i=0; i<T; i++){
		assert(scanf("%lld %lf",&solJudge,&tol)==2);
		nSamples = ceil( log(1/(1-0.95)) / log(0.01*tol+1) );
		solTeam = estimate_flavours(nSamples);
		score += max(solTeam,solJudge)-min(solTeam,solJudge) <= tol*solJudge*0.01;
	}
	if ( score/(0.01*T) >= 95.00 ) {
		printf("CORRECT - 780977ab23bb95e3b52b1af9408fce96\n");
        }
	else {
                printf("Solved %.3lf%% of tests\n", score/(0.01*T));
		printf("INCORRECT\n");
        }
	return 0;
}
