#include "weightedgraph.h"
#include<bits/stdc++.h>

using namespace std;

void initializeSingleSource(int n, int source, int distancesFromSource[], int parents[], bool dequed[])
{
    for(int i = 0; i < n; i++)
    {
        distancesFromSource[i] = INT_MAX;
        parents[i] = -1;
        dequed[i] = false;
    }

    distancesFromSource[source] = 0;
}

void dijkstra(int n, WeightedGraph &g, int source, int distancesFromSource[], int parents[])
{
    bool dequed[n];
    initializeSingleSource(n, source, distancesFromSource, parents, dequed);

    Vertex sourceVertex(source);
    sourceVertex.set_distanceFromSource(0);

    priority_queue<Vertex, vector<Vertex>, CompareVertex> q;

    q.push(sourceVertex);

    while(!q.empty())
    {
        Vertex u = q.top();
        q.pop();
        int uidx = u.get_idx();

        if(!dequed[uidx])
        {
            vector<pair<Vertex, int>> adjOfU = g.get_adj(uidx);

            for(int i = 0; i < adjOfU.size(); i++)
            {
                Vertex v = adjOfU[i].first;
                int vidx = v.get_idx();
                int tempDist = distancesFromSource[uidx] + adjOfU[i].second;

                if(distancesFromSource[vidx] > tempDist)
                {
                    v.set_distanceFromSource(tempDist);
                    distancesFromSource[vidx] = tempDist;
                    parents[vidx] = uidx;
                    q.push(v);
                }
            }

            dequed[uidx] = true;
        }
    }
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
    int distancesFromSource[n], parents[n];
//    freopen("mst.in", "r", stdin);

    cin >> n >> e;

    WeightedGraph graph(n);

    for(int i = 0; i < e; i++)
    {
        cin >> u >> v >> w;
        graph.add_edge(u, v, w);
    }

    cin >> source >> destination;


    dijkstra(n, graph, source, distancesFromSource, parents);
    cout << "Shortest Path Cost: " << distancesFromSource[destination] << endl;
    print(source, destination, parents);
}
