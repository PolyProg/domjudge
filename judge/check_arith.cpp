#include <iostream>
#include <cstdio>

using namespace std;

typedef long long int LL;

LL multiply(LL a, LL mod, LL x){
  LL y;
  if (x==0) {
    return 0LL;
  }
  y = multiply(a, mod, x/2);
  y = (y+y)% mod;
  if (x%2) {
    y = (y+a)%mod;
  }
  return y;
}

LL pow(LL a, LL mod, LL x){
  LL y;
  if (x==0) {
    return 1LL;
  }
  y = pow(a, mod, x/2);
  y=multiply(y, mod, y);
  if (x%2) {
    y=multiply(y, mod, a);
  }
  return y;
}

bool check(LL a, LL b, LL p, LL k, LL ans){
  LL pk = 1LL;
  for (LL i=0;i<k;i++) {
    pk*=p;
  }
  LL ap = pow(a, pk, ans);
  LL bp = pow(b, pk, ans);
  LL res = (ap+bp) % pk;
  if( res == 0 ) {
    return true;
  } else {
    printf("         %lld^%lld + %lld^%lld = %lld (mod %lld)\n", a, ans, b, ans, res, pk);
    return false;
  }
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

  int errors = 0;
  int line=0;

  while(true) {
    line++;

    LL a, b, p, k;
    if(4!=fscanf(testdata, "%lld %lld %lld %lld\n", &a, &b, &p, &k)) {
      perror("Improper input format");
      return -3;
    }
    if(a==0 && b==0 && p==0 && k==0) {
      break;
    }
    LL ans;
    if(1!=fscanf(contestant, "%lld\n", &ans)) {
      printf("Problem reading contestant's input at line %d.\n", line);
      errors++;
      break;
    }
    LL sol;
    if(1!=fscanf(correct, "%lld\n", &sol)) {
      perror("Improper solution format");
      return -4;
    }
    if(sol == -1) {
      if(ans!=sol) {
        check(a, b, p, k, ans);
        printf("Line %2d: no solution, but contestant output %lld.\n", line, ans);
        errors++;
      }
    } else {
      if (ans==-1) {
        printf("Line %02d: contestant's answer is incorrect: %lld (correct = %lld).\n", line, ans, sol);
        errors++;
      } else if (ans<0 or ans>1000000000000000000LL) { //10^18
        printf("Line %02d: contestant's answer is out of acceptable range: %lld.\n", line, ans);
        errors++;
      } else if(!check(a, b, p, k, ans)) {
        printf("Line %02d: contestant's answer is incorrect: %lld (correct = %lld).\n", line, ans, sol);
        errors++;
      }
    }
  }

  if(errors!=0) {
    // If anything is printed on stdout, the result is considered WRONG ANSWER
    printf("Contestant solution contains %d errors.\n", errors);
  }

  return 0;
}
