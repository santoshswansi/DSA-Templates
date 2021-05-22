//Find the maximum S-T flow in a flow network
//Dinic's algorithm to find maximum flow
// T = O(E * V^2)

#include<iostream>
#include<vector>
#include<climits>
#include<string.h>
#include<queue>
#include<algorithm>

using namespace std;

//To represent edge in a flow network
struct  Edge
{
  int v;    // vertex v of a directed edge u-v
  int flow; //current flow in the edge
  int C;    //capacity of the edge

  unsigned int rev; //To store reverse edge in adjacency list
                    //so that we can quickly access it
};

class Graph
{
    int V; //number of vertices in the graph
    vector<int> level; //To store level of the graph
    vector<Edge> *adj; //To store adjacent edges for each vertex

    public:
      Graph(int v)
      {
          this->V = v;
          level.resize(V);
          adj = new vector<Edge>[V];
      }

      void addEdge(int u, int v, int C)
      {
          Edge a{v, 0, C, adj[v].size()}; //Forward Edge
          Edge b{u, 0, 0, adj[u].size()}; //Backward Edge

          adj[u].push_back(a);
          adj[v].push_back(b);
      }

      bool bfs(int s, int t);
      int sendFlow(int s, int t, int flow, int *start);
      int dinicMaxFlow(int s, int t);
};

//Returns true if there is a S-T path
//Also fills level[] array
bool Graph::bfs(int s, int t)
{
   //All nodes are not visited
   for(int i = 0; i < V; ++i)
   {
       level[i] = -1; 
   }

   level[s] = 0;

   //Create a queue and enqueue source node
   queue<int> Q;
   Q.push(s);

   vector<Edge>::iterator it;
   while(!Q.empty())
   {
      int u = Q.front();
      Q.pop();

      for(it = adj[u].begin(); it != adj[u].end(); ++it)
      {
        Edge &e = *it;

        if(level[e.v] < 0 && e.C > e.flow)
        {
           level[e.v] = level[u] + 1;
           Q.push(e.v);
        } 
      }
   } 
  return level[t] < 0 ? false : true;
}

//A DFS based function to send flow from 'S' to 'T' when there exist
//a path from 'S' to 'T'
//Called multiple times after  a single bfs (Calculated level graph)
//start[i] : stores the number of visited vertices from vertex 'i'
// flow : Flow to be sent 
//        Initially it is INT_MAX as we go from source towards the 
//        sink its value gets updated and finally stores bottle-neck
//        value of the found S-T path 
int Graph::sendFlow(int u, int t, int flow, int *start)
{
  if(u == t)
    return flow;

  //Traverse all the adjacent edges one-by-one
  //For a single bfs() multiple dfs() are called
  //It will avoid visiting the edges which is  already visited
  for( ; start[u] < adj[u].size(); ++start[u])
  {
      //pick the reference to edge from adjacency list of u
      //so that it characteristics can be modified
      Edge &e = adj[u][start[u]];

      //If it a valid edge to pick
      // CONDITION : { e.flow < e.C } Will be true for backward edge
      //             if it had been part of previous path . 
      //             This means e.C = 0   e.flow = -ve
      // It can be part of s-t path only level[e.v] = level[e.u] + 1            
      if(level[e.v] == level[u] + 1 && e.flow < e.C)
      {
         
          //send flow to next edge until we hit sink node
          int bottleneck_value = sendFlow(e.v, t, min(flow, e.C-e.flow), start);

          // flow > 0
          if(bottleneck_value > 0)
          {
              //add flow to current edge
              e.flow += bottleneck_value;

              //subtract flow from reverse edge of current edge
              adj[e.v][e.rev].flow -= bottleneck_value;
              return bottleneck_value;
          }
      }
  } 
  return 0; // 0 flow is possible if we reach here  
}

int Graph::dinicMaxFlow(int s, int t)
{
   // s== t
   if(s == t)
     return -1;

   int total = 0;

   //start[i] = stores number of vertices visited from 'i'
   int *start = new int[V + 1];

   //Augment the flow while there is path from source to sink
   while(bfs(s, t))
   {
      memset(start, 0, sizeof(int) * (V+1));

      //While blocking flow is not reached update the result
      //BLOCKING FLOW : flow = 0
      while(int flow = sendFlow(s, t, INT_MAX, start))
          total += flow;   
   }  
   return total;  
}

int main()
{
    //Example - 1
    Graph graph1(6);
    graph1.addEdge(0, 1, 10);
    graph1.addEdge(0, 2, 10);
    graph1.addEdge(1, 2, 2);
    graph1.addEdge(1, 3, 4);
    graph1.addEdge(1, 4, 8);
    graph1.addEdge(2, 4, 9);
    graph1.addEdge(3, 5, 10);
    graph1.addEdge(4, 3, 6);
    graph1.addEdge(4, 5, 10);
    cout<<"Max Flow = "<<graph1.dinicMaxFlow(0, 5)<<endl; //ANS : 19

    //Example - 2 
    Graph graph2(6);

    graph2.addEdge(0, 1, 16);
    graph2.addEdge(0, 2, 13);
    graph2.addEdge(1, 2, 10);
    graph2.addEdge(1, 3, 12);
    graph2.addEdge(2, 1, 4);
    graph2.addEdge(2, 4, 14);
    graph2.addEdge(3, 2, 9);
    graph2.addEdge(3, 5, 20);
    graph2.addEdge(4, 3, 7);
    graph2.addEdge(4, 5, 4);
    cout << "Max Flow = " << graph2.dinicMaxFlow(0, 5) << endl; //ANS : 23
    return 0;
}