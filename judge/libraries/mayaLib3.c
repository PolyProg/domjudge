/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include "mayaLib3.h"

#define MAX_C 26

static const int C = 26;
static int d[MAX_C] = {1, 5, 5, 5, 3, 4, 5, 5, 3, 4, 3, 5, 3, 3, 5, 5, 5, 3, 5, 5, 4, 4, 5, 5, 5, 5};
static int g[MAX_C][MAX_C] = {
	{0},
	{2, 20, 0, 24, 4},
	{1, 13, 15, 17, 5},
	{4, 2, 20, 0, 24},
	{3, 7, 14},
	{6, 10, 22, 19},
	{5, 1, 13, 15, 17},
	{8, 23, 21, 12, 16},
	{7, 14, 3},
	{10, 22, 19, 6},
	{9, 18, 11},
	{12, 16, 8, 23, 21},
	{11, 9, 18},
	{14, 3, 7},
	{13, 15, 17, 5, 1},
	{16, 8, 23, 21, 12},
	{15, 17, 5, 1, 13},
	{18, 11, 9},
	{17, 5, 1, 13, 15},
	{20, 0, 24, 4, 2},
	{19, 6, 10, 22},
	{22, 19, 6, 10},
	{21, 12, 16, 8, 23},
	{24, 4, 2, 20, 0},
	{23, 21, 12, 16, 8},
	{0, 24, 4, 2, 20}
};

static int OUTSIDE = 1;
static int INSIDE  = 33554432;
static int current=33554432, next, cumul=0;

static void graph_to_bitmask() {
  int i, j;
	for (i=0; i<C; i++)
		for (j=0; j<d[i]; j++)
			g[i][j] = 1<<g[i][j];
}

static int bit_count (int n) {
	n = n - ((n >> 1) & 0x55555555);
	n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
	return (((n + (n >> 4)) & 0xF0F0F0F) * 0x1010101) >> 24;
}

void take_exit_number(int n) {
	next = 0;
        int j;
	for (j=0; j<C; j++)
		if ( current & (1<<j) )
			next |= g[j][n%d[j]];
	cumul += n*(bit_count(current)-1);	
	current = next;
}

int main() {
	graph_to_bitmask();
	get_heidi_out();
	if (current!=OUTSIDE) {
		printf("Bad directions\n");
		return 0;
	}
	if (cumul>432) {
		printf("Directions are not minimal\n");
		return 0;
	}
	printf("Accepted! 56b69deae7c5513fb8623c5a1bc5c286\n");
	return 0;
}
