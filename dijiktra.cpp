#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class edge{
    public : 
    int v=0,w=0;
    edge(int src,int we){
        v=src;
        w = we;
    }
};
class pair_{
    public:
    int src=0,par=0,w=0,wsf=0;
    pair_(int s,int p,int we,int ps){
        src = s;
        par = p;
        w =we;
        wsf = ps;
    }
    pair_(int s,int p,int we){
        pair_(s,p,we,0);
    }
};
struct cmp{
     bool operator()(pair_ &a,pair_ &b){
      return a.wsf>b.wsf;
     }
};
void dijiktra( vector<vector<edge>> graph,int N,int src){
     priority_queue<pair_,vector<pair_>,cmp> pq;
     pq.push(pair_(src,-1,0,0));
     vector<bool> vis(N,false);
     while(!pq.empty()){
        pair_ p = pq.top();
        pq.pop();
        if(vis[p.src]) continue;
        vis[p.src] = true;
        for(edge e :graph[p.src]){
            if(vis[e.v]==false){
                pq.push(pair_(e.v,p.src,e.w,e.w+p.wsf));
            }
        }
     }
}
void prims( vector<vector<edge>> graph,int N,int src){
     priority_queue<pair_,vector<pair_>,cmp> pq;
     pq.push(pair_(src,-1,0,0));
     vector<bool> vis(N,false);
     while(!pq.empty()){
        pair_ p =  pq.top();
        pq.pop();
        if(vis[p.src]) continue;
        vis[p.src] = true;
        for(edge e :graph[p.src]){
            if(vis[e.v]==false){
                pq.push(pair_(e.v,p.src,e.w,e.w+p.wsf));
            }
        }
     }
}
int main(){
    
}