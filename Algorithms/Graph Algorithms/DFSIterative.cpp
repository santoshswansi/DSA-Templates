//Iterative implementation of DFS graph traversal

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

void DFSIterative(Graph const &graph, int v, vector<bool> &discovered)
{
  stack<int> stack;
  stack.push(v); //push the source node into the stack

  while(!stack.empty())
  {
  //pop a vertex from the stack   
   v=stack.top();
   stack.pop(); 

  //if the vertex is already discovered yet,continue with the next iteration
   if(discovered[v])
    continue;

  //we will reach here if the popped vertex v is not  discovered yet.
  //We print it and process its undiscovered adjacent nodes into stack

   discovered[v] = true;
   cout<<v<<" ";

  //Do for every edge(v->u)
  //We are using reverse iterator so that they could be pushed into 
  //the stack first(will be explored later)
   for (auto it = graph.adjList[v].rbegin(); it != graph.adjList[v].rend();
            ++it)
   {
    int u = *it;
    if(!discovered[u])
     stack.push(u); 
   }          
  }    
}

int main()
{
    vector<Edge> edges = {{1, 2}, {1, 7}, {1, 8},
                          {2, 3}, {2, 6}, {3, 4}, 
                          {3, 5}, {8, 9}, {8, 12}, 
                          {9, 10}, {9, 11}};

    int noNodes = 13; //Number of nodes in the  graph
    Graph graph(edges, noNodes);

    vector<bool> discovered(noNodes, false);

    //Do BFS traversal
    for (int i = 0; i < noNodes; ++i)
    {
        if (!discovered[i])
            DFSIterative(graph, i, discovered); 
    }
    return 0;
}