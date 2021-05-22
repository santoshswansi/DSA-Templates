#include <iostream>
#include <vector>

using namespace std;

typedef pair<int,int> Pair;

struct Edge
{
    int src, dest,weight;
};

class Graph
{
public:
    vector<vector<Pair>> adjList; //To store adjacency list of a vertices
    Graph(vector<Edge> const &edges, int noVertices)
    {
        adjList.resize(noVertices);
        for (auto edge : edges)
        {
            adjList[edge.src].push_back(make_pair(edge.dest,edge.weight));
            //For undirected graph
            //adjList[edge.dest].push_back(make_pair(edge.src,edge.weight));
        }
    }
};

void printGraph(Graph const &graph, int noVertices)
{
    for (int i = 0; i < noVertices; ++i)
    {
        for (Pair v : graph.adjList[i])
            cout <<"("<<i<<","<<v.first<<","<<v.second<<")";
        cout << endl;
    }
}

int main()
{
    vector<Edge> edges = {{0, 1, 6}, {1, 2, 7}, {2, 0, 5}, {2, 1, 4}, {3, 2, 10}, {4, 5, 3}, {5, 4, 1}};
    int noVertices = 6;
    Graph graph(edges, noVertices); //construct graph
    printGraph(graph, noVertices);
    return 0;
}