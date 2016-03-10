#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char * argv[]) {
   setName("checker for jigsaw puzzle medium");
   registerTestlibCmd(argc, argv);
   
   int tests = inf.readInt();
   int wrongAnswers = 0, firstWA = -1;
   
   for (int test = 1; test <= tests; ++test) {
      int height = inf.readInt();
      int width = inf.readInt();
      int pieces = inf.readInt();
      for (int i = 0; i < height; ++i) {
         for (int j = 0; j < width; ++j) {
            inf.readInt(); // just rewind
         }
      }
      
      vector<int> jPerm, pPerm; // correct, participant
      
      for (int piece = 1; piece <= pieces; ++piece) {
         jPerm.push_back(ans.readInt());
         pPerm.push_back(ouf.readInt());
      }
      
      if (jPerm != pPerm) {
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
