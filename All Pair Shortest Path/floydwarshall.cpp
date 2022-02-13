#include<bits/stdc++.h>
#include "weightedgraph.h"

#define INF INT_MAX

using namespace std;

int** floydWarshall(WeightedGraph graph)
{
    int n = graph.get_n();

    int **dist;
    dist = new int*[n];

    for(int i = 0; i < n; i++)
    {
        dist[i] = new int[n];
        for(int j = 0; j < n; j++)
        {
            if(i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INF;
        }
    }

    for(int i = 0; i < n; i++)
    {
        vector<pair<Vertex, int> > adj = graph.get_adj(i);
        for(int j = 0; j < adj.size(); j++)
        {
            dist[i][adj[j].first.get_idx()] = adj[j].second;
        }
    }

    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if((dist[k][j] != INF && dist[i][k] != INF) && dist[i][j] > (dist[i][k] + dist[k][j]))
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    return dist;
}

void print_all_pair_shortest_path(WeightedGraph graph)
{
    int** dist = floydWarshall(graph);
    int n = graph.get_n();

    cout << "Shortest distance matrix" << endl;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(dist[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
        }
        cout << endl;
    }
}

int main()
{
    int n, e, u, v, w;
    freopen("apsp.in", "r", stdin);

    cin >> n >> e;

    WeightedGraph graph(n);

    for(int i = 0; i < e; i++)
    {
        cin >> u >> v >> w;
        graph.add_edge(Vertex(u - 1), Vertex(v - 1), w);
    }

    print_all_pair_shortest_path(graph);
}
