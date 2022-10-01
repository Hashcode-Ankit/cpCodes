/*

Author : Ankit Sharma

github:https://github.com/ankitkumar2698

linkedin : https://www.linkedin.com/in/ankitsharmakaushik

*/


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
    for(int i=0;i<v;i ++){
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
class pair_{
    public :
    string path;
    int w;
    pair_(){
        path ="";
        w =0;
    }
    pair_(string s,int we) {
        path  = s;
        w = we;
    }
};
pair_ heavyPath(vector<vector<edge>>& graph,int src,int dest, vector<bool>& visited)
{
    if(src == dest){
        pair_ p(to_string(dest),0);
        // cout<<"hellp";
        return p;
    }
    visited[src] = true;
    pair_ myPair("",-1);
    for(edge e : graph[src]){
        // cout<<src<<e.v<<endl;
        if(!visited[e.v]){
            // cout<<"come here";
            pair_ p = heavyPath(graph,e.v,dest,visited);

            // cout<<p.w<<" "<<p.path<<endl;
            if(p.w!=-1 && ((p.w+e.w) > myPair.w)){
                myPair.w = p.w+e.w;
                myPair.path=to_string(src)+p.path;
            }
        }
    }
    visited[src] = false;
return myPair;
}
pair_ lightestPath(vector<vector<edge>> graph,int src,int dest,vector<bool> visited){
    if(src == dest){
        pair_ p(to_string(dest),0);
        // cout<<"hellp";
        return p;  
    }
    visited[src] = true;
    pair_ myPair("",INT8_MAX);
    for(edge e : graph[src]){
        if(!visited[e.v]){
            pair_ p = heavyPath(graph,e.v,dest,visited);
            if(p.w!=-1 && ((p.w+e.w) < myPair.w)){
                myPair.w = p.w+e.w;
                myPair.path=to_string(src)+p.path;
            }
        }
    }
    visited[src] = false;
return myPair;
}
pair_ longPath(vector<vector<edge>> graph,int src,int dest,vector<bool> visited){
    if(src == dest){
        pair_ p(to_string(src),0);
        return p;
    }
    visited[src] = true;
    pair_ myPair("",0);
    for(edge e  : graph[src]){
        if(!visited[e.v]){
            pair_ p = longPath(graph,e.v,dest,visited);
            if((p.path).length()!=0 && (p.path).length()+(to_string(src)).length()>myPair.path.length()){
                myPair.w = p.w + e.w;
                myPair.path = to_string(src) + p.path;
            }
        }
    }
    visited[src] = false;
    return myPair;
}
pair_ shortPath(vector<vector<edge>> graph,int src,int dest,vector<bool> visited){
    if(src == dest){
        pair_ p(to_string(src),0);
        return p;
    }
    visited[src] = true;
    pair_ myPair("ABCDEFGHIJKLMNOPQRSTUVWXYZ",0);
    for(edge e  : graph[src]){
        if(!visited[e.v]){
            pair_ p = shortPath(graph,e.v,dest,visited);
            if((p.path).length()!=0 && (p.path).length()+(to_string(src)).length()<myPair.path.length()){
                myPair.w = p.w + e.w;
                myPair.path = to_string(src) + p.path;
            }
        }
    }
    visited[src] = false;
    return myPair;
}
//hamadonian path     
void hamandonianPath(vector<vector<edge>> graph,int src,int osrc,int edgeCount,vector<bool> visited,string path){
    if(edgeCount == (graph.size()-1)){
        path+=to_string(src);
        if(findEdge(graph,src,osrc)!=-1){
            path+="*";
        }
        cout<<path<<endl;
        return;
    }
    visited[src] = true;
    for(edge e : graph[src]){
        if(!visited[e.v]){
                hamandonianPath(graph,e.v,osrc,edgeCount+1,visited,path+to_string(src));
        }
    }
    visited[src] = false;
}
//get connected components
void dfs_comp(vector<vector<edge>> graph,int src,vector<bool> & visited){
    visited[src]=true;
    for(edge e: graph[src]) if(!visited[e.v]) dfs_comp(graph,e.v,visited);
}

void gcc(vector<vector<edge>> graph,int src){
     vector<bool> visited(graph.size(),false);
     int ans = 0;
     for(int i = src;i<graph.size();i++){
        if(!visited[i]){
            ans++;
            cout<<i<<endl;
            dfs_comp(graph,i,visited);
        }
     }
     for(auto x: visited) if(x) cout<<1<<endl; else cout<<"0"<<endl;
     cout<<ans<<endl;
}
//////////////////Breadth First Search ///////////////////////////////

// First Method
// void bfs_first(vector<vector<edge>> graph,int src,vector<bool> &vis){
//     list<int> q;
//     cout<<"here";
//     q.push_back(src);
//     int i = 0;
//     while(!q.size()>0){
//         int size = q.size();
//         while((size--)>0) {
//             int front  = q.front();
//             q.pop_front();
//             if(vis[front]){
//                 cout<<endl<<"CYCLE Present"<<endl; 
//                 continue;
//             }
//             vis[front] = true;
//             cout<<front<<" ";
//             for(edge e : graph[front]){
//                 q.push_back(e.v);
//             }
//         }
//     cout<<endl<<"Level "<<i++<<"----------->"<<endl;
//     }
// }


void constructGraph(){
    int n=7;
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
    // pair_ p = heavyPath(graph,0,6,visited);
    // // display(graph,9);
    // cout<<p.path<<"@"<<p.w<<endl;
    // pair_ q = lightestPath(graph,0,6,visited);
    // // display(graph,9);
    // cout<<q.path<<"@"<<q.w<<endl;
    // pair_ r = longPath(graph,0,6,visited);
    // cout<<r.path<<"@"<<r.w<<endl;
    // pair_ s = shortPath(graph,0,6,visited);
    // cout<<s.path<<"@"<<s.w<<endl;
    // cout<<graph.size()-1<<endl;
    // hamandonianPath(graph,0,0,0,visited,"");
    // gcc(graph,0);
    // bfs_first(graph,0,visited);
}
int main(){
   constructGraph();
    return 0;
}

