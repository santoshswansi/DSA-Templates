#include<iostream>

using namespace std;

struct Node//Data structure to store adjacent list nodes
{
  int value;
  Node *next; 
};

struct Edge //Data structure to store Edge
{
  int src;
  int dest;  
};

class Graph
{
    //Function to allocate new node of adjacency list
    Node* getAdjListNode(int dest,Node *head)
    {
     Node *newNode=new Node;
     newNode->value=dest;
     newNode->next=head; //point new node to current node
     return newNode;
    }
    int noVertices;//number of nodes in the graph

  public :
    //An array of pointers to node to represent adjacency list
    Node **head;
    Graph(Edge edges[],int noEdges,int noVertices)
    {
        //Allocate memory for pointer to node for storing 
        //adjacent nodes to each vertices
        head = new Node *[noVertices]();
        this->noVertices = noVertices;

        //Initialise each pointers to null
        for (int i = 0; i < noVertices; ++i)
         head[i]=nullptr;

        //Add edges to the  directed graph
        for(int i=0;i<noEdges;++i)
        {
          int src=edges[i].src;
          int dest=edges[i].dest;

          //get the adjacent list node 
          Node *newNode=getAdjListNode(dest,head[src]);
          head[src]=newNode;

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
     for(int i=0;i<noVertices;++i)
         delete[] head[i];
     delete[] head;
  }
};

//To print all neighbouring vertices of given vertex
void printList(Node *ptr)
{
  while(ptr!=NULL)
  {
    cout<<"->"<<ptr->value<<" ";
    ptr=ptr->next;
  }  
  cout<<endl;
}
int main()
{
  Edge edges[]={{0,1},{1,2},{2,0},{2,1},{3,2},{4,5},{5,4}};
  int noVertices=6;
  int noEdges=sizeof(edges)/sizeof(edges[0]); 

  Graph graph(edges,noEdges,noVertices); //construct graph

  //print the adjacency list of  vertices
  for(int i=0;i<noVertices;++i)
  {
    cout<<i<<"--";
    //head contains adjacency list of each vertex
    printList(graph.head[i]); 
  }
  return 0;  
}