#include<bits/stdc++.h>

using namespace std;

class Edge
{
private:
    int u;
    int v;
    double w;

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

    double get_weight()
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
    int n; // no. of vertices
    int *parents;
    int *ranks;
    vector<Edge> edges;
    vector<Edge> *adjEdges;

public:
    WeightedGraph(int n)
    {
        this -> n = n;
        parents = new int[n];
        ranks = new int[n];
        adjEdges = new vector<Edge>[n];
    }

    vector<Edge> get_edges()
    {
        return edges;
    }

    vector<Edge> get_adjEdges(int u)
    {
        return adjEdges[u];
    }

    void add_edge(int u, int v, double weight)
    {
        Edge e(u, v, weight);
        edges.push_back(e);
        adjEdges[u].push_back(e);
        adjEdges[v].push_back(e);
    }

    void make_set(int x)
    {
        parents[x] = x;
        ranks[x] = 0;
    }

    int find_set(int x)
    {
        if(x != parents[x])
        {
            parents[x] = find_set(parents[x]);
        }

        return parents[x];
    }

    void link(int x, int y)
    {
        if(ranks[x] > ranks[y])
            parents[y] = x;
        else
        {
            parents[x] = y;
            if(ranks[x] == ranks[y])
                ranks[y]++;
        }
    }

    void uni(int x, int y)
    {
        link(find_set(x), find_set(y));
    }

    void sort_edges()
    {
        sort(edges.begin(), edges.end());
    }

    ~WeightedGraph()
    {
        delete []parents;
        delete []ranks;
    }
};

vector<Edge> mst_kruskal(int n, WeightedGraph &g)
{

    vector<Edge> mstEdges;

    for(int i = 0; i < n; i++)
    {
        g.make_set(i);
    }

    g.sort_edges();

    vector<Edge> edges = g.get_edges();
    int size = edges.size();

    for(int i = 0; i < size; i++)
    {
        int u = edges[i].get_u();
        int v = edges[i].get_v();
        if(g.find_set(u) != g.find_set(v))
        {
            mstEdges.push_back(edges[i]);
            g.uni(u, v);
        }
    }

    return mstEdges;
}

void makeFalse(int n, bool visited[])
{
    for(int i = 0; i < n; i++)
        visited[i] = false;
}

vector<Edge> mst_prim(int n, int start, WeightedGraph &g)
{
    bool visited[n];
    vector<Edge> mstEdges;
    priority_queue<Edge, vector<Edge>, CompareEdge> pq;
    makeFalse(n, visited);

    visited[start] = true;
    vector<Edge> adjEdges = g.get_adjEdges(start);

    for(int i = 0; i < adjEdges.size(); i++)
    {
        pq.push(adjEdges[i]);
    }

    while(!pq.empty())
    {
        Edge e = pq.top();
        pq.pop();
        int u = e.get_u();
        int v = e.get_v();
        int notVisited = -1;

        if(!visited[u])
        {
            notVisited = u;
        }
        else if(!visited[v])
        {
            notVisited = v;

        }

        if(notVisited != -1)
        {
            visited[notVisited] = true;
            adjEdges = g.get_adjEdges(notVisited);

            for (int i = 0; i < adjEdges.size(); i++)
            {
                pq.push(adjEdges[i]);
            }

            mstEdges.push_back(e);
        }
    }

    return mstEdges;
}

void print_sets(vector<Edge> sp, vector<Edge> sk)
{
    double cost = 0.0;

    for(int i = 0; i < sp.size(); i++)
    {
        cost += sp[i].get_weight();
    }

    cout << "Cost of the minimum spanning tree : " << cost << endl;
    cout << "List of edges selected by Prim's : {";

    for (Edge x : sp)
    {
        cout << "(" << x.get_u() << ","
             << x.get_v() << ")";
    }
    cout << "}\n";

    cout << "List of edges selected by Kruskal's : {";

    for (Edge x : sk)
    {
        cout << "(" << x.get_u() << ","
             << x.get_v() << ")";
    }
    cout << "}\n";
}

int main()
{
    int n, e, u, v;
    double w;

    freopen("mst.in", "r", stdin);

    cin >> n >> e;

    WeightedGraph graph(n);

    for(int i = 0; i < e; i++)
    {
        cin >> u >> v >> w;
        graph.add_edge(u, v, w);
    }

    vector<Edge> mstSetByPrim = mst_prim(n, 0, graph);
    vector<Edge> mstSetByKruskal = mst_kruskal(n, graph);
    print_sets(mstSetByPrim, mstSetByKruskal);
}
