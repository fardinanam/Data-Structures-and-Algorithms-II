#include<bits/stdc++.h>
#include "weightedgraph.h"

using namespace std;

int factorial(int n) {
    int f = 1;
    for(int i = 1; i <= n; i++)
        f *= i;
    return f;
}

int combination(int n, int r)
{
    if(n == 0)
    {
        cout << "n = 0" << endl;
        return -1;
    }
    else if(n < r)
    {
        cout << "r is greater than n";
        return -1;
    }

    return factorial(n) / (factorial(r) * factorial(n - r));
}

bool bfs(WeightedGraph g, int **resGraph, int s, int t, int parent[])
{
    int n = g.get_n();
    bool isVisited[n];

    for(int i = 0; i < n; i++)
    {
        isVisited[i] = false;
    }

    queue<int> q;
    q.push(s);
    isVisited[s] = true;
    parent[s] = -1;

    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        vector<pair<int, int> > adj = g.get_adj(u);

        for(int i = 0; i < adj.size(); i++)
        {
            int v = adj[i].first;

            if(!isVisited[v] && resGraph[u][v] > 0)
            {
                parent[v] = u;
                isVisited[v] = true;

                if(v == t)
                {
                    return true;
                }

                q.push(v);
            }
        }
    }

    return false;
}

int edmondsKarp(WeightedGraph g, int s, int t)
{
    int u, v;
    int n = g.get_n();

    int **resGraph;
    resGraph = new int*[n];
    for(int i = 0; i < n; i++)
    {
        resGraph[i] = new int[n];
    }

    for (u = 0; u < n; u++)
    {
        for (v = 0; v < n; v++)
        {
            resGraph[u][v] = g.get_adj_matrix()[u][v];
        }
    }

    int parent[n];
    int maxFlow = 0;

    while (bfs(g, resGraph, s, t, parent)) {
        int pathFlow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            pathFlow = min(pathFlow, resGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            resGraph[u][v] -= pathFlow;
            resGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main()
{
    int n;
    cin >> n;

    string teams[n];
    int wins[n], losses[n], left[n];
    int **against = new int*[n];

    for(int i = 0; i < n; i++)
    {
        against[i] = new int[n];
        cin >> teams[i];
        cin >> wins[i] >> losses[i] >> left[i];
        for(int j = 0; j < n; j++)
        {
            cin >> against[i][j];
        }
    }

    for(int i = 0; i < n; i++)
    {
        int numberOfNodes = n + 2 + combination((n - 1), 2);
        int s = numberOfNodes - 2, t = numberOfNodes - 1;

        int maxCapacity = 0;
        WeightedGraph g = WeightedGraph(numberOfNodes);
        int matchNo = n;
        bool eliminated = false;

        for(int j = 0; j < n; j++)
        {
            for(int k = j + 1; k < n; k++)
            {
                if(wins[i] + left[i] - wins[j] < 0 || wins[i] + left[i] - wins[k] < 0)
                {
                    eliminated = true;
                    break;
                }
                if(j != i && k != i)
                {
                    maxCapacity += against[j][k];

                    g.add_edge(s, matchNo, against[j][k]);
                    g.add_edge(matchNo, j, INT_MAX);
                    g.add_edge(matchNo, k, INT_MAX);
                    g.add_edge(j, t, wins[i] + left[i] - wins[j]);
                    g.add_edge(k, t, wins[i] + left[i] - wins[k]);
                    matchNo++;
                }
            }

            if(eliminated)
                break;
        }

        if(eliminated)
        {
            cout << teams[i] << " is eliminated" << endl;
        }
        else
        {
            int maxFlow = edmondsKarp(g, s, t);
            if(maxFlow != maxCapacity)
                cout << teams[i] << " is eliminated" << endl;
        }
    }

    return 0;
}


