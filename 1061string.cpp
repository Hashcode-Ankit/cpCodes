#include<iostream>
#include<vector>
using namespace std;
vector<int> par;
int findPar(int u) {
    return par[u]==u?u:(par[u]=findPar(par[u]));
}
using namespace std;
int main() {
    string a,b,c;
    cin>>a>>b>>c;
    
    for(int i=0;i<26;i++) par.push_back(i);

    for(int i=0;i<a.length();i++){
        char d = a[i],e = b[i];
        int p1 = findPar(d-'a'),p2 = findPar(e-'a');
        par[p1] = min(p1,p2);
        par[p2]= min(p1,p2);
    }
  string ans = "";
  for(auto ch : c){
    int p1 = findPar(ch-'a');
    ans+=(char)(p1+'a');
  }
  cout<<ans<<endl;
}