/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include "mayaLib1.hpp"
using namespace std;

static vector<vector<int> > p;
static int ourSol;
static int yourSol;
static int T;
static FILE* fin;

static void read_case() {
	int R, C;
	fscanf(fin, "%d",&R);
	p = vector<vector<int> > (R+1);
	for (int i=0; i<=R; i++) {
		fscanf(fin, "%d",&C);
		p[i] = vector<int> (C);
		for (int j=0; j<C; j++)
			fscanf(fin, "%d",&(p[i][j]));
	}
	fscanf(fin, "%d",&ourSol);
}

int main() {
        fin = stdin;
	fscanf(fin, "%d",&T);
	while (T--) {
		read_case();
		yourSol = fetch_calendar(p);
		if (yourSol != ourSol) {
			printf("Incorrect\n");
			exit(0);
		}
	}
	printf("Correct dd4ecd6fa7ca205a407d8d6dcaddaa64\n");
	return 0;
}
