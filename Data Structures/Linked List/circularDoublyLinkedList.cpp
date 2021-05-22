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
void pushBeg(int data,Node **head)
{
  Node *newNode=getNode(data);
  if(*head==NULL)
  {  
    newNode->left=newNode;
    newNode->right=newNode;
    *head=newNode;
  }
  else
  {
    Node *temp=(*head)->left;
    newNode->right=*head;
    (*head)->left=newNode;
    newNode->left=temp;
    temp->right=newNode;
    *head=newNode;
  } 
}

void pushEnd(int data,Node **head)
{
  Node *newNode=getNode(data);
  if(*head==NULL)
  {
    newNode->left=newNode;
    newNode->right=newNode;
    *head=newNode;
  }
  else
  {
    Node *temp=(*head)->left;
    newNode->right=*head;
    (*head)->left=newNode;
    newNode->left=temp;
    temp->right=newNode;
  } 
}

void popBeg(Node **head)
{
 if(*head==NULL)
 {
   cout<<"No Element!";
 }
 else if((*head)->right==(*head))
 {
   free(*head);
   *head=NULL; 
 } 
 else
 {
   Node *temp=(*head)->left;
   temp->right=(*head)->right;
   free(*head);
   *head=temp->right;  
   (*head)->left=temp; 
 }
}

void popEnd(Node **head)
{
 if(*head==NULL)
  cout<<"No Element!";
 else if((*head)->right==(*head))
 {
   free(*head);
   *head=NULL; 
 } 
 else
 {
   Node *temp=(*head)->left;
   (temp->left)->right=*head;
   (*head)->left=temp->left;
   free(temp);   
 }
}
void forwardTraverse(Node *head)
{
  Node *cloneHead=head;
  if(cloneHead==NULL)
   cout<<"No Element!";
  else
  {
      while(cloneHead->right!=head)
      {
          cout<<cloneHead->data<<", ";
          cloneHead=cloneHead->right;
      }
      cout<<cloneHead->data<<", ";
  }
}
void backwardTraverse(Node *head)
{
  if(head==NULL)
   cout<<"No Element!";
  else
  {
      Node *temp=head->left;
      while(temp->left!=(head->left))
      {
          cout<<temp->data<<", ";
          temp=temp->left;
      }
      cout<<temp->data<<", ";
  }
}

Node* search(int data,Node *head)
{
  while(head->right!=head)
  {
      if(head->data==data)
       return head;
  }
  return head;
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
     cout<<"\n1.PUSH BEGGINING";
     cout<<"\n2.PUSH END";
     cout<<"\n3.POP BEGGINING";
     cout<<"\n4.POP END";
     cout<<"\n5.SEARCH";
     cout<<"\n6.FORWARD TRAVERSE"; 
     cout<<"\n7.BACKWARD TRAVERSE\n";
     cin>>choosenOpt;
     switch(choosenOpt)
     {
        case 1 :
            cout<<"\nEnter data : ";
            cin>>data;
            pushBeg(data,&head);
            break;
            
        case 2 :
            cout<<"\nEnter data : ";
            cin>>data;
            pushEnd(data,&head);
            break;
        case 3 : 
            popBeg(&head);
            break;
        case 4 : 
            popEnd(&head);
            break;  
        case 5 : 
            cout<<"Which data ? ";
            cin>>data;
            if(search(data,head)!=NULL)
             cout<<"\nFound !";
            else
             cout<<"\nNot Found!";
            break;
        case 6 :
             cout<<"\nElements are : ";
             forwardTraverse(head);
             break;
        case 7 :
             cout<<"\nElements are : ";
             backwardTraverse(head);
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