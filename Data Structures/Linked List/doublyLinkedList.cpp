#include<iostream>

using namespace std;

struct Node
{
   int data;
   Node *left;
   Node *right; 
};
Node* getNode(int data)
{
   Node *newNode=new Node;
   newNode->data=data;
   newNode->left=NULL;
   newNode->right=NULL;
   return newNode; 
}
void pushFront(int data,Node **head,Node **rear)
{
   Node *newNode=getNode(data);  
   if(*head==NULL)
   {
       *head=newNode;
       *rear=newNode;
   }
   else
   {
       newNode->right=(*head);
       (*head)->left=newNode;
       *head=newNode;
   }
}

void pushEnd(int data,Node **head,Node **rear)
{
   Node *newNode=getNode(data);  
   if(*head==NULL)
   {
       *head=newNode;
       *rear=newNode;
   }
   else
   {
       newNode->left=(*rear);
       (*rear)->right=newNode;
       *rear=newNode;
   }
}
//data will be inserted after first occurrence of the element(pointed by after pointer)
void pushAfter(int data,Node **rear,Node *after) 
{ 
  if(after==NULL)
  {
    cout<<"\nElement no present!";
    return;  
  }    
  Node *newNode=getNode(data);  
  if(after==(*rear)) //So that it can be used to insert element at last i.e. after last element
  {
    (*rear)->right=newNode;
    *rear=newNode;
  }
  else
  {
   Node *next=after->right; 
   after->right=newNode;
   newNode->left=after;
   newNode->right=next;
   next->left=newNode;   
  }
}
void popFront(Node **head,Node **rear)
{
  if(*head==NULL)
   cout<<"\nNo element to delete";
  else
  {
   if((*head)->right==NULL)
   {
     free(*head);
     *head=NULL;
     *rear=NULL;       
   }   
   else
   {
     Node *temp=(*head);
     free(temp);
     *head=(*head)->right;
   } 
  }
}
void popEnd(Node **head,Node **rear)
{
  if(*head==NULL)
   cout<<"\nNo element to delete";
  else
  {
   if((*head)->right==NULL)
   {
     free(*head);
     *head=NULL;
     *rear=NULL;       
   }   
   else
   {
     Node *temp=(*rear);
     *rear=(*rear)->left;
     (*rear)->right=NULL;
     free(temp);
   } 
  }
}
void popAt(Node **head,Node **rear,Node *at) //first occurrence of the element will be deleted
{
  if(at==NULL)
  {
    cout<<"\nElement no present!";
    return;  
  }
  Node *cloneHead=(*head);
  while(cloneHead->right!=at)
  {
    cloneHead=cloneHead->right;
  }
  if((*head)->right==NULL) //this means there's only one element which is to be deleted 
  {
   free(*head);
   *head=NULL;
   *rear=NULL; 
  }
  else
  {
    cloneHead->right=at->right;
    free(at);  
  }
}
Node* search(int data,Node *head)
{
  while(head!=NULL)
  {
    if(head->data==data)
       return head; 
    head=head->right;   
  }
  return NULL;
}
void traverse(Node *head)
{
  if(head==NULL)
  {
    cout<<"\nNo element!";
    return;  
  }  
  while(head!=NULL)
  {
    cout<<head->data<<", ";
    head=head->right;  
  }  
}
int main()
{
 int choosenOpt;
 char ans;
 int data;
 int num;
 Node *head=NULL;
 Node *rear=NULL;
 Node *at;
 Node *after;
 do
 {
    cout<<"\nEnter your choice :-";
    cout<<"\n1.PUSH FRONT";
    cout<<"\n2.PUSH END";
    cout<<"\n3.PUSH AFTER";
    cout<<"\n4.POP FRONT";
    cout<<"\n5.POP END";
    cout<<"\n6.POP AT";
    cout<<"\n7.TRAVERSE\n";
    cin>>choosenOpt;

    switch (choosenOpt)
    {
     case 1:
        cout<<"\nEnter the data : ";
        cin>>data;
        pushFront(data,&head,&rear);
        break;
     case 2:
        cout<<"\nEnter the data : ";
        cin>>data;
        pushEnd(data,&head,&rear);
        break;
     case 3:
        cout<<"After which data : ";
        cin>>num;
        after=search(num,head);
        cout<<"\nEnter the data : ";
        cin>>data;
        pushAfter(data,&rear,after);
        break; 
     case 4 :
         popFront(&head,&rear);
         break;
     case 5 :
         popEnd(&head,&rear);
         break;
     case 6 :
         cout<<"\nEnter the data that you want to delete : ";
         cin>>data;
         at=search(data,head);
         popAt(&head,&rear,at);
         break;
     case 7 : 
          cout<<"Elements are : ";
          traverse(head); 
          break;           
     default:
          cout<<"\nWrong Option!";
          break;
    }
    cout<<"\nDo you want to continue (y/n)?";
    cin>>ans;
 } while (ans=='y' || ans=='Y');
 
 return 0; 
}