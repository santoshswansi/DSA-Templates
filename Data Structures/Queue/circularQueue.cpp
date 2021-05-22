#include<iostream>

using namespace  std;

int SIZE=5; //size of the queue
int currSize=0; //current size

void enqueue(int data,int &front,int &rear,int array[])
{
  if(currSize==SIZE)
   cout<<"\nQUEUE OVERFLOW!";
  else if(front==-1)
  {
    array[++front]=data;
    ++currSize;
    ++rear;
  }
  else if(currSize<SIZE)
  {
    rear=(rear+1)%SIZE;  
    array[rear]=data;  
    ++currSize;  
  }
}

void dequeue(int &front,int &rear,int array[])
{
  if(currSize==0)
    cout<<"\nQUEUE UNDERFLOW!";
  else if(front==rear)
  {
    cout<<"\nDeleted Element : "<<array[front];
    front=-1;
    rear=-1;
  }  
  else
  {
     front=(front+1)%SIZE;
     cout<<"\nDeleted Element : "<<array[front];
     --currSize; 
  }  
}

void traverse(int front,int rear,int array[])
{
   int i;
   if(currSize==0)
      cout<<"\nQUEUE UNDERFLOW!";
   else
   {
      for(i=front;i!=rear;i=(i+1)%SIZE)
      {
         cout<<array[i]<<", ";      
      }     
      cout<<array[i]<<", ";
   }
}
int main()
{
    int choosenOpt;
    char ans;
    int data;
    int rear=-1;
    int front=-1;
    int array[5];

    do
    {      
       cout<<"\nChoose one option:-";
       cout<<"\n1.Enqueue";
       cout<<"\n2.Dequeue";
       cout<<"\n3.Traverse\n";
       cin>>choosenOpt;

       switch(choosenOpt)
       {
         case 1 :
             cout<<"\nEnter the item : ";
             cin>>data;
             enqueue(data,front,rear,array);
             break;  
         case 2 :
             dequeue(front,rear,array);
             break;
         case 3 :
              traverse(front,rear,array);
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