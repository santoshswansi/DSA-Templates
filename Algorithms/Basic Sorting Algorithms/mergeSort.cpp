/*
 Time Complexity : O(nLogn)
 Auxiliary Space : O(n)
 Stable : YES
*/
#include<iostream>
#define SIZE(x) x

using namespace std;

void merge(int array[],int start,int middle,int end)
{
  int i;
  int j;
  int k=0;
  int lLength=middle-start+1; //length of left sub-array
  int rLength=end-middle;//length of right sub-array
  int leftArray[lLength];
  int rightArray[rLength];

  for(i=start;i<=middle;++i)
   leftArray[k++]=array[i];

  k=0;

  for(i=middle+1;i<=end;++i)
   rightArray[k++]=array[i]; 

  i=0;
  j=0;
  k=start; 

  while(i<lLength && j<rLength)
  {
      if(leftArray[i]>rightArray[j])
        array[k++]=rightArray[j++];
      else if(leftArray[i]<rightArray[j])
        array[k++]=leftArray[i++];
      else
      {
        array[k++]=leftArray[i++];
        array[k++]=rightArray[j++];
      }
      
  }
  while(i<lLength || j<rLength)
  {
    if(i<lLength)
      array[k++]=leftArray[i++]; 
    else
      array[k++]=rightArray[j++];
  }
}

int mergeSort(int array[],int start,int end)
{ 
  if(start<end)
  {
   int middle=(start + end)/2;
   mergeSort(array,start,middle);
   mergeSort(array,middle+1,end);
   merge(array,start,middle,end); 
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
   mergeSort(array,0,size-1);
   cout<<"\nAfter sorting : ";
   display(array,size);
   return 0;  
}