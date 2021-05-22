//Kosaraju's algorithm to find Strongly Connected Components
//T = O(V + E)

#include<iostream>
#include<list>
#include<stack>
#include<string.h> //for memset

using namespace std;

int totSCCs = 0;

class Graph
{
    int V;
    list<int> *adj;
  public :
    Graph(int v);
    void addEdge(int v, int w);
    void DFSUtil(int u, bool visited[]);
    void fillOrder(int u, bool visited[], stack<int> &stack); 
    void printSCCs();
    Graph getTranspose();
};

Graph::Graph(int v)
{
    this->V = v;
    this->adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); //Directed graph
}

//Returns the transpose or reverse of the graph
Graph Graph::getTranspose()
{
  Graph g(this->V);
  for(int i = 0; i < V; ++i)
  {
     list<int>::iterator it;
     for(it = adj[i].begin(); it != adj[i].end(); ++it)
     {
         g.adj[*it].push_back(i);
     } 
  }
  return g;
}

//Function to fill stack with node with minimum finishing time on top
//Based on DFS
void Graph::fillOrder(int u, bool visited[], stack<int> &stack)
{
  //Mark the node visited
  visited[u] = true;

  //Iterate over it adjacent nodes
  list<int>::iterator it;
  for(it = adj[u].begin(); it != adj[u].end(); ++it)
  {
      if(!visited[*it])
        fillOrder(*it, visited, stack);
  }

  stack.push(u);
}

void Graph::DFSUtil(int u, bool visited[])
{
    //Mark the  node visited and print it
    visited[u] = true;
    cout<<u<<" ";

    list<int>::iterator it;
    for(it = adj[u].begin(); it != adj[u].end(); ++it)
    {
        if(!visited[*it])
          DFSUtil(*it, visited);
    }
}

void Graph::printSCCs()
{
   bool *visited = new bool[V];
   stack<int> stack;

   //Initialise visited[] with 'false' for 1st DFS call
   memset(visited, false, sizeof(bool)*V);

   //Fill the stack with node having lowest finishing time on top
   for(int i = 0; i < V; ++i)
   {
       if (!visited[i])
           fillOrder(i, visited, stack);
   }  

   //Initialise visited[] with 'false' for 2nd DFS call
   memset(visited, false, sizeof(bool) * V);

   //Reverse the graph
   Graph g = this->getTranspose();

   //Call DFS A/T least to highest finishing time of nodes
   while(!stack.empty())
   {
       int v = stack.top();
       stack.pop();

       //Print SSC of popped vertex
       if(!visited[v])
       {
          g.DFSUtil(v, visited);
          ++totSCCs; 
          cout<<endl;
       }
   } 
}

int main()
{
    /* 
       GRAPH-1

       3----->4
       ^
       |
       0<-----1
       |      ^ 
       V _____|
       2
    */

    cout << "\nStrongly Connected Components of graph-1 are : \n";
    Graph g1(5);
    g1.addEdge(1, 0);
    g1.addEdge(0, 2);
    g1.addEdge(2, 1);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    g1.printSCCs();
    cout << "\nTotal SCCs in graph-1 is : " << totSCCs << endl;

    totSCCs  = 0;
    cout << "\nStrongly Connected Components of graph-2 are : \n";
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.printSCCs();
    cout << "\nTotal SCCs in graph-2 is : " << totSCCs << endl;

    totSCCs = 0;
    cout << "\nStrongly Connected Components of graph-3 are : \n";
    Graph g3(7);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(2, 0);
    g3.addEdge(1, 3);
    g3.addEdge(1, 4);
    g3.addEdge(1, 6);
    g3.addEdge(3, 5);
    g3.addEdge(4, 5);
    g3.printSCCs();
    cout << "\nTotal SCCs int graph-3 is : " << totSCCs << endl;

    totSCCs = 0;
    cout << "\nStrongly Connected Components of graph-4 are : \n";
    Graph g4(11);
    g4.addEdge(0, 1);
    g4.addEdge(0, 3);
    g4.addEdge(1, 2);
    g4.addEdge(1, 4);
    g4.addEdge(2, 0);
    g4.addEdge(2, 6);
    g4.addEdge(3, 2);
    g4.addEdge(4, 5);
    g4.addEdge(4, 6);
    g4.addEdge(5, 6);
    g4.addEdge(5, 7);
    g4.addEdge(5, 8);
    g4.addEdge(5, 9);
    g4.addEdge(6, 4);
    g4.addEdge(7, 9);
    g4.addEdge(8, 9);
    g4.addEdge(9, 8);
    g4.printSCCs();
    cout << "\nTotal SCCs in graph-4 is : " << totSCCs << endl;

    totSCCs =  0;
    cout << "\nStrongly Connected Components of graph-5 are : \n";
    Graph g5(5);
    g5.addEdge(0, 1);
    g5.addEdge(1, 2);
    g5.addEdge(2, 3);
    g5.addEdge(2, 4);
    g5.addEdge(3, 0);
    g5.addEdge(4, 2);
    g5.printSCCs();
    cout << "\nTotal SCCs in graph-5 is : " << totSCCs << endl;

    return 0;
}