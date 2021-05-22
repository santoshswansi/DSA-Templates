//Recursive implementation of DFS graph traversal

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Edge
{
    int src, dest;
};

class Graph
{
public:
    vector<vector<int>> adjList; //To store adjacency list of edges
    Graph(vector<Edge> const &edges, int noNodes)
    {
        adjList.resize(noNodes); //resize the the total rows of adjList
        for (auto &edge : edges) //Add undirected edges to the graph
        {
            adjList[edge.src].push_back(edge.dest);
            adjList[edge.dest].push_back(edge.src);
        }
    }
};

void DFSRecursive(Graph const &graph, int v, vector<bool> &discovered)
{
  //mark current node as visited and print it
  discovered[v] = true;
  cout<<v<<" ";

  //Do for every edge(v->u)
  for(int u:graph.adjList[v])
  {
    if(!discovered[u])
     DFSRecursive(graph, u, discovered); 
  }
}

int main()
{
    vector<Edge> edges = {{1, 2}, {1, 7}, {1, 8}, {2, 3}, {2, 6}, {3, 4}, {3, 5}, {8, 9}, {8, 12}, {9, 10}, {9, 11}};

    int noNodes = 13; //Number of nodes in the  graph
    Graph graph(edges, noNodes);

    vector<bool> discovered(noNodes, false);

    //Do BFS traversal
    for (int i = 0; i < noNodes; ++i)
    {
        if (!discovered[i])
            DFSRecursive(graph, i, discovered);
    }
    return 0;
}