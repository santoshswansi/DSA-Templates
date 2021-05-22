//Naive method of implementing Union Find OR disjoint set data structures
//(Implemenation of detection of cycle in a non-directed graph)

#include<iostream>
#include<string.h> //For memset(array, value, memory_size);

using namespace std;

struct Edge
{
   int src, dest; //Edge(src,dest) OR Edge(dest,src)  are same
};

class Graph
{
   public :
    int V,E; //no of vertices and edges in the graph
    Edge *edges;//An array of edges
};

Graph* createGraph(int v, int e)
{ 
   Graph *graph = new Graph(); //an instance of Graph
   graph->V = v;
   graph->E = e;
   graph->edges = new Edge[(graph->E) * sizeof(Edge)];
   return graph;
}

int Find(int parent[], int i)
{
   if(parent[i] == -1)
    return i;
   return Find(parent,  parent[i]);  
}

void Union(int parent[], int x, int y)
{
   int xRoot = Find(parent, x);
   int yRoot = Find(parent, y); 

   if(xRoot != yRoot)
    parent[xRoot] = yRoot; //make parent of xRoot as yRoot
}

bool isCycle(Graph *graph)
{
 int *parent = new int[sizeof(int) * graph->V];
 
 //initialise parent with -1
 memset(parent , -1, sizeof(int) * graph->V);

 //Iterate over each edge
 for(int i =0; i < graph->E ; ++i)
 {
   int srcSubset = Find(parent, graph->edges[i].src);
   int destSubset = Find(parent, graph->edges[i].dest);

  if(srcSubset == destSubset)
   return true;

  //if  they does not belong to same subset unify them
  Union(parent, srcSubset, destSubset);  
 }
 return false;
}

int main()
{
  int V=3 , E = 3;  
  Graph *graph = createGraph(V, E);
   
  graph->edges[0] = {0,1};   //{ src , dest }
  graph->edges[1] = {1,2};
  graph->edges[2] = {2,0};
   
  if(isCycle(graph))
   cout<<"\nCycle Present!";
  else
   cout<<"\nCycle not present";
    
  return 0;  
}