#include<iostream>
#include<vector>
#include<climits>
#include<queue>

using namespace std;

enum Color {WHITE, GRAY, BLACK};

class Vertex
{
private:
    int idx;
    int distanceFromSource;

public:
    Vertex(int idx)
    {
        this -> idx = idx;
        distanceFromSource = INT_MAX;
    }

    void set_distanceFromSource(int d)
    {
        distanceFromSource = d;
    }

    int get_idx()
    {
        return idx;
    }

    int get_distanceFromSource()
    {
        return distanceFromSource;
    }

    bool operator<(Vertex &v)
    {
        return distanceFromSource < v.distanceFromSource;
    }

    bool operator>(Vertex &v)
    {
        return distanceFromSource > v.distanceFromSource;
    }

    bool operator==(Vertex &v)
    {
        return distanceFromSource == v.distanceFromSource;
    }
};

class CompareVertex
{
public:
    bool operator()(Vertex a, Vertex b)
    {
        return a.get_distanceFromSource() > b.get_distanceFromSource();
    }
};

class Edge
{
private:
    int u;
    int v;
    int w;

public:
    Edge(int u, int v, int weight)
    {
        this -> u = u;
        this -> v = v;
        this -> w = weight;
    }

    int get_u()
    {
        return u;
    }

    int get_v()
    {
        return v;
    }

    int get_weight()
    {
        return this -> w;
    }

    bool operator<(const Edge &e) const
    {
        return w < e.w;
    }

    bool operator>(const Edge &e) const
    {
        return w > e.w;
    }
};

class CompareEdge
{
public:
    bool operator()(Edge a, Edge b)
    {
        return a.get_weight() > b.get_weight();
    }
};

class WeightedGraph
{
private:
    int n; // No. of nodes
    vector<Edge> edges;
    vector<pair<int, int> > *adj; // adjacency list
    int **adjMatrix;

public:
    WeightedGraph(int n)
    {
        this -> n = n;
        adj = new vector<pair<int, int> >[n];
        adjMatrix = new int*[n];

        for(int i = 0; i < n; i++)
        {
            adjMatrix[i] = new int[n];

            for(int j = 0; j < n; j++)
                adjMatrix[i][j] = 0;
        }
    }

    void add_edge(int u, int v, int w)
    {
        adj[u].push_back(make_pair(v, w));
        adjMatrix[u][v] = w;
    }

    void add_edge(Edge e)
    {
        edges.push_back(e);
    }

    vector<pair<int, int> > get_adj(int u)
    {
        return adj[u];
    }

    vector<Edge> get_edges()
    {
        return edges;
    }

    int** get_adj_matrix()
    {
        return adjMatrix;
    }

    int get_n()
    {
        return n;
    }
};
