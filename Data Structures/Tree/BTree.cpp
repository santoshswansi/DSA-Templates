#include<iostream>

using namespace std;

class BTreeNode
{
  int *keys; //An array of keys 
  int t; //Maximum degree
  BTreeNode **Childs;//An array of pointers to childs
  int currNoOfKeys;//Current number of keys present
  bool leaf;//True(if leaf)

  public:
    BTreeNode(int _t,bool _leaf); //Constructor
    void traverse();
    BTreeNode* search(int key);
    int findKey(int key); //Returns the index of first key i.e.
                              //greater or equal to k
    void insertNonFull(int key);

    void remove(int key);
    void removeFromLeaf(int index);
    void removeFromNonLeaf(int index);

    //To get the predecessor of the key-where key is present int the 
    //index-th position in the node
    int getPredecessor(int index); 
    int getSuccessor(int index);  

    //To fill up the child node present in the index-th position in the
    //childs[] array if the child has less than t-1 keys(t=order)
    void fill(int index);    

    //To borrow a key from the Childs[index+1] node & place it in
    //Childs[index] node
    void borrowFromPrev(int index);

    void borrowFromNext(int index);

    //To merge index-th child of the node with (index+1)-th child of node
    void merge(int index);

    //To split child y of this node
    //i is the index of y in child array Childs[]
    //Child y must be full when this function is called
    void splitChild(int i,BTreeNode *y);

    //To access private members of the class BTreeNode
    friend class BTree;
};

class BTree
{
    BTreeNode *root;
    int t;//Minimum degree

    public:
     BTree(int _t)
     {
         root=NULL;
         t=_t;
     }

     void traverse()
     {
       if(root!=NULL)
        root->traverse();
       else 
        cout<<"Tree is empty!";
     }

     BTreeNode* search(int key)
     {
        return (root==NULL)?NULL : root->search(key);
     }
     void insert(int key);
     void remove(int key);

};

BTreeNode::BTreeNode(int _t,bool _leaf)
{
    t=_t;
    leaf=_leaf;
    keys=new int[2*t-1];//Maximum keys possible in a node : 
    Childs=new BTreeNode *[2*t];
    currNoOfKeys=0;
}

int BTreeNode::findKey(int key)//Returns first key ie greater or equal to k
{
  int index=0;
  while(index<currNoOfKeys && keys[index]<key)
    ++index;
  return index;  
}

void BTreeNode::remove(int key)
{
    int index=findKey(key);
    if(index<currNoOfKeys && keys[index]==key) //key is present is same node
    {
      if(leaf)
       removeFromLeaf(index);
      else
       removeFromNonLeaf(index);  
    }
    else
    {
      if(leaf)//if key not found in same node and it is leaf then key not present
      {
        cout<<"\nKey not found!";
        return;
      } 

      bool flag=((index==currNoOfKeys)? true : false);

      //If the child where the key is supposed to present 
      //has less than t keys fill that child
      //Borrowing of key OR merging of two childs happen 
      if(Childs[index]->currNoOfKeys <t ) 
       fill(index);

      //If the last child has been merged,it must have been merged with 
      //the previous child & so we recurse on the (index-1)-th child
      //Else we recurse on index-th child which has now at least t-keys
      if(flag && index>currNoOfKeys) //Merged with previous child
       Childs[index-1]->remove(key);
      else
       Childs[index]->remove(key); 
    }

}

void BTreeNode::removeFromLeaf(int index)
{
  for(int i=index+1;i<currNoOfKeys;++i)
   keys[i-1]=keys[i];
  currNoOfKeys--;

}

void BTreeNode::removeFromNonLeaf(int index)
{
  int key=keys[index];
  //If childs[index] has >=t keys then find predecessor and replace the
  //key with predecessor and recursively delete predecessor in
  //subtree root Childs[index]
  if(Childs[index]->currNoOfKeys >= t)
  {
    int pred=getPredecessor(index);
    keys[index]=pred;
    Childs[index]->remove(pred);
  }
  else if(Childs[index+1]->currNoOfKeys >= t)
  {
    int succ=getSuccessor(index);
    keys[index]=succ;
    Childs[index+1]->remove(succ);
  }
  //Else deleting key from left or right child will result into 
  //lesser number of keys than required therefore we need to merge the left
  // and right childs and recursively delete the required key
  else 
  {
    merge(index);
    Childs[index]->remove(key);
  }

}

int BTreeNode::getPredecessor(int index)
{
  BTreeNode *curr=Childs[index];
  while(!curr->leaf)//while it is not leaf
   curr=curr->Childs[curr->currNoOfKeys];
  return curr->keys[curr->currNoOfKeys-1]; 
}

int BTreeNode::getSuccessor(int index)
{
  BTreeNode *curr=Childs[index+1];
  while(!curr->leaf)//while it is not leaf
   curr=curr->Childs[0];
  return curr->keys[0]; 
}

//It tries to fill the key-deficient Childs[index] which has < (t-1) keys 
void BTreeNode::fill(int index)
{
  //If previous child has more than t-1 keys borrow from it
  if(index!=0 && Childs[index-1]->currNoOfKeys >= t)
   borrowFromPrev(index);
  //If next child has more than t-1 keys borrow from it
  else if(index!=currNoOfKeys && Childs[index+1]->currNoOfKeys>=t)
   borrowFromNext(index);
  //Merge Childs[index] with the next child if Childs[index] is not 
  //the last child 
  //Else
  //Merge the Childs[index-1] and Childs[index]
  else
  {
    if(index!=currNoOfKeys)
     merge(index);
    else
     merge(index-1); 
  }
   
}

void BTreeNode::borrowFromPrev(int index)
{
  BTreeNode *child=Childs[index];
  BTreeNode *sibling=Childs[index-1];

  //Make room from from in child
  for(int i=child->currNoOfKeys-1;i>=0;--i)
   child->keys[i+1]=child->keys[i];

  //If Child is not leaf it must contains children
  if(!child->leaf)
  {
    for(int i=child->currNoOfKeys;i>=0;--i)
     child->Childs[i+1]=child->Childs[i];
  } 

  //Move a key from this node to make first key of child
  child->keys[0]=keys[index-1];

  //If sibling is not leaf move the last child to make the first 
  //child of child node
  if(!child->leaf) 
   child->Childs[0]=sibling->Childs[sibling->currNoOfKeys];

  //Set the Keys[index-1]  to the last key of sibling
  keys[index-1]=sibling->keys[sibling->currNoOfKeys-1];

  //Reduce the number of keys in sibling  by 1 and 
  //Increase the number of keys in child by 1
  child->currNoOfKeys+=1;
  sibling->currNoOfKeys-=1;
  
}

void BTreeNode::borrowFromNext(int index)
{
  BTreeNode *child=Childs[index];
  BTreeNode *sibling=Childs[index+1];

  //Move a key from this node to make the last key of child
  child->keys[child->currNoOfKeys]=keys[index]; 

  //If the child OR sibling node is not leaf move first child 
  //of child node to make the last child of sibling
  if(!(child->leaf))
   child->Childs[(child->currNoOfKeys)+1]=sibling->Childs[0];

  //Move first key of sibling to parent
  keys[index]=sibling->keys[0];

  //move all keys of sibling forward by 1
  for(int i=1;i<sibling->currNoOfKeys;++i)
   sibling->keys[i-1]=sibling->keys[i];

  //If sibling is not leaf move the child of sibling forward by 1
  if(!sibling!=leaf)
  {
   for(int i=1;i<=sibling->currNoOfKeys;++i)
    sibling->Childs[i-1]=sibling->Childs[i];
  }

  //Reduce the number of keys in sibling  by 1 and 
  //Increase the number of keys in child by 1
  child->currNoOfKeys+=1;
  sibling->currNoOfKeys-=1;

}

void BTreeNode::merge(int index)
{
  BTreeNode *child=Childs[index];
  BTreeNode *sibling=Childs[index+1];
  
  //Move the key from this node to child node[which contain t-1 keys]
  child->keys[t-1]=keys[index];

  //Move keys from sibling to child node
  for(int i=0;i<sibling->currNoOfKeys;++i)
   child->keys[t+i]=sibling->keys[i];

  //If child node is not leaf move child of sibling to child of child node
  if(!(child->leaf))
  {
    for(int i=0;i<=sibling->currNoOfKeys;++i)
     child->Childs[t+i]=sibling->Childs[i];
  } 

  //Move the keys of parent backward by 1 from 'index'
  for(int i=index+1;i<currNoOfKeys;++i)
   keys[i-1]=keys[i];

  //Move the child pointers of current node one step before after (index+1)
  for(int i=index+2;i<=currNoOfKeys;++i)
   Childs[i-1]=Childs[i];

  child->currNoOfKeys += sibling->currNoOfKeys+1;
  currNoOfKeys--;
  delete(sibling);
 
}

void BTree::insert(int key)
{
  if(root==NULL)
  {
    root=new BTreeNode(t,true);
    root->keys[0]=key;
    root->currNoOfKeys=1;
  }
  else
  {
    if(root->currNoOfKeys == 2*t-1)//root node is full
    {
      //Create a new node
      //make it a parent node
      //split the root node
      BTreeNode *s=new BTreeNode(t,false);
      s->Childs[0]=root;

      // split the child of s which is at 0 in Childs[] array
      //Which will put one key to the s node
      s->splitChild(0,root);
      
      //To determine in which child the key is going 
      //to be inserted
      int i=0;
      if(s->keys[0]<key)
       ++i;
      s->Childs[i]->insertNonFull(key);

      root=s;
    }
    else
     root->insertNonFull(key);
  }
}

void BTreeNode::insertNonFull(int key)
{
  int i=currNoOfKeys-1;
  if(leaf==true)
  {
    while(i>=0 && keys[i]>key)
    {
      keys[i+1]=keys[i];
      --i;
    }
    keys[i+1]=key;
    currNoOfKeys+=1;
  }
  else //node is not leaf
  {
    while (i>=0 && keys[i]>key)
     --i;

    //If the child in which the key is supposed to be inserted if full 
    //we slit it 
    if(Childs[i+1]->currNoOfKeys == 2*t-1)
    {
      splitChild(i+1,Childs[i+1]);
      //To determine in which child the key is going 
      //to be inserted
      if(keys[i+1]<key)
       ++i;
    }
    Childs[i+1]->insertNonFull(key); 
  }
}

void BTreeNode::splitChild(int i,BTreeNode *y)
{
  //Create a new Node
  BTreeNode *z=new BTreeNode(y->t,y->leaf);
  z->currNoOfKeys=t-1;//New node will contain t-1 keys
  
  //Copy last (t-1) keys to y to z
  for(int j=0;j<t-1;++j)
   z->keys[j]=y->keys[j+t];

  //If y is not leaf move last t child of y to z 
  if(y->leaf==false)
  {
    for(int j=0;j<t;++j)
     z->Childs[j]=y->Childs[j+t];
  }

  //REMEMBER : 
  //y and z will contain t-1 keys each and one key will bw moved up
  y->currNoOfKeys=t-1;

  //Create space for new child in this node
  for(int j=currNoOfKeys;j>=i+1;--j)
   Childs[j+1]=Childs[j];

  //Link the new child to the this node
  Childs[i+1]=z;

  //A key of y will move to this node 
  //Find location of new key and move all greater key one step forward
  for(int j=currNoOfKeys-1;j>=i;--j)
   keys[j+1]=keys[j];
 
  //Copy the middle key of y to this node
  keys[i]=y->keys[t-1];
  //Increase the count of total keys in this node
  currNoOfKeys+=1;
}

void BTreeNode::traverse()
{
  int i;
  for(i=0;i<currNoOfKeys;++i)
  {
    if(leaf==false)
     Childs[i]->traverse();
    cout<<keys[i]<<" "; 
  }
  //Print the subtree rooted with last child
  if(leaf==false)
   Childs[i]->traverse();
}

BTreeNode* BTreeNode::search(int key)
{
  int i=0;
  while(i<currNoOfKeys && keys[i]<key)
   ++i;
  if(keys[i]==key)
   return this;
  if(leaf)
   return NULL;
  return Childs[i]->search(key);   
}

void BTree::remove(int key)
{
  if(root==NULL)
  {
    cout<<"\nTree is empty!";
    return;
  } 
  root->remove(key);
  if(root->currNoOfKeys==0) //If root node contains zero element
  {
    BTreeNode *temp=root;
    if(root->leaf==true)//is root is leaf initialise root as NULL
     root=NULL;
    else//Else set first child of root as the root
     root=root->Childs[0];
    delete temp;  
  }
 // return;
}

int main()
{
  BTree t(3);//Minimum degree =3

  t.insert(1);
  t.insert(2);
  t.insert(3);
  t.insert(5);
  t.insert(6);
  t.insert(8);
  t.insert(11);
  t.insert(19);
  t.insert(21);
  t.insert(23);
  t.insert(29);
  t.insert(211);
  t.insert(121);
  t.insert(51);
  
  cout<<"\nTree Traversal :";
  t.traverse();

  t.remove(1);
  cout<<"\nAfter removing 1 Tree Traversal : ";
  t.traverse();

  t.remove(19);
  cout << "\nAfter removing 19 Tree Traversal : ";
  t.traverse();

  t.remove(211);
  cout << "\nAfter removing 211 Tree Traversal : ";
  t.traverse();

  t.remove(5);
  cout << "\nAfter removing 5 Tree Traversal : ";
  t.traverse();
  return 0;
}