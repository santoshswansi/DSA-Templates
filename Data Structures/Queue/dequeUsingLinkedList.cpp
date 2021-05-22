//IMPLEMENTATION OF DEQUE USING SINGLY LINKED LIST
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

class Deque
{
  private:
    Node *front;
    Node *rear;
    int currSize;

  public:
    Deque()
    {
        front=NULL;
        rear=NULL;
        currSize=0;
    }
    void pushFront(int data);
    void pushRear(int data);
    void popFront();
    void popRear();
    int size();
    void clear();
    bool isEmpty();
    int getRear();
    int getFront();
    void Traverse();
};

bool Deque::isEmpty()
{
    return front==NULL;
}

void Deque::clear()
{
    Node *temp=front;
    while(temp!=NULL)
    {
        Node *node=temp;
        temp=temp->next;
        free(node);
    }
    currSize=0;
    front=NULL;
    rear=NULL;
}

void Deque::pushFront(int data)
{
    Node *newNode=getNode(data);
    if(front==NULL)
    {
        front=newNode;
        rear=newNode;
    }
    else
    {
        newNode->next=front;
        front=newNode;
    }
    currSize++;
}
void Deque::pushRear(int data)
{
    Node *newNode=getNode(data);
    if(front==NULL)
    {
        front=newNode;
        rear=newNode;
    }
    else
    {
        rear->next=newNode;
        rear=newNode;
    }
    currSize++;
}

void Deque::popFront()
{
    if(isEmpty())
     cout<<"\nDEQUE UNDERFLOW!";
    else if(front->next==NULL)
    {
      cout<<"\nDeleted Element : "<<front->data;  
      free(front);
      front=NULL;
      rear=NULL;
      currSize--;
    } 
    else
    {
      Node *temp=front;
      front=front->next;
      cout<<"\nDeleted Element : "<<temp->data;
      free(temp);
      currSize--;
    }
}

void Deque::popRear()
{
    if(isEmpty())
     cout<<"\nDEQUE UNDERFLOW!";
    else if(front->next==NULL)
    {
      cout<<"\nDeleted Element : "<<front->data;  
      free(front);
      front=NULL;
      rear=NULL;
    } 
    else
    {
      Node *temp=front;
      while(temp->next!=rear)
       temp=temp->next;
      cout<<"\nDeleted Element : "<<rear->data;
      free(rear);
      rear=temp;
      rear->next=NULL;
      currSize--;
    }
}

int Deque::size()
{
    return currSize;
}

int Deque::getFront()
{
    if(front!=NULL)
     return front->data;
    return INT_MIN; 
}

//Here INT_MIN has been used as a garabage value
int Deque::getRear()
{
    if(rear!=NULL)
     return rear->data;
    return  INT_MIN; 
}

void Deque::Traverse()
{
    if(front==NULL)
     cout<<"\nDEQUE UNDERFLOW!";
    else
    {          
     Node *temp=front;
     while(temp!=NULL)
     {
         cout<<temp->data<<", ";
         temp=temp->next;
     }
    }
}

int main()
{
    int choosenOpt;
    char ans;
    int data;

    Deque obj;

    do
    {      
       cout<<"\nChoose one option:-";
       cout<<"\n1.Push Front";
       cout<<"\n2.Push Rear";
       cout<<"\n3.Pop Front";
       cout<<"\n4.Pop Rear";
       cout<<"\n5.Get Front ";
       cout<<"\n6.Get Rear";
       cout<<"\n7.Size";
       cout<<"\n8.Clear";
       cout<<"\n9.Traverse\n";
       cin>>choosenOpt;

       switch(choosenOpt)
       {
         case 1 :
             cout<<"\nEnter the data : ";
             cin>>data;
             obj.pushFront(data);
             break;  
         case 2 :
             cout<<"\nEnter the data : ";
             cin>>data;
             obj.pushRear(data);
             break;
         case 3 :
              obj.popFront();
              break;   
         case 4 :
              obj.popRear();
              break;
         case 5 :
              cout<<"Front Element : "<<obj.getFront();
              break;
         case 6 :
              cout<<"Rear Element : "<<obj.getRear();
              break; 
         case 7 :
              cout<<"Deque Size : "<<obj.size();
              break; 
         case 8 :
              obj.clear();
              break; 
         case 9 :
              cout<<"Elements are : ";
              obj.Traverse();
                break;         
         default :
              cout<<"\nWrong input";
              break;         
       } 

      cout<<"\nDo you want to continue (y/n) ? ";
      cin>>ans;
    }while(ans=='y' || ans == 'Y');
  return 0;
}