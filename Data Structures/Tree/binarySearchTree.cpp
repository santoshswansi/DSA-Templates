#include<iostream>
#include<vector>

using namespace std;

struct Node
{
    int key;
    Node *left;
    Node *right;
};

Node* getNode(int key)
{
    Node *newNode=new Node;
    newNode->key=key;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

void inorder(Node *head)
{
    if(head!=NULL)
    {
      inorder(head->left);
      cout<<head->key<<", ";
      inorder(head->right);
    }
}

void preorder(Node *head)
{
    if(head!=NULL)
    {
      cout<<head->key<<", ";
      preorder(head->left);
      preorder(head->right);
    }
}

void postorder(Node *head)
{
    if(head!=NULL)
    {  
      postorder(head->left);
      postorder(head->right);
      cout<<head->key<<", ";
    }
}

void insertRecurive(Node* &root,int key)
{
  if(root==NULL)
  {
      root=getNode(key);
      return;
  }
  if(key<root->key)
   insertRecurive(root->left,key);
  else 
   insertRecurive(root->right,key);
}

void insertIterative(Node* &root,int key)
{
    Node *curr=root;
    Node *parent=NULL;
    if(root==NULL)
    {
        root=getNode(key);
        return;
    } 
    while(curr!=NULL)
    {
        parent=curr;
        if(key<curr->key)
         curr=curr->left;
        else
         curr=curr->right;
    }
    if(key<parent->key)
     parent->left=getNode(key);
    else
     parent->right=getNode(key);
}

void searchRecursive(Node *root,int key,Node *parent)
{
  if(root==NULL)
  {
      cout<<"\nKey not found!";
      return;
  }
  if(root->key == key)
  {
      if(parent==NULL)
       cout<<"\nGiven key is the root node.";
      else if(key<parent->key)
       cout<<"\nGiven key is the left child of the parent node : "<<parent->key;
      else  
       cout<<"\nGiven key is the right child of the parent node : "<<parent->key;
      return; 
  }
  if(key<root->key)
   searchRecursive(root->left,key,root);
  else
   searchRecursive(root->right,key,root); 
}

void searchIterative(Node *root,int key)
{
  Node *parent=NULL;
  Node *curr=root;
  while(curr!=NULL && curr->key!=key)
  {
      parent=curr;
      if(key<curr->key)
       curr=curr->left;
      else 
       curr=curr->right;
  }

  if(curr==NULL)
    cout<<"\nKey is not found!";
  else if(parent==NULL)
    cout<<"\nKey is the root node.";
  else if(key<parent->key)
    cout<<"\nKey is the left node of the parent node : "<<parent->key;
  else 
    cout<<"\nKey is the right node of the parent node : "<<parent->key;
}

void searchKey(Node* &curr,int key,Node* &parent)
{
  while(curr!=NULL && curr->key!=key)
  {
    parent=curr;
    if(key<curr->key)
     curr=curr->left;
    else
     curr=curr->right;    
  }
}

Node* minimumKey(Node *curr)
{
  while(curr->left!=NULL)
   curr=curr->left;
  return curr; 
}
//err
void removeNode1(Node* &root,int key)
{
  //First find parent-node-pointer and key-node-pointer
  Node *parent=NULL;
  Node *curr=root;
  searchKey(curr,key,parent);

  if(curr==NULL) //if key is not present
   return;
  if(curr->left==NULL && curr->right==NULL)//Leaf Node
  {
    if(curr!=root)
    {
      if(parent->left==curr)
       parent->left=NULL;
      else
       parent->right=NULL;
    }
    else
    {
      root=NULL;
    }
    free(curr);
  } 
  else if(curr->left!=NULL && curr->right!=NULL) // key-node-pointer has two childs
  {
    Node *successor=minimumKey(curr->right); //mininmum key element in right subtree
    int value=successor->key;
    removeNode1(root,value); //remove the node with key of value - 'value'
    curr->key=value; //set the element to be deleted with the value - 'value'
  }
  else
  {
    Node *child=(curr->left!=NULL)?curr->left:curr->right;
    if(curr!=root)
    {
      if(parent->left==curr)
       parent->left=child;
      else
       parent->right=child;
    }
    else
      root=child;
    free(curr);
  }
}

Node* maximumKey(Node *curr)
{
  while(curr->right!=NULL)
   curr=curr->right;
  return curr; 
}
//err
void removeNode2(Node* &root,int key)
{
 if(root==NULL)
  return;
 if(key<root->key)
  removeNode2(root->left,key);
 else if(key>root->key)
  removeNode2(root->right,key);
 else
 {
   if(root->left==NULL && root->right==NULL)
   {
     delete root;
     root=NULL;
   }
   else if(root->left!=NULL && root->right!=NULL)
   {
     Node *predecessor=maximumKey(root->left);
     int value=predecessor->key;
     root->key=value;
     removeNode2(root->left,value);
   }
   else
   {
     Node *child=(root->left!=NULL)?root->left:root->right;
     Node *curr=root;
     root=child;
     delete curr;
     curr=NULL;
   }
 }
}

int main()
{
    int choosenOpt;
    char ans;

    vector<int> keys;
    int size;
    Node *root=NULL;
    int key;
    cout<<"\nTotal Nodes (<=15): ";
    cin>>size;
    keys.resize(size);

    cout<<"Enter "<<size<<" elements : ";
    for(int i=0;i<size;++i)
    {
      cin>>keys[i];
      insertRecurive(root,keys[i]);
    }

    do
    {
      cout<<"\nChoose one : ";
      cout<<"\n1.INSERT Recursively";
      cout<<"\n2.INSERT Iteratively";
      cout<<"\n3.DELETE Method - 1";
      cout<<"\n4.DELETE Method - 2";
      cout<<"\n5.SEARCH Recursively";
      cout<<"\n6.SEARCH Iteratively";
      cout<<"\n7.INORDER TRAVERSAL";
      cout<<"\n8.PREORDER TRAVERSAL";
      cout<<"\n9.POSTORDER TRAVERSAL\n";
      cin>>choosenOpt;
      switch(choosenOpt)
      {
        case 1: 
           cout<<"\n Key : ";
           cin>>key;
           insertRecurive(root,key);
           break;
        case 2: 
           cout<<"\n Key : ";
           cin>>key;
           insertIterative(root,key);
           break;
        case 3: 
           cout<<"\n Key : ";
           cin>>key;
           removeNode1(root,key);
           break;  
        case 4: 
           cout<<"\n Key : ";
           cin>>key;
           removeNode2(root,key);
           break; 
        case 5: 
           cout<<"\n Key : ";
           cin>>key;
           searchRecursive(root,key,NULL);
           break;
        case 6: 
           cout<<"\n Key : ";
           cin>>key;
           searchIterative(root,key);
           break;
        case 7:
           cout<<"\nINORDER TRAVERSAL : ";
           inorder(root);
           break;
        case 8:
           cout<<"\nPREORDER TRAVERSAL : ";
           preorder(root);
           break;
        case 9:
           cout<<"\nPOSTORDER TRAVERSAL : ";
           postorder(root);
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