//Implementation of basic operations on singly linked list
#include<iostream>
#include<conio.h>

using namespace std;


//structure Node 
struct Node
{
 int data;
 Node *next;
};

Node *previousNode;

Node* getNode(int data)
{
  Node *newNode=new Node;
  newNode->data=data;
  newNode->next=NULL;
  return newNode;
}
 
void push(int data,Node **head)
{
  Node *newNode=getNode(data);
  if(*head==NULL)
  {
   previousNode=newNode;
   *head=newNode;
  }
  else
  {
    previousNode->next=newNode;
    previousNode=newNode;
  } 
}

void traverse(Node *head)
{
  if(head==NULL)
  {
    cout<<"No elements";
    return;
  }
  while(head!=NULL)
  {
    cout<<head->data<<", ";
    head=head->next;
  } 
}
Node* search(int data,Node *head)
{
  while(head!=NULL)
  {
    if(head->data==data)
     return head;
    head=head->next; 
  }
  return NULL;
} 
void pop(Node **head,Node *toDelete)
{  
  Node *prevNode=*head;
  if(toDelete==NULL)
  {
    cout<<"\nElement not present";
    return;
  }
  while(prevNode!=NULL)
  {
    if(prevNode->next!=toDelete)
     prevNode=prevNode->next;
    else
     break; 
  }
  if(*head==toDelete)
  {
    *head=toDelete->next;
  } 
  else if(toDelete->next==NULL)
  {
    prevNode->next=NULL;
  }
  else
  {
    prevNode->next=toDelete->next;
  }
}

int main()
{
    int choosenOpt;
    char ans;
    int data;
    
    Node *head=NULL;//head pointer will point to the head node
    Node *toDelete=NULL;
    do{      
       cout<<"\nChoose one :-";
       cout<<"\n1.push";
       cout<<"\n2.pop";
       cout<<"\n3.Traverse\n";
       cin>>choosenOpt;
       switch(choosenOpt)
       {
         case 1:
             cout<<"\nEnter the item : ";
             cin>>data;
             push(data,&head);
             break;  
         case 2:
             cout<<"\nEnter the element that you want to pop : ";
             cin>>data;
             toDelete=search(data,head);
             pop(&head,toDelete);
             break;
         case 3:
              traverse(head);
              break;
         default:
              cout<<"\nWrong input";
              break;         
       } 

      cout<<"\nDo you want to continue (y/n)?";
      cin>>ans;
    }while(ans=='y' || ans == 'Y');
  return 0;
}