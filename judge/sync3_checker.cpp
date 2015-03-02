#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

const string YES = "YES";
const string NO = "NO";

pattern pat("[ab]{1,500000}");

int main(int argc, char * argv[]) {
   setName("checker for synchronizing automata");
   registerTestlibCmd(argc, argv);

   string ja = upperCase(ans.readWord()); // correct output
   string pa = upperCase(ouf.readWord()); // participant output

   if (ja != YES && ja != NO) {
      quitf(_fail, "%s or %s expected in answer, but %s found", YES.c_str(), NO.c_str(), compress(ja).c_str());
   }

   if (pa != YES && pa != NO) {
      quitf(_pe, "%s or %s expected, but %s found", YES.c_str(), NO.c_str(), compress(pa).c_str());
   }

   if (ja != pa) {
      quitf(_wa, "expected %s, found %s", compress(ja).c_str(), compress(pa).c_str());
   }
   
   if (ja == YES) {
      // have to check the second word
      string ps = ouf.readWord(pat); // check if it looks like a command sequence
      
      // read input and convert to 0-based
      int n = inf.readInt();
      vector<int> a(n), b(n);
      for (int i = 0; i < n; ++i) {
         a[i] = inf.readInt() - 1;
         b[i] = inf.readInt() - 1;
      }
      
      // do the simulation
      vector<bool> active(n, true);
      for (int ch = 0; ch < ps.size(); ++ch) {
         vector<bool> newActive(n, false);
         for (int i = 0; i < n; ++i) {
            if (active[i]) {
               if (ps[ch] == 'a') {
                  newActive[a[i]] = true;
               } else {
                  newActive[b[i]] = true;
               }
            }
         }
         active = newActive;
      }
      
      int cnt = 0;
      for (int i = 0; i < n; ++i) {
         if (active[i]) {
            ++cnt;
         }
      }
      if (1 != cnt) {
         quitf(_wa, "answer is YES but command sequence given by participant is not synchronizing");
      } else {
         quitf(_ok, "answer is YES and command sequence given by participant is synchronizing");
      }
   } else {
      quitf(_ok, "answer is NO");
   }
}
