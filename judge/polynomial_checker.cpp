#include "testlib.h"

using namespace std;

int main(int argc, char * argv[])
{
    setName("Common root checker");
    registerTestlibCmd(argc, argv);

    int n = 0;
    string ans_yes_no = ans.readToken("YES|NO");
    string out_yes_no = ouf.readToken("YES|NO");
    if (ans_yes_no != out_yes_no) {
      expectedButFound(_wa, ans_yes_no, out_yes_no);
    }
    if (ans_yes_no == "NO") {
      quitf(_ok, "Answers match (\"NO\")");
    }
    for (int i = 0; i < 2; ++i) {
      double j = ans.readDouble();
      double p = ouf.readDouble();
      const double EPS = 1e-8;
      if (!doubleCompare(j, p, EPS)) {
        quitf(_wa,
              "%d%s numbers differ - expected: '%.8lf', found: '%.8lf', error "
              "= '%.9lf'",
              i+1, englishEnding(n).c_str(), j, p, doubleDelta(j, p));
      }
    }
    if (!ans.seekEof()) {
      quitf(_fail, "Answer contains extra tokens");
    }
    if (!ouf.seekEof()) {
      quitf(_wa, "Participant output contains extra tokens");
    }
    quitf(_ok, "Answers match (\"YES\")");
}
