/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "artLib3.h"

int CODE_FIRST_CREATURE_NOT_HEIDI = -2;
int CODE_NEGATIVE_MARMOT = -3;
int CODE_NO_FRIENDSHIP = -4;

static int checkSolution(int n, int m, int* a, int* b, const int* teamTour) {
	int table[n][n];
	int visited[n];
	memset(table, 0, sizeof(table));
	memset(visited, 0, sizeof(visited));
	int i;
	for (i = 0; i < m; i++) {
		table[a[i]-1][b[i]-1] = 1;
		table[b[i]-1][a[i]-1] = 1;
	}
	
	if (teamTour[0] != 1)
		return CODE_FIRST_CREATURE_NOT_HEIDI;
	
	for (i = 1; i < n+1; i++) {
		if (teamTour[i] < 1)
			return CODE_NEGATIVE_MARMOT;
		else if (teamTour[i] > n)
			return teamTour[i];
		int a = teamTour[i-1]-1;
		int b = teamTour[i]-1;
		if (visited[b])
			return b+1;
		if (!table[a][b]) {
			printf("no such friendship [%d, %d]\n", a+1, b+1);
			return CODE_NO_FRIENDSHIP;
		}
		visited[b] = 1;
	}
	// probably, because there were no duplicate visits - 
	// then the last creature is automatically Heidi
	return 0;
}

int* answer(const int teamTour[], int N) {
	int* solution = calloc(1+N+1, sizeof(int));
	assert(solution);
	solution[0] = N;
	memcpy(solution+1, teamTour, (N+1)*sizeof(int));
	return solution;
}

int main() {
	int numOfCases;
	int n, m;
	scanf("%d",&numOfCases);
	int tt;
	for (tt = 0; tt < numOfCases; tt++) {
		scanf("%d", &n);
		scanf("%d", &m);
		int* schemeA = calloc(m, sizeof(int));
		assert(schemeA);
		int* schemeB = calloc(m, sizeof(int));
		assert(schemeB);
		int i;
		for (i = 0; i < m; i++) {
			int a, b;
			scanf("%d %d",&a, &b);
			schemeA[i] = a;
			schemeB[i] = b;
		}
		int* teamAnswer = arrange_marmots(n, m, schemeA, schemeB);
		assert(teamAnswer[0] == n);
		
		int checkResult = checkSolution(n, m, schemeA, schemeB, teamAnswer+1);
		free(teamAnswer);
		
		if (checkResult) {
			printf ("INCORRECT - Test case %d: ", tt+1);
			if (checkResult == CODE_FIRST_CREATURE_NOT_HEIDI)
				printf("first creature is not Heidi");
			else if (checkResult == CODE_NO_FRIENDSHIP)
				printf("tour includes nonexistent friendship");
			else if (checkResult == CODE_NEGATIVE_MARMOT)
				printf("tour includes negative marmot numbers; not our Cyberspace");
			else if (checkResult > 0)
				printf("creature %d is duplicated or doesn't exist at all", checkResult);
			else
				printf("unknown code error");
			printf("\n");
			exit(0);
		}
		free(schemeA);
		free(schemeB);
	}
	printf("CORRECT fHPWZsCJy6Sn7BUF0kzOxEm2CnQE83p1\n");
	return 0;
}
