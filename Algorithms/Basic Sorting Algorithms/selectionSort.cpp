/*
 Time Complexity : O(n^2)
 Auxiliary Space : O(1)
*/
#include<iostream>

using namespace std;

void swap(int *num1,int *num2)
{
    int temp;
    temp=*num1;
    *num1=*num2;
    *num2=temp;
}

void selectionSort(int array[],int size)
{
  int i;
  int j;
  int minIndex;
  for(i=0;i<size-1;++i)
  {
   minIndex=i;   
   for(j=i+1;j<size;++j) 
   {
     if(array[minIndex]>array[j])
      minIndex=j;
   }
   if(minIndex!=i)
    swap(&array[minIndex],&array[i]);
  }
}
void display(int array[],int size)
{
 int i;
 for(i=0;i<size;++i)
 {
   cout<<array[i]<<", ";  
 }
}
int main()
{
 int array[10]={1,6,27,3,7,5,19,10,13,0};
   const int size=sizeof(array)/sizeof(array[0]);
   cout<<"\nBefore sorting : ";
   display(array,size);
   selectionSort(array,size);
   cout<<"\nAfter sorting : ";
   display(array,size);
   return 0; 
}