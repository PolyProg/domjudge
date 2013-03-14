/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <set>
#include "artLib2.hpp"

using namespace std;

const int CODE_SIZE_MISMATCH = -1;
const int CODE_NO_TOUR = -2;
const int CODE_FIRST_COLOR_NOT_ONE = -3;
const int CODE_NO_CONNECTION = -4;
const int CODE_TOO_LONG_DIST = -5;
const int CODE_TOUR_EXCESS = -6;

static int checkSolution(int n, int m, const vector<connection> & scheme, const pair<vector<int>, vector<int> > & teamAnswer) {
#define colors teamAnswer.first
#define tour teamAnswer.second
	// create set out of list of connections
	set <pair <int, int> > s;
	int a, b;
	for (int i = 0; i < m; i++) {
		a = scheme[i].a-1;
		b = scheme[i].b-1;
		s.insert(make_pair(a,b));
		s.insert(make_pair(b,a));
	}
	
	if ((int) colors.size() != n)
		return CODE_SIZE_MISMATCH;
	
	if ((int) tour.size() < 1)
		return CODE_NO_TOUR;
	
	for (int i = 1; i < (int) tour.size(); i++) {
		if (s.find(make_pair(tour[i-1],tour[i])) == s.end()) {
			printf("bad connection [%d, %d]\n", tour[i-1], tour[i]);
			return CODE_NO_CONNECTION;
		}
	}
	
	if (colors[tour[0]] != 1)
		return CODE_FIRST_COLOR_NOT_ONE;
	
	int cur = 0;
	for (int i = 2; i <= n+1; i++) {
		// searching for color i
		int col = i;
		if (col == n+1)
			col = 1;
		int prev = cur;
		while ((cur < (int) tour.size()) && (colors[tour[cur]] != col)) {
			cur++;
		}
		if (cur == (int) tour.size())
			return i;
		if (cur - prev > 3)
			return CODE_TOO_LONG_DIST;
	}
	if (cur != (int) tour.size() - 1)
		return CODE_TOUR_EXCESS;
	return 0;
}

int main() {
	int numOfCases;
	int n, m;
	vector<connection> scheme;
	scanf("%d",&numOfCases);
	for (int tt = 0; tt < numOfCases; tt++) {
		scheme.clear();
		scanf("%d", &n);
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d %d",&a, &b);
			connection e = {a,b};
			scheme.push_back(e);
		}
		pair<vector<int>, vector<int> > teamAnswer = draw_literate_painting(n, m, scheme);
		int checkResult = checkSolution(n, m, scheme, teamAnswer);
		if (checkResult) {
			printf ("INCORRECT - Test case %d: ", tt+1);
			if (checkResult == CODE_SIZE_MISMATCH)
				printf("size mismatch, received %d, expected %d", (int) teamAnswer.first.size(), n);
			else if (checkResult == CODE_NO_TOUR)
				printf("received empty tour");
			else if (checkResult == CODE_FIRST_COLOR_NOT_ONE)
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
	}
	printf("CORRECT 1ZVLsWpdrdt1UGg3s4qnpuS9cJpTBHqZ\n");
	return 0;
}
