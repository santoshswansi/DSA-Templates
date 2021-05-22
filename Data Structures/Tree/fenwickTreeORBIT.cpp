#include<iostream>

using namespace std;

void updateBIT(int BITree[],int n,int index,int value)
{
  index+=1;
  //Traverse all ancestors and add 'value'
  while(index<=n)
  {
    BITree[index]+=value;
    index+=index&(-index);  //For getting the parent(IN UPDATE VIEW)
  }  
}

int* constructBIT(int array[],int n)
{
   int *BITree=new int[n+1];//Make BI Tree of size n+1
   //Initialise BI Tree with 0
   for(int i=1;i<=n;++i)
    BITree[i]=0;
   //Insert the element one by one to BI Tree
   for(int i=0;i<n;++i)
    updateBIT(BITree,n,i,array[i]);
   return BITree; 
}

int getSum(int BITree[],int index)
{
  index+=1;
  int sum = 0;

  //Traverse ancestors and sum their value to get the required sum
  while(index>0)
  {
    sum+=BITree[index];
    index-=index&(-index);  //To get parent(FOR getSum VIEW)
  }  
  return sum;
}

int main()
{
  int array[]={2,17,11,32,11,34,7,67,32,56};
  int size=sizeof(array)/sizeof(array[0]);
  int *BITree=constructBIT(array,size);
  int result=getSum(BITree,7);
  cout<<"\nSum of elements from index 0 to 7 is : "<<result;
  //index 5 to 9(RANGE SUM)
  result=getSum(BITree,9)-getSum(BITree,5-1);
  cout<<"\nSum of elements from index 5 to 9 is : "<<result;
  return 0;  
}