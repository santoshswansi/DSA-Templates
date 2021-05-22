#include<iostream>
#include<string.h>

using namespace std;
#define V 9 //Number of nodes in an input array

int euler[2*V + 1]; //Array to store elements in euler tour
int level[2*V + 1];  //Array to store level of elements in euler tour
//Array to store first occurrence of element in euler tour
int firstOccurrence[V+1];
int index; //Variable to fill in euler & level arrays

struct Node
{
  int key;
  Node *left, *right;  
};

Node* newNode(int key)
{
  Node *node = new Node;
  node->key = key;
  node->left = node->right = NULL;  
  return node;
}

int Log2(int x)
{
    int ans = 0;
    while (x >>= 1)
        ans++;
    return ans;
}

int RMQUtil(int si,int ss,int se, int qs,int qe,int *st)
{
  //If segment of this node is a part of given range , then return
  //the minimum of the segment
  if(qs <= ss && qe>=se)
   return st[si];
  else if(se < qs || ss>qe)
   return -1;

  int mid = (ss + se) / 2;
  int q1 = RMQUtil(si * 2 + 1, ss, mid, qs, qe, st);
  int q2 = RMQUtil(si * 2 + 2, mid+1, se, qs, qe, st);

  if(q1==-1)
   return q2;
  else if(q2==-1)
   return q1; 
  return (level[q1]<level[q2])?q1:q2; 
}

int RMQ(int *st, int n, int qs, int qe)
{
  if(qs<0 || qe>n-1 || qs>qe)
  {
    cout<<"\nInvalid Input!";
    return -1;  
  }  
  return RMQUtil(0, 0, n-1, qs, qe, st);
}

void constructSegmentTreeUtil(int si, int ss, int se, int array[], int *st)
{
  //Only one element
  if(ss==se)
   st[si]=ss;
  else
  {
    int mid=(ss+se)/2;
    constructSegmentTreeUtil(si * 2 + 1, ss, mid, array, st);
    constructSegmentTreeUtil(si * 2 + 2, mid + 1, se, array, st);

    //Minimum of two nodes in this node
    if(array[st[2*si+1]] < array[st[2*si+2]])
     st[si] = st[2*si +1];
    else
     st[si] = st[2*si + 2]; 
  } 
}

int* constructSegmentTree(int array[], int n)
{
  //Height of segment tree
  int heightOfST = Log2(n)+1;  
  //maximum size of segment tree
  int maxSize = 2*(1<<heightOfST)-1;

  int *st=new int[maxSize];

  constructSegmentTreeUtil(0,0,n-1,array,st);

  return st;
}

void eulerTour(Node *root, int l)
{
 if(root!=NULL)
 {
  euler[index]=root->key;
  level[index]=l;  
  index++;

  //Modify the firstOccurrence[]
  if(firstOccurrence[root->key] == -1)
   firstOccurrence[root->key] = index-1;

  //Recur in left and right subtree if they are present 
  //and store the minimum in current node
  if(root->left!=NULL)
  {
   eulerTour(root->left,l+1);
   euler[index] = root->key;
   level[index] = l;
   index++;
  }
  
  if (root->right != NULL)
  {
    eulerTour(root->right, l + 1);
    euler[index] = root->key;
    level[index] = l;
    index++;
  }
 }
}

//function to find LCA of two nodes u and v
int findLCA(Node *root, int u, int v)
{
  //Initialise firstOccurrence array with -1(Non-Visited node)  
  memset(firstOccurrence, -1, sizeof(int)*(V+1)); 

  index=0;

  //start the euler tour from root with level = 0
  eulerTour(root,0);

  //construct segment tree on level array
  int *st=constructSegmentTree(level, 2*V - 1);

  //If v before u in Euler Tour 
  //For RMQ to work, first parameter 'u' must be smaller than second 'v'
  if(firstOccurrence[u]>firstOccurrence[v])
   swap(u,v);

  int qs=firstOccurrence[u];
  int qe=firstOccurrence[v];

  int index = RMQ(st, 2*V-1, qs, qe);

  //return LCA node
  return euler[index]; 
}

int main()
{
  Node *root=newNode(1);
  root->left=newNode(2);
  root->right=newNode(3);
  root->left->left=newNode(4);
  root->left->right=newNode(5);
  root->right->left = newNode(6);
  root->right->right = newNode(7);

  root->left->right->left=newNode(8);
  root->left->right->left = newNode(9);
  int u=4,v=9;
  cout<<"\nLowest Common Ancestor of "<<u<<" and "<<v<<" is ";
  cout << findLCA(root, u, v);
  u = 1, v = 7;
  cout << "\nLowest Common Ancestor of " << u << " and " << v << " is ";
  cout << findLCA(root, u, v);
  u = 5, v = 6;
  cout << "\nLowest Common Ancestor of " << u << " and " << v << " is ";
  cout << findLCA(root, u, v);
  return 0;  
}