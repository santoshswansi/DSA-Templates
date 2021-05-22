#include<iostream>

using namespace std;
#define k 2  //for 2d tree
struct Node
{
 int point[k];
 Node *left,*right;
};

Node* newNode(int point[])
{
  Node *node=new Node;
  for(int i=0;i<k;++i)
   node->point[i]=point[i];
  node->left=node->right=NULL;
  return node;   
}

//unsigned=non negative integer
Node* insertRec(Node *root,int point[],unsigned depth)
{
  if(root==NULL)
   return newNode(point);
  unsigned currDimension=depth%k;//calculate current dimension
  if(point[currDimension]<root->point[currDimension])
   root->left=insertRec(root->left,point,depth+1);
  else 
   root->right=insertRec(root->right,point,depth+1);
  return root;     
}

//Wrapper function for insertion of new node
Node* insert(Node *root,int point[])
{
  return insertRec(root,point,0);  
}

//Utility function to find minimum of three nodes with given dimension
Node* minNode(Node *x,Node *y,Node *z,int dimension)
{
   Node *result=x;
   if(y!=NULL && y->point[dimension]<result->point[dimension])
    result=y;
   if(z!=NULL && z->point[dimension]<result->point[dimension])
    result=z;
   return result;  
}

Node* findMinRec(Node *root,int d,unsigned depth)
{
  if(root==NULL)
   return NULL;
  unsigned cd=depth%k;
  //if dimension of curr node matches with the dimension of 
  //root of the subtree in which we want to find the minimum value node
  //Then minimum will be found in left subtree
  if(cd==d)
  {
    if(root->left==NULL)//if left
     return root; 
    return findMinRec(root->left,d,depth+1); 
  }
  //Else find the minimum out of three possible nodes
  return minNode(root,findMinRec(root->left,d,depth+1),
                      findMinRec(root->right,d,depth+1),d);

}

//Wrapper function over findMinRec()
Node* findMin(Node *root,int d)
{
  return findMinRec(root,d,0);
}

bool arePointsSame(int point1[],int point2[])
{
  for(int i=0;i<k;++i)
  {
    if(point1[i]!=point2[i])
     return false;  
  }  
  return true;
}

void copyPoints(int point1[],int point2[])
{
  for(int i=0;i<k;++i)
   point1[i]=point2[i];  
}

//To get the given point present or not in the tree
bool searchRec(Node *root,int point[],unsigned depth)
{
  if(root== NULL)
   return false;

  if(arePointsSame(root->point,point)) 
   return true;
  unsigned cd=depth%k;
  if(point[cd]<root->point[cd])
   return searchRec(root->left,point,depth+1);
  else
   return searchRec(root->right,point,depth+1);
}

//Wrapper function over searchRec()
bool search(Node *root,int point[])
{
  return searchRec(root,point,0);  
}

Node* deleteRec(Node *root,int point[],unsigned depth)
{
  if(root==NULL)//Tree is empty
   return NULL;

  unsigned cd=depth%k;//Calculate current dimension

  //1.If current node's point and point are same 
  if(arePointsSame(root->point,point))
  {
    //1.a : If right child is not null(Right child present)  
    //Find the minimum node in right subtree
    //Replace the node to be deleted with the min node 
    //Then recursively delete minimum node 
    if(root->right!=NULL)
    {
      Node *min=findMin(root->right,cd); 
      copyPoints(root->point,min->point);
      root->right=deleteRec(root->right,point,depth+1);
    }  
    else if(root->left!=NULL)//Rigth Child :absent & Left Child : present
    {
      //1.b Find minimum node in left subtree of current dimension
      //Replace the node to be deleted with min node
      //make left subtree the right subtree of the node  
      Node *min=findMin(root->left,cd);
      copyPoints(root->point,min->point);
      root->right=deleteRec(root->left,point,depth+1); 
    }
    else //Left and Right Children are not present
    {
      delete root;
      return NULL;   
    }
    return root;
  }
  //2.If current node's point and point are not same
  if(point[cd]<root->point[cd])
   root->left=deleteRec(root->left,point,depth+1);
  else
   root->right=deleteRec(root->right,point,depth+1);

  //compiler will reach here when the node to be deleted 
  //is not present i.e. no change in root
  return root; 
}

Node* deleteNode(Node *root,int point[])
{
   return deleteRec(root,point,0); 
}
int main()
{
  Node *root=NULL;
  int points[][k]={{30,40},{5,25},{70,70},{10,12},{50,30},{35,45}};
  int size=sizeof(points)/sizeof(points[0]);
  cout<<size<<endl;
  for(int i=0;i<size;++i)
   root=insert(root,points[i]);
  cout<<"Root's point : ("<<root->point[0]<<","<<root->point[1]<<")";
  int point[2]={50,30};
  if(search(root,point))
   cout<<"\n(50,30) present in tree";
  root=deleteNode(root,points[0]);
  cout<<"\nAfter deleting (30,40) : ";
  cout<<"\nRoot's point :("<<root->point[0]<<","<<root->point[1]<<")";
  return 0;
}