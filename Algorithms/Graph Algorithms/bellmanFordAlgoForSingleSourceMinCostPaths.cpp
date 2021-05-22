//BELLMAN FORD ALGORITHM : Given a source in a graph
//find the minimum cost path to all other vertices

//DRAWBACK : It may not give incorrect min-cost paths if there
//are negative cycle

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

//To store graph edge
struct Edge
{
    int src, dest, weight;
};

//To store heap nodes
struct Node
{
    int vertex, weight;
};

class Graph
{
public:
    //Vector of vectors of Edge to represent adjacency list
    vector<vector<Edge>> adjList;

    //Graph constructor
    Graph(vector<Edge> const &edges, int noNodes)
    {
        adjList.resize(noNodes);
        //add edges to the  undirected graph
        for (auto const &edge : edges)
        {
            adjList[edge.src].push_back(edge);
        }
    }
};

void printRoute(vector<int> const &prev, int i)
{
    if (i < 0)
        return;
    printRoute(prev, prev[i]);
    cout << i << " ";
}

void bellmanFord(vector<Edge> const &edges, int source, int noNodes)
{
  int noEdges = edges.size();

  //set distance from source to all other vertices a infinity initially
  vector<int> distance(noNodes, INT_MAX);
  distance[source] = 0; //distance of source from source is zero

  //stores predecessor of a vertex(to print path)
  vector<int> prev(noNodes, -1);

  int u,v,w,temp=noNodes;

  //Relaxation step(run noNodes-1 times)
  while(--temp)
  {
    for(int i=0; i<noEdges; ++i)
    {
      u=edges[i].src;
      v=edges[i].dest;
      w=edges[i].weight;

      if(distance[u] != INT_MAX && (distance[u] + w) < distance[v])
      {
          distance[v] = distance[u] + w;
          prev[v] = u;
      }
    }  
  }

  //NEGATIVE-WEIGHT CYCLE DETECTION PROCEDURE
  for(int i=0; i<noEdges; ++i)
  {
      u = edges[i].src;
      v = edges[i].dest;
      w = edges[i].weight;

      if (distance[u] != INT_MAX && (distance[u] + w) < distance[v])
      {
          cout<<"\nNegative-weight cycle present!";
          return;
      }
  }

  //PRINT MIN-COST ROUTES FROM SOURCE TO ALL OTHER NODES
  for(int i=0; i<noNodes; ++i)
  {
    if(i!=source && distance[i]!=INT_MAX)  
    cout<<"\nPath("<<source<<","<<i<<") : Minimum Cost = "
        <<distance[i]<<" AND Route : ";
    printRoute(prev, i);      
  }
}

int main()
{
    vector<Edge> edges = {{0, 1, -1}, {0, 2, 4}, {1, 2, 3},
                          {1, 3, 2}, {1, 4, 2}, {3, 2, 5},
                          {3, 1, 1}, {4, 3, -3}};

    int noNodes = 5; //Number of nodes in the graph

    Graph graph(edges, noNodes);

    int source = 0;
    bellmanFord(edges, source, noNodes);
    return 0;
}