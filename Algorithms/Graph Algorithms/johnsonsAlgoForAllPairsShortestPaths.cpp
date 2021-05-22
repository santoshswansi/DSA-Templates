/*
Johnson's algorithm to find aall pairs shortest paths 
We will transform the graph to make all edges positive
It will give us the positive cost 
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

//To store graph edge
struct Edge
{
    int src, dest, weight;
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
    Graph(vector<Edge> const &edges, int noNodes)
    {
        adjList.resize(noNodes);
        //add edges to the  undirected graph
        for (auto const &edge : edges)
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
    if (i < 0)
        return;
    printRoute(prev, prev[i]);
    cout << i << " ";
}

void shortestPath(Graph const &graph, int source, int noNodes)
{
    //create min_heap and push source node having distance 0
    priority_queue<Node, vector<Node>, compare> min_heap;
    min_heap.push({source, 0});

    //set distance from source to all other vertices a infinity initially
    vector<int> distance(noNodes, INT_MAX);
    distance[source] = 0; //distance of source from source is zero

    //vector to trace vertices whose min cost is already found!
    vector<bool> done(noNodes, false);
    done[source] = true;

    //stores predecessor of a vertex(to print path)
    vector<int> prev(noNodes, -1);

    Node node;
    while (!min_heap.empty())
    {
        node = min_heap.top();
        min_heap.pop();

        int u = node.vertex; //get vertex number

        for (Edge i : graph.adjList[u])
        {
            int v = i.dest;
            int weight = i.weight;
             
            //Relaxation step
            if (!done[v] && distance[u]!=INT_MAX && (weight + distance[u]) < distance[v])
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
    for (int i = 0; i < noNodes; ++i)
    {
        if (i != source && distance[i] != INT_MAX)
        {

            cout << "\nPath (" << source << "," << i << ") : Minimum Cost = " << distance[i]
                 << " And Route : ";
            printRoute(prev, i);
        }
        else if (i == source)
            cout << "\nPath (" << source << "," << i << ") : Minimum Cost = 0";
        else if(distance[i] == INT_MAX)
            cout << "\nPath (" << source << "," << i << ") : Minimum Cost = inf";
    }
}

vector<int> bellmanFord(vector<Edge> const &edges, int source, int noNodes)
{
    int noEdges = edges.size();

    //set distance from source to all other vertices a infinity initially
    vector<int> distance(noNodes, INT_MAX);
    distance[source] = 0; //distance of source from source is zero

    //stores predecessor of a vertex(to print path)
    vector<int> prev(noNodes, -1);

    int u, v, w, temp = noNodes;

    //Relaxation step(run noNodes-1 times)
    while (--temp)
    {
        for (int i = noEdges-1; i >= 0; --i)
        {
            u = edges[i].src;
            v = edges[i].dest;
            w = edges[i].weight;

            if (distance[u] != INT_MAX && (distance[u] + w) < distance[v])
            {
                distance[v] = distance[u] + w;
                prev[v] = u;
            }
        }
    }

    //NEGATIVE-WEIGHT CYCLE DETECTION PROCEDURE
    for (int i = 0; i < noEdges; ++i)
    {
        u = edges[i].src;
        v = edges[i].dest;
        w = edges[i].weight;
        
        if (distance[u] != INT_MAX && (distance[u] + w) < distance[v])
        {
            cout << "\nNegative-weight cycle present!";
            exit(0); //exit  from the program
        }
    }
   return distance; 
}

void johnsonUtil(Graph &graph, vector<Edge>   &edges, int noNodes)
{
  //Since graph contains noNodes 
  //It must contain nodes from 0 to (noNodes - 1)  
  int newNode = noNodes;
  vector<Edge> tempEdges = edges;

  for(int i =0;i<noNodes;++i)
   tempEdges.push_back({newNode, i, 0}); //vertex i with weight 0

  //call Bellman Ford algorithm to get h[noNodes]
  vector<int> h = bellmanFord(tempEdges , newNode, noNodes + 1);

  //Modify the graph to make all edges positive
  int noEdges =edges.size();
  for(int i =0 ; i<noEdges ;++i)
    edges[i].weight = (edges[i].weight + h[edges[i].src] - h[edges[i].dest]);

  //change the graph with +ve weights only to know the min-cost paths
  graph = Graph(edges, noNodes); 

  //call djikstra's algo for all vertices
  for( int i = 0; i < noNodes ; ++i)
    shortestPath(graph, i, noNodes);

}

int main()
{
    /*            4->3
              0<-------1
        0<-(-2) \   ^  |
                 / \   | 3->4
         0<-(-1) /   > v
              3<-------2 
                  2 -> 0
   */
    vector<Edge> edges = {{0,2,-2},{1,0,4},
                         {1,2,3},{2,3,2},
                         {3,1,-1}};
    int noNodes = 4;                     
    Graph graph(edges, noNodes);
    johnsonUtil(graph, edges, noNodes);
    return 0;
}