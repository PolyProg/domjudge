/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "artLib2.h"

const int CODE_FIRST_COLOR_NOT_ONE = -3;
const int CODE_NO_CONNECTION = -4;
const int CODE_TOO_LONG_DIST = -5;
const int CODE_TOUR_EXCESS = -6;

typedef struct {
	int a, b;
} connection;

static int compare(const void* v1, const void* v2) {
	connection c1 = *(connection*)v1;
	connection c2 = *(connection*)v2;
	if (c1.a < c2.a)
		return -1;
	else if (c1.a > c2.a)
		return 1;
	else if (c1.b < c2.b)
		return -1;
	else if (c1.b > c2.b)
		return 1;
	else
		return 0;
} 

static int checkSolution(int n, int m, int* a, int* b, const int* teamColors, const int* teamTour) {
	connection* scheme = (connection*) calloc(2*m, sizeof(connection));
	assert(scheme);
	
	int j = 0;
	while ((j < 3*n) && (teamTour[j]))
		j++;
	int tourSize = j;
	
	int schemeSize = tourSize-1;
	
	connection* teamScheme = (connection*) calloc(schemeSize, sizeof(connection));
	assert(teamScheme);
	int i;
	for (i = 0; i < m; i++) {
		scheme[2*i].a = a[i];
		scheme[2*i].b = b[i];
		scheme[2*i+1].a = b[i];
		scheme[2*i+1].b = a[i];
	}
	for (i = 1; i < tourSize; i++) {
		teamScheme[i-1].a = teamTour[i-1];
		teamScheme[i-1].b = teamTour[i];
	}
	
	// sort and compare these sets of connections
	qsort(scheme, 2*m, sizeof(connection), compare);
	qsort(teamScheme, schemeSize, sizeof(connection), compare);
	
	int p1 = 0;
	int p2 = 0;
	// invariant: scheme[p1] <= teamTour[p2]
	while ((p1 < 2*m) && (p2 < schemeSize)) {
		if (compare(&scheme[p1], &teamScheme[p2]) == 1) {
			free(scheme);
			free(teamScheme);
			return CODE_NO_CONNECTION;
		}
		if (compare(&scheme[p1], &teamScheme[p2]) == -1)
			p1++;
		else p2++;
	}
	if (p2 < schemeSize) {
		free(scheme);
		free(teamScheme);
		return CODE_NO_CONNECTION;
	}
	
	free(scheme);
	free(teamScheme);
	
	if (teamColors[teamTour[0]-1] != 1)
		return CODE_FIRST_COLOR_NOT_ONE;
	int cur = 0;
	
	for (i = 2; i <= n+1; i++) {
		// searching for color i
		int col = i;
		if (col == n+1)
			col = 1;
		int prev = cur;
		while ((cur < tourSize) && (teamColors[teamTour[cur]-1] != col)) {
			cur++;
		}
		if (cur == tourSize) {
			return i;
		}
		if (cur - prev > 3) {
			return CODE_TOO_LONG_DIST;
		}
	}
	if (cur != tourSize - 1)
		return CODE_TOUR_EXCESS;
	return 0;
}

int* answer(const int teamColors[], const int teamTour[], int N) {
	int* solution = calloc(1+N+3*N, sizeof(int));
	assert(solution);
	solution[0] = N;
	memcpy(solution+1, teamColors, N*sizeof(int));
	memcpy(solution+N+1, teamTour, 3*N*sizeof(int));
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
		int* teamAnswer = draw_literate_painting(n, m, schemeA, schemeB);
		assert(teamAnswer[0] == n);
		
		int checkResult = checkSolution(n, m, schemeA, schemeB, teamAnswer+1, teamAnswer+1+n);
		free(teamAnswer);
		if (checkResult) {
			printf ("INCORRECT - Test case %d: ", tt+1);
			if (checkResult == CODE_FIRST_COLOR_NOT_ONE)
				printf("color of the first vertex in tour is not 1");
			else if (checkResult == CODE_NO_CONNECTION)
				printf("tour includes nonexistent connection");
			else if (checkResult == CODE_TOO_LONG_DIST)
				printf("distance between some pair of colors is bigger than 3 (tour is illiteral)");
			else if (checkResult == CODE_TOUR_EXCESS)
				printf("tour is too long, should be shorter");
			else if (checkResult > 0)
				printf("didn't find color %d", checkResult % n);
			else
				printf("unknown code error");
			printf("\n");
			exit(0);
		}
		free(schemeA);
		free(schemeB);
	}
	printf("CORRECT 1ZVLsWpdrdt1UGg3s4qnpuS9cJpTBHqZ\n");
	return 0;
}
