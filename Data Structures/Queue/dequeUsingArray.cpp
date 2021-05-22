#include<iostream>
#include<vector>
#include<limits.h>

using namespace std;

class Deque
{
  private :
   int currSize;
   int totalSize;
   int front;
   int rear;
   vector<int> dequeue;
  public : 
   Deque(int size)
   {
     currSize=0;
     currSize=0;
     front=-1;
     rear=-1;
     totalSize=size;
     dequeue.resize(totalSize);
   }
   void pushFront(int data);
   void pushRear(int data);
   void popFront();
   void popRear();
   int SIZE();
   int getFront();
   int getRear();
   void clear();
   bool isEmpty();
   bool isFull();
   void Traverse();
};

bool Deque::isEmpty()
{
    return front==-1;
}

bool Deque::isFull()
{
    return currSize==totalSize;
}

int Deque::SIZE()
{
    return currSize;
}

void Deque::clear()
{
    front=-1;
    rear=-1;
    currSize=0;
}

void Deque::Traverse()
{
    int i;
    if(isEmpty())
    {
     cout<<"\nDEQUE UNDERFLOW!";
     return;
    }
    for(i=front;i!=rear;i=(i+1)%totalSize)
     cout<<dequeue[i]<<", ";
    cout<<dequeue[i]<<", "; 
}

int Deque::getFront()
{
    if(front!=-1)
     return dequeue[front];
    return INT_MIN; 
}

int Deque::getRear()
{
    if(rear!=-1)
     return dequeue[rear];
    return INT_MIN; 
}
void Deque::pushFront(int data)
{
    if(isFull())
    {
        cout<<"\nDEQUE OVERFLOW!";
        return;
    }
    if(isEmpty())
    {
        front=0;
        rear=0;
    } 
    else if(front==0)
       front=totalSize-1;
    else
       front=(front-1);
   
    dequeue[front]=data;
    currSize++;
}

void Deque::pushRear(int data)
{
    if(isFull())
    {
        cout<<"\nDEQUE OVERFLOW!";
        return;
    }
    if(isEmpty())
    {
        front=0;
        rear=0;
    }    
    else if(rear==totalSize-1)
        rear=0;
    else
        rear=rear+1;

    dequeue[rear]=data;    
    currSize++;
}
void Deque::popFront()
{
    if(isEmpty())
    {
        cout<<"\nDEQUE UNDERFLOW!";
        return;
    }
    cout<<"\nDeleted Element : "<<dequeue[front];
    if(front==rear)
    {
        front=-1;
        rear=-1;
    }
    else 
    {
        if(front==totalSize-1)
         front=0;
        else 
         front=front+1;
    }
    currSize--;
}

void Deque::popRear()
{
    if(isEmpty())
    {
        cout<<"\nDEQUE UNDERFLOW!";
        return;
    }
    cout<<"\nDeleted Element : "<<dequeue[rear];
    if(front==rear)
    {
        front=-1;
        rear=-1;
    }
    else if(rear==0)
    {
        rear=totalSize-1;
    }
    else
    {
        rear=rear-1;
    } 
    currSize--;
}

int main()
{
    int choosenOpt;
    char ans;
    int data;

    Deque obj(5);

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
              cout<<"Deque Size : "<<obj.SIZE();
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