#include<iostream>

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
void pushBeg(int data,Node **rear)
{
    Node *newNode=getNode(data);
    if(*rear == NULL)
    {
      *rear=newNode; 
      (*rear)->next=(*rear); 
    }
    else
    {
        Node *temp=(*rear)->next; // it will give the head node
        (*rear)->next=newNode;
        newNode->next=temp;
    } 
}
void pushEnd(int data ,Node **rear)
{
    Node *newNode=getNode(data);
    if(*rear==NULL)
    {
        *rear=newNode;
        (*rear)->next=(*rear);
    }
    else
    {
        Node *temp=(*rear)->next;
        (*rear)->next=newNode;
        newNode->next=temp;
        *rear=newNode;
    }
}
void popBeg(Node **rear)
{
    if(*rear==NULL)
    {
        cout<<"\nNo Element!";
    } 
    else if((*rear)->next==(*rear))
    {
      free(*rear);
      *rear=NULL;
    } 
    else
    {
        Node *temp=(*rear)->next;
        (*rear)->next=temp->next;
        free(temp);
        temp=NULL;
    }  
}
void popEnd(Node **rear)
{
    if(*rear==NULL)
    {
        cout<<"\nNo Element!";
    }   
    else if((*rear)->next==(*rear))
    {
      free(*rear);
      *rear=NULL;
    } 
    else
    {
        Node *temp=*rear;
        temp=temp->next;
        while(temp->next!=(*rear))
          temp=temp->next;
        temp->next=(*rear)->next;
        free(*rear);
        *rear=temp; 
    }  
}
void traverse(Node *rear)
{
  Node *cloneRear=rear;
  if(cloneRear==NULL)
   cout<<"No Element!";
  else
  {
    cloneRear=cloneRear->next;  //start printing from the first node
    while(cloneRear!=rear)
    {
        cout<<cloneRear->data<<", ";
        cloneRear=cloneRear->next;
    }
    cout<<cloneRear->data<<", "; // it will print last element
  }
}
Node* search(int data,Node *rear)
{
  if(rear!=NULL)
  {
    Node  *cloneRear=rear;
    cloneRear=cloneRear->next;
    while(cloneRear!=rear)
    {
       if(cloneRear->data==data) 
        return cloneRear;
       cloneRear=cloneRear->next; 
    }
    if(cloneRear->data==data)
     return cloneRear;
  }  
  return  NULL;
}
int main()
{
   int choosenOpt;
   char ans;
   int data;
   Node *rear=NULL;
   do
   {
     cout<<"\nChoose one :-";
     cout<<"\n1.PUSH BEGGINING";
     cout<<"\n2.PUSH END";
     cout<<"\n3.POP BEGGINING";
     cout<<"\n4.POP END";
     cout<<"\n5.SEARCH";
     cout<<"\n6.TRAVERSE\n"; 
     cin>>choosenOpt;
     switch(choosenOpt)
     {
        case 1 :
            cout<<"\nEnter data : ";
            cin>>data;
            pushBeg(data,&rear);
            break;
            
        case 2 :
            cout<<"\nEnter data : ";
            cin>>data;
            pushEnd(data,&rear);
            break;
        case 3 : 
            popBeg(&rear);
            break;
        case 4 : 
            popEnd(&rear);
            break;  
        case 5 : 
            cout<<"Which data ? ";
            cin>>data;
            if(search(data,rear)!=NULL)
             cout<<"\nFound !";
            else
             cout<<"\nNot Found!";
            break;
        case 6 :
             cout<<"\nElements are : ";
             traverse(rear);
             break;
        default :
             cout<<"\nWrong Option!";
             break;                       
     }
     cout<<"\nDo you want to continue ? (y/n) ";
     cin>>ans;
   } while (ans=='y' || ans=='Y');
   
  return 0;
}