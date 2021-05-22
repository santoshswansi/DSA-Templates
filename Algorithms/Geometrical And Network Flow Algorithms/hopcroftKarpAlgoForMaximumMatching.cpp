//Given a bipartite graph find the maximum cardinality matching
// T = O(root(V)*E)
#include <iostream>
#include <list>
#include <queue>
#include <climits>
#include <string.h>

using namespace std;
#define NIL 0
#define INF INT_MAX

//Data structuree to represent bipartite graph
class biGraph
{
    int noOfLVertices, noOfRVertices;

    list<int> *adj; //adj[u] : Stores adjacent of left side vertex 'u'
                    // {1 to noOfLVertices}

    int *pairU, *pairV, *dist; // U and V are the sets

public:
    biGraph(int leftVertices, int rightVertices);
    void addEdge(int u, int v);
    bool bfs(); // Tells whether there is an augmenting path

    //Add augmenting if there exist starting with 'u'
    bool dfs(int u);
    int hopcroftKarp(); //Main method to return count of maximum matching
};

biGraph::biGraph(int leftVertices, int rightVertices)
{
    this->noOfLVertices = leftVertices;
    this->noOfRVertices = rightVertices;
    adj = new list<int>[noOfLVertices + 1];
}

void biGraph::addEdge(int u, int v)
{
    //NOTE : adj[u] --> list of adjacent vertices of u(set U)
    this->adj[u].push_back(v); // Add v to u's list
}

//Returns size of maximum matching
int biGraph::hopcroftKarp()
{
    //pairU[u] : Stores pair of 'u' on set  V (If matched vertex)
    //           Else NIL(0) {Matched to NIL vertex}
    pairU = new int[noOfLVertices + 1];

    //pairV[v] : Stores pair of 'v' on set  U(If matched vertex)
    //           Else NIL(0) {Matched to NIL vertex}
    pairV = new int[noOfRVertices + 1];

    // dist[u] = dist[u'] + 1 if u appears next to u' in augmenting path
    dist = new int[noOfLVertices + 1];

    //Initialise NIL value to pairU, pairV
    //All vertices connected to NIL vertex
    for (int u = 0; u <= noOfLVertices; u++)
        pairU[u] = NIL;
    for (int v = 0; v <= noOfRVertices; v++)
        pairV[v] = NIL;

    int result = 0;

    //bfs() either gives augmenting path of total edges = 1 OR 3
    //WHY?
    //Beacuse as soon as we reach a free vertex in set V
    //we return TRUE

    //Keep updating the result while there is an augmenting path
    //(Denotes maximum  matching is not yet reached)

    while (bfs())
    {
        //Find a free vertex
        for (int u = 1; u <= noOfLVertices; ++u)
            //If vertex in set U is free and there exist an augmenting
            //path which starts at u{ which is a free vertex}
            //Update the result by 1
            if (pairU[u] == NIL && dfs(u))
                 result = result + 1;
    }
    return result;
}

bool biGraph::bfs()
{
    queue<int> Q;

    //set first layer of vertices(set distance = 0)
    for (int u = 1; u <= noOfLVertices; ++u)
    {
        //If there is a free vertex , add it  to the queue
        //Update the dist[] value to 0
        if (pairU[u] == NIL)
        {
            dist[u] = 0;
            Q.push(u);
        }
        //Else set dist[] as INF so that it will be selected next
        else
            dist[u] = INF;
    }

    //Initialise dist[NIL] to INF
    //So that when it is reached again from vertices of set V,
    //It value gets updated to finite value and we have found an augmenting
    //path
    dist[NIL] = INF;

    //Q contain vertices of set U only
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();

        //If this node is not NIL & can provide a shorter path to NIL
        //CONDITION : To ensure vertex u of set U lead to vertex v
        //            int set V and the edge is not-matching
        if (dist[u] < dist[NIL])
        {
            list<int>::iterator it;
            for (it = adj[u].begin(); it != adj[u].end(); ++it)
            {
                int v = *it;

                //If we have not considered pair of v
                //That is : The  edge is matching edge
                //Update distance of  pairV[v] to dist[u] + 1
                //(It will be used in dfs() to find augmenting path
                // ALSO it will be not considered again)
                // push pairV[v] to Q(queue) so that it will be considered
                // again

                //Here pairV[v] is either NIL(0) or end-vertex of the
                //matching
                //If matching not exist from v :
                //dist[NIL] gets updated to finite value
                //(So that it can be considered next)
                //Thus augmenting path is found
                if (dist[pairV[v]] == INF)
                {
                    dist[pairV[v]] = dist[u] + 1;
                    Q.push(pairV[v]);
                }
            }
        }
    }
    return (dist[NIL] != INF);
}

//Returns true if there is an augmenting path starting with u
bool biGraph::dfs(int u)
{
    if (u != NIL)
    {
        list<int>::iterator it;
        for (it = adj[u].begin(); it != adj[u].end(); ++it)
        {
            int v = *it;

            //follow the dist[] developed by bfs()
            if (dist[pairV[v]] == dist[u] + 1)
            {
                //If dfs of pairV[v] also returns true
                //There exist an augmenting path starting from u
                if (dfs(pairV[v]) == true)
                {
                    pairU[u] = v;
                    pairV[v] = u;
                    return true;
                }
            }
        }
        //If there is no augmenting path beginning with u
        //update the dist[u] to INF so that it will not  be considered
        //next time
        dist[u] = INF;
        return false;
    }
    return true;
}

int main()
{
    biGraph g(4, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 1);
    g.addEdge(3, 2);
    g.addEdge(4, 2);
    g.addEdge(4, 4);

    cout << "Size of maximum matching is " << g.hopcroftKarp();

    return 0;
}