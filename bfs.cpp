
#include <iostream>
#include <vector>
#include <list>

using namespace std;
class edge{
  public :
  int v,w;
  edge(int r,int s){
      v = r;
      w = s;
  }
};
void addEdge(vector<vector<edge>>& graph,int u,int v,int w){
    graph[u].push_back(edge(v,w));
    graph[v].push_back(edge(u,w));
}
void display(vector<vector<edge>> graph,int v){
    for(int i=0;i<v;i++){
        for(edge e: graph[i]){
            cout<<e.v<<" "<<e.w<<endl;
        }
        cout<<endl;
    }
}
int findEdge(vector<vector<edge>>& graph,int u,int v){
    for(int i=0;i<graph[u].size();i++){
        if(graph[u][i].v==v) return i;         
    }
    return -1;     
}
void removeEdge(vector<vector<edge>> graph,int u,int v){
    int idx = findEdge(graph,u,v);
    graph[u].erase(graph[u].begin()+idx);
    idx = findEdge(graph,v,u);
    graph[v].erase(graph[v].begin()+idx);
}
void removeVertex(vector<vector<edge>> graph,int u){
     for(int i=graph[u].size()-1;i>=0;i++){
        removeEdge(graph,u,graph[u][i].v);
     }
}
bool hasPath(vector<vector<edge>> graph,int src,int dest,vector<int> visited){
    if(src == dest) return true;
    bool res= false;
        visited[src] = true;
        for(edge e: graph[src]){
            res = res || hasPath(graph,e.v,dest,visited);
        }
        return res;
}

int allPath(vector<vector<edge>> graph,int src,int dest, vector<int> visited,string psf){
    if(src == dest) {
        cout<<psf<<"+"<<dest<<endl;
    }
    int count=0;
    visited[src] = true;
    for(edge e : graph[src]) {
        if(!visited[e.v])
        count+=allPath(graph,e.v,dest,visited,psf+to_string(e.v));
    }
    visited[src] = false;
    return count;
}
void preorder(vector<vector<edge>> graph,int src,int dest,int wsf, vector<int> visited){
    visited[src] = true;
    cout<<src<<"@"<<wsf<<" ";
    for(edge e : graph[src]){
        preorder(graph,e.v,dest,wsf+e.w,visited);
    visited[src]=false;
} 
    }


// First Method
void bfs_first(vector<vector<edge>> graph,int src,vector<bool> &vis){
    list<int> q;
    q.push_back(src);
    int i = 0;
    while(q.size()>0){
        int size = q.size();
        while((size--)>0) {
            int front  = q.front();
            q.pop_front();
            if(vis[front]){
                cout<<endl<<"CYCLE Present"<<endl; 
                continue;
            }
            vis[front] = true;
            cout<<front<<" ";
            for(edge e : graph[front]){
                if(!vis[e.v]) 
                q.push_back(e.v);
            }
        }
    cout<<endl<<"Level "<<i++<<"----------->"<<endl;
    }
}

// Second Approach of BFS
void bfs_Sec(vector<vector<edge>> graph,int src,vector<bool> &vis){
    list<int> q;
    q.push_back(src);
    vis[src] = true;

    int i = 0;
    while(q.size()>0){
        int size = q.size();
        while((size--)>0) {
            int front  = q.front();
            q.pop_front();
            cout<<front<<" ";
            for(edge e : graph[front]){
                if(!vis[e.v]){
                vis[e.v] = true;
                q.push_back(e.v);
                }
            }
        }
    cout<<endl<<"Level "<<i++<<"----------->"<<endl;
    }
}
// Bypatrite
bool Bypatrite(vector<vector<edge>> graph, int src, vector<int> &vis){
    list<int> q;
    q.push_back(src);
    bool isBypatrite=true,cycle  = false;
    int color = 0; // 0 : red, 1: green, -1 : Nocolor
    while(q.size()>0){
        int size = q.size();
        while(size-- >0){
            int front = q.front();
            q.pop_front();
            if(vis[front]!=-1){
                cycle = true;
                if(color!=vis[front]) {
                    isBypatrite = false;
                }
                continue;
            }
            vis[front] = color;
            for(edge e  : graph[front]){
                if(vis[e.v]==-1)
                q.push_back(e.v);
            }
        }
        color = (color+1)%2;
     }
    if(cycle){
    if(isBypatrite) {cout<<"Even Cycle Present"<<endl; return true;}
    else {cout<<"ODD Cycle Present"<<endl; return false;}
    }
    else return true;

    return true;

}

///
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
       list<int> q;
        int n=grid.size(),m= grid[0].size();
        if(grid[0][0]==1 || grid[n-1][m-1]==1) return -1;
        q.push_back(0);
        vector<vector<int>> dir = {{0,1},{1,0},{-1,0},{0,-1},{1,1},{-1,-1},{-1,1},{1,-1}};
        int times = 0;
        while(q.size()>0){
            int size = q.size();
            while(size-->0){
                int front = q.front();
                q.pop_front();
                int sr = front/m,sc = front%m;
                if(sr == n-1 && sc == m-1) return times+1;
    
                for(vector<int> d : dir) {
                    int r = sr + d[0];
                    int c = sc + d[1];
                    if(r>=0 && c>=0 && r<n && c<m && grid[r][c]==0){
                        grid[r][c] =1;
                        q.push_back(r*m+c);
                    }
                }
            }
            times++;
        }
        return -1;
    }
};

// // topologycol order 
// void top_dfs(vector<vector<edge>> graph, int i, vector<bool> &vis,vector<int> &res){
//     vis[i] = true;
//     for(edge e : graph[i]){
//         top_dfs(graph,e.v,vis,res);
//     }
//     res.push_back(i);
// }
// void topology(vector<vector<edge>> graph  ){
//     int n = graph.size();
//     vector<bool> vis(n,false);
//     vector<int> res;
//     for(int i=0;i<n;i++){
//         if(!vis[i]){
//             top_dfs(graph,i,vis,res);
//         }
//     }
//     for(int i=res.size()-1;i>=0;i--){
//         cout<<res[i]<<endl;
//     }
// }
// // this does not work for graph and stuck in that case the order also not correct in that case
// //let us see how another method work

// //kahns Algo

// // void kahnsAlgo(vector<vector<edge> graph,)
void constructGraph(){
    int n=9;
    vector<vector<edge>> graph(n,vector<edge>());
    addEdge(graph,0,1,10);
    addEdge(graph,0,3,10);
    addEdge(graph,1,2,10);
    addEdge(graph,2,3,40);
    addEdge(graph,2,7,2);
    addEdge(graph,2,8,4);
    addEdge(graph,7,8,3);
    addEdge(graph,3,4,2);
    addEdge(graph,4,5,2);
    addEdge(graph,4,6,8);
    addEdge(graph,5,6,3);
    vector<bool> visited(9,false);
    // bfs_first(graph,0,visited);
    vector<int> v(n,-1);
if(!Bypatrite(graph,0,v)) cout<<"No\n";

}
int main(){
   constructGraph();
    return 0;
}

