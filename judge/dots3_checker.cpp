#include "testlib.h"
#include<cassert>
#include<cstdio>
#include<vector>
#include<map>
#include<algorithm>
#include<iostream>
using namespace std;
#define MAX 100010
int z,n,m,x,y,needs[MAX],hash[MAX],seen,p[MAX];
int find(int x){return p[x]==x?x:p[x]=find(p[x]);}
typedef vector<int> vi;
typedef pair<int,int> p2;
typedef vector<p2> tree_hash;
ostream operator<<(ostream &o,tree_hash &h){
  cout<<"[";
  for(int i=0;i<h.size();i++)cout<<h[i].first<<"."<<h[i].second<<",";
  cout<<"]";
}
map<vi,int> nr;
vi s[MAX],s2[MAX],q,qq;
bool b[MAX];
void dfs(int x){
  b[x]=true;
  for(int i=0;i<s[x].size();i++)if(!b[s[x][i]])dfs(s[x][i]);
  needs[x]=s[x].size();
  if(needs[x]<=1){
    q.push_back(x);
    needs[x]=-1;
  }
}
void assign(int x){
  vi nbr;
  for(int i=0;i<s[x].size();i++)if(needs[s[x][i]]==-2)nbr.push_back(hash[s[x][i]]);
  sort(nbr.begin(),nbr.end());
  map<vi,int>::const_iterator it=nr.find(nbr);
  if(it!=nr.end())hash[x]=it->second;else{
    int next=nr.size();
    hash[x]=nr[nbr]=next;
  }
}
void process(int x){
  needs[x]=-2;
  for(int i=0;i<s[x].size();i++)if(needs[s[x][i]]>-1&&--needs[s[x][i]]<=1){
    needs[s[x][i]]=-1;
    qq.push_back(s[x][i]);
  }
}
tree_hash visit(){
  tree_hash t;
  for(int j=1;j<=n;j++)b[j]=false;
  for(int j=1;j<=n;j++)if(!b[j]){
    q.clear();
    dfs(j);
    while(q.size()>1){
      qq.clear();
      for(int k=0;k<q.size();k++)assign(q[k]);
      for(int k=0;k<q.size();k++)process(q[k]);
      swap(q,qq);
    }
    if(q.size()==1){
      assign(q[0]);
      t.push_back(p2(-1,hash[q[0]]));
    }else{
      assert(qq.size()==2);
      t.push_back(p2(hash[qq[0]],hash[qq[1]]));
      if(t.back().first>t.back().second)swap(t.back().first,t.back().second);
    }
  }
  sort(t.begin(),t.end());
  return t;
}

const string YES = "YES";
const string NO = "NO";

int main(int argc,char *argv[]){
  setName("checker for connect-the-dots-hard");
  registerTestlibCmd(argc, argv);

  z = inf.readInt();
  while(z--){
    n = inf.readInt();
    inf.readInt(); // rewind k
    nr.clear();
    vector<tree_hash> t;
    bool found=false;
    for(int i=1;i<=2;i++){
      m = inf.readInt();
      for(int j=1;j<=n;j++)s[j].clear();
      while(m--){
        x = inf.readInt();
        y = inf.readInt();
        s[x].push_back(y);
        s[y].push_back(x);
      }
      t.push_back(visit());
    }
    sort(t.begin(),t.end());

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
    
    if (ja == NO) continue;
    
    
    for(int i=1;i<=n;i++){
      s2[i].clear();
      p[i]=i;
    }
    for(int i=1;i<n;i++){
      x = ouf.readInt(1, n, "x");
      y = ouf.readInt(1, n, "y");
      
      // also fast-forward through x, y in ans
      ans.readInt(1, n, "x in ans");
      ans.readInt(1, n, "y in ans");
      
      s2[x].push_back(y);
      s2[y].push_back(x);
      x=find(x);
      y=find(y);
      if(x==y){
        quitf(_wa, "not a tree");
      }
      p[x]=y;
    }
    
    for(int removed=1;removed<=n;removed++){
      for(int i=1;i<=n;i++){
        s[i].clear();
        if(i!=removed)for(int j=0;j<s2[i].size();j++)if(s2[i][j]!=removed)s[i].push_back(s2[i][j]);
      }      
      tree_hash tt=visit();
      for(int i=0;i<t.size();i++)if(tt==t[i]){
        t.erase(t.begin()+i);
        break;
      }
    }
    if(!t.empty()){
      quitf(_wa, "wrong");
    }
  }
  quitf(_ok, "everything is ok");
}

