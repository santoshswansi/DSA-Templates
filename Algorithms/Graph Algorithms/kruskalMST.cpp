//KRUSKAL ALGO FOR MST USING UNION FIND
// T  = O(ELogE)(For sorting All edges) + O(ELogV){Union-Find}
#include<iostream>
#include<vector>

using namespace std;

struct Edge
{
    int src, dest, weight; //Edge(src,dest) OR Edge(dest,src)  are same
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

Graph *createGraph(int v, int e)
{
    Graph *graph = new Graph(); //an instance of Graph
    graph->V = v;
    graph->E = e;
    graph->edges = new Edge[(graph->E) * sizeof(Edge)];
    return graph;
}

int Find(subset subsets[], int i)
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
    if (subsets[xRoot].rank < subsets[yRoot].rank)
        subsets[xRoot].parent = yRoot;
    else if (subsets[xRoot].rank > subsets[yRoot].rank)
        subsets[yRoot].parent = xRoot;
    else //make one of them as root and increase the rank by one
    {
        subsets[yRoot].parent = xRoot;
        (subsets[yRoot].rank)++;
    }
}

//comparator function used in qSort
int compare(const void *a, const void *b)
{
  Edge *a1 = (Edge*)a;
  Edge *b1 = (Edge*)b;
  return a1->weight > b1->weight;
}

void kruskalMST(Graph *graph)
{
  int V = graph->V;
  //It will contain the edges of MST
  Edge *result = new Edge[sizeof(Edge) * V];

  int e = 0; //Index variable used for result
  int i = 0; //Index variable for sorted edges

  //STEP 1 :Sort the edges a/t their weight
  qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compare);

  subset *subsets = new subset[V * sizeof(subset)];

  //Initialise subsets
  for(int i =0;i< V;++i)
  {
    subsets[i].parent = i;
    subsets[i].rank = 0;  
  }

  //Number of edges to be included is  V-1
  while( e < V-1 && i < graph->E)
  {
    //STEP 2 : pick the least weight edge and include it in MST if it does 
    //not form cycle
    Edge next_edge = graph->edges[i++];

    //Get subsets of its source and destination
    int srcSubset = Find(subsets, next_edge.src);
    int destSubset = Find(subsets, next_edge.dest);

    //If they does not belong to same subset include it in MST
    //And Union them
    if(srcSubset != destSubset)
    {
      result[e++] = next_edge;
      Union(subsets, srcSubset, destSubset);  
    }
  }
  //Print the MST
  cout<<"\nMST of the graph is :\n";
  cout<<"\nEdge \t weight\n";
  for(int i = 0 ;i < e ;++i)
  {
    cout<<"\n"<<result[i].src<<"--"<<result[i].dest<<" : "<<result[i].weight;
  }
}

int main()
{  /*    
                10 
       0--------------------1
       | \_____________     |
     6 |        5      \    | 15
       |                \___|
       2--------------------3
                4

   */

   int V = 4 ,E = 5;
   Graph *graph = createGraph(V, E);
   vector<Edge> edges = {{0,1,10},{0,2,6},
                         {0,3,5},{1,3,15},{2,3,4}};
   for(int i = 0; i<E;++i)
   {
       graph->edges[i].src = edges[i].src;
       graph->edges[i].dest = edges[i].dest;
       graph->edges[i].weight = edges[i].weight;
   }

   kruskalMST(graph);
   return 0;  
}