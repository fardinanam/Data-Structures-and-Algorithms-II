#include "weightedgraph.h"
#include<bits/stdc++.h>

using namespace std;

void initializeSingleSource(int n, int source, int distancesFromSource[], int parents[])
{
    for(int i = 0; i < n; i++)
    {
        distancesFromSource[i] = INT_MAX;
        parents[i] = -1;
    }

    distancesFromSource[source] = 0;
}

void relax(int u, int v, int w, int distancesFromSource[], int parents[])
{
    int tempDist = INT_MAX;
    if(distancesFromSource[u] < INT_MAX)
        tempDist = distancesFromSource[u] + w;

    if(distancesFromSource[v] > tempDist)
    {
        distancesFromSource[v] = tempDist;
//        cout << v << " : " << distancesFromSource[v] << endl;
        parents[v] = u;
    }
}

bool bellmanford(int n, WeightedGraph &g, int source, int distancesFromSource[], int parents[])
{
    initializeSingleSource(n, source, distancesFromSource, parents);
    vector<Edge> edges = g.get_edges();

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < edges.size(); j++)
        {
            Edge e = edges[j];
            relax(e.get_u(), e.get_v(), e.get_weight(), distancesFromSource, parents);
        }
    }

    for(int j = 0; j < edges.size(); j++)
    {
        int u = edges[j].get_u();
        int v = edges[j].get_v();

        if(distancesFromSource[v] > distancesFromSource[u] + edges[j].get_weight())
            return false;
    }

    return true;
}

void print(int source, int destination, int parents[])
{
    if(destination == source)
    {
        cout << source << " -> ";
        return;
    }

    print(source, parents[destination], parents);
    cout << destination << " -> ";
}

int main()
{
    int n, e, u, v, w, source, destination;

    cin >> n >> e;
    int distancesFromSource[n], parents[n];
    WeightedGraph graph(n);

    for(int i = 0; i < e; i++)
    {
        cin >> u >> v >> w;
        Edge edge(u, v, w);
        graph.add_edge(edge);
    }

    cin >> source >> destination;

    if(bellmanford(n, graph, source, distancesFromSource, parents))
    {
        cout << "The graph does not contain a negative cycle" << endl;
        cout << "Shortest Path Cost: " << distancesFromSource[destination] << endl;
        print(source, destination, parents);
    }
    else
    {
        cout << "The graph contains a negative cycle" << endl;
    }

    return 0;
}
