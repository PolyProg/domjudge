#include <iostream>

using namespace std;

const int TESTS = 10000;

static unsigned int my_rand(void)
{
        static unsigned int x_n = 924928;

        const unsigned int A = 1664525;
        const unsigned int C = 1013904223;
        x_n = A*x_n + C;

        return x_n;
}

int main(int argc, char** argv) {
  bool fail = false;
  for(int i=0;i<TESTS;++i) {
    if(!fail) {
      unsigned int one=1;
      unsigned int M=0;
      cin>>one>>M;
      if(one != 1 || cin.fail()) {
        fail = true;
        cerr<<"Filter failed at line "<<i<<endl;
        cout<<"1 0"<<endl;
      } else {
        unsigned long long int newM = M;
        unsigned long long int errorExp = my_rand() % 32;
        unsigned long long int error = (1ULL) << errorExp;
        newM ^= error; 
        cout<<"1 "<<newM<<endl;
      }
    } else {
      cout<<"1 0"<<endl;
    }
  }
  return 0;
}
