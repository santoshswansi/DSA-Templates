//Naive method of implementing Union Find OR disjoint set data structures
//(Implemenation of detection of cycle in a non-directed graph)

#include <iostream>

using namespace std;

struct Edge
{
    int src, dest; //Edge(src,dest) OR Edge(dest,src)  are same
};

class Graph
{
public:
    int V, E;    //no of vertices and edges in the graph
    Edge *edges; //An array of edges
};

struct subset
{
  int parent;
  int rank;  
};

Graph* createGraph(int v, int e)
{
    Graph *graph = new Graph(); //an instance of Graph
    graph->V = v;
    graph->E = e;
    graph->edges = new Edge[(graph->E) * sizeof(Edge)];
    return graph;
}

int Find(subset subsets[] , int i)
{
    //Find root and make root as parent of i
    if (subsets[i].parent != i)
        subsets[i].parent = Find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(subset subsets[], int x, int y)
{
    int xRoot = Find(subsets, x);
    int yRoot = Find(subsets, y);

    //Attach smaller rank tree under higher rank tree
    if(subsets[xRoot].rank < subsets[yRoot].rank)
      subsets[xRoot].parent = yRoot;
    else if(subsets[xRoot].rank > subsets[yRoot].rank)  
      subsets[yRoot].parent = xRoot;
    else //make one of them as root and increase the rank by one
    {
      subsets[yRoot].parent = xRoot;
      (subsets[yRoot].rank)++;
    }
}

bool isCycle(Graph *graph)
{
    subset *subsets = new subset[sizeof(subset) * graph->V];

    //Inititalise parent and rank of the subsets
    for(int i = 0 ; i < graph->V ; ++i)
    {
      subsets[i].parent = i;
      subsets[i].rank = 0;  
    }
   
    //Iterate over each edge
    for (int i = 0; i < graph->E; ++i)
    {
        int srcSubset = Find(subsets, graph->edges[i].src);
        int destSubset = Find(subsets, graph->edges[i].dest);

        if (srcSubset == destSubset)
            return true;

        //if  they does not belong to same subset unify them
        Union(subsets, srcSubset, destSubset);
    }
    return false;
}

int main()
{
    int V = 3, E = 3;
    Graph *graph = createGraph(V, E);

    graph->edges[0] = {0, 1}; //{ src , dest }
    graph->edges[1] = {1, 2};
    graph->edges[2] = {2, 0};

    if (isCycle(graph))
        cout << "\nCycle Present!";
    else
        cout << "\nCycle not present";

    return 0;
}