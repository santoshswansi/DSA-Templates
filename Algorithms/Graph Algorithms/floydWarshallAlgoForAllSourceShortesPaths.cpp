#include<iostream>
#include<climits>
#include<iomanip>

using namespace std;

#define N 4//Number of vertices in the graph

//Funstion to print path of given vertex u from source v
void  printPath(int parent[][N], int v, int u)
{
  if(parent[v][u] == v) //if parent[v][u] is same as source
   return;
  printPath(parent, v, parent[v][u]);
  cout<<parent[v][u]<<" "; 
}

//Function to print min-cost path for every pair vertices
//And also path
void printSolution(int cost[N][N], int parent[N][N])
{
 //print the min-cost int matrix form
 for(int v = 0; v < N ; ++v)
 {
    for(int u = 0; u < N; ++u)
    {
      if(cost[v][u]==INT_MAX)
       cout<<"inf ";
      else
       cout<<cost[v][u]<<" ";   
    } 
    cout<<endl;
 }  
 
 cout<<"\n\n";

 for(int v = 0; v < N; ++v)
 {
   for(int u = 0; u < N; ++u)
   {
     //if cost is INT_MAX assign its parent as -1
     if (v != u && parent[v][u] != -1)
     {
       cout<<"\nPath("<<v<<","<<u<<") : "<<v<<" ";
       printPath(parent, v, u);
       cout<<u;
     }
   }  
 }
}

//adjMatrix : 
//Initially it will contain cost of adjacent directed edges
//Otherwise the edge cost is empty
void floydWarshall(int adjMatrix[][N])
{
  //cost[][] and parent[][] contains information about 
  //minimum cost and shortest route respectively
  int cost[N][N], parent[N][N];

  //initialise cost[][] and parent[][]
  for(int v = 0; v < N; ++v)
  {
    for(int u = 0; u < N; ++u)
    {
       //Initially cost would be same as the weight of the edge 
       cost[v][u] = adjMatrix[v][u]; 
       
       //v->u
       if(v==u) 
        parent[v][u] = 0;
       else if(cost[v][u] != INT_MAX)
        parent[v][u] = v;
       else //if cost is INT_MAX assign its parent as -1
        parent[v][u] = -1;       
    }  
  }

  //run floyd warshall algorithm
  for(int k = 0 ; k < N; ++k) //Intermediate vertex
  {
    for(int v = 0; v < N; ++v)
    {
       for(int u = 0; u < N; ++u)
       {
         //If vertex k is on the shortest path from v to u,
         //then update the value of cost[v][u], path[v][u]
         if(cost[v][k] != INT_MAX && cost[k][u] != INT_MAX 
            && cost[v][k] + cost[k][u] < cost[v][u])
         {
             cost[v][u] = cost[v][k] + cost[k][u];
             parent[v][u] = parent[k][u];
         }   
       } 

       //if diagonal element become negative, the graph contains 
       //a negative weight cycle
       if(cost[v][v] != 0)
       {
          cout<<"\nNegative Weight Cycle Found!";
          return; 
       }
    }  
  }
  //print the minimum cost path between every pair of vertices
  //And print the path also
  cout<<"\nAdjacency Matrix containing shortest distance : \n";
  printSolution(cost, parent);
}

int main()
{

    /*    4
    0<-------1
(-2) \    ^  |
       / \   | 3
(-1) /     > v
    3<-------2 
        2 
  */
    //adjacency matrix
    int adjMatrix[N][N] = {
        {0, INT_MAX, -2, INT_MAX},
        {4, 0, 3, INT_MAX},
        {INT_MAX, INT_MAX, 0, 2},
        {INT_MAX, -1, INT_MAX, 0}};

    //Run Floyd Warshall Algorithm
    floydWarshall(adjMatrix);    

    return 0;  
}