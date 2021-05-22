//KRUSKAL ALGO FOR MST USING UNION FIND
// T = O(V^2)
#include <iostream>
#include <vector>
#include<climits>

using namespace std;

#define V 5 //maximum number of vertices

//Function to find index of min key from key[](stores min weight edge in cut)
int minKey(int key[], bool mstSet[])
{
  int min = INT_MAX, minIndex; 
  for( int i = 0 ; i< V;++i)
  {
    if(mstSet[i] == false && key[i] < min)
    {
      min = key[i];
      minIndex = i;  
    }  
  } 
  return minIndex;
}

//graph[][] contains weight of edge 
//If there is no direct edge, weight = 0
//parent[] stores MST information
void printMST(int parent[], int graph[V][V])
{
    //starting from 1 so to get parent[1] not parent[0] which is -1
    cout << "\nEdge \tWeight\n";
    for (int i = 1; i < V; ++i)
    {
      cout<<"\n"<<parent[i]<<"--"<<i<<" : "<<graph[i][parent[i]];
    } 
}

void primMST(int graph[V][V])
{
  int parent[V]; //stores info about MST  
  int key[V]; // key values of vertices from where we need min key value
  bool mstSet[V]; //whether a vertex is included in MST or not

  //Initialise key[] values as INFINITE
  for(int i = 0 ; i<V;++i)
   key[i] = INT_MAX, mstSet[i] = false;

  key[0] = 0; //so as to pick it first
  parent[0] = -1;  //First node is always root of MST

  //We want to include V-1 edges
  for( int count = 0; count < V-1; ++count)
  {
    //Find the minkey value in key[]
    int u = minKey(key, mstSet);
    mstSet[u] = true;

    //Update key value and parent index of the adjacent vertices of 
    // 'u' [Consider only those vertices which are not yet included
    // in MST ] {Loop through all possible vertices of the graph}
    for(int v = 0; v<V; ++v)
    {
       //First check is taking care of the adjacent vertex of 'u' 
      //Third check  is showing key at v i.e key[v] = INFINITE  
      if(graph[u][v] != 0 && mstSet[v] == false && graph[u][v] < key[v] ) 
       parent[v] = u, key[v] = graph[u][v];
    }
  }
  printMST(parent, graph); 
}

int main()
{ /*    
                10                12
       0--------------------1--------------4
       | \_____________     |         ____/
     6 |        5      \    | 15  ___/ 3
       |                \___|____/
       2--------------------3
                4

   */
    
    int graph[V][V] = {
                       {0,10,6,5,0},
                       {10,0,0,15,12},
                       {6,0,0,4,0},
                       {5,15,4,0,3},
                       {0,12,0,3,0}
                      } ;

    primMST(graph);                  
  
    return 0;
}