#include<iostream>
#include<limits.h>

using namespace std;

class Stack
{
    private :
      int head=-1;
      int stack[5];
      int size=5;
    public :
      void push(int data);
      void pop();
      void traverse(); 
      bool isEmpty();
      int peek(); 
}obj;

void Stack::push(int data)
{
    if(head<size-1)
     stack[++head]=data;
    else
    {
        cout<<"STACK OVERFLOW!";
    }
}
bool Stack::isEmpty()
{
  if(head==-1)
   return true;
  return false; 
}
void Stack::pop()
{
    if(isEmpty())
      cout<<"STACK UNDERFLOW!";
    else
    {
        cout<<"\nDeleted Element : "<<stack[head];
        --head;
    }  
}
int Stack::peek()
{
    if(head==-1)
     return INT_MIN;
    return stack[head]; 
}

void Stack::traverse()
{
    if(isEmpty())
     cout<<"\nSTACK UNDERFLOW!";
    else
    {
      for(int i=head;i>=0;--i)
       cout<<stack[i]<<", "; 
    }
}

int main()
{
    int choosenOpt;
    char ans;
    int data;

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
             obj.push(data);
             break;  
         case 2:
             obj.pop();
             break;
         case 3:
             cout<<"\nTop Element : "<<obj.peek();
             break;
         case 4:
              obj.traverse();
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