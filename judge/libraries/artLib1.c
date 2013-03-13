/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "artLib1.h"

static int checkSolution(int N, const int teamAnswer[]) {
	int* colors = (int*) calloc(2*N, sizeof(int));
	int i;
	for (i = 0; i < N; i++) {
		if (teamAnswer[i] < 1) {
			free(colors);
			return -2;
		}
		else if (teamAnswer[i] > 2*N-1) {
			free(colors);
			return teamAnswer[i];
		}
		else if (colors[teamAnswer[i]]) {
			free(colors);
			return teamAnswer[i];
		}
		else {
			colors[teamAnswer[i]] = 1;
		}
	}
	
	for (i = 1; i < N; i++) {
		int l1 = teamAnswer[i-1];
		int l2 = teamAnswer[i];
		if (colors[abs(l1-l2)]) {
			free(colors);
			return abs(l1-l2);
		}
		else {
			colors[abs(l1-l2)] = 1;
		}
	}
	free(colors);
	return 0;
}

int* answer(const int teamAnswer[], int N) {
  int* solution = (int*) calloc(N+1, sizeof(int));
  assert(solution);
  solution[0] = N;
  memcpy(solution+1, teamAnswer, N*sizeof(int));
  return solution;
};

int main() {
	int numOfCases;
	int N;
	scanf("%d",&numOfCases);
	int tt;
	for (tt = 0; tt < numOfCases; tt++) {
		scanf("%d",&N);
		int* teamAnswer = draw_charming_painting(N);
		assert(teamAnswer[0]==N);
		int checkResult = checkSolution(N, teamAnswer+1);
		free(teamAnswer);
		if (checkResult) {
			printf("INCORRECT - Test case %d: ", tt+1);
			if (checkResult > 2*N-1)
				printf("colors are too high, received %d", checkResult);
			else if (checkResult == -2)
				printf("received color less than 1");
			else
				printf("there is a duplicate in the color %d", checkResult);
			printf("\n");
			exit(0);
		}
	}
	printf("CORRECT fHPWZsCJy6Sn7BUF0kzOxEm2CnQE83p1\n");
	return 0;
}
