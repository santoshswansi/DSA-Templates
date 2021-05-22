// Given  a flow network with  source(s) and sink nodes(t)
// Find the minimum cut {cut-set with minimum sum of capacities}
// which separates s(source) from sink(t)

#include <iostream>
#include <string.h>
#include <queue>
#include <climits>
#include <algorithm>

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

        for (int v = 0; v < V; ++v)
        {
            if (visited[v] == false && rGraph[u][v] != 0)
            {
                q.push(v);
                visited[v] = true;
                parent[v] = u;
            }
        }
    }

    return (visited[sink] == true); //If we visited sink path is present
}

//DFS based function to find all vertices which are reachable from 
//source (You can also use BFS)
void dfs(int rGraph[V][V], int src, bool visited[V])
{
  visited[src] = true;
  for(int i = 0; i < V; ++i)
      //Edge exist and not visited
      if (rGraph[src][i] != 0 && visited[i] == false)
          dfs(rGraph, i, visited);
}

void minSTCut(int graph[V][V], int source, int sink)
{
    //Make the residual graph
    int rGraph[V][V];

    //Initialise residual graph (Can you work on the original graph)
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            rGraph[i][j] = graph[i][j];

    int parent[V]; // To store path

    int MaxFlow = 0;
    int pathFlow;
    int u;

    while (isThereAnyAugmentingPath(rGraph, source, sink, parent))
    {
        // Find the bottleneck value of the path
        pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v])
        {
            u = parent[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }

        //Update residual capacities of edges of the residual graph
        for (int v = sink; v != source; v = parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow; // backward edge (To allow undo op.)
        }

        MaxFlow += pathFlow;
    }

    //flow is maximum now
    //Find the  vertices reachable from source
    bool visited[V];
    memset(visited, false, sizeof(visited));
    dfs(rGraph, source, visited);

    //Print all edges which are from reachable vertex to un-reachable
    //vertices in the original graph
    for(int i = 0; i<V; ++i)
       for(int j = 0; j<V; ++j)
           if(visited[i] && !visited[j] && graph[i][j])
              cout<<"Edge : "<<i<<"-"<<j<<" capacity : "<<graph[i][j]<<endl;
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

    cout<<"Edges of Minimum ST-Cut are "<<endl; 
    minSTCut(graph, 0, 5);

    return 0;
}