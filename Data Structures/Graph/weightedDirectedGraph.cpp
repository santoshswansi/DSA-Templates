#include <iostream>

using namespace std;

struct Node //Data structure to store adjacent list nodes
{
    int value;
    int cost;
    Node *next;
};

struct Edge //Data structure to store Edge
{
    int src;
    int dest;
    int weight;
};

class Graph
{
    //Function to allocate new node of adjacency list
    Node *getAdjListNode(int dest,int weight, Node *head)
    {
        Node *newNode = new Node;
        newNode->value = dest;
        newNode->cost=weight;
        newNode->next = head; //point new node to current node
        return newNode;
    }
    int noVertices; //number of nodes in the graph

public:
    //An array of pointers to node to represent adjacency list
    Node **head;
    Graph(Edge edges[], int noEdges, int noVertices)
    {
        //Allocate memory for pointer to node for storing
        //adjacent nodes to each vertices
        head = new Node *[noVertices]();
        this->noVertices = noVertices;

        //Initialise each pointers to null
        for (int i = 0; i < noVertices; ++i)
            head[i] = nullptr;

        //Add edges to the  directed graph
        for (int i = 0; i < noEdges; ++i)
        {
            int src = edges[i].src;
            int dest = edges[i].dest;
            int weight= edges[i].weight;

            //get the adjacent list node
            Node *newNode = getAdjListNode(dest, weight, head[src]);
            head[src] = newNode;

            //For UNDIRECTED GRAPH
            // since (x,y)==(y,x)
            // therefore me must store them
            /*
           newNode=getAdjListNode(src,head[dest]);
           head[dest]=newNode;
          */
        }
    }
    ~Graph()
    {
        //Free up the memory occupied by head[]
        for (int i = 0; i < noVertices; ++i)
            delete[] head[i];
        delete[] head;
    }
};

//To print all neighbouring vertices of given vertex
void printList(Node *ptr,int i)
{
    while (ptr != NULL)
    {
        cout<<"("<<i<<","<<ptr->value<<","<<ptr->cost<<")";
        ptr = ptr->next;
    }
    cout << endl;
}
int main()
{
    Edge edges[] = {{0, 1, 6}, {1, 2, 7}, {2, 0, 5}, 
                    {2, 1, 4}, {3, 2, 10}, {4, 5, 3}, {5, 4, 1}};
    int noVertices = 6;
    int noEdges = sizeof(edges) / sizeof(edges[0]);

    Graph graph(edges, noEdges, noVertices); //construct graph

    //print the adjacency list of  vertices
    for (int i = 0; i < noVertices; ++i)
    {
        //head contains adjacency list of each vertex
        printList(graph.head[i],i);
    }
    return 0;
}