#include "testlib.h"
using namespace std;

const string YES = "YES";
const string NO = "NO";

int main(int argc, char * argv[]) {
   setName("checker for jigsaw puzzle easy");
   registerTestlibCmd(argc, argv);
   
   int tests = inf.readInt();
   int wrongAnswers = 0, firstWA = -1;
   
   for (int test = 1; test <= tests; ++test) {
      string ja = upperCase(ans.readWord()); // correct output
      string pa = upperCase(ouf.readWord()); // participant output

      if (ja != YES && ja != NO) {
         quitf(_fail, "%s or %s expected in answer, but %s found", YES.c_str(), NO.c_str(), compress(ja).c_str());
      }

      if (pa != YES && pa != NO) {
         quitf(_pe, "%s or %s expected, but %s found", YES.c_str(), NO.c_str(), compress(pa).c_str());
      }

      if (ja != pa) {
         wrongAnswers++;
         if (firstWA == -1) firstWA = test;
      }
   }
   
   // accept iff at least 75% correct answers
   if (4 * wrongAnswers <= tests) {
      quitf(_ok, "accepted: %d correct answers out of %d tests", tests - wrongAnswers, tests);
   } else {
      quitf(_wa, "too many wrong answers: %d correct answers out of %d tests. first WA = test %d", tests - wrongAnswers, tests, firstWA);
   }
   
   // if participant has more output than necessary - whatever. ignore it
}
