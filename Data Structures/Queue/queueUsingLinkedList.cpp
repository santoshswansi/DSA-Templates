
#include<iostream>
#include<conio.h>

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

void enqueue(int data,Node **front,Node **rear)
{
  Node *newNode=getNode(data);
  if(newNode==NULL)
  {
    cout<<"\nQUEUE OVERFLOW";
    return;
  } 
  if(*front==NULL)
  {
      *front=newNode;
      *rear=newNode;
  }
  else
  {
      (*rear)->next=newNode;
      *rear=newNode;
  }
}

void dequeue(Node **front,Node **rear)
{
  if(*front==NULL)
   cout<<"QUEUE UNDERFLOW";
  else if ((*front)->next==NULL)
  {
     cout<<"\nDeleted element : "<<(*front)->data;
     free(*front);
     *front=NULL;
     *rear=NULL; 
  }
  else
  {
     Node *temp=*front;
     *front=(*front)->next;
     cout<<"\nDeleted element : "<<temp->data;
     free(temp); 
  } 
}

void traverse(Node *front)
{
  if(front==NULL)
   cout<<"\nNo Element!";
  else
  {
    while(front!=NULL)
    {
        cout<<front->data<<", ";
        front=front->next;
    }
  }
}

bool isEmpty(Node *front)
{
    if(front==NULL)
     return true;
  return false;
}

int main()
{
    int choosenOpt;
    char ans;
    int data;
    
    Node *front=NULL;
    Node *rear=NULL;

    do{      
       cout<<"\nChoose one :-";
       cout<<"\n1.Enqueue";
       cout<<"\n2.Dequeue";
       cout<<"\n3.IS EMPTY";
       cout<<"\n4.Traverse\n";
       cin>>choosenOpt;
       switch(choosenOpt)
       {
         case 1:
             cout<<"\nEnter the item : ";
             cin>>data;
             enqueue(data,&front,&rear);
             break;  
         case 2:
             dequeue(&front,&rear);
             break;
         case 3:
             if(isEmpty(front))
              cout<<"\nQueue is empty!";
             else
              cout<<"\nQueue is not empty!";
             break;
         case 4:
              traverse(front);
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