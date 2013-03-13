/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////
#include<cstdio>
#include<vector>
#include<stdlib.h>
#include<string.h>

#include"portalLib1.h"

#define	NSPEEDS		1000

using namespace std;

static int nGateTeam, nTopTeam, nGateJudge, nTopJudge;

void answer(int T, int L){
	nGateTeam = L;
	nTopTeam = T;
}

int main(){
	int ntc, nsp;
	cube c;
	double speeds[NSPEEDS];
	scanf("%d",&ntc);
	for (int i=0; i<ntc; i++){
		memset(speeds,0,sizeof(speeds));
		scanf("%d %d %d",&c.x, &c.y, &nsp);
		for (int j=0; j<nsp;j++){
			scanf("%lf",&speeds[j]);
		}
		scanf("%d %d", &nGateJudge, &nTopJudge);
		speed_assessment(c,nsp,speeds);
		if (nGateTeam != nGateJudge || nTopTeam != nTopJudge){
			printf("INCORRECT - Test case %d received (gate,top) (%d,%d) / expected (%d,%d)\n",
				i+1, nGateTeam, nTopTeam, nGateJudge, nTopJudge);
			exit(0);
		}
	}
	printf("OK - 6673454bb0eb6491f54407deed2b7a23\n");
}
