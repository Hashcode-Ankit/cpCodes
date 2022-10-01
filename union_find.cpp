#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
class edge
{
public:
    int v, w;
    edge(int r, int s)
    {
        v = r;
        w = s;
    }
};
void addEdge(vector<vector<edge>> &graph, int u, int v, int w)
{
    graph[u].push_back(edge(v, w));
}

//union find

int findPar(int u){
    return par[u]==u?u:(par[u]=findPar(par[u]));
}
void Union(int u,int v,vector<int>& siz){
    if(siz[u]<siz[v]){
        par[u] = v;
        siz[v]+=siz[u];
    }else{
        par[v] = u;
        siz[u]+=siz[v];
    }
}class ppair {
      public: 
        string c;
        int r;
        ppair(string co,int ra ){
            c = co;
            r=ra;
        }
    };
void union_find(vector<vector<int>> edg,int N){
    vector<int> par(N);
    vector<int> siz(N,1);
    vector<vector<edge>> graph(N);
    for(int i=0;i<N;i++) par[i] = i;
    for(vector<int> e : edg){
        int u = e[0]; int v = e[1]; int w = e[2];
        int p1 = findPar(u,par);
        int p2 = findPar(v,par);
        if(p1!=p2){
            Union(u,v,par,siz);
            addEdge(graph,u,v,w);
        }
    }
}
vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int N = edges.size();
        vector<int> par(N);
        vector<int> siz(N,1);
        vector<vector<edge>> graph(N);
        for(int i=0;i<N;i++) par[i] = i;
        int a1,a2;
        for(vector<int> e : edges){
            int u = e[0]; int v = e[1];
            int p1 = findPar(u,par);
            int p2 = findPar(v,par);
            if(p1!=p2){
                Union(u,v,par,siz);
            }else{
                a1=u;a2=v;
            }
        }
return {a1,a2};
}

// 839
bool isSimilar(string s,string t){
   int count = 0;
   for(int i = 0;i<s.length();i++) if(s[i]!=t[i] && ++count>2) return false;
   return true;
}
int numSimilarGroups(vector<string>& strs) {
    int n = strs.size();
    int ans = n;
    vector<int> par(n);
    for(int i=0;i<n;i++) par.push_back(i);
    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++){
            if(isSimilar(strs[i],strs[j])){
                int p1=findPar(i);
                int p2 = findPar(j);
                if(p1!=p2){
                    par[p1] = p2;
                    ans--;
                }
            }
        }
    }         return ans;
}

//Number of Islands 2
  vector<int> numIslands2(int n, int m, vector<vector<Point>> &operators) {
    vector<int> par;
    for(int i=0;i<m*n;i++) par.push_back(i);
    vector<vector<int>> grid(n,vector<int>(m,0));
    vector<int> ans;
    int count = 0;
    for(Point &p : operators){
        int x = p.x, y = p.y;
        if(grid[x][y]==1) {
            ans.push_back(count);
            continue;
        }
        grid[x][y] = 1;
        int p1 = findPar(x*m+y);
        for(auto d : dir) {
            int r = x + d[0];
            int c = x + d[1];
            if(r>=0 && c>=0 && r<n && c<m && grid[r][c]==1){
                int p2 = findPar(r*m+c);
                if(p1!=p2){
                    par[p2] = p1;
                    count--;
                }
            }
        }
        ans.push_back(count);
    }
    return ans;
}

void constructGraph()
{
    int n = 9;
    vector<vector<edge>> graph(n, vector<edge>());
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 3, 10);
    addEdge(graph, 1, 2, 10);
    addEdge(graph, 2, 3, 40);
    addEdge(graph, 2, 7, 2);
    addEdge(graph, 2, 8, 4);
    addEdge(graph, 7, 8, 3);
    addEdge(graph, 3, 4, 2);
    addEdge(graph, 4, 5, 2);
    addEdge(graph, 4, 6, 8);
    addEdge(graph, 5, 6, 3);
    vector<bool> visited(9, false);
    // bfs_first(graph,0,visited);
}
int main()
{
    constructGraph();
    return 0;
}

/* //optimal water distribution
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class edge{
    public : 
    int u,v,w;
    edge(int i, int j, int k){
        u = i;
        v = j;
        w = k;
    }
};
vector<int> par;
int findPar(int u){
    return par[u]==u?u:(par[u]=findPar(par[u]));
}
int main(){
    int n,m;
    cin>>n>>m;
     vector<edge> li;
    for(int i=0;i<n;i++){
        int x; cin>>x;
       int u=i+1,v = 0;
       edge e(u,v,x);
       li.push_back(e);
    }
    for(int i =0;i<m;i++){
       int u,v,w;
       cin>>u>>v>>w;
       edge e(u,v,w);
       li.push_back(e);
    }
    for(int i=0;i<n+1;i++) par.push_back(i);
    sort(li.begin(),li.end(),[](edge &a,edge &b){
        return a.w<b.w;
    });
    int cost = 0;
    for(edge e : li){
        int  u = e.u,v = e.v,w=e.w;
        int p1  = findPar(u);
        int p2 = findPar(v);
        if(p1!=p2){
            par[p1] = p2;
            cost += w; 
        }
    }
    cout<<cost<<endl;
    return 0;
}
*/