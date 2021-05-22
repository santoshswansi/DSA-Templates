/*
 Worst Case Time Complexity : O(n*n)
                              when array is reverse sorted
 Best Case Time Complexity : O(n)
                             when array is already sorted 
 Auxiliary space : O(1)
 Sorting In_Place : YES (Almost no extra memory is required ,hence in place)
 Stable: YES

*/
#include<iostream>
#include<conio.h>

using namespace std;

void swap(int *num1,int *num2)
{
    int temp;
    temp=*num1;
    *num1=*num2;
    *num2=temp;
}

void bubbleSort(int array[],int size)
{
  bool isSwapped;  
 for(int i=0;i<size-1;++i)
 {
  isSwapped=false;    
  for(int j=0;j<size-i-1;++j)
  {
      if(array[j+1]<array[j])
      {
        swap(&array[j],&array[j+1]);
        isSwapped=true;
      }
  }
  //if no swapping occurred elements are already sorted
  if(isSwapped==false)
   break;
 }
}
void display(int array[],int size)
{
 for(int i=0;i<size;++i)
  cout<<array[i]<<", ";
}
int main()
{
    
  int array[10]={4,51,16,8,19,1,8,4,1,0};
  const int size=sizeof(array)/sizeof(array[0]);
  cout<<"\nBefore sorting : ";
  display(array,size); 
  bubbleSort(array,size);
  cout<<"\nAfter sorting : ";
  display(array,size); 
  return 0;
}