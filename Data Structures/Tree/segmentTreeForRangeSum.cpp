#include<iostream>
#include<math.h>

using namespace std;

//si is the index of current node in the segment tree
//ss & se are the starting and ending indices of segment segmentTree[si]
//qs and qe are the starting and ending indices of query 

int getMid(int start,int end)
{
  return (start+(end-start)/2);  
}

int getSumUtil(int *segmentTree,int ss,int se,int qs,int qe,int si)
{
  if(qs<=ss && qe>=se) // If segment is part of given range
   return segmentTree[si];
  if(qs>se || qe<ss)//If segment of this node is outside the given range
   return 0;
  //If a part of this segment of this node overlaps within the given range
  int mid=getMid(ss,se);
  return (getSumUtil(segmentTree, ss, mid, qs, qe, si*2 + 1)
         + getSumUtil(segmentTree, mid+1, se, qs, qe,si*2 + 2));
}

int getSum(int *segmentTree,int size,int qs,int qe)
{
  if(qs<0 || qe>size-1 || qs>qe)
  {
    cout<<"\nWrong Input!";
    return -1;  
  }  
  return getSumUtil(segmentTree,0,size-1,qs,qe,0);
}

//index =index of array[] where it needs to be updated
//diff=difference of old and new values of array[index]
void updateValueUtil(int *segmentTree,int ss,int se,int index,int diff,int si)
{
  if(index<ss || index>se) //Base: index is out of range
   return;  
  //If the input index is in the range of this node,then update the value
  //of the node and its children 
  segmentTree[si]+=diff;
  if(se!=ss) //if this node is not leaf
  {
    int mid=getMid(ss,se);
    updateValueUtil(segmentTree, ss, mid, index, diff, si*2 + 1);
    updateValueUtil(segmentTree, mid+1, se, index, diff, si*2 + 2);
  } 
}

void updateValue(int array[],int *segmentTree,int size,int index,int value)
{
  if(index<0 || index>size-1)
  {
    cout<<"Invalid Input!";
    return;  
  }
  int diff=value-array[index];//store the diff between old and new values
  array[index]=value; //update the value in array
  updateValueUtil(segmentTree,0,size-1,index,diff,0);
}

int constructSegmentTreeUtil(int array[],int ss,int se,int *segmentTree,int si)
{
  if(ss==se) //Only one element in array
  {
    segmentTree[si]=array[ss];
    return array[ss];  
  } 
  int mid=getMid(ss,se);
  segmentTree[si] = constructSegmentTreeUtil(array, ss, mid, segmentTree, 2 * si + 1) +
                    constructSegmentTreeUtil(array, mid+1, se, segmentTree, 2 * si + 2);
  return segmentTree[si];                   
}

int* constructSegmentTree(int array[],int size)
{
  int x=(int)(ceil(log2(size)));
  int maxSize=2*(int)pow(2,x)-1; //maximum size of segment tree
  int *segmentTree=new int[maxSize];
  constructSegmentTreeUtil(array,0,size-1,segmentTree,0); 
  return segmentTree;
}

int main()
{
  int array[]={1,5,2,6,8,7};   
  int size=sizeof(array)/sizeof(array[0]);
  int *segmentTree=constructSegmentTree(array,size);

  cout<<"\nSum of numbers [0-2] : "<<getSum(segmentTree, size, 0, 2);

  updateValue(array,segmentTree,size,1,10);//update value at index 1 to 10
  cout<<"\nSum of numbers [1-4] after updating array[1] to 10 : ";
  cout<<getSum(segmentTree, size, 1, 4);

  return 0;
}