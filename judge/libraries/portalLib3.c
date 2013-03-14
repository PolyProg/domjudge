/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"portalLib2.h"

#define NOBS		200000
#define NSPEEDS		200000

int main(){
	int speedsJudge[NSPEEDS];
	int ntc,i,j;
	int nsp,nob,nsol,sol,teamAnswer;
	double speed;
	cube gate, obstacle;
	cube obstacles[NOBS];
	scanf("%d",&ntc);
	for (i=0; i<ntc; i++){
		memset(speedsJudge,0,sizeof(speedsJudge));
		scanf("%d %d %d %d %d",&gate.x, &gate.y, &nob, &nsp, &nsol);
		for (j=0; j<nob; j++){
			scanf("%d %d",&obstacles[j].x, &obstacles[j].y);
		}
		// team initialize
		initialize(gate, nob, obstacles);
		while (nsol--){
			scanf("%d", &sol);
			speedsJudge[sol] = 1;
		}
		for (j=0; j<nsp; j++){
			scanf("%lf",&speed);
			// team queries
			teamAnswer = check_speed(speed);
			if (teamAnswer && !speedsJudge[j]){
				printf("INCORRECT - Test case %d speed %lf is bad.\n",i+1,speed);
				exit(0);
			}
			if (!teamAnswer && speedsJudge[j]){
				printf("INCORRECT - Test case %d speed %lf would be good.\n",i+1,speed);
				exit(0);
			}
		}
	}
	printf("OK - 6673454bb0eb6491f54407deed2b7a23\n");
}
