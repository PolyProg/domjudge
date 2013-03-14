/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////
#include<cstdio>
#include<vector>
#include<set>
#include<algorithm>
#include<iterator>
#include<stdlib.h>

#include"portalLib2.hpp"
using namespace std;

#define MAX_OBS		200000

int main(){
	set<int> speedsJudge;
	int ntc;
	int nsp,nob,nsol,sol,teamAnswer;
	double speed;
	cube gate, obstacle;
	cube obstacles[MAX_OBS];
	scanf("%d",&ntc);
	for (int i=0; i<ntc; i++){
		speedsJudge.clear();
		scanf("%d %d %d %d %d",&gate.x, &gate.y, &nob, &nsp, &nsol);
		for (int j=0; j<nob; j++){
			scanf("%d %d",&obstacles[j].x, &obstacles[j].y);
		}
		// team initialize
		initialize(gate, nob, obstacles);
		while (nsol--){
			scanf("%d", &sol);
			speedsJudge.insert(sol);
		}
		for (int j=0; j<nsp; j++){
			scanf("%lf",&speed);
			// team queries
			teamAnswer = check_speed(speed);
			if (teamAnswer && speedsJudge.find(j) == speedsJudge.end()){
				printf("INCORRECT - Test case %d speed %lf is bad.\n",i+1,speed);
				exit(0);
			}
			if (!teamAnswer && speedsJudge.find(j) != speedsJudge.end()){
				printf("INCORRECT - Test case %d speed %lf would be good.\n",i+1,speed);
				exit(0);
			}
		}
	}
	printf("OK - 6673454bb0eb6491f54407deed2b7a23\n");
}
