#include "testlib.h"
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#include<map>
#include<queue>
#include<cassert>
#define PB push_back
#define MP make_pair
#define sz(v) (in((v).size()))
#define forn(i,n) for(in i=0;i<(n);++i)
#define forv(i,v) forn(i,sz(v))
#define fors(i,s) for(auto i=(s).begin();i!=(s).end();++i)
#define all(v) (v).begin(),(v).end()
using namespace std;
typedef long long in;
typedef vector<in> VI;
typedef vector<VI> VVI;
in n;
VI p,q;
int main(int argc, char* argv[]){
  registerTestlibCmd(argc, argv);
  in mans=ouf.readInt();
  in hasol=(ans.readInt()!=-1);
  if(mans==-1){
    if(hasol)
      quitf(_wa, "Solution exists but you didn't find it\n");
    quitf(_ok, "Solution doesn't exist\n");
  }
  if(mans<-1)
    quitf(_wa, "Invalid number of operations");
  n=inf.readInt();
  p=q=VI(n);
  forn(i,n)
    p[i]=inf.readInt();
  forn(i,n)
    q[i]=inf.readInt();
  in ta,tb;
  forn(i,mans){
    ta=ouf.readInt();
    tb=ouf.readInt();
    --ta;
    --tb;
    if(ta<0 || ta>=n || tb<0 || tb>=n || ta>=tb || p[ta]<=p[tb])
      quitf(_wa, "Attempted an invalid operation\n");
    swap(p[ta],p[tb]);
  }
  forn(i,n){
    if(p[i]!=q[i])
      quitf(_wa, "Your sequence of operations isn't a solution\n");
  }
  if(!hasol)
    quitf(_fail, "You found a solution but we claimed it doesn't exist\n");
  quitf(_ok, "You found a solution\n");
  return 0;
}
