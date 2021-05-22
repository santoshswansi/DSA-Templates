//Iterative implementation of BFS graph traversal

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct Edge
{
 int src,dest;
};

class Graph
{
 public:
  vector<vector<int>> adjList; //To store adjacency list of edges
  Graph(vector<Edge> const &edges, int noNodes)
  {
    adjList.resize(noNodes); //resize the the total rows of adjList
    for(auto &edge:edges)//Add undirected edges to the graph
    {
     adjList[edge.src].push_back(edge.dest);
     adjList[edge.dest].push_back(edge.src);
    }   
  }
};

void BFSIterative(Graph const &graph, int v, vector<bool> &discovered)
{
 queue<int> q;
 discovered[v]=true; //mark source vertex as discovered
 q.push(v); //push source vertex into the queue

 while(!q.empty())//run till queue is not empty
 {
  //pop front node and print it   
  v=q.front();
  q.pop();  
  cout<<v<<" ";

  //Do for every edge(v->u)
  for(int u:graph.adjList[v])
  {
    if(!discovered[u])
    {
      discovered[u] = true;
      q.push(u);
    }  
  }
 }
}

int main()
{
    vector<Edge> edges = {{1, 2}, {1,3}, {1,4}, {2,5}, {2,6} ,
                          {5,9}, {5,10}, {4,7}, {4,8}, 
                          {7,11}, {7,12}};
                          //vertex 0, 13 and 14 are single  nodes
    int noNodes=15;//Number of nodes in the  graph                      
    Graph graph(edges,noNodes);

    vector<bool> discovered(noNodes, false);

    //Do BFS traversal 
    for(int i = 0; i<noNodes;++i)
    {
      if(!discovered[i])
      {
        BFSIterative(graph, i, discovered);  
      }  
    }

    return 0;  
}