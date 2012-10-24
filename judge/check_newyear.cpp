#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int MaxN = 201;
const int MaxK = 21;

int n, m, k;
vector<pair<int, int> > edges;
int color[MaxN][MaxN];

bool valid_coloring() {
  for (int a = 1; a <= n; a++){
    bool used[MaxK]; for (int i = 0; i < MaxK; i++) used[i] = false;
    for (int b = 1; b <= n; b++){
      if (color[a][b] != -1){
	if (used[color[a][b]]) return false;
	else used[color[a][b]] = true;
      }
    }
  }

  return true;
}

int main(int argc, char** argv) {
  if(argc != 4) {
    fprintf(stderr, "Usage: %s TESTDATA.in CONTESTANT.out TESTDATA.out\n", argv[0]);
    return -1;
  }
  FILE* testdata = fopen(argv[1], "rt");
  if(!testdata) {
    perror("Could not open testdata input");
    return -2;
  }
  FILE* contestant = fopen(argv[2], "rt");
  if(!contestant) {
    perror("Could not open contestant output");
    return -2;
  }
  FILE* correct = fopen(argv[3], "rt");
  if(!correct) {
    perror("Could not open testdata output");
    return -2;
  }

  int error = 0;
  int testCase=0;

  while(true) {
    testCase++;

    // Read testcase
    if(3!=fscanf(testdata, "%d %d %d\n", &n, &m, &k)) {
      perror("Improper input format");
      return -3;
    }
    if(n == 0 && m == 0 && k == 0){
      break;
    }
    for (int i = 0; i < MaxN; i++)
      for (int j = 0; j < MaxN; j++)
	color[i][j] = -1;
    edges.clear();
    for (int i = 0; i < m; i++) {
      int a, b;
      if (2 != fscanf(testdata, "%d %d\n", &a, &b)) {
	perror("Improper input format - edge");
	return -5;
      }
      edges.push_back(make_pair(a, b));
    }

    // Read our solution (it contains only number of edges, but not a coloring)
    int colEdges;
    if (1 != fscanf(correct, "%d\n", &colEdges)) {
      perror("Improper solution format");
      return -6;
    }
    
    // Read contestant's solution
    int conEdges;
    if(1!=fscanf(contestant, "%d\n", &conEdges)) {
      printf("Problem reading contestant's solution (number of edges) for test case %d.\n", testCase);
      error++;
      break;
    }
    for (int i = 0; i < conEdges; i++) {
      int e, c;
      if (2!=fscanf(contestant, "%d %d\n", &e, &c)) {
	printf("Problem reading contestant's solution (edge color) for test case %d.\n", testCase);
	error++;
	break;
      }
      if (e <= 0 || e > m) {
	printf("Edge id is not valid: %d (1..%d).\n", e, m);
	error++;
	break;
      }
      int a = edges[e-1].first, b = edges[e-1].second;
      if (color[a][b] != -1) {
	printf("Edge %d is colored twice.\n", e);
	error++;
	break;
      }
      if (c <= 0 || c > k) {
	printf("Color is invalid: %d (1..%d).\n", c, k);
	error++;
	break;
      }
      color[a][b] = color[b][a] = c;
    }

    if (colEdges != conEdges) {
      printf("Wrong solution %d (correct %d).\n", conEdges, colEdges);
      error++;
      break;
    }
    if (!valid_coloring()) {
      printf("Invalid coloring.\n");
      error++;
      break;
    }
  }

  if(error!=0) {
    // If anything is printed on stdout, the result is considered WRONG ANSWER
    printf("Contestant solution contains %d errors.\n", error);
  }

  return 0;
}
