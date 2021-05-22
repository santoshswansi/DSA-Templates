#include<iostream>
#include<unordered_map>

using namespace std;
#define CHAR_SIZE 26

struct TrieNode
{
  bool isLeaf;//True when it is a leaf node(meaning a possible word upto here)
  unordered_map<char,TrieNode*> map;   
};

TrieNode* getTrieNode()
{
  TrieNode *node=new TrieNode;
  node->isLeaf=false;
  return node;  
}

void insert(TrieNode* &head,char str[])
{
  if(head==nullptr)
   head=getTrieNode();
  TrieNode *curr=head;
  while(*str) //while character of the string exist
  {
    //If memory not allocated, allocate it
    if (curr->map.find(*str) == curr->map.end())
     curr->map[*str]=getTrieNode();
    curr=curr->map[*str];//move to next node
    str+=1;//increase the string memory address to next char 
  } 
  curr->isLeaf=true;//mark it a leaf node(consider it a word) 
}

bool search(TrieNode *head,char str[])
{
  if(head==nullptr)//Trie is empty
   return false;   
  while(*str)
  {
    head=head->map[*str];//move to next node
    if(head==nullptr)
     return false;
    str++; 
  }
  //after reaching end of the char of the word check whether it is 
  //marked as leaf or not (OR VALID word or not)
  return head->isLeaf;
}

bool hasChildren(TrieNode *curr)
{
  for(auto it:curr->map)
   if(it.second!=nullptr)
    return true;
  return false;  
}

bool deletion(TrieNode **curr,char str[])
{
  if(*curr==nullptr)
   return false;
  if(*str)//If we have not reached end of the character of the string
  {
    //recur for the node corresponding to next character in the string 
    //& if returns true ,delete current node(if it is non-leaf)  
    if((*curr)!=nullptr && (*curr)->map.find(*str)!= (*curr)->map.end()
       && deletion(&((*curr)->map[*str]),str+1) && (*curr)->isLeaf==false)
    {
      if(!hasChildren(*curr))//no children 
      {
        free(*curr);
        *curr=NULL;
        return true;  //deleted
      }
      else
      {
        return false; //not deleted
      }
    }
  }

  //If we reached end of the character of the string
  if (*str == '\0' && (*curr)->isLeaf)
  {
      if (!hasChildren(*curr)) //no children
      {
          free(*curr);
          *curr = NULL;
          return true; //deleted
      }
      else //if current node is leaf and have children
      {
          (*curr)->isLeaf = 0; //mark it non-leaf(not a word)
          return false;        //do not delete its parent node
      }
  }
  return false;
}

int main()
{
 TrieNode *head=getTrieNode();

 char str[]="hello";
 insert(head,str);
 printf("\nsearch(hello) : %d",search(head,str));
 char str1[]="helloworld";
 insert(head,str1);
 char str2[]="hell";
 insert(head,str2);
 char str3[]="h";
 insert(head,str3);

 printf("\nsearch(hell) : %d", search(head, str2));
 printf("\nsearch(h) : %d", search(head,str3));
 printf("\nsearch(helloworld) : %d", search(head,str1));

 deletion(&head, str3);
 printf("\nsearch(h) : %d", search(head, str3));

 deletion(&head, str1);
 printf("\nsearch(helloworld) : %d", search(head, str1));
 deletion(&head, str2);
 deletion(&head, str);
 if(head==nullptr)
  cout<<"\nTrie empty!!";

 printf("\nsearch(helloworld) : %d", search(head, str1));
 return 0;  
}