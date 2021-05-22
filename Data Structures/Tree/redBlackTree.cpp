#include<iostream>
#include<queue>

using namespace std;

enum COLOR{RED,BLACK};

class RBTreeNode
{
 public:
  int value;
  RBTreeNode *left,*right,*parent;
  COLOR color;
  RBTreeNode(int value)
  {
      left=right=parent=NULL;
      color=RED;
      this->value=value;
  }
  bool isOnLeft()
  {
      return this==parent->left;
  }
  RBTreeNode* uncle()
  {
      //Parent OR Grandparent is NULL => no uncle
      if(parent==NULL || parent->parent==NULL) 
       return NULL;
      if(isOnLeft())
       return parent->parent->right;
      else
       return parent->parent->left;
  }
  RBTreeNode* sibling()
  {
    if(parent==NULL)
     return NULL;
    if(isOnLeft())
     return parent->right;
    else
     return parent->left;  
  }

  bool hasRedChild()
  {
      return (left!=NULL && left->color==RED)||(right!=NULL && right->color==RED);
  }
   
  void moveDown(RBTreeNode *newParent) //it will make newParent as parent
  {                                    //of x
   if(parent!=NULL)                    //and newParent's parent will be
   {                                   //x's parent
     if(isOnLeft())
      parent->left=newParent;
     else
      parent->right=newParent;
   }      
   newParent->parent=parent;
   parent=newParent; //It will set parent of current node as newParent
  } 
};

class RBTree
{
 RBTreeNode *root;

 void leftRotate(RBTreeNode *x)
 {
   RBTreeNode *newParent=x->right;

   if(x==root)
    root=newParent;
   x->moveDown(newParent);
   //making left child of newParent as right child of x
   x->right=newParent->left; 
   if(newParent->left!=NULL)
    newParent->left->parent=x; 
   newParent->left=x;  //making left child of newParent as x
 }

 void rightRotate(RBTreeNode *x)
 {
   RBTreeNode *newParent=x->left;

   if(x==root)
    root=newParent;
   x->moveDown(newParent);
   //making right child of newParent as left child of x
   x->left=newParent->right; 
   if(newParent->right!=NULL)
    newParent->right->parent=x; 
   newParent->right=x;  //making right child of newParent as x
 }

 void swapColors(RBTreeNode *x1,RBTreeNode *x2)
 {
     COLOR temp;
     temp=x1->color;
     x1->color=x2->color;
     x2->color=temp;
 }

 void swapValues(RBTreeNode *u,RBTreeNode *v)
 {
     int temp=u->value;
     u->value=v->value;
     v->value=temp;
 }

 //Fixing consecutive red RBTreeNodes after standard BST insert operation
 void fixRedRed(RBTreeNode *x)
 {
   if(x==root)
   {
     x->color=BLACK;
     return;  
   }
   RBTreeNode *parent=x->parent;
   RBTreeNode *grandParent=parent->parent;
   RBTreeNode *uncle=x->uncle();
   if(parent->color!=BLACK)
   {
     if(uncle!=NULL && uncle->color==RED)
     {
       parent->color=uncle->color=BLACK;
       grandParent->color=RED;  
       fixRedRed(grandParent);
     }  
     else //4 cases
     {
        if(parent->isOnLeft())
        {
          if(x->isOnLeft())
            swapColors(parent,grandParent);
          else 
          {
            leftRotate(parent);
            swapColors(x,grandParent);  
          }  
          rightRotate(grandParent);
        }  
        else
        {
          if(x->isOnLeft())
          {
            rightRotate(parent);
            swapColors(x,grandParent);
          } 
          leftRotate(grandParent);
        } 
     }
   }
 }

 //Find successor (or node which does not have left child)
 //To be used in delete operation of a node
 RBTreeNode* successor(RBTreeNode *x)
 {
    RBTreeNode *temp=x;
    if(temp->left!=NULL)
     temp=temp->left;
    return temp; 
 }

 //Find the node that will replace a deleted Node
 //To be used in delete operation of a node
 RBTreeNode* BSTReplace(RBTreeNode *x)
 {
   //Here x is the node to be deleted 
   if(x->left!=NULL && x->right!=NULL) //--> internal node
    return successor(x->right);//find successor  in right subtree(minValKey)
   if(x->left==NULL && x->right==NULL) //No child
    return NULL;

   //Single child 
   if(x->left!=NULL) 
    return x->left;
   else
    return x->right;  
 }

 void deleteNode(RBTreeNode *v)
 {
   //u=It will replace v(node to be deleted)  
   RBTreeNode *u=BSTReplace(v); //Two cases :- 1. u=NULL 2. u=only child of v
   
   //Double Black Case
   bool uvBlack=((u==NULL || u->color==BLACK) && (v->color==BLACK)); //leaf=BLACK
   RBTreeNode *parent=v->parent;
   if(u==NULL) // 1st case
   {
     if(v==root)
      root=NULL;
     else
     {
       if(uvBlack)
        fixDoubleBlack(v);  
       else
       {
        if(v->sibling()!=NULL)
         v->sibling()->color=RED;
       } 
       if(v->isOnLeft())
        parent->left=NULL;
       else
        parent->right=NULL; 
     } 
     delete v;
     return;
   }
   if(v->left==NULL || v->right==NULL) 
   {
     //ONE CHILD  
     if(v==root)
     {
       v->value=u->value;
       v->left=v->right=NULL;
       delete u;  
     }
     else
     {
       if(v->isOnLeft())
        parent->left=u;
       else
        parent->right=u;
       delete v;
       u->parent=parent;
       if(uvBlack)
        fixDoubleBlack(u);
       else
        u->color=BLACK;  
     }
     return;
   }
   swapValues(u,v); // v has two children, swap their values 
   deleteNode(u);   //and recurse for successor
 }
 void fixDoubleBlack(RBTreeNode *x)
 {
   if(x==root)
    return;
   RBTreeNode *parent=x->parent;
   RBTreeNode *sibling=x->sibling();
   if(sibling==NULL) //No sibling , Double black pushed up
    fixDoubleBlack(parent);
   else
   {
    if(sibling->color==RED) 
    {
        parent->color=RED;
        sibling->color=BLACK;
        if(sibling->isOnLeft())
         rightRotate(parent);
        else
         leftRotate(parent);
        fixDoubleBlack(x); 
    }  
    else
    {
     if(sibling->hasRedChild()) //Sibling=BLACK & has at least one children
     {
       if(sibling->left!=NULL && sibling->left->color==RED) //left child:RED
       {
         if(sibling->isOnLeft())  //Left Left Case
         {
           sibling->left->color=sibling->color;
           sibling->color=parent->color;
           rightRotate(parent);
         }
         else //Left Right Case
         {
           sibling->left->color=parent->color;
           rightRotate(sibling);
           leftRotate(parent);
         }
       } 
       else
       {
        if(sibling->isOnLeft()) //Left Right Case
        {
          sibling->right->color=parent->color;
          leftRotate(sibling);
          rightRotate(parent); 
        }
        else //Right Right Case
        {
          sibling->right->color=sibling->color;
          sibling->color=parent->color;
          leftRotate(parent);  
        }
       }
       parent->color=BLACK;
     }
     else //sibling = BLACK & its 2 children = BLACK
     {
       sibling->color=RED; //recolor
       if(parent->color==BLACK) //if parent=BLACK recurse else set it BLACK
        fixDoubleBlack(parent);
       else   
        parent->color=BLACK;
     }
    }
   }
 }

 void levelOrder(RBTreeNode *x)
 {
   if(x==NULL)
    return;

   queue<RBTreeNode*> q;

   RBTreeNode *curr;
   q.push(x);
   while(!q.empty())
   {
     curr=q.front();  
     q.pop();  
     cout<<curr->value<<", ";
  
     if(curr->left!=NULL)
      q.push(curr->left);
     if(curr->right!=NULL)
      q.push(curr->right); 
   }
 }
 void inorder(RBTreeNode *x)
 {
   if(x==NULL)
    return;
   inorder(x->left);
   cout<<x->value<<", ";
   inorder(x->right);    
 }
 public:
  RBTree()
  {
      root=NULL;
  }
  RBTreeNode* getRoot(){ return root;}
  RBTreeNode* search(int num) //if found returns searched node(search) 
  {                           //else returns parent of the node(Insert) 
    RBTreeNode *temp=root;
    while(temp!=NULL)
    {
      if(num<temp->value)
      {
       if(temp->left==NULL)
        break;
       else
        temp=temp->left;
      }  
      else if(num==temp->value)
       break;
      else
      {
       if(temp->right==NULL)
        break;
       else
        temp=temp->right;   
      }
    }
    return temp;
  }
  
  void insert(int num)
  {
    RBTreeNode *newNode=new RBTreeNode(num); 
    if(root==NULL)
    {
      newNode->color=BLACK;
      root=newNode;  
    } 
    else
    {
      RBTreeNode *temp=search(num);
      if(temp->value==num)
       return;
      newNode->parent=temp;
      if(num<temp->value)
       temp->left=newNode;
      else
       temp->right=newNode;
      fixRedRed(newNode); //FIX RED RED consecutive nodes 
    }
  }
  void deleteByKey(int num)
  {
    if(root==NULL)
     return;
    RBTreeNode *v=search(num);
    RBTreeNode *u;
    if(v->value!=num)   
    {
      cout<<"\nNot found : "<<num<<endl;
      return;
    }
    deleteNode(v);
  }
  void printInorder()
  {
     cout<<"Inorder : ";
     if(root==NULL) 
      cout<<"Tree is empty!"<<endl;
     else
      inorder(root);
     cout<<endl; 
  }
  void printLevelOrder()
  {
     cout<<"Level Order : ";
     if(root==NULL) 
      cout<<"Tree is empty!"<<endl;
     else
      levelOrder(root);
     cout<<endl; 
  }
};

int main()
{
    RBTree tree;

    tree.insert(7);
    tree.insert(10);
    tree.insert(71);
    tree.insert(12);
    tree.insert(14);
    tree.insert(54);
    tree.insert(23);
    tree.insert(100);
    tree.insert(-1);
    tree.printInorder();
    tree.printLevelOrder();
    cout<<"\nDeleting 100 and 23 : ";
    tree.deleteByKey(100);
    tree.deleteByKey(23);
    tree.printInorder();
    tree.printLevelOrder();
    return 0;
}