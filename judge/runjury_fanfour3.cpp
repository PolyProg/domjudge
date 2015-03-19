#include <iostream>

using namespace std;

const int TESTS = 10000;

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
        cout<<"1 "<<M<<endl;
      }
    } else {
      cout<<"1 0"<<endl;
    }
  }
  return 0;
}
