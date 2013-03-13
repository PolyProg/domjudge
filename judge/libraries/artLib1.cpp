/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <set>
#include "artLib1.hpp"

using namespace std;

static int checkSolution(int N, const vector<int> & teamAnswer) {
	set<int> colors;
	if (N != (int) teamAnswer.size())
		return -1;
	for (int i = 0; i < (int) teamAnswer.size(); i++) {
		if (teamAnswer[i] < 1)
			return -2;
		else if (teamAnswer[i] > 2*N-1)
			return teamAnswer[i];
		else if (colors.find(teamAnswer[i]) != colors.end())
			return teamAnswer[i];
		else {
			colors.insert(teamAnswer[i]);
		}
	}
	
	for (int i = 1; i < N; i++) {
		int l1 = teamAnswer[i-1];
		int l2 = teamAnswer[i];
		if (colors.find(abs(l1-l2)) != colors.end())
			return abs(l1-l2);
		else {
			colors.insert(abs(l1-l2));
		}
	}
	return 0;
}

int main() {
	int numOfCases;
	int N;
	scanf("%d",&numOfCases);
	for (int tt = 0; tt < numOfCases; tt++) {
		scanf("%d",&N);
		vector<int> teamAnswer = draw_charming_painting(N);
		int checkResult = checkSolution(N, teamAnswer);
		if (checkResult) {
			if (checkResult == -1)
				printf("INCORRECT - Test case %d: size mismatch, received %d, expected %d\n",
						tt+1, (int) teamAnswer.size(), N);
			else if (checkResult > 2*N-1)
				printf("INCORRECT - Test case %d: colors are too high, received %d\n",
						tt+1, checkResult);
			else if (checkResult == -2)
				printf("INCORRECT - Test case %d: received color less than 1\n",
					   tt+1);
			else
				printf("INCORRECT - Test case %d has duplicate in the coloring %d\n",
						tt+1, checkResult);
			exit(0);
		}
	}
	printf("CORRECT fHPWZsCJy6Sn7BUF0kzOxEm2CnQE83p1\n");
	return 0;
}
