/* Query on the tree of the type :-
    1.) change(e, val) : change  edge number e's weight to 'val'
    2.) maxEdge(u, v) : Max edge between nodes 'u' and 'v'
   
    Using HEAVY LIGHT DECOMPOSITION
*/     

#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>

using namespace std;

#define N 1000  //Assuming maximum number of nodes to be 1000

int tree[N][N]; // To store edge number between node 'u' and 'v'

struct TreeNode
{
    int parent; // parent of the node
    int size;   // sub-tree size rooted at this node
    int posInSegTreeBase; //position of this node in the base of segTree
    int level;  // level of node in the tree
    int chain;  // Chain number to which it belongs 
}node[N];

//Edge of the tree
struct Edge
{
    int weight; // weight of edge
    int deeperNode; // Stores the deeper node
}edge[N];   // One imaginary edge to root node is also used 

//To represent segment tree
struct SegmentTree
{
  int baseArray[N], tree[2*N];
}s;

//To add edge to to the tree[][]
void addEdge(int edgeID, int u, int v, int weight)
{
    tree[u-1][v-1] = edgeID-1;
    tree[v-1][u-1] = edgeID-1;
    edge[edgeID-1].weight = weight;
}

//DFS of the tree to store parent, sub-tree size, level 
//Also store deeper node of the edge
void dfs(int curr, int prev, int lev, int n)
{
    node[curr].parent = prev;
    node[curr].level = lev;
    node[curr].size = 1;

    //Visit every child of current node
    for(int i = 0; i < n; ++i)
    {
       if(i != curr && i != node[curr].parent && tree[curr][i] != -1)
       {
           //Set deeper end of the edge as this child
           edge[tree[curr][i]].deeperNode = i;

           //Do DFS on subtree
           dfs(i, curr, lev+1, n);

           //Update sub-tree sizes
           node[curr].size += node[i].size;
       }
    }
}

//A recursive function which decomposes the tree into different chains
void HLD(int currNode, int edgeID, int &edgeCounted, int &currChain, int n, vector<int> &chainHeads)
{
   //If head of current chain is not set
   if(chainHeads[currChain] == -1)
      chainHeads[currChain] = currNode;

   //set chainID to which the node belongs
   node[currNode].chain = currChain;

   //Set the position of node in the segment tree
   node[currNode].posInSegTreeBase = edgeCounted;

   //Update base array of the segment tree
   s.baseArray[edgeCounted++] = edge[edgeID].weight;

   //Find the special child
   int spclChild = -1, spclEdgeID;
   for(int i = 0; i < n; ++i)
   {
       if(i != currNode && i != node[currNode].parent && tree[currNode][i] != -1)
       {
           if(spclChild == -1 || node[spclChild].size < node[i].size)
              spclChild = i, spclEdgeID = tree[currNode][i];
       }
   }

   //If special child found extend chain
   if(spclChild != -1)
    HLD(spclChild, spclEdgeID, edgeCounted, currChain, n, chainHeads);

   //For every other normal child , do HLD on child subtree as 
   //separate chain
   for(int i = 0; i < n; ++i)
   {
       if(i != currNode  && i != node[currNode].parent && 
         tree[currNode][i] != -1 && i != spclChild)
       {
           currChain++;
           HLD(i, tree[currNode][i], edgeCounted, currChain, n, chainHeads);
       }  
   }
     
}

//To construct segment tree for array[ss....se)  {se exclusive}
// si = curr index of the segment tree
int construct_ST(int ss, int se, int si)
{
  if(ss == se-1)
  {
      s.tree[si] = s.baseArray[ss];
      return s.baseArray[ss];
  }

  //If there are more than one element, then recur for left and right 
  //subtrees and store the maximum of the values in this node
  int mid = (ss+se)/2;
  s.tree[si] = max(construct_ST(ss, mid, 2*si),
                   construct_ST(mid, se, 2*si +1));

  return s.tree[si];                 
}

/* To update segment tree
   x : is the node to be updated
   si : starting index of segment tree
   ss, se : Corners of the range represented by si
*/
int update_ST(int ss, int se, int si, int x, int val)
{
   if(ss > x || se <= x); // Out of range
   else if( ss == x && ss==se-1)  // only one element
     s.tree[si] = val;
   else
   {
       int mid = (ss+se)/2;
       s.tree[si] = max(update_ST(ss, mid, si*2, x, val),
                        update_ST(mid, se, si*2 + 1, x, val));
   }  
   return s.tree[si];
}

//Update the weight of edge 'e' to given weight 'val'
void change(int e, int val, int n)
{
    update_ST(0, n, 1, node[edge[e].deeperNode].posInSegTreeBase, val);
}

//Find LCA of two nodes 'u' and 'v' (You can use binary lifting)
int LCA(int u, int v, int n)
{
    //Array to store path from 'u' to root
    vector<int> LCA_Aux(n, -1);

    //set u as deeper node
    if(node[u].level < node[v].level)
      swap(u, v);
    
    while(u != -1)
    {
        LCA_Aux[u] = 1;
        u = node[u].parent;
    }

    while(v)
    {
        if(LCA_Aux[v] == 1)
           break;
        v = node[v].parent; 
    }
    return v;
}

//Find max value in a given range
// index : index of curr node in the segment tree
// ss & se : starting and ending indexes of the segment represented by
//           current node : s.tree[index]
// qs & qe : starting and ending indexed of the query range
int RMQUtil(int ss, int se, int qs, int qe, int index)
{
    //Total overlap 
    if(qs <= ss && qe >= se-1)
      return s.tree[index];

    //Segment is outside the range of current query range
    if( se-1 < qs || qe < ss)
      return -1;  // Edge weight have +ve values 

    //If a part of the segment overlaps with the given query range
    //(Partial Overlap)
    int mid = (ss + se)/2;
    return max(RMQUtil(ss, mid, qs, qe, 2*index),
               RMQUtil(mid, se, qs, qe, 2*index + 1));   
}

//Return maximum of elements in range(qs, qe)
int RMQ(int qs, int qe, int n)
{
  if(qs < 0 || qe > n-1 || qs > qe)
  {
      printf("Invalid Input");
      return -1;
  } 
  return RMQUtil(0, n, qs, qe, 1);
}

//Move u to v keeping track of the max weight of the edges
int crawlTree(int u, int v, int n, vector<int> chainHeads)
{
    int chain_u, chain_v = node[v].chain, ans = 0;
    while(true)
    {
        chain_u = node[u].chain;

        //If both nodes belong to same chain
        if(chain_u == chain_v)
        {
            if(u == v);
            else
                ans = max(RMQ(node[v].posInSegTreeBase + 1,
                              node[u].posInSegTreeBase, n), ans);
            break;
        }
        else
        {
            ans = max(ans, RMQ(node[chainHeads[chain_u]].posInSegTreeBase,
                           node[u].posInSegTreeBase, n));

            u = node[chainHeads[chain_u]].parent;                 
        }   
    }
    return ans;
}

void maxEdge(int u, int v, int n, vector<int> chainHeads)
{
    int lca = LCA(u, v, n);
    int ans = max(crawlTree(u, lca, n, chainHeads), crawlTree(v, lca, n, chainHeads));

    printf("%d\n", ans);               
}

int main()
{
    /* fill adjacency matrix with -1 to indicate no connections */
    memset(tree, -1, sizeof(tree));

    int n = 11;

    /* arguments in order: Edge ID, node u, node v, weight w*/
    addEdge(1, 1, 2, 13);
    addEdge(2, 1, 3, 9);
    addEdge(3, 1, 4, 23);
    addEdge(4, 2, 5, 4);
    addEdge(5, 2, 6, 25);
    addEdge(6, 3, 7, 29);
    addEdge(7, 6, 8, 5);
    addEdge(8, 7, 9, 30);
    addEdge(9, 8, 10, 1);
    addEdge(10, 8, 11, 6);

    /* our tree is rooted at node 0 at depth 0 */
    int root = 0, parentOfRoot = -1, levelOfRoot = 0;

    /* a DFS on the tree to set up: 
	* arrays for parent, depth, subtree size for every node; 
	* deeper end of every Edge */
    dfs(root, parentOfRoot, levelOfRoot, n);

    vector<int> chainHeads(N, -1);

    /* Stores number of edges for construction of segment 
	tree. Initially we haven't traversed any Edges. */
    int edgeCounted = 0;

    /* we start with filling the 0th chain */
    int currChain = 0;

    /* HLD of tree */
    HLD(root, n-1, edgeCounted, currChain, n, chainHeads);

    /* ST of segregated Edges */
    construct_ST(0, edgeCounted, 1);

    /* Since indexes are 0 based, node 11 means index 11-1, 
	8 means 8-1, and so on*/
    int u = 11, v = 9;
    cout << "Max edge between " << u << " and " << v << " is ";
    maxEdge(u-1, v-1, n, chainHeads);

    // Change value of edge number 8 (index 8-1) to 28
    change(8-1, 28, n);

    cout << "After Change: max edge between " << u << " and "
         << v << " is ";
    maxEdge(u-1, v-1, n, chainHeads);

    v = 4;
    cout << "Max edge between " << u << " and " << v << " is ";
    maxEdge(u-1, v-1, n, chainHeads);

    // Change value of edge number 5 (index 5-1) to 22
    change(5-1, 22, n);
    cout<<"After Change: max edge between "<<u<<" and "<<v<<" is ";
    maxEdge(u-1, v-1, n, chainHeads);
    return 0;
}