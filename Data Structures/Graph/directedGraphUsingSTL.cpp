#include<iostream>
#include<vector>

using namespace std;

struct Edge
{
  int src,dest;  
};

class Graph
{
 public:
  vector<vector<int>> adjList; //To store adjacency list of a vertices
  Graph(vector<Edge> const &edges,int noVertices)
  {
    adjList.resize(noVertices);
    for(auto edge:edges)
    {
      adjList[edge.src].push_back(edge.dest);
      //For undirected graph
      //adjList[edge.dest].push_back(edge.src);
    }
  } 
};

void printGraph(Graph const &graph,int noVertices)
{
  for(int i=0;i<noVertices;++i)
  {
    cout<<i;
    for(int v:graph.adjList[i])
      cout<<"-->"<<v;
    cout<<endl;    
  }  
}

int main()
{
    vector<Edge> edges= {{0, 1}, {1, 2}, {2, 0}, {2, 1}, {3, 2}, {4, 5}, {5, 4}};
    int noVertices = 6;
   
    Graph graph(edges, noVertices); //construct graph
    printGraph(graph,noVertices);
    return 0;  
}