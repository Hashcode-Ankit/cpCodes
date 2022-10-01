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

// topologycol order
void top_dfs(vector<vector<edge>> graph, int i, vector<bool> &vis, vector<int> &res)
{
    vis[i] = true;
    for (edge e : graph[i])
    {
        top_dfs(graph, e.v, vis, res);
    }
    res.push_back(i);
}
void topology(vector<vector<edge>> graph)
{
    int n = graph.size();
    vector<bool> vis(n, false);
    vector<int> res;
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            top_dfs(graph, i, vis, res);
        }
    }
    for (int i = res.size() - 1; i >= 0; i--)
    {
        cout << res[i] << endl;
    }
}
// this does not work for graph and stuck in that case the order also not correct in that case
// let us see how another method work

// kahns Algo

void kahnsAlgo(vector<vector<edge>> graph)
{
    int n = graph.size();
    vector<int> indegree(n, 0);
    for (vector<edge> v : graph)
    {
        for (edge e : v)
            indegree[e.v]++;
    }
    list<int> q;
    vector<int> ans;
    vector<vector<int>> res;
    int level = 0;
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0)
            q.push_back(i);
    while (q.size() > 0)
    {
        int size = q.size();
        vector<int> p;
        while (size-- > 0)
        {
            int front = q.front();
            p.push_back(front);
            ans.push_back(front);
            q.pop_front();
            for (edge e : graph[front])
            {
                if (--indegree[e.v] == 0)
                    q.push_back(e.v);
            }
        }
        level++;
        res.push_back(p);
    }
    if (ans.size() != n)
        cout << "Topological Not possible due to cycle" << endl;
    else
    {
        for (auto x : ans)
            cout << x << " " << endl;
    }
    /// vector vector for parallel processes  res
}
bool canFinish(int n, vector<vector<int>> &nums)
{
    vector<int> indegree(nums.size(), 0);
    vector<vector<int>> graph(nums.size());
    for (auto x : nums)
    {
        graph[x[0]].push_back(x[1]);
        indegree[x[1]]++;
    }
    list<int> q;
    vector<int> ans;
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0)
            q.push_back(i);
    while (q.size() > 0)
    {
        int front = q.front();
        q.pop_front();
        ans.push_back(front);
        for (int e : graph[front])
        {
            if (--indegree[e] == 0)
                q.push_back(e);
        }
    }
    if (ans.size() == n)
        return true;
    return false;
}
vector<int> findOrder(int n, vector<vector<int>> &nums)
{
    vector<int> indegree(n, 0);
    vector<vector<int>> graph(n);
    for (auto x : nums)
    {
        graph[x[0]].push_back(x[1]);
        indegree[x[1]]++;
    }
    list<int> q;
    vector<int> ans;
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0)
            q.push_back(i);
    while (q.size() > 0)
    {
        int front = q.front();
        q.pop_front();
        ans.push_back(front);
        for (int e : graph[front])
        {
            if (--indegree[e] == 0)
                q.push_back(e);
        }
    }
    reverse(ans.begin(), ans.end());
    if (ans.size() == n)
        return ans;
    ans.clear() return ans;
}

// longest increase path in matrix
int longestIncreasingPath(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();
    vector<vector<int>> dir = {{1, 0}, {0, 1}, {-1, 0}, {0,-1}};
    vector<int> indegree(m * n, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (auto x : dir)
            {
                int r = i + x[0];
                int c = j + x[1];
                if (r < n && c < m && r >= 0 && c >= 0 && matrix[r][c] < matrix[i][j])
                {
                    indegree[r * m + c]++;
                }
            }
        }
    }
    list<int> q;
    for (int i = 0; i < m * n; i++)
    {
        if (indegree[i] == 0)
            q.push_back(i);
    }
    int level = 0;
    while (q.size() > 0)
    {
        int size = q.size();
        while (size-- > 0)
        {
            int front = q.front();
            q.pop_front();
            int sr = front / m;
            int sc = front % m;
            for (auto x : dir)
            {
                int r  = sr + x[0];
                int c  = sc + x[1];

                if (r < n && c < m && r >= 0 && c >= 0 && matrix[r][c] > matrix[sr][sc])
                {
                    if(--indegree[r*m+c]==0) q.push_back(r*m+c);
                }
            }
        }
        level++;
    }
    return level;
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