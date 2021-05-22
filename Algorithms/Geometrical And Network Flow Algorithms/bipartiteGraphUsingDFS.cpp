
//Check whether the given graph(non-connected also) is bi-partite or not
// IDEA : 2-colourable graph are bi-partitie graph

#include<iostream>
#include<string.h>

using namespace std;
#define V 7

//DFS based function whether the graph is bipartite or not
// col--> color of node 'pos'
bool isBipartiteUtil(int graph[V][V], int color[], int pos, int col)
{
   //Check  if the given is colored  with color
   //other than given color
   if(color[pos] != -1 && color[pos] != col)
    return false;

  //color the current node
  color[pos] = col;
  bool ans = true;
  for(int i = 0; i<V; ++i)
  {
      if(graph[pos][i] != 0) // edge exist
      {
          //If not colored recur for next with alternate color
          // if ans & isBipartite(graph, color, i, 1-col) is false
          // --> current node and next node are colored with same color
          if (color[i] == -1)
              ans &= isBipartiteUtil(graph, color, i, 1 - col);

          //If colored and same as current color return false
          if(color[i] != -1 && color[i] == color[pos])
           return false;    
      }
      if(!ans)
       return false;
  } 
  return true;  
}

bool isBipartite(int graph[V][V])
{
    int color[V];
    memset(color, -1, sizeof(color));

    for(int i = 0; i < V; ++i)
    {
        if(color[i] == -1)
          if(isBipartiteUtil(graph, color, i, 1)== false)
            return false;
    }
    return true;
}

int main()
{
    /* 
      3_________________       ______________ 
      |                 |      |            |
      0--------1--------2      4-----5------6  

    */

    int graph[V][V] = {
                       {0, 1, 0, 1, 0, 0, 0},
                       {1, 0, 1, 0, 0, 0, 0},
                       {0, 1, 0, 1, 0, 0, 0},
                       {1, 0, 1, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 1, 1},
                       {0, 0, 0, 0, 1, 0, 1},
                       {0, 0, 0, 0, 1, 1, 0},
                      };
    cout << "\nIs given connected graph bipartite : ";
    isBipartite(graph) ? cout << "Yes" : cout << "No";
    return 0;
}