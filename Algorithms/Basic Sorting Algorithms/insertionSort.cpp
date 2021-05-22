/*
 Time Complexity : O(n)
 In-Place : YES
 Stable : YES(Does not change the relative ordering of elements of equal keys)
*/
/*
 Insertion sort tries to fix the each element in correct place in the sorted sub-array
*/
#include<iostream>

using namespace std;

void insertionSort(int array[],int size)
{
 int key;
 int i;
 int j;   
 for(i=1;i<size;++i) //first element is already sorted
 {
   key=array[i];
   j=i-1;
   while(key<array[j] &&  j>=0)
   {
     array[j+1]=array[j];
     --j;
   }
   array[j+1]=key;
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
   insertionSort(array,size);
   cout<<"\nAfter sorting : ";
   display(array,size);
   return 0; 
}