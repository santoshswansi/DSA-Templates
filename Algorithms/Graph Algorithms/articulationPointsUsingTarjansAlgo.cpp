//Using TARJAN'S ALGORITHM find all articulation points of the graph
//T = O(V + E)

#include<iostream>
#include<list>
#include<algorithm>

using namespace std;

/*
  visited[] = keeps track of the element which are not visited
  
  disc[] = stores the  discovery time of vertices in DFS tree
           [  A vertex which is visited first in DFS traversal 
            will have  lesser disc[] value than that of later  ]
  
  low[v] = stores the vertex with minimum discovery time from where
           we can reach node 'v'

  parent[v] = stores the parent of the vertex 'v' 

  ap[] = 1) TRUE :  given vertex is articulation point else FALSE
*/

class Graph
{
    int V;
    list<int> *adj;
  
  public:
    Graph(int v);
    void addEdge(int v, int w); // v : source w : destination
    void APUtil(int u, bool visited[], int disc[], int low[], int parent[],
                bool ap[]);
    void AP(); 
};

Graph::Graph(int v)
{
    this->V = v;
    this->adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    //Add vertices in undirected graph
    adj[v].push_back(w); //Adding w to  v's list
    adj[w].push_back(v); //Addding v to w's list
}

void Graph::APUtil( int u, bool visited[], int disc[], int low[],
                    int parent[], bool ap[])
{
  static int time =0; //will be declared once
  int children = 0; //to count total childrens

  //mark the current node visited
  visited[u] = true;

  //Initialise discovery time and low value
  disc[u] = low[u] = ++time;

  //Iterate through adjacent nodes of v
  list<int>::iterator it;
  for(it = adj[u].begin(); it != adj[u].end(); ++it)
  {
    int v = *it;
    
    //If v is not visited 
    if(!visited[v])
    {
      children++; // Increase the children count
      parent[v] = u;
      APUtil(v, visited, disc, low, parent, ap);  

      //Update the low value of u to min of low[u] and low[v]
      low[u] = min(low[u], low[v]);

      // u is Articulation point if  it satisfy one of the following :-
      
      //1.) u is root and has at least two child 
      if(parent[u] == -1 && children > 1)
       ap[u] = true;

      //2.) u is not root and low[v] >= disc[u]  
      //OR { low value of dest } is more than { discovery time of source }    }
      //MEANING : There is no path from subtree rooted 'v' to 'u' OR
      //          ancestor of 'u'

      if(parent[u] != -1 && low[v] >= disc[u])
       ap[u] = true;
    }
    //Update low value of 'u' for parent function calls
    else if(v != parent[u]) 
     low[u]  = min(low[u], disc[v]);
  }
}  

void Graph::AP()
{
   bool *visited = new bool[V];
   int *disc = new int[V];
   int *low = new int[V];
   int *parent = new int[V];
   bool *ap = new bool[V]; 

   //Initialise visited[], parent[] and ap[]
   for(int i = 0; i < V; ++i)
   {
     parent[i] = -1;
     visited[i] = false;
     ap[i] = false;  
   } 

   for(int i = 0; i < V; ++i)
   {
       if(!visited[i])
        APUtil(i, visited, disc, low, parent, ap);
   }

   //Print APs
   for(int i = 0; i < V; ++i)
   {
       if (ap[i])
           cout << i << " ";
   } 
}

int main()
{
   /*    GRAPH1           GRAPH2              GRPAPH3
 
    1-----0------3    0---1---2----3    0-----1-----3-----5 
    |____/       |                      |____/|\__________|
    2            4                      2     6           4
    
   */

   //GRAPH1  {Add undirected edge}
   Graph graph1(5);
   graph1.addEdge(0, 1);
   graph1.addEdge(0, 3);
   graph1.addEdge(1, 2);
   graph1.addEdge(0, 2);
   graph1.addEdge(3, 4);
   cout<<"\nArticulation Points of graph1 : ";
   graph1.AP();

   //GRAPH2  {Add undirected edge}
   Graph graph2(4);
   graph2.addEdge(0, 1);
   graph2.addEdge(1, 2);
   graph2.addEdge(2, 3);
   cout << "\nArticulation Points of graph2 : ";
   graph2.AP();

   //GRAPH3  {Add undirected edge}
   Graph graph3(7);
   graph3.addEdge(0, 1);
   graph3.addEdge(1, 3);
   graph3.addEdge(3, 5);
   graph3.addEdge(5, 4);
   graph3.addEdge(0, 2);
   graph3.addEdge(2, 1);
   graph3.addEdge(4, 1);
   graph3.addEdge(6, 1);
   cout << "\nArticulation Points of graph3 : ";
   graph3.AP();

   return 0; 
}