#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

bool compare(char* sol, char* cont) {
  char* p = strchr(sol, '\n');
  if(p) {
    *p = '\0';
  }
  p = strchr(sol, '\r');
  if(p) {
    *p = '\0';
  }
  p = strchr(cont, '\n');
  if(p) {
    *p = '\0';
  }
  p = strchr(cont, '\r');
  if(p) {
    *p = '\0';
  }
  return (0 == strcmp(sol, cont));
}

int main(int argc, char** argv) {
  if(argc != 4) {
    fprintf(stderr, "Usage: %s TESTDATA.in CONTESTANT.out TESTDATA.out\n", argv[0]);
    return -1;
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

  // Read our solution
  const int BUF_SIZE = 10000;
  char en_sol[BUF_SIZE];
  char fr_sol[BUF_SIZE];
  char de_sol[BUF_SIZE];
  if (NULL == fgets(en_sol, BUF_SIZE, correct)) {
    perror("Improper solution format");
    return -3;
  }
  if (NULL == fgets(fr_sol, BUF_SIZE, correct)) {
    perror("Improper solution format");
    return -4;
  }
  if (NULL == fgets(de_sol, BUF_SIZE, correct)) {
    perror("Improper solution format");
    return -5;
  }
  char con[BUF_SIZE];
  if (NULL == fgets(con, BUF_SIZE, contestant)) {
    printf("Problem reading contestant's input.\n");
    return -6;
  }

  if(compare(en_sol, con) || compare(fr_sol, con) || compare(de_sol, con)) {
    // ok
  } else {
    printf("Contestant solution is incorrect.\n");
    con[50]='\0';
    en_sol[50]='\0';
    fr_sol[50]='\0';
    de_sol[50]='\0';
    printf("C: %50s\n", con);
    printf("E: %50s\n", en_sol);
    printf("F: %50s\n", fr_sol);
    printf("D: %50s\n", de_sol);
  }

  fclose(contestant);
  fclose(correct);
  return 0;
}
