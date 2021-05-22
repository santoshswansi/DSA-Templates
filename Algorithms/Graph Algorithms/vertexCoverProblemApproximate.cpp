//Approximate polynomial time vertex cover solution

#include<iostream>
#include<list>
#include<vector>

using namespace std;

class Graph
{
     int V; //Total number of vertices
     list<int> *adjList;
    public :
     Graph(int v);
     void addEdge(int u, int v);
     void printVertexCover();
};

Graph::Graph(int v)
{
    this->V = v;
    this->adjList = new list<int>[V];
}

void Graph::addEdge(int u, int v)
{
    adjList[u].push_back(v);
    adjList[v].push_back(u);  //For undirected graph
}

void Graph::printVertexCover()
{
    vector<bool> visited(V, false);
    
    list<int>::iterator it;
    for(int u = 0; u < V; ++u)
    {
        if(!visited[u])
        {
            for(it = adjList[u].begin(); it != adjList[u].end(); ++it)
            {
                int v = *it;
                if(!visited[v])
                {
                    //Include both vertices of the edge in vertex cover
                    visited[u] = true;
                    visited[v] = true;
                    break; //So that all edges incident on either of the 
                           //vertices 'u' OR 'v' will not be checked
                }
            }
        }
    }

    //Print vertex  cover
    cout<<"Vertex cover using approximate algorithm : ";
    for(int i = 0; i < V; ++i)
      if(visited[i])
       cout<<i<<" ";
}

int main()
{
    Graph graph(6);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    graph.addEdge(2, 5);

    graph.printVertexCover();
    
    return 0;
}