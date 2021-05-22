//Implementation of hashing using separate chaining
//with the use of linked list
#include<iostream>
using namespace std;

struct Node
{
  int key;
  Node *next;  
};

Node* newNode(int key)
{
  Node *node=new Node;
  node->key=key;
  node->next=NULL;  
  return node;
}

class Hash
{
  int totBuckets; //total number of buckets
  Node* buckets[];//an array of addresses to the linked list(separate chain)
 
 public :

  Hash(int totbuckets);
  void insert(int key);
  int hashFunction(int key);
  Node* search(int key);
  void remove(int key);
};

int Hash::hashFunction(int key)
{
  int index=key%totBuckets;
  return index;  
}

Hash::Hash(int totbuckets)
{
 totBuckets=totbuckets;   
 for(int i=0;i<totBuckets;++i)
  buckets[i]=NULL;
}

void Hash::insert(int key)
{
  int index=hashFunction(key);
  Node *node=newNode(key);
  if(buckets[index]==NULL)
   buckets[index]=node;
  else
  {
    Node *temp=buckets[index];  
    while(temp->next!=NULL) 
    {
      temp=temp->next;  
    }  
    temp->next=node;
  }
}

Node* Hash::search(int key)
{
  int index=hashFunction(key); //find the hashed value

  if(buckets[index]==NULL)//if bucket at hashed value is null return false
   return NULL;
  else
  {
    //Else search in the separate chain for the key
    Node *temp=buckets[index];  
    while(temp!=NULL)
    {
      if(temp->key==key)
       return temp;
      temp=temp->next;   
    }   
    return NULL;
  }
}

void Hash::remove(int key)
{
  Node *temp=search(key);
  int index=hashFunction(key);
  if(temp==NULL)
   cout<<"\nKey not present!";
  else
  {
    Node *bucket=buckets[index];
    if(bucket==temp)
      buckets[index] = temp->next;
    else
    {
      while(bucket->next!=temp)
        bucket=bucket->next;  
      bucket->next=temp->next;  
    }  
    free(temp);
  }   
}

int main()
{
  Hash hash(7);

  hash.insert(18);
  hash.insert(8);
  hash.insert(1);
  hash.insert(25);
  hash.insert(67);
  hash.insert(11);
  hash.insert(121);
  hash.insert(19);
  hash.insert(45);
  hash.insert(18);
  hash.insert(6);
  if(hash.search(18)!=NULL)
   cout<<"\n18 is present!";
  else 
   cout<<"\n18 is not present!";

  if(hash.search(20) != NULL)
      cout<<"\n20 is present!";
  else
      cout<<"\n20 is not present!";

  if(hash.search(121) != NULL)
      cout<<"\n121 is present!";
  else
      cout<<"\n121 is not present!";
 
  hash.remove(121);
  cout<<"\nAfter removing 121 :";
  if(hash.search(121) != NULL)
      cout<<"\n121 is present!";
  else
      cout<<"\n121 is not present!";
  return 0;
}