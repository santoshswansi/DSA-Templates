// Find the max from from source to sink in a flow network

// T = O(E * V^3) which can be lowered to O(V * E^2)

#include<iostream>
#include<string.h>
#include<queue>
#include<climits>
#include<algorithm>

using namespace std;
#define V 6

//BFS based function if there is any augmenting path in the residual graph
// or not
bool isThereAnyAugmentingPath(int rGraph[6][6], int source, int sink, int parent[])
{
    bool visited[V];
    memset(visited, false, sizeof(visited));
    
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    //Standard BFS
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for(int v = 0 ; v < V; ++v)
        {
            if(visited[v]== false && rGraph[u][v] != 0)
            {
                q.push(v);
                visited[v] = true;
                parent[v] = u;
            }
        }
    }
    
  return (visited[sink] == true); //If we visited sink path is present
}

int fordFulkerson(int graph[V][V], int source, int sink)
{
  //Make the residual graph
  int rGraph[V][V];

  //Initialise residual graph (Can you work on the original graph)
  for(int i = 0; i<V; ++i)
    for(int j = 0; j<V; ++j)
       rGraph[i][j] = graph[i][j];

  int parent[V]; // To store path

  int MaxFlow = 0;
  int pathFlow;
  int u;

  while(isThereAnyAugmentingPath(rGraph, source, sink, parent))   
  {
    // Find the bottleneck value of the path
    pathFlow = INT_MAX;
    for(int v = sink; v!=source; v=parent[v])
    {
       u = parent[v];
       pathFlow = min(pathFlow, rGraph[u][v]);
    }

    //Update residual capacities of edges of the residual graph
    for(int v = sink; v != source; v = parent[v])
    {
       u = parent[v];
       rGraph[u][v] -= pathFlow;
       rGraph[v][u] += pathFlow; // backward edge (To allow undo op.)
    }

    MaxFlow += pathFlow;
  }  
 return MaxFlow;
}

int main()
{
    // Let us create a graph 
    // Stores the residual capacities of the edges
    int graph[V][V] = {{0, 16, 13, 0, 0, 0},
                       {0, 0, 10, 12, 0, 0},
                       {0, 4, 0, 0, 14, 0},
                       {0, 0, 9, 0, 0, 20},
                       {0, 0, 0, 7, 0, 4},
                       {0, 0, 0, 0, 0, 0}};

    cout << "The maximum possible flow is " << fordFulkerson(graph, 0, 5);

    return 0;
}