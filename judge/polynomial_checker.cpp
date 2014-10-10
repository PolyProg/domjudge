#include "testlib.h"
#include <iostream>
#include <cstdio>

using namespace std;

int main(int argc, char * argv[])
{
    setName("Common root checker");
    registerTestlibCmd(argc, argv);

    int n = 0;
    string ans_yes_no = ans.readToken("YES|NO");
    string out_yes_no = ouf.readToken("YES|NO");
    if (ans_yes_no != out_yes_no) {
      cout<<"Expected yes but found no"<<endl;
      return 0;
    }
    if (ans_yes_no == "NO") {
      cerr<<"Answers match"<<endl;
      return 0;
    }
    for (int i = 0; i < 2; ++i) {
      double j = ans.readDouble();
      double p = ouf.readDouble();
      const double EPS = 1e-8;
      if (!doubleCompare(j, p, EPS)) {
        printf(
              "%d%s numbers differ - expected: '%.8lf', found: '%.8lf', error "
              "= '%.9lf'",
              i+1, englishEnding(n).c_str(), j, p, doubleDelta(j, p));
        return 0;
      }
    }
    if (!ans.seekEof()) {
      cout<<"Answer contains extra tokens"<<endl;
      return 1;
    }
    if (!ouf.seekEof()) {
      cout<<"Participant output contains extra tokens"<<endl;
      return 0;
    }
    cerr<<"Answers match (\"YES\")"<<endl;
    return 0;
}
