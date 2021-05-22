#include<iostream>

using namespace std;

struct Node
{
    int key;
    Node *left;
    Node *right;
    bool lThreaded;
    bool rThreaded;
};

Node* getNode(int key)
{
    Node *newNode=new Node;
    newNode->key=key;
    newNode->left=NULL;
    newNode->right=NULL;
    newNode->lThreaded=true;
    newNode->rThreaded=true;
    return newNode;
}

Node* leftMostNode(Node *temp)
{
    while(temp->lThreaded==false)
     temp=temp->left;
    return temp; 
}

//used in inorder
Node* inorderSuccessor(Node *temp)
{
  if(temp->rThreaded==true) //Leaf node
   return temp->right;

  //left most node in right sub-tree
  return leftMostNode(temp->right);  
}

void inorder(Node *root)
{
    if(root==NULL)
    {
      cout<<"\nTree is empty!";
      return;
    }

    //Reaching leftmost node
    Node *temp=leftMostNode(root);
    while(temp!=NULL)
    {
        cout<<temp->key<<", ";
        temp=inorderSuccessor(temp);
    } 
}

//Insertion of only unique elements are expected
void insert(Node* &root,int key)
{
  Node *curr=root;
  Node *parent=NULL;
  if(root==NULL) //for the first time root node is left and right NULL-threaded
  {
      root=getNode(key);
      return;
  }
  while(curr!=NULL)
  {
      parent=curr;
      if(key==curr->key)
      {
        cout<<"\nUnique element expected!";
        return;
      }
      if(key<curr->key && curr->lThreaded==false)
       curr=curr->left;
      else if(key>curr->key && curr->rThreaded==false)
       curr=curr->right;
      else
       break;
  }
  parent=curr;
  curr=getNode(key);
  if(key<parent->key)
  {
    curr->left=parent->left;
    curr->right=parent;
    parent->left=curr; 
    parent->lThreaded=false;
  }
  else
  {
    curr->left=parent;
    curr->right=parent->right;
    parent->right=curr;
    parent->rThreaded=false;
  } 
}

void searchKey(Node* &curr,int key,Node* &parent)
{
    while(curr!=NULL && curr->key!=key)
    {
        parent=curr;
        if(key<curr->key && curr->lThreaded==false)
         curr=curr->left;
        else if(key>curr->key && curr->rThreaded==false)
         curr=curr->right;
        else
        {
         curr=NULL;
         return;
        }
    }
}

//Used in deletion
Node* minimumKey(Node *curr)
{
  while(curr->lThreaded==false)
   curr=curr->left;
  return curr; 
}

//used in deletion
Node* inSuccessor(Node *curr)
{
  if(curr->rThreaded==true)
   return curr->right;
  curr=curr->right;
  curr=leftMostNode(curr);
  return curr;  
}

Node* inPredecessor(Node *curr)
{
  if(curr->lThreaded==true)
   return curr->left;
  curr=curr->left;
  while(curr->rThreaded==false)
   curr=curr->right;
  return curr; 
}

void removeThreadedNode(Node* &root,int key)
{
  Node *parent=NULL;
  Node *curr=root;
  searchKey(curr,key,parent);
  if(curr==NULL)
  {
    cout<<"\nKey not present!";
    return;
  }
  if(curr->lThreaded==true && curr->rThreaded==true)
  {
    if(curr!=root)
    {
      if(parent->left==curr)
      {
        parent->lThreaded=true;
        parent->left=curr->left;        
      } 
      else
      {
        parent->rThreaded=true;
        parent->right=curr->right;
      }   
      free(curr);
      curr=NULL;
    } 
    else
    {
      free(root);
      root=NULL;
    }       
  } 
  else if(curr->lThreaded==false && curr->rThreaded==false)
  {
    Node *successor=minimumKey(curr->right);
    int value=successor->key;
    removeThreadedNode(root,value);
    curr->key=value;
  }
  else
  {
    Node *child=(curr->lThreaded==false)?curr->left:curr->right;
    if(curr!=root)
    {
      if(parent->left==curr)
        parent->left=child;
      else
       parent->right=child;
      Node *s=inSuccessor(curr);
      Node *p=inPredecessor(curr);
      if(curr->lThreaded==false)
       p->right=s;
      else if(curr->rThreaded==false)
       s->left=p;  
    } 
    else
    {
      root=child;
    }
    free(curr);    
  }
}

int main()
{
    int choosenOpt;
    char ans;

    int size;
    Node *root=NULL;
    int key;
    cout<<"\nTotal Nodes (<=15): ";
    cin>>size;

    cout<<"Enter "<<size<<" elements : ";
    for(int i=0;i<size;++i)
    {
      cin>>key;
      insert(root,key);
    }
    do
    {
      cout<<"\nChoose one : ";
      cout<<"\n1.INSERT ";
      cout<<"\n2.DELETE ";
      cout<<"\n3.INORDER TRAVERSAL\n";
      cin>>choosenOpt;
      switch(choosenOpt)
      {
        case 1: 
           cout<<"\n Key : ";
           cin>>key;
           insert(root,key);
           break;
        case 2: 
           cout<<"\n Key : ";
           cin>>key;
           removeThreadedNode(root,key);
           break;  
        case 3:
           cout<<"\nINORDER TRAVERSAL : ";
           inorder(root);
           break; 
        default:
           cout<<"\nWrong Option!";
           break;   
      }
      cout<<"\nDo you want to continue (y/n)?: ";
      cin>>ans;
    }while(ans=='y'||ans=='Y');
    
    return 0;
}