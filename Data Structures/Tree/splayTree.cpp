#include<iostream>
#include<queue>

using namespace std;

struct splayTreeNode
{
    int key;
    splayTreeNode *left,*right;
};

splayTreeNode* newNode(int key)
{
    splayTreeNode *node=new splayTreeNode();
    node->key=key;
    node->left=node->right=NULL;
    return node;
}

splayTreeNode* leftRotate(splayTreeNode *x)
{
    splayTreeNode *newParent=x->right;
    x->right=newParent->left;
    newParent->left=x;
    return newParent;
}

splayTreeNode *rightRotate(splayTreeNode *x)
{
    splayTreeNode *newParent = x->left;
    x->left = newParent->right;
    newParent->right = x;
    return newParent;
}

//splay() brings the key at root if key is present in tree
//If key is not present , then it bring the last 
//accessed item(possible parent of key) to root
//It modifies the tree and return the new root
splayTreeNode* splay(splayTreeNode *root,int key)
{
    //If root is NULL OR root is the searched key
    if (root == NULL || root->key == key)
        return root; 
    if(root->key>key) //If root is present in left subtree
    {
      if(root->left==NULL)//Left subtree does not exist
       return root;
      if(root->left->key>key)//LEFT LEFT 
      {
        //splay the left node of left tree of root node  
        root->left->left=splay(root->left->left,key);
        //Do first rotation for root
        //Second rotation is done after
        root=rightRotate(root);  
      } 
      else if(root->left->key<key)//LEFT RIGHT
      {
        root->left->right=splay(root->left->right,key);
        if(root->left->right!=NULL)//Do first rotation for root->left
         root->left=leftRotate(root->left);
      }
      return (root->left==NULL)?root:rightRotate(root);//Second rotation
    }   
    else//right subtree
    {
      if(root->right==NULL)//right subtree not present
       return root;  
      if(root->right->key<key)//RIGHT RIGHT
      {
        root->right->right=splay(root->right->right,key);
        root=leftRotate(root);//First rotation at root
      } 
      else//RIGHT LEFT
      {
        root->right->left=splay(root->right->left,key);
        if(root->right->left!=NULL)//right rotate at root->right 
         root->right=rightRotate(root->right);
      }
      return (root->right==NULL)?root:leftRotate(root);//2nd rotation 
    }
}

//return new root
splayTreeNode* deleteKey(splayTreeNode *root,int key)
{
  splayTreeNode *temp;
  if(root==NULL)//No Element
   return NULL;

  //If key is present make it root
  //Otherwise key's possible parent will be made root
  root=splay(root,key); 

  if(key!=root->key)//key not present
   return root;

  //If key is present
  if(root->left==NULL)    //left subtree not present
  {
    temp=root;
    root = root->right; //make right child as the root of the tree
  }  
  else                    //Left subtree present
  {
    temp=root;
    //In left subtree key's possible parent can be made root
    root = splay(root->left, key);
    //link the right subtree of previous root with the present root
    root->right=temp->right;
  }
  free(temp);
  return root;
}

splayTreeNode* search(splayTreeNode *root,int key)
{
    return splay(root,key);
}

splayTreeNode* insert(splayTreeNode *root,int key)
{
    if(root==NULL)
     return newNode(key);

    root=splay(root,key); 

    //already present 
    if(root->key==key)
     return root;
    
    splayTreeNode *node=newNode(key);

    if(key<root->key)
    {
      node->right=root;
      node->left=root->left;
      root->left=NULL;
    }
    else
    {
      node->left=root;
      node->right=root->right;
      root->right=NULL;  
    }
    return node;
}

void levelOrder(splayTreeNode *root)
{
  if(root==NULL)
  {
    cout<<"\nTree not present!";
    return;  
  }  
  queue<splayTreeNode *> q;
  q.push(root);  
  while(!q.empty())
  {
    splayTreeNode *node=q.front();   
    cout<<node->key<<" ";
    q.pop();

    if(node->left!=NULL)
     q.push(node->left);  
    if(node->right!=NULL)
     q.push(node->right);  
  }
}

void preOrder(splayTreeNode *root)
{
  if (root != NULL)
  {
    cout << root->key << " ";
    preOrder(root->left);
    preOrder(root->right);
  }
}

int main()
{
//  splayTreeNode *root=newNode(100);
//  root->left=newNode(50);
//  root->right=newNode(200);
//  root->left->left=newNode(40);
//  root->left->left->left=newNode(30);
//  root->left->left->left->left=newNode(20);
//  root=insert(root,25);
//  root=insert(root,10);

//  cout<<"\nLEVEL ORDER : ";
//  levelOrder(root);

//  cout<<"\nSearching 25!";
//  root=search(root,25);
//  if(25==root->key)
//   cout<<"\n25 is present!";
//  else
//   cout<<"\nNot present!";

//  cout << "\nLEVEL ORDER : ";
//  levelOrder(root);

//  //After deleting 20
//  root=deleteKey(root,20);
//  cout<<"\nAfter deleting 20 LEVEL ORDER TRAVERSAL : ";
//  levelOrder(root);
splayTreeNode *root = newNode(100);
root->left = newNode(50);
root->right = newNode(200);
root->left->left = newNode(40);
root->left->left->left = newNode(30);
root->left->left->left->left = newNode(20);
root = insert(root, 25);
cout << "Preorder traversal of the modified Splay tree is \n";
preOrder(root);
return 0;
return 0;
}