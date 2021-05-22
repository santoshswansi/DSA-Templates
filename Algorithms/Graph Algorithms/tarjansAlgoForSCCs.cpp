//Tarjan's algorithm for Strongly Connected Components
//T = O(V + E)


#include<iostream>
#include<list>
#include<stack>
#include<algorithm>

using namespace std;

int totSCCs = 0;

class Graph
{
    int V;
    list<int> *adj;

public:
    Graph(int v);
    void addEdge(int v, int w);
    void DFSUtil(int u, int disc[], int low[], stack<int> &stack, bool stackMember[]);
    void SCC();
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

//stack ----> To store all connected ancestors
// stackMember[] --> To quickly check whether a node is in stack or not
void Graph::DFSUtil(int u, int disc[], int low[], stack<int> &stack, bool stackMember[])
{
   static int time = 0;
   disc[u] = low[u] = ++time; //Initialise low and disc

   //push the node in stack
   stack.push(u);
   stackMember[u] = true;

   list<int>::iterator it;
   for(it = adj[u].begin(); it != adj[u].end(); ++it)
   {
       //Better utilisation of memory
       //Initialise disc with -1(can be used to check whether a node visited or not)
      if(disc[*it] == -1)
      {
        DFSUtil(*it, disc, low, stack, stackMember);
        low[u] = min(low[u], low[*it]);
      }  
      //Update low value if the child is back edge not a cross edge
      //That is child is already being in the stack
      else if (stackMember[*it] == true)
      {
        low[u] = min(low[u], disc[*it]);
      }
   }

   //Head node found , pop the stack and print it until the same node 
   // is found and also print the head node---> They will form one SCC
   int w = 0;
   if(disc[u] == low[u])
   {
       while(stack.top() != u)
       {
          w = (int) stack.top();
          cout<<w<<", ";
          stackMember[w] = false;
          stack.pop(); 
       }
       w = (int)stack.top();
       cout<<w<<", "<<endl;
       stackMember[w] = false;
       stack.pop();
       ++totSCCs;
   }
}

void Graph::SCC()
{
  int *disc = new int[V];
  int *low = new int[V];
  bool *stackMember = new bool[V];
  stack<int> stack;

  // Initialise disc[], low[] and stackMember[]
  for(int i = 0 ; i < V; ++i)
  {
      disc[i] = -1;
      low[i] = -1;
      stackMember[i] = false;
  } 

  for(int i = 0; i < V; ++i)
  {
    if(disc[i] == -1)
     DFSUtil(i, disc, low, stack, stackMember);
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
    g1.SCC();
    cout << "\nTotal SCCs in graph-1 is : " << totSCCs << endl;

    totSCCs = 0;
    cout << "\nStrongly Connected Components of graph-2 are : \n";
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.SCC();
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
    g3.SCC();
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
    g4.SCC();
    cout << "\nTotal SCCs in graph-4 is : " << totSCCs << endl;

    totSCCs = 0;
    cout << "\nStrongly Connected Components of graph-5 are : \n";
    Graph g5(5);
    g5.addEdge(0, 1);
    g5.addEdge(1, 2);
    g5.addEdge(2, 3);
    g5.addEdge(2, 4);
    g5.addEdge(3, 0);
    g5.addEdge(4, 2);
    g5.SCC();
    cout << "\nTotal SCCs in graph-5 is : " << totSCCs << endl;

    return 0;
}