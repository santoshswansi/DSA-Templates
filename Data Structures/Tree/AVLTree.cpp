#include<iostream>

using namespace std;

struct AVLTreeNode
{
    int key;
    AVLTreeNode *left; 
    AVLTreeNode *right;
    int height; 
};

int max(int no1,int no2)
{
  return (no1>no2)?no1:no2;
}

int height(AVLTreeNode *N)
{
    if(N==NULL)
     return 0;
    return N->height; 
}

AVLTreeNode* newNode(int key)
{
  AVLTreeNode *node=new AVLTreeNode();
  node->key=key;
  node->left=node->right=NULL;
  node->height=1; // new Node will always bbe leaf node therefore height =1
  return node;
}

AVLTreeNode* leftRotate(AVLTreeNode *x)
{
   AVLTreeNode *y=x->right;
   AVLTreeNode *T2=y->left;

   //perform rotation
   y->left=x;
   x->right=T2; 

   //update heights
   x->height=max(height(x->left),height(x->right));
   y->height=max(height(y->left),height(y->right));

   return y; //Return new parent
}

AVLTreeNode* rightRotate(AVLTreeNode *y)
{
   AVLTreeNode *x=y->left;
   AVLTreeNode *T2=x->right;

   //perform rotation
   x->right=y;
   y->left=T2; 

   //update heights
   x->height=max(height(x->left),height(x->right));
   y->height=max(height(y->left),height(y->right));

   return x; //Return new parent
}

int getBalance(AVLTreeNode *N)
{
    if(N==NULL)
     return 0;
    return height(N->left)-height(N->right); 
}

AVLTreeNode* insert(AVLTreeNode *node,int key)
{
    //1.Perform standard BST insertion
    if(node==NULL)
     return newNode(key);
    else if(key<node->key)
     node->left=insert(node->left,key);
    else if(key>node->key)
     node->right=insert(node->right,key);
    else    //equal keys not allowed
     return node;

    //2.Update height of ancestor node
    node->height=1+max(height(node->left),height(node->right));

    //3.Get the balance factor of the ancestor node 
    // to check whether this node become unbalanced 
    int balance=getBalance(node);

    //if unbalanced: 4 cases
    //LEFT LEFT CASE
    if(balance>1 && key<node->left->key)
     return rightRotate(node);

    //RIGHT RIGHT CASE
    if(balance<-1 && key>node->right->key)
     return leftRotate(node);

    //LEFT RIGHT CASE 
    if(balance>1 && key>node->left->key)  
    {
      node->left=leftRotate(node->left);
      return rightRotate(node);
    }
    //RIGHT LEFT CASE 
    if(balance<-1 && key<node->right->key)  
    {
      node->right=rightRotate(node->right);
      return leftRotate(node);
    }
    return node; //return unchanged root  pointer
}

AVLTreeNode* minValueNode(AVLTreeNode *node)
{
  AVLTreeNode *curr=node;
  while(curr->left!=NULL)
   curr=curr->left;
  return curr;   
}

AVLTreeNode* deleteNode(AVLTreeNode *root,int key)
{
    //STEP 1: Perform standard delete operation
    if(root==NULL)
     return root;
    if(key<root->key)
     root->left=deleteNode(root->left,key);
    else if(key>root->key)
     root->right=deleteNode(root->right,key);
    else //node to be deleted found
    {
      if(root->left==NULL || root->right==NULL) //ONE CHILD or NO CHILD
      {
        AVLTreeNode *child=(root->left!=NULL)?root->left:root->right;
        if(child==NULL)//NO CHILD
        {
          child=root; //To delete it after
          root=NULL; //make the current node null
        }
        else //ONE CHILD
         *root=*child; //copy content of the child to *root
        free(child);
      }
      else //TWO CHILD
      {
        AVLTreeNode *successor=minValueNode(root->right);
        root->key=successor->key;
        root->right=deleteNode(root->right,successor->key);
      }
    }

    //If the tree had only one node 
    if(root==NULL)
     return root;

    //STEP 2: Update the height of the current node
    root->height=1+max(height(root->left),height(root->right));

    //STEP 3: Get balance factor of this node
    int balance=getBalance(root);

    //If UNBALANCED , 4 cases
    
    //LEFT LEFT CASE
    if(balance>1 && getBalance(root->left)>=0)
     return rightRotate(root);
    
    //RIGHT RIGHT CASE
    if(balance<-1 && getBalance(root->right)<=0)
     return leftRotate(root);

    //LEFT RIGHT CASE
    if(balance>1 && getBalance(root->left)<0)
    {
        root->left=leftRotate(root->left);
        return rightRotate(root);
    } 

    //RIGHT LEFT CASE
    if(balance<-1 && getBalance(root->right)>0)
    {
        root->right=rightRotate(root->right);
        return leftRotate(root);
    }
  return root;
}

void inOrder(AVLTreeNode *root)
{
    if(root!=NULL)
    {
      inOrder(root->left);  
      cout<<root->key<<" ";
      inOrder(root->right);  
    }
}
int main()
{
    AVLTreeNode *root=NULL;
    root=insert(root,12);
    root=insert(root,2);
    root=insert(root,1);
    root=insert(root,10);
    root=insert(root,-12);
    root=insert(root,23);
    root=insert(root,19);
    root=insert(root,28);
    root=insert(root,17);

    cout<<"\nInorder : ";
    if(root==NULL)
     cout<<"\nNo element!";
    else
     inOrder(root);
     
  
    root=deleteNode(root,1);
    
    cout<<"\nAfter deleting node with key : "<<1;
    cout<<"\nInorder : ";
    if(root==NULL)
     cout<<"\nNo element!";
    else
     inOrder(root);

    return 0;
}