/*



*/
#include<iostream>

using namespace std;

void swap(int *num1,int *num2)
{
  int temp=*num1;
  *num1=*num2;
  *num2=temp;
}

int partition(int array[],int start,int end)
{
 int pivot=array[end];//assuming pivot as the last element of the array
 int pIndex=start;
 for(int j=start;j<=(end-1);++j)
 {
   if(array[j]<=pivot) // making all the elements lesser than pivot to the left of the pivot 
                       //and larger elements to the right of the  pivot
   {
    swap(&array[j],&array[pIndex]);
    pIndex++;
   }
 }
 swap(&array[end],&array[pIndex]);
 return pIndex;
}
void quickSort(int array[],int start,int end)
{
 if(start<end)
 {
  int pIndex=partition(array,start,end);
  quickSort(array,start,pIndex-1);
  quickSort(array,pIndex+1,end);
 }
}
void display(int array[],int size)
{
  for(int i=0;i<size;++i)
   cout<<array[i]<<", ";
}
int main()
{ 
   int array[10]={1,6,27,3,7,5,19,10,13,0};
   const int size=sizeof(array)/sizeof(array[0]);
   cout<<"\nBefore sorting : ";
   display(array,size);
   quickSort(array,0,size-1);
   cout<<"\nAfter sorting : ";
   display(array,size);
   return 0;  
}