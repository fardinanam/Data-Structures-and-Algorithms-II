#include<iostream>
#include<vector>
#include<climits>
#include<queue>

using namespace std;

enum Color {WHITE, GRAY, BLACK};

class Graph
{
private:
    int n; // No. of nodes
    vector<int> *adj; // adjacency list

public:
    Graph(int n)
    {
        this -> n = n;
        adj = new vector<int>[n];
    }

    void add_edge(u, v)
    {
        adj[u].push_back(v);
    }

    Graph get_transpose()
    {
        Graph transGraph(n);
        for (int u = 0; u < n; u++)
        {
            int size = adj[u].size();

            for(int i = 0; i < size; i++)
            {
                int v = adj[u][i];
                transGraph.adj[v].push_back(u);
            }
        }
        return transGraph;
    }

    void dfs_visit(int source, Color visited[])
    {
        visited[source] = GRAY;

        int size = adj[source].size();

        for(int i = 0; i < size; i++)
        {
            int v = adj[source][i];
            if(visited[v] == WHITE)
            {
                dfs_visit(v, visited);
            }
        }

        visited[source] = BLACK;
    }

    void dfs(int visited[])
    {
        for(int i = 0; i < n; i++)
        {
            visited[i] = WHITE;
        }

        for(int i = 0; i < n; i++)
        {
            if(visited[i] == WHITE)
            {
                dfs_visit(i, visited);
            }
        }
    }

    void bfs(int source, int parent[], int distanceFromSource[], Color visited[])
    {
        for(int i = 0; i < n; i++)
        {

            visited[i] = WHITE;
            distanceFromSource[i] = INT_MAX;
            parent[i] = -1; // means it has no parent

        }

        visited[source] = GRAY;
        distanceFromSource[source] = 0;

        queue<int> q;
        q.push(source);

        while(!q.empty())
        {
            int u = q.front();
            q.pop();

            int size = adj[u].size();

            for(int i = 0; i < size; i++)
            {
                int v = adj[u][i];
                if(visited[v] == WHITE)
                {
                    visited[v] = GRAY;
                    distanceFromSource[v] = distanceFromSource[u] + 1;
                    parent[v] = u;
                    q.push(v);
                }
            }

            visited[u] = BLACK;
        }
    }

    int get_n()
    {
        return n;
    }

    vector<int> get_adj(int u)
    {
        return adj[u];
    }
};
