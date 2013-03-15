/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "artLib3.hpp"

using namespace std;

const int CODE_SIZE_MISMATCH = -1;
const int CODE_FIRST_CREATURE_NOT_HEIDI = -2;
const int CODE_NEGATIVE_MARMOT = -3;
const int CODE_NO_FRIENDSHIP = -4;

static int checkSolution(int n, const vector<connection> & scheme, const vector<int> & teamAnswer) {
	int table[n][n];
	bool visited[n];
	memset(table,0,sizeof(table));
	memset(visited,false,sizeof(visited));
	for (int i = 0; i < (int) scheme.size(); i++) {
		table[scheme[i].a-1][scheme[i].b-1] = 1;
		table[scheme[i].b-1][scheme[i].a-1] = 1;
	}
	if ((int) teamAnswer.size() != n+1)
		return CODE_SIZE_MISMATCH;
	if (teamAnswer[0] != 1)
		return CODE_FIRST_CREATURE_NOT_HEIDI;
	
	for (int i = 1; i < (int) teamAnswer.size(); i++) {
		if (teamAnswer[i] < 1)
			return CODE_NEGATIVE_MARMOT;
		else if (teamAnswer[i] > n)
			return teamAnswer[i];
		int a = teamAnswer[i-1]-1;
		int b = teamAnswer[i]-1;
		if (visited[b])
			return b+1;
		if (!table[a][b]) {
			printf("no such friendship [%d, %d]\n", a+1, b+1);
			return CODE_NO_FRIENDSHIP;
		}
		visited[b] = true;
	}
	// probably, because the size matches and there were no duplicate visits - 
	// then the last creature is automatically Heidi
	return 0;
}

int main() {
	int numOfCases;
	vector<connection> scheme;
	scanf("%d",&numOfCases);
	for (int tt = 0; tt < numOfCases; tt++) {
		scheme.clear();
		int n,m;
		scanf("%d",&n);
		scanf("%d",&m);
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d %d",&a, &b);
			connection e = {a,b};
			scheme.push_back(e);
		}
		vector<int> teamAnswer = arrange_marmots(n, scheme);
		int checkResult = checkSolution(n, scheme, teamAnswer);
		if (checkResult) {
			printf("INCORRECT - Test case %d: ", tt+1);
			if (checkResult == CODE_SIZE_MISMATCH)
				printf("tour size mismatch, received %d, expected %d", (int) teamAnswer.size(), n+1);
			else if (checkResult == CODE_FIRST_CREATURE_NOT_HEIDI)
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
	}
	printf("CORRECT fHPWZsCJy6Sn7BUF0kzOxEm2CnQE83p1\n");
	return 0;
}
