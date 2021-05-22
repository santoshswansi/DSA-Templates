
//Check whether the given graph(non-connected also) is bi-partite or not
// IDEA : 2-colourable graph are bi-partitie graph

#include <iostream>
#include <string.h>
#include <queue>

using namespace std;
#define V 4

// BFS based function to check whether the graph is 2-colorable or not
bool isBipartiteUtil(int graph[V][V], int src, int color[V])
{
    //Assign color to source
    color[src] = 1;
    queue<int> q;
    q.push(src);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        //Self loop exist
        if (graph[u][u] == 1)
            return false;

        for (int v = 0; v < V; ++v)
        {
            //Edge exist AND not colored
            if (graph[u][v] != 0 && color[v] == -1)
            {
                color[v] = 1 - color[u];
                q.push(v);
            }
            //Edge exist  AND colored with same color as u
            else if (graph[u][v] != 0 && color[v] == color[u])
                return false;
        }
    }
    return true; //2-colorable = true
}

bool isBipartite(int graph[V][V])
{
  int color[V];
  memset(color, -1, sizeof(color));

  for(int i = 0; i<V; ++i)
  {
      if(color[i] == -1)
        if(isBipartiteUtil(graph, i, color) == false)
          return false;
  }
  return true;
}

int main()
{
    int graph[V][V] = {{0, 1, 0, 1},
                  {1, 0, 1, 0},
                  {0, 1, 0, 1},
                  {1, 0, 1, 0}};
    cout << "\nIs given connected graph bipartite : ";
    isBipartite(graph) ? cout << "Yes" : cout << "No";
    return 0;
}