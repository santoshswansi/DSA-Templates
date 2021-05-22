//Find all the biconnected components of the graph
//T = O(V + E)


#include<iostream>
#include<list>
#include<stack>
#include<algorithm>

using namespace std;

int totBiComps  = 0;

//Data structure to be used in the stack
struct Edge
{
  int src, dest;  
};

class Graph
{
    int V;  // Number of vertices
    list<int> *adj; //An array of adjacent vertices
    void DFS(int u, int disc[], int low[], int parent[], bool visited[], stack<Edge> &stack);

  public:

    Graph(int v);
    void addEdge(int v, int w); 
    void biconnectedComponent();
};

Graph::Graph(int v)
{
   this->V = v;
   this->adj = new list<int>[V]; 
}

void Graph::addEdge(int v, int w)
{
  adj[v].push_back(w); 
  adj[w].push_back(v);  //For undirected graph 
}

void Graph::DFS(int u, int disc[], int low[], int parent[], bool visited[], 
         stack<Edge> &stack)
{
  static int time = 0; //Declared once

  //Mark current node as visited
  visited[u] = true;

  //Initialise low and disc of u
  disc[u] = low[u] = ++time;

  int child = 0; //To counnt number of child of node 'u'

  //Iterate through all the adjacent vertices of 'u'
  list<int>::iterator it;
  for(it = adj[u].begin(); it != adj[u].end(); ++it)
  {
    if(!visited[*it])
    {
        child = child + 1;
        stack.push({u, *it}); //Push the edge
        parent[*it] = u;
        DFS(*it, disc, low, parent, visited, stack);

        //By now all nodes of u is visited
        //It backtraces the the same path
        low[u] = min(low[u], low[*it]);

        //Two Cases (To check presence of Articulation Point)
        //CASE-1(Root Node and Has at least 2 childs)
        //CASE-2( Not a root node and low[*it] >= disc[u] )
        //Pop and print from the stack until edge (u, *it) is being found
        if ((parent[*it] == -1 && child > 1) || (parent[*it] != -1 && low[*it] >= disc[u]))
        {
            while (!(stack.top().src == u && stack.top().dest == *it))
            {
                cout << stack.top().src << "--" << stack.top().dest<<", ";
                stack.pop();
            }
            cout<<stack.top().src<<"--"<<stack.top().dest<<endl;
            totBiComps++;
            stack.pop();
        }
    } 
    else if( *it != parent[u] && disc[*it] < low[u]) //Back Edge , not a Cross Edge
    {
      low[u] = min(low[u], disc[*it]);
      stack.push({u, *it});
    } 
 }
}    

void Graph::biconnectedComponent()
{
  bool *visited = new bool[V];
  int *disc = new int[V];
  int *low = new int[V];
  int *parent = new int[V];
  stack<Edge> stack;

  int j = 0;

  //Initialise visited[] and parent[]
  for(int i = 0; i < V ; ++i)
  {
     visited[i] = false;
     parent[i] =  -1; 
  }

  for(int i = 0; i < V; ++i)
  {
      if (!visited[i])
          DFS(i, disc, low, parent, visited, stack);

      //While stack is not empty, print last element and then pop
      while (!stack.empty())
      {
          j = 1;
          cout << stack.top().src << "--" << stack.top().dest <<", ";
          stack.pop();
      }
      if(j == 1)
      {
        cout<<endl;
        ++totBiComps;
      }
  } 

}

int main()
{
    /*       GRAPH - 1
                                         
      0-------------3------------2------------5 
                                  \___        |     
                                      \___    |
                                          \___|
      1---------------------------------------4 

    */
    int V = 6;
    Graph g1(V);
   
    g1.addEdge(0, 3);
    g1.addEdge(3, 2);
    g1.addEdge(2, 4);
    g1.addEdge(2, 5);
    g1.addEdge(5, 4);
    g1.addEdge(1, 4);

    cout<<"\nBiconnected Components of given graph is/are : \n";
    g1.biconnectedComponent();
    cout<<"\nTotal Biconnected Components are : "<<totSCCs<<endl;

    /*      GRAPH - 2
        4                 7
      /  \              /    \
     2----3            /      \
      \  /            /        \
       1-------------5----------8---------9
       |             |
       |             |
       0-------------6          10--------11

   */

    V = 12;
    totSCCs = 0;
    Graph g2(V);

    g2.addEdge(0, 1);
    g2.addEdge(0, 6);
    g2.addEdge(1, 5);
    g2.addEdge(6, 5);
    g2.addEdge(5, 7);
    g2.addEdge(7, 8);
    g2.addEdge(5, 8);
    g2.addEdge(8, 9);
    g2.addEdge(10, 11);
    g2.addEdge(1, 2);
    g2.addEdge(2, 4);
    g2.addEdge(2, 3);
    g2.addEdge(3, 4);
    g2.addEdge(1, 3);

    cout << "\nBiconnected Components of given graph is/are : \n";
    g2.biconnectedComponent();
    cout << "\nTotal Biconnected Components are : " << totSCCs << endl;
    return 0;
}