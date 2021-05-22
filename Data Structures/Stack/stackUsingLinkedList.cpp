#include<iostream>
#include<limits.h>

using namespace std;

struct Node
{
 int data;
 Node *next;
};

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
  if(newNode==NULL)
  {
    cout<<"\nSTACK OVERFLOW";
    return;
  } 
  else
  {
      newNode->next=(*head);
      *head=newNode;
  }
}
bool isEmpty(Node *head)
{
    if(head==NULL)
     return true;
    return false; 
}
void pop(Node **head)
{
  if(isEmpty(*head))
   cout<<"STACK UNDERFLOW";
  else
  {
    Node *temp=(*head)->next;
    cout<<"\nDeleted element : "<<(*head)->data;
    free(*head);
    *head=temp;
  } 
}

void traverse(Node *head)
{
  if(isEmpty(head))
   cout<<"\nSTACK UNDERFLOW!";
  else
  {
    while(head!=NULL)
    {
        cout<<head->data<<", ";
        head=head->next;
    }
  }
}

int peek(Node *head)
{
    if(isEmpty(head))
     return INT_MIN;
    return head->data; 
}

int main()
{
    int choosenOpt;
    char ans;
    int data;
    
    Node *head=NULL;

    do
    {      
       cout<<"\nChoose one :-";
       cout<<"\n1.Push";
       cout<<"\n2.Pop";
       cout<<"\n3.Peek";
       cout<<"\n4.Traverse\n";
       cin>>choosenOpt;
       switch(choosenOpt)
       {
         case 1:
             cout<<"\nEnter the item : ";
             cin>>data;
             push(data,&head);
             break;  
         case 2:
             pop(&head);
             break;
         case 3:
             cout<<"\nTop Element : "<<peek(head);
             break;
         case 4:
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