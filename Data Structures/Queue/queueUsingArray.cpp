#include<iostream>

int SIZE=5;

using namespace std;

void enqueue(int data,int &front,int &rear,int array[])
{
 if(rear==-1)
 {
    array[++front]=data;
    ++rear;
 }
 else if(rear<(SIZE-1))
 {
    array[++rear]=data;
 }
 else
 {
   cout<<"\nQUEUE OVERFLOW!";
 }
}
void dequeue(int &front,int &rear,int array[])
{
  if(front>rear || front==-1)
  {
    cout<<"\nNo Element!";  
  }
  else
  {
    cout<<"\nDeleted Element : "<<array[front];
    front++;
  }
}
void traverse(int front,int rear,int array[])
{
    if(front>rear || front==-1)
     cout<<"No Element!";
    else
    {
      for(int i=front;i<=rear;++i)
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