//DJIKSTRA ALGORITHM : Given a source in a graph
//find the minimum cost path to all other vertices

/*DRAWBACK : It may not give incorrect min-cost paths if there 
         are negative cost edges */

#include<iostream>
#include<vector>
#include<queue>
#include<climits>

using namespace std;

//To store graph edge
struct Edge
{
   int src,dest,weight;
};

//To store heap nodes
struct Node
{
   int vertex, weight;
};


class Graph
{
   public:
    //Vector of vectors of Edge to represent adjacency list 
    vector<vector<Edge>> adjList;    

    //Graph constructor
    Graph(vector<Edge> const &edges,int noNodes)
    {
      adjList.resize(noNodes);  
      //add edges to the  undirected graph
      for(auto const &edge:edges)
      {
        adjList[edge.src].push_back(edge); 
      }
    }
};

//Comparison object to be used to order the heap
struct compare
{
  bool operator()(const Node &LHS, const Node &RHS)
  {
    return LHS.weight > RHS.weight;  
  }
};

void printRoute(vector<int> const &prev, int i)
{
   if(i<0)
    return;
   printRoute(prev, prev[i]);
   cout<< i <<" "; 
}

void shortestPath(Graph const &graph, int source, int noNodes)
{
  //create min_heap and push source node having distance 0
  priority_queue<Node, vector<Node>,compare> min_heap;
  min_heap.push({source,0});
  
  //set distance from source to all other vertices a infinity initially
  vector<int> distance(noNodes, INT_MAX);
  distance[source]=0;//distance of source from source is zero

  //vector to trace vertices whose min cost is already found! 
  vector<bool> done(noNodes,false);
  done[source]=true;

  //stores predecessor of a vertex(to print path)
  vector<int> prev(noNodes, -1);

  Node node;
  while(!min_heap.empty())
  {
     node=min_heap.top();
     min_heap.pop();

     int u=node.vertex;//get vertex number

     for(Edge i : graph.adjList[u])
     {
       int v = i.dest;
       int  weight = i.weight;

       //Relaxation step
       if(!done[v] && distance[u] != INT_MAX && (weight+distance[u])<distance[v])
       {
         distance[v] = weight + distance[u];
         prev[v] = u;
         //so that its neighours can also be explored
         min_heap.push({v, distance[v]});
       }
       //mark vertex u as done as it will not be visited again
       done[u] = true;
     }
  }

  //Print the min-cost-path of source to all other vertices
  for(int i=0; i<noNodes; ++i)
  {
    if(i!=source && distance[i]!=INT_MAX)
    {
      cout<<"\nPath ("<<source<<","<<i<<") : Minimum Cost = "<<distance[i]
          <<" And Route : ";
          printRoute(prev, i);
    }
  }
}

int main()
{
 vector<Edge> edges={{0,1,10},{0,4,3},{1,2,2},
                     {1,4,4},{2,3,9},{3,2,7},
                     {4,1,1},{4,2,8},{4,3,2}};

 int noNodes=5;//Number of nodes in the graph

 Graph graph(edges, noNodes);

 int source = 0;
 shortestPath(graph, source, noNodes);                    
 return 0;   
}