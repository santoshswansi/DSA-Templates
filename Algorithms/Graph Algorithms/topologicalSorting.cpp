//Implementation of topological sorting
#include<iostream>
#include<list>
#include<stack>
#include<string.h>

using namespace std;

class Graph
{ 
    int V; //number of vertices
    list<int> *adj; //adjacency list
  
  public :
     Graph(int v);
     void addEdge(int v, int w); // v : source , w : dest
     void topologicalSortUtil(int v, bool visited[], stack<int> &stack);
     void topologicalSort(); //To print top sort
};

Graph::Graph(int v)
{
  this->V = v;
  this->adj = new list<int>[V];  
}

void Graph::addEdge(int v, int w)
{
   adj[v].push_back(w); //Adding w to  v's list
}

void Graph::topologicalSortUtil(int v, bool visited[], stack<int> &stack)
{
   //Mark v as visited
   visited[v] = true;
   
   //Recur for all vertices adjacent to the  vertex
   list<int>::iterator it;
   for(it = adj[v].begin() ; it != adj[v].end(); ++it)
   {
      if(!visited[*it])
       topologicalSortUtil(*it, visited, stack); 
   } 

   stack.push(v);
}

void Graph::topologicalSort()
{
   bool *visited = new bool[this->V];
   stack<int> stack;
   
   //Initialise all elements of visited as false
   memset(visited, false, sizeof(int)*V);

   //Iterate through each of the vertices of the graph
   //If it's not visited call topologicalSortUtil()
   for(int i = 0; i < V ; ++i)
   {
      if(!visited[i])
       topologicalSortUtil(i, visited, stack); 
   } 

   //Print the stack from top to  bottom
   while(!stack.empty())
   {
     cout<<stack.top()<<" ";
     stack.pop();  
   }
} 


int main()
{
   /*
      5--------->0<---------4
      |                     |
      |                     |
      V                     V
      2-------->3---------->1 
   */
   int V = 6;
   Graph graph(V);

   graph.addEdge(2, 3);
   graph.addEdge(3, 1);
   graph.addEdge(4, 0);
   graph.addEdge(4, 1);
   graph.addEdge(5, 2);

   graph.topologicalSort();

   return 0; 
}
